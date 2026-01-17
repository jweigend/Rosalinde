/* ------------------------------------------------------------------------
|   Dateiname:      $RCSfile: knde.c,v $
|   Version:        $Revision: 1 $
|   Erstellt am:    00.00.96
|   Geaendert am:   $Date: 19.11.97 9:36 $
|   Komponente:     GLOB
|   Erstellt von:   Johannes Weigend
|   Geandert von:   $Author: Johannes $
|   Copyright:      Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
|   Bermerkung:     Tabstop = 4
--------------------------------------------------------------------------*/

#include "ctab.h"
#include "cmgr.h"
#include "knde.h"
#include "btab.h"
#include "knto.h"
#include "dbms.h"

/* Allokation und Initialisierung */
knde * knde_new () {

    knde * k;

    k = (knde *) malloc (sizeof (knde));
    Assert (k);

    knde_init (k);

    return k;
}


void   knde_init (knde * k) {

    Assert (k);

    pkrn_init (&(k->persistent));
    anrd_init (&(k->anrede));
    strg_init (&(k->name),      MAX_KUNDENNAME);
    strg_init (&(k->vorname),   MAX_KUNDENNAME);
    adrs_init (&(k->adresse));
    list_init (&(k->konten));
}


void    knde_clear (knde * k) {

    Assert (k);

    pkrn_clear (&(k->persistent));
    anrd_clear (&(k->anrede));
    strg_clear (&(k->name));
    strg_clear (&(k->vorname));
    adrs_clear (&(k->adresse));
    list_clear (&(k->konten));
}


knde * knde_delete (knde * k) {

    Assert (k);

    knde_clear (k);
    free (k);
    return NULL;
}

    /* set... und get... Methoden */
void   knde_set_name  (knde * k, strg * name) {

    Assert (k && name);
    strg_copy (&(k->name), name);

    pkrn_modify (&(k->persistent));
}

void   knde_set_vorname  (knde * k, strg * vorname) {

    Assert (k && vorname);
    strg_copy (&(k->vorname), vorname);

    pkrn_modify (&(k->persistent));
}

void   knde_set_anrd (knde * k, anrd * a) {

    Assert (k && a);

    k->anrede = *a;

    pkrn_modify (&(k->persistent));
}

void   knde_set_adrs (knde * k, adrs * a) {

    Assert (k && a);

    adrs_copy (&k->adresse, a);

    pkrn_modify (&(k->persistent));
}

void   knde_set_konten (knde * k, list * kl) {

    void * konto;

    Assert (k && kl);

        /* shallow copy */
    while (konto = list_getnext (kl)) {
        list_append (&k->konten, konto);
    }
    pkrn_modify (&(k->persistent));
}


strg * knde_get_name (knde * k) {

    Assert (k);
    return &(k->name);
}

strg * knde_get_vorname  (knde * k) {

    Assert (k);
    return &(k->vorname);
}

anrd * knde_get_anrede (knde * k) {

    Assert (k);
    return (&k->anrede);
}

adrs * knde_get_adresse (knde * k) {

    Assert (k);
    return (&k->adresse);
}

list * knde_get_konten (knde * k) {

    list * l;
    RC rc;

    Assert (k);

    /* TODO Liste auf Zeiger umstellen (list *) um dauerndes Suchen zu vermeiden */

    if (list_not_empty (&k->konten)) return &k->konten;


    /* Kontenliste aufbauen wenn nicht schon vorhanden */

#ifndef KNTO_PROXY
    l = knto_find_by_kunde (k, pkrn_get_rid (&k->persistent), &rc); /* LOCAL */
#else
    l = knto_find_by_kunde ((knde *) pkrn_get_oid (&k->persistent), 
                                     pkrn_get_rid (&k->persistent), &rc);
    /* CHECK: Funktioniert nur bei persistenten KUNDEN TODO ... */
#endif 
 
    Assert (l);

    knde_set_konten (k, l);

    list_delete (l); /* Nur Liste (nicht Objekte) loeschen */

    return (&k->konten);
}

long   knde_get_rid (knde * k) {

   Assert (k);
   return pkrn_get_rid (&k->persistent);
}


    /* Drucken */
void knde_print (knde * k) {

    Assert (k);

    LOG ("Kunde:\n");
    anrd_print (&(k->anrede));
    strg_print (&(k->name));
    strg_print (&(k->vorname));
    adrs_print (&(k->adresse));
    /*list_print (&(k->konten), knto_print); */
    pkrn_print (&(k->persistent));
    LOG ("--------\n");
}


void  knde_insert (void * k, long * sk) {

    strg db_string;

    Assert (k && sk);

    strg_init (&db_string, 0);

    knde_db_out (k, &db_string);

    btab_append (dbms_get_btab (KNDE_BTAB_SVC), strg_out (&db_string), sk);

    strg_clear (&db_string);
}


void knde_reread (void * k, long sk) {

    char buffer [KNDE_DB_RECORDLENGTH + 1] = {0};
    strg db_string;
    RC rc;

    Assert (k && sk);

    strg_init (&db_string, 0);

    rc = btab_get_at (dbms_get_btab (KNDE_BTAB_SVC), sk, buffer);
    Assert (rc == OK);

    strg_in (&db_string, buffer);

    knde_db_in (k, &db_string);

    strg_clear (&db_string);
}


void  knde_update (void * k, long sk) {

    strg db_string;
    RC rc;
    knde dbk;

    Assert (k && (sk >= 0));

    strg_init (&db_string, 0);
    knde_init (&dbk);

    knde_reread (&dbk, sk);

    if (dbk.persistent.change_cnt > ((knde *) k)->persistent.change_cnt) {
        /* ein anderer Client hat den Eintrag schon veraendert */

        strg_clear (&db_string);
        knde_clear (&dbk);
        throw (DB_CHANGED);
    }

    /* Hier ist alles OK ... UPDATE() */

/*  TODO: Lock btab  ... */
    ((knde *) k)->persistent.change_cnt ++;

    knde_db_out (k, &db_string);

    btab_put_at (dbms_get_btab (KNDE_BTAB_SVC), strg_out (&db_string));
/*  TODO: Unlock btab ... */

    strg_clear (&db_string);
    knde_clear (&dbk);
}


void knde_db_out (knde * k, strg * dbstr) {

    Assert (k && dbstr);

    pkrn_db_out (&(k->persistent), dbstr);
    anrd_db_out (&(k->anrede), dbstr);
    strg_db_out (&(k->name), dbstr);
    strg_db_out (&(k->vorname), dbstr);
    adrs_db_out (&(k->adresse), dbstr);

    /* Liste der Konten wird seperat behandelt */
}


void knde_db_in (knde * k, strg * dbstr) {

    Assert (k && dbstr);

    pkrn_db_in (&(k->persistent), dbstr);
    anrd_db_in (&(k->anrede), dbstr);
    strg_db_in (&(k->name), dbstr);
    strg_db_in (&(k->vorname), dbstr);
    adrs_db_in (&(k->adresse), dbstr);

    /* Liste der Konten wird seperate behandelt */
}


    /* suchen ueber rid */
knde * knde_find_by_key (long key, RC * rc) {

    knde * k    = NULL;
    oent * o    = NULL;
    strg * dbs  = NULL;
    pkrn * pk   = NULL;
    otab * ot   = NULL;
    cent * ce;
    long oid;

    char record [KNDE_DB_RECORDLENGTH + 1] = "";


    Assert ((key >= 0) && rc);

        /* Zuerst richtige OTAB holen */
    ce = ctab_get (cmgr_get_cid());

       /* OK hier gibt es eine OTAB */
    if (ce) {

        ot = cent_get_otab (ce);
        Assert (ot);

        /* Dann in der OTAB suchen */

        *rc = otab_find_by_rid (ot, key, &o);
        if (*rc == OK) {

            pk = oent_get_pkrn (o);
            Assert (pk);

            return (pk->owner);

        }
    }

        /* Jetzt aus der DB lesen */


    *rc = btab_get_at (dbms_get_btab (KNDE_BTAB_SVC), key, record);
    if (*rc != OK) return NULL;

    dbs = strg_new (KNDE_DB_RECORDLENGTH);
    Assert (dbs);

    strg_in (dbs, record);

        /* Wenn in DB gefunden muss neuer Kunde angelegt werden. */

    k = knde_new ();
    Assert (k);

    knde_db_in (k, dbs);

    k->persistent.state = os_clean;

    knde_register (k, &oid);

    strg_delete (dbs);

    *rc = OK;

    return k;
}


    /* Make persistent */
void knde_register (knde * k, long * oid) {

    Assert (k);

    LOG ("cid = %s", cmgr_get_cid ());
    ctab_register (cmgr_get_cid(), oid, &k->persistent, k, knde_update, knde_insert, knde_reread);
    ctab_print ();
}


void knde_unregister (knde * k) {

    Assert (k);

    if (pkrn_get_oid (&k->persistent) == 0) return;

    ctab_unregister (cmgr_get_cid(), pkrn_get_oid (&k->persistent));
    ctab_print ();
}


void   knde_set_anrede (knde * k, anrd * a) {

    Assert (k && a);
    k->anrede = *a;
}


void   knde_set_adresse (knde * k, adrs * a) {

    Assert (k && a);
    adrs_copy (&k->adresse, a);
}


BOOL
knde_is_persistent (knde * k) 
{
    Assert (k);
    return pkrn_get_oid (&k->persistent) == 0 ? FALSE : TRUE;
}
