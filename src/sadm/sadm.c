/* ------------------------------------------------------------------------
|   Dateiname:      $RCSfile: sadm.c,v $
|   Version:        $Revision: 1 $
|   Erstellt am:    00.00.96
|   Geaendert am:   $Date: 19.11.97 9:36 $
|   Komponente:     SERVER-ADMINISTRATOR
|   Erstellt von:   Johannes Weigend
|   Geandert von:   $Author: Johannes $
|   Copyright:      Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
|   Bermerkung:     Tabstop = 4
---------------------------------------------------------------------------*/

#include "sadm.h"
#include "brok.h"

#ifdef LOCAL
#include "local.h"
#else
#include "r_brok.h"
#endif

static sadm derServerAdministrator;     /* Singleton-Object */


/* private: */
static void sadm_append (sent * s);

static struct timeval PING_TIMEOUT  = { 240, 0 };
static struct timeval BROK_TIMEOUT  = { 240, 0 };
static struct timeval SERV_TIMEOUT  = { 240, 0 };


     /* Benoetigt fuer rebind ... */
char * sadm_get_broker () {
    return derServerAdministrator.brokerhost;
}


    /* OK == success, NOK == error */
RC sadm_ping_server (CLIENT * cl) {

    Assert (cl);

        /* ping nullproc */
    if (clnt_call(cl, 0, (xdrproc_t) xdr_void, 0, (xdrproc_t) xdr_void, 0, PING_TIMEOUT) != RPC_SUCCESS){
        LOG ("[SADM]: ping failed !");
        return NOK;
    }
    return OK;
}


   /* OK == success, NOK == error */
RC sadm_ping (char * host, long prognr, long versnr, char * proto) {

    CLIENT * cl;
    RC rc;

    Assert (host && prognr && versnr && proto);
 
    cl = clnt_create (host, prognr, versnr, proto);
    if (! cl) {
        LOG ("[SADM]: ping failed !");
        return NOK;
    }
    rc = sadm_ping_server (cl);

    clnt_destroy (cl);

    return rc;
}


void sadm_init (char * brokerhost) {

    hash_init (&(derServerAdministrator.cltab), SADM_HASH_TAB_SIZE);

    strcpy (derServerAdministrator.brokerhost, brokerhost);

    derServerAdministrator.brokerhandle = NULL;
}


void sadm_clear () {

    hash_clear (&(derServerAdministrator.cltab), TRUE);
}


    /* druckt alle Serveradmin-entrys aus */
void sadm_print () {

    hash_print (&(derServerAdministrator.cltab), sent_print);
}


CLIENT * sadm_get_brokerhandle () {

    bool_t success;

    if (! derServerAdministrator.brokerhandle) {

        Assert (derServerAdministrator.brokerhost);

        derServerAdministrator.brokerhandle =
                clnt_create (derServerAdministrator.brokerhost, R_BROK, R_BROK_VERSION, R_BROK_PROTO);

        Assert (derServerAdministrator.brokerhandle);

        derServerAdministrator.brokerhandle->cl_auth = authunix_create_default();

        success = clnt_control (derServerAdministrator.brokerhandle, CLSET_TIMEOUT, (char *) &BROK_TIMEOUT);
        Assert (success);
    }

    return derServerAdministrator.brokerhandle;
}


CLIENT * sadm_get_serverhandle (char * svcn) {

    bent    b;
    sent    s;
    sent * ps;
    RC rc;
    CLIENT * cl;
    bool_t success;

    Assert (svcn);


        /* Suche in der Tabelle ob svc schon vorhanden */

    sent_init (&s);

    sent_set_svcn (&s, svcn);

    ps = hash_get (&(derServerAdministrator.cltab), (void *) &s, sent_hash_fnk, sent_cmp);
    if (ps) {

        cl = sent_get_client (ps);
        Assert (cl);

        if (sadm_ping_server (cl) == OK) {
                /* Gefunden und raus */
            return cl;
        }
        /* Fehler beim Ping ist aufgetreten also ist der
           Eintrag ungueltig und wird entfernt */
        sadm_remove (svcn);
    }

        /* Frage den Broker nach dem gueltigen SVC-Host */
    bent_init (&b);

    rc = brok_bind (svcn, &b);

    if (rc != OK) {
        fprintf(stderr, "[SADM]: brok_bind failed for svc='%s' (rc=%d), broker='%s'\n",
                svcn, (int) rc, derServerAdministrator.brokerhost);
        return NULL;
    }

        /* Der Broker hat einen Eintrag zurueckgegeben ... */

    cl = clnt_create (bent_get_host (&b),
        bent_get_prgnr (&b), bent_get_versnr (&b), bent_get_proto (&b));
    if (! cl) {
        /* Provide clearer diagnostics when client creation fails */
        fprintf(stderr, "[SADM]: clnt_create failed for host=%s prog=%ld ver=%ld proto=%s\n",
                bent_get_host(&b), (long) bent_get_prgnr(&b), (long) bent_get_versnr(&b), bent_get_proto(&b));
        clnt_pcreateerror("sadm_get_serverhandle");
        return NULL;
    }

    if (sadm_ping_server (cl) != OK) {

        LOG ("[SADM]: fatal: Server &s reagiert nicht\n", bent_get_host (&b));
        Assert (FALSE);
    }

    sent_set_client (&s, cl);

    /* den Clienthost in die Uebergabestruktur eintragen */
    cl->cl_auth = authunix_create_default ();

    /* den Timeout auf SERV_TIMEOUT setzen */
    success = clnt_control (cl, CLSET_TIMEOUT, (char *) &SERV_TIMEOUT);
    Assert (success);

    /* Eintrag in die Hashtabelle einfuegen */
    sadm_append (&s);

    return cl;
}


void sadm_append (sent * s) {

    sent * ps;

    Assert (s);

    ps = sent_new ();
    Assert (ps);

    sent_copy (s, ps);

    hash_insert (&(derServerAdministrator.cltab), ps, sent_hash_fnk);

    return;
}


void sadm_remove (char * svcn) {

    sent s;
    sent * removedEntry;

    Assert (svcn);

    sent_set_svcn (&s, svcn);

    removedEntry = hash_remove (&(derServerAdministrator.cltab), (void *) &s, sent_hash_fnk, sent_cmp);

    if (! removedEntry) {
        LOG ("[SADM]: cant find entry to remove.\n");
        return;
    }

#ifdef RPC
    auth_destroy (removedEntry->cl->cl_auth);
    clnt_destroy (removedEntry->cl);
#endif

    if (removedEntry) free (removedEntry);

    return;
}

