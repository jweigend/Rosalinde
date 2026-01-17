/* ------------------------------------------------------------------------
|   Dateiname:      $RCSfile: knde_clnt.c,v $
|   Version:        $Revision: 1 $
|   Erstellt am:    00.00.96
|   Geaendert am:   $Date: 19.11.97 9:36 $
|   Komponente:     GLOB
|   Erstellt von:   Johannes Weigend
|   Geandert von:   $Author: Johannes $
|   Copyright:      Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
|   Bermerkung:     Tabstop = 4
--------------------------------------------------------------------------*/

#ifndef KNDE_PROXY
#pragma message("Clientstub must be compiled with -DKNDE_PROXY")
#endif

#ifndef KNTO_PROXY
#pragma message("Clientstub must be compiled with -DKNTO_PROXY")
#endif


#include "r_knde.h"
#include "sadm.h"
#include "cmgr.h"

static CLIENT * cl = NULL;



/* Allokation und Initialisierung */
knde * knde_new () {

    rknd * pr;
    rknd r;

    cl = sadm_get_serverhandle (KNDE_SVC);
    Assert (cl);

    rknd_init (&r);

    r.cid = cmgr_get_cid ();
    Assert (r.cid);

    pr = knde_new_1 (&r, cl);
    Assert (pr);

    return (knde *) pr->oid;
}


void   knde_init (knde * k) {

    rknd r;
    rknd * pr;

    Assert (k);

    cl = sadm_get_serverhandle (KNDE_SVC);
    Assert (cl);

    rknd_init (&r);

    r.oid = (long)  k;
    r.cid = cmgr_get_cid ();
    Assert (r.cid);

    pr = knde_init_1 (&r, cl);
    Assert (pr && (pr->rc == OK));

    xdr_free ((xdrproc_t) xdr_rknd, (char *) pr);
}


void  knde_clear (knde * k) {

    rknd r;
    rknd * pr;

    Assert (k);

    cl = sadm_get_serverhandle (KNDE_SVC);
    Assert (cl);

    rknd_init (&r);

    r.oid = (long) k;
    r.cid = cmgr_get_cid ();
    Assert (r.cid);

    pr = knde_clear_1 (&r, cl);
    Assert (pr && (pr->rc == OK));

    xdr_free ((xdrproc_t) xdr_rknd, (char *) pr);
}


knde * knde_delete (knde * k) {

    rknd r;
    rknd * pr;

    Assert (k);

    cl = sadm_get_serverhandle (KNDE_SVC);
    Assert (cl);

    rknd_init (&r);

    r.oid = (long) k;
    r.cid = cmgr_get_cid ();
    Assert (r.cid);

    pr = knde_delete_1 (&r, cl);
    Assert (pr && (pr->rc == OK));

    xdr_free ((xdrproc_t) xdr_rknd, (char *) pr);

    return NULL;
}


    /* set... und get... Methoden */
void   knde_set_name  (knde * k, strg * name) {

    rknd r;
    rknd * pr;

    Assert (k && name);

    cl = sadm_get_serverhandle (KNDE_SVC);
    Assert (cl);

    rknd_init (&r);

    r.oid  = (long) k;
    r.cid = cmgr_get_cid ();
    r.name = strg_out (name);
    Assert (r.name && r.cid);

    pr = knde_set_name_1 (&r, cl);
    Assert (pr && (pr->rc == OK));

    xdr_free ((xdrproc_t) xdr_rknd, (char *) pr);

}

void   knde_set_vorname  (knde * k, strg * vorname) {

    rknd r;
    rknd * pr;

    Assert (k && vorname);

    cl = sadm_get_serverhandle (KNDE_SVC);
    Assert (cl);

    rknd_init (&r);

    r.oid = (long) k;
    r.cid = cmgr_get_cid ();
    r.vorname = strg_out (vorname);
    Assert (r.cid && r.vorname);

    pr = knde_set_vorname_1 (&r, cl);
    Assert (pr && (pr->rc == OK));

    xdr_free ((xdrproc_t) xdr_rknd, (char *) pr);
}

void   knde_set_anrede  (knde * k, anrd * a) {

    rknd r;
    rknd * pr;

    Assert (k && a);

    cl = sadm_get_serverhandle (KNDE_SVC);
    Assert (cl);

    rknd_init (&r);

    r.oid = (long) k;
    r.cid = cmgr_get_cid ();
    r.anrede = anrd_out (a, LANG);
    Assert (r.cid && r.anrede);

    pr = knde_set_anrede_1 (&r, cl);
    Assert (pr && (pr->rc == OK));

    xdr_free ((xdrproc_t) xdr_rknd, (char *) pr);
}

void   knde_set_adresse  (knde * k, adrs * adresse) {

    rknd r;
    rknd * pr;

    Assert (k && adresse);

    cl = sadm_get_serverhandle (KNDE_SVC);
    Assert (cl);

    rknd_init (&r);

    r.oid = (long) k;
    r.cid = cmgr_get_cid ();

    r.adresse.strasse = adrs_get_strasse (adresse);
    r.adresse.hausnr  = adrs_get_hausnr  (adresse);
    r.adresse.plz     = adrs_get_plz       (adresse);
    r.adresse.ort     = adrs_get_ort     (adresse);
    r.adresse.land    = adrs_get_land    (adresse);

    Assert (r.cid);

    pr = knde_set_adresse_1 (&r, cl);
    Assert (pr && (pr->rc == OK));

    xdr_free ((xdrproc_t) xdr_rknd, (char *) pr);
}

strg * knde_get_name (knde * k) {

    rknd r;
    rknd * pr;
    strg * s;

    Assert (k);

    cl = sadm_get_serverhandle (KNDE_SVC);
    Assert (cl);

    rknd_init (&r);

    r.oid = (long) k;
    r.cid = cmgr_get_cid ();
    Assert (r.cid);

    pr = knde_get_name_1 (&r, cl);
    Assert (pr && (pr->rc == OK));

    s = strg_new (MAX_KUNDENNAME); /* Wer gibt das wieder frei ? */
    strg_in (s, pr->name);

    xdr_free ((xdrproc_t) xdr_rknd, (char *) pr);
    return s;
}


strg * knde_get_vorname  (knde * k) {

    rknd r;
    rknd * pr;
    strg * s;

    Assert (k);

    cl = sadm_get_serverhandle (KNDE_SVC);
    Assert (cl);

    rknd_init (&r);

    r.oid = (long) k;
    r.cid = cmgr_get_cid ();
    Assert (r.cid);

    pr = knde_get_vorname_1 (&r, cl);
    Assert (pr && (pr->rc == OK));

    s = strg_new (MAX_KUNDENNAME);
    strg_in (s, pr->vorname);

    xdr_free ((xdrproc_t) xdr_rknd, (char *) pr);
    return s;
}


adrs * knde_get_adresse  (knde * k) {

    rknd r;
    rknd * pr;
    adrs * a;

    Assert (k);

    cl = sadm_get_serverhandle (KNDE_SVC);
    Assert (cl);

    rknd_init (&r);

    r.oid = (long) k;
    r.cid = cmgr_get_cid ();
    Assert (r.cid);

    pr = knde_get_adresse_1 (&r, cl);
    Assert (pr && (pr->rc == OK));

    a = adrs_new ();
    adrs_in (a, pr->adresse.strasse, pr->adresse.hausnr, pr->adresse.plz, pr->adresse.ort, pr->adresse.land);

    xdr_free ((xdrproc_t) xdr_rknd, (char *) pr);
    return a;
}


long knde_get_rid  (knde * k) {

    rknd r;
    rknd * pr;
    long rid;

    Assert (k);

    cl = sadm_get_serverhandle (KNDE_SVC);
    Assert (cl);

    rknd_init (&r);

    r.oid = (long) k;
    r.cid = cmgr_get_cid ();
    Assert (r.cid);

    pr = knde_get_rid_1 (&r, cl);
    Assert (pr && (pr->rc == OK));

    rid = pr->rid;

    xdr_free ((xdrproc_t) xdr_rknd, (char *) pr);
    return rid;
}


anrd * knde_get_anrede  (knde * k) {

    rknd r;
    rknd * pr;
    anrd * a;
    RC rc;

    Assert (k);

    cl = sadm_get_serverhandle (KNDE_SVC);
    Assert (cl);

    rknd_init (&r);

    r.oid = (long) k;
    r.cid = cmgr_get_cid ();
    Assert (r.cid);

    pr = knde_get_anrede_1 (&r, cl);
    Assert (pr && (pr->rc == OK));

    a = anrd_new ();
    anrd_in (a, &rc, LANG, pr->anrede);

    xdr_free ((xdrproc_t) xdr_rknd, (char *) pr);
    return a;
}


    /* Drucken */
void knde_print (knde * k) {

    Assert (k);

    anrd_print (knde_get_anrede (k));

    LOG ("Name: %s, Vorname: %s\n", strg_out(knde_get_name (k)),
                                           strg_out(knde_get_vorname (k)));
    adrs_print (knde_get_adresse (k));
}



knde * knde_find_by_key (long key, RC * rc) {

    rknd r;
    rknd * pr;

    Assert (rc && (key >= 0));

    cl = sadm_get_serverhandle (KNDE_SVC);
    Assert (cl);

    rknd_init (&r);

    r.rid = key;
    r.cid = cmgr_get_cid ();
    Assert (r.cid);

    pr = knde_find_by_key_1 (&r, cl);
    Assert (pr);

    *rc = pr->rc;

    if (*rc == OK) {

        return (knde *) pr->oid;
    }
    return NULL;
}

void   knde_register (knde * k, OID * oid) {

    rknd r;
    rknd * pr;

    Assert (k);

    cl = sadm_get_serverhandle (KNDE_SVC);
    Assert (cl);

    rknd_init (&r);

    r.oid = (long)  k;
    r.cid = cmgr_get_cid ();
    Assert (r.cid);

    pr = knde_register_1 (&r, cl);
    Assert (pr && (pr->rc == OK));

    *oid = pr->oid;

    xdr_free ((xdrproc_t) xdr_rknd, (char *) pr);
}


void   knde_unregister (knde * k) {

    rknd r;
    rknd * pr;

    Assert (k);

    cl = sadm_get_serverhandle (KNDE_SVC);
    Assert (cl);

    rknd_init (&r);

    r.oid = (long)  k;
    r.cid = cmgr_get_cid ();
    Assert (r.cid);

    pr = knde_unregister_1 (&r, cl);
    Assert (pr && (pr->rc == OK));

    xdr_free ((xdrproc_t) xdr_rknd, (char *) pr);
}

list * knde_get_konten (knde * k) {

    rknd r;
    rknd * pr;
    list * l;
    long * ko;
    int i;

    Assert (k);

    cl = sadm_get_serverhandle (KNDE_SVC);
    Assert (cl);

    rknd_init (&r);
 
    r.oid = (long) k;
    r.cid = cmgr_get_cid ();
    Assert (r.cid);

    pr = knde_get_konten_1 (&r, cl);
    Assert (pr && (pr->rc == OK));

    l = list_new ();
    Assert (l);

    for (i = 0; i < pr->list_of_konten.list_of_konten_len; i++) {
        ko = (long *) pr->list_of_konten.list_of_konten_val [i];
        list_append (l, ko);
    }


    xdr_free ((xdrproc_t) xdr_rknd, (char *) pr);

    return l;
}

