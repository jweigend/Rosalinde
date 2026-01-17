/* ------------------------------------------------------------------------
|   Dateiname:      $RCSfile: brok_clnt.c,v $
|   Version:        $Revision: 1 $
|   Erstellt am:    00.00.96
|   Geaendert am:   $Date: 19.11.97 9:36 $
|   Komponente:     BROKER RPC Client Stubs
|   Erstellt von:   Johannes Weigend
|   Geandert von:   $Author: Johannes $
|   Copyright:      Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
|   Bermerkung:     Tabstop = 4
---------------------------------------------------------------------------*/

#include "brok.h"
#include "sadm.h"
#include "r_brok.h"



/*  haengt einen broker-entry Eintrag an die Brokerlist an
    RC: OK                   wenn alles klappt
        DUPLICATE_SVC_ENTRY  fuer doppelte Registrierung */
RC brok_register (bent * be) {

    int * result;
    r_bent r;

    r.svcn = be->svcn;
    r.host = be->host;
    r.prgnr= be->prgnr;
    r.versnr = be->versnr;
    r.proto = be->proto;

    result = brok_register_1(&r, sadm_get_brokerhandle ());
    Assert (result);

    return *result;
}


/*  deregistriert einen Service:
    RC: OK
        SVC_NOT_REGISTERED  fuer nicht gefundene Servicenamen */
RC brok_unregister (char * svcn) {

    int * result;

    Assert (sadm_get_brokerhandle ());
    Assert (svcn);

    result = brok_unregister_1(&svcn, sadm_get_brokerhandle ());
    Assert (result);

    return *result;
}


/*  Fuellt be mit dem gefunden Eintrag:
    RC: OK
        SVC_NOT_REGISTERED  fuer nicht gefundene Servicenamen */

RC brok_bind (char * svcn, bent * b) {

    r_bent * result;

    Assert (sadm_get_brokerhandle ());
    Assert (svcn && b);

    result = brok_bind_1(&svcn, sadm_get_brokerhandle ());
    Assert (result);

    bent_set_host (b, result->host);
    bent_set_svcn (b, result->svcn);
    bent_set_prgnr(b, result->prgnr);
    bent_set_versnr(b, result->versnr);
    bent_set_proto (b, result->proto);


        /* Bei leerem SVC-Namen wird SVC_NOT... zurueckgegeben */
    if (b->svcn[0] == '\0') return SVC_NOT_REGISTERED;
    return OK;
}

    /* Vergibt eine eindeutige CID */
char * brok_get_cid () {

    static char arg;
    r_cid * result;

    result = brok_get_cid_1 (&arg, sadm_get_brokerhandle ());
    Assert (result && result->cid);

    return result->cid;
}

