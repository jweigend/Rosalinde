/* ------------------------------------------------------------------------
|   Dateiname:      $RCSfile: knde_clnt.c,v $
|   Version:        $Revision: 1 $
|   Erstellt am:    00.00.96
|   Geaendert am:   $Date: 19.11.97 9:36 $
|   Komponente:     Konto
|   Erstellt von:   Christian Stoellinger
|   Geandert von:   $Author: Johannes $
|   Copyright:      Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
|   Bermerkung:     Tabstop = 4
--------------------------------------------------------------------------*/


#ifndef KNTO_PROXY
#error "Clientstub must be compiled with -DKNTO_PROXY"
#endif

#ifndef KNDE_PROXY
#error "Clientstub must be compiled with -DKNDE_PROXY"
#endif

#include "r_knto.h"
#include "sadm.h"
#include "cmgr.h"


static CLIENT* cl = NULL;


/* Allokation und Initialisierung */
knto* knto_new()
{
    rknt * pr;
    rknt r;

    cl = sadm_get_serverhandle(KNTO_SVC);
    Assert(cl);

    rknt_init(&r);

    r.cid = cmgr_get_cid();
    Assert(r.cid);


    pr = knto_new_1(&r, cl);
    Assert(pr);

    return (knto*)pr->oid;
}


void knto_init(knto* k)
{
    rknt r;
    rknt * pr;

    Assert(k);

    cl = sadm_get_serverhandle(KNTO_SVC);
    Assert(cl);

    rknt_init(&r);

    r.oid = (long)k;
    r.cid = cmgr_get_cid();
    Assert(r.cid);

    pr = knto_init_1(&r, cl);
    Assert(pr && (pr->rc == OK));

    xdr_free((xdrproc_t) xdr_rknt, (char *) pr);
}


void knto_clear(knto * k)
{
    rknt r;
    rknt * pr;

    Assert(k);

    cl = sadm_get_serverhandle(KNTO_SVC);
    Assert(cl);

    rknt_init(&r);

    r.oid = (long)k;
    r.cid = cmgr_get_cid();
    Assert(r.cid);

    pr = knto_clear_1(&r, cl);
    Assert(pr && (pr->rc == OK));

    xdr_free((xdrproc_t) xdr_rknt, (char *) pr);
}


knto* knto_delete(knto* k)
{
    rknt r;
    rknt * pr;

    Assert(k);

    cl = sadm_get_serverhandle(KNTO_SVC);
    Assert(cl);

    rknt_init(&r);

    r.oid = (long)k;
    r.cid = cmgr_get_cid();
    Assert(r.cid);

    pr = knto_delete_1(&r, cl);
    Assert(pr && (pr->rc == OK));

    xdr_free((xdrproc_t) xdr_rknt, (char *) pr);
    return NULL;
}


/* Get/Set */

void knto_set_kunde(knto* k, knde * ku)
{
    rknt r;
    rknt * pr;

    Assert(k);

    cl = sadm_get_serverhandle(KNTO_SVC);
    Assert(cl);

    rknt_init(&r);
    r.oid  = (long)k;
    r.cid = cmgr_get_cid();
    r.kunde_oid = (long) ku;
    Assert(r.cid);

    pr = knto_set_kunde_1(&r, cl);
    Assert(pr && (pr->rc == OK));

    xdr_free((xdrproc_t) xdr_rknt, (char *) pr);
}


void knto_set_unassigned(knto * k)
{
    rknt r;
    rknt * pr;

    Assert(k);

    cl = sadm_get_serverhandle(KNTO_SVC);
    Assert(cl);

    rknt_init(&r);

    r.oid = (long)k;
    r.cid = cmgr_get_cid();
    Assert(r.cid);

    pr = knto_set_unassigned_1(&r, cl);
    Assert(pr && (pr->rc == OK));

    xdr_free((xdrproc_t) xdr_rknt, (char *) pr);
}


knde * knto_get_kunde(knto* k)
{
    rknt  r;
    rknt* pr;
        long  kunde_oid;

    Assert(k);

    cl = sadm_get_serverhandle(KNTO_SVC);
    Assert(cl);

    rknt_init(&r);

    r.oid = (long)k;
    r.cid = cmgr_get_cid();
    Assert(r.cid);

    pr = knto_get_kunde_1(&r, cl);
    Assert(pr && (pr->rc == OK));

        kunde_oid = pr->kunde_oid;

    xdr_free((xdrproc_t) xdr_rknt, (char *) pr);
    return (knde *) kunde_oid;
}



long knto_get_konto_nummer(knto* k)
{
    rknt  r;
    rknt* pr;
    long  konto_nummer;

    Assert(k);

    cl = sadm_get_serverhandle(KNTO_SVC);
    Assert(cl);

    rknt_init(&r);

    r.oid = (long)k;
    r.cid = cmgr_get_cid();
    Assert(r.cid);

    pr = knto_get_konto_nummer_1(&r, cl);
    Assert(pr && (pr->rc == OK));

    konto_nummer = pr->konto_nummer;

    xdr_free((xdrproc_t) xdr_rknt, (char *) pr);
    return konto_nummer;
}


void knto_set_konto_nummer(knto* k, long konto_nr)
{
    rknt r;
    rknt * pr;

    Assert(k);

    cl = sadm_get_serverhandle(KNTO_SVC);
    Assert(cl);

    rknt_init(&r);
    r.oid  = (long)k;
    r.cid = cmgr_get_cid();
    r.konto_nummer = konto_nr;
    Assert(r.cid);

    pr = knto_set_konto_nummer_1(&r, cl);
    Assert(pr && (pr->rc == OK));

    xdr_free((xdrproc_t) xdr_rknt, (char *) pr);
}


void knto_set_blz(knto* k, long blz)
{
    rknt r;
    rknt * pr;

    Assert(k);

    cl = sadm_get_serverhandle(KNTO_SVC);
    Assert(cl);

    rknt_init(&r);
    r.oid  = (long)k;
    r.cid = cmgr_get_cid();
    r.blz = blz;
    Assert(r.cid);

    pr = knto_set_blz_1(&r, cl);
    Assert(pr && (pr->rc == OK));

    xdr_free((xdrproc_t) xdr_rknt, (char *) pr);
}


long knto_get_blz(knto* k)
{
    rknt  r;
    rknt* pr;
    long  blz;

    Assert(k);

    cl = sadm_get_serverhandle(KNTO_SVC);
    Assert(cl);

    rknt_init(&r);

    r.oid = (long)k;
    r.cid = cmgr_get_cid();
    Assert(r.cid);

    pr = knto_get_blz_1(&r, cl);
    Assert(pr && (pr->rc == OK));

    blz = pr->blz;

    xdr_free((xdrproc_t) xdr_rknt, (char *) pr);
    return blz;
}


void knto_set_bankname(knto* k, strg* bankname)
{
    rknt r;
    rknt * pr;

    Assert(k && bankname);

    cl = sadm_get_serverhandle(KNTO_SVC);
    Assert(cl);

    rknt_init(&r);
    r.oid  = (long)k;
    r.cid = cmgr_get_cid();
    r.bankname = strg_out(bankname);
    Assert(r.bankname && r.cid);

    pr = knto_set_bankname_1(&r, cl);
    Assert(pr && (pr->rc == OK));

    xdr_free((xdrproc_t) xdr_rknt, (char *) pr);
}


strg* knto_get_bankname(knto* k)
{
    rknt r;
    rknt * pr;
    strg * s;

    Assert(k);

    cl = sadm_get_serverhandle(KNTO_SVC);
    Assert(cl);

    rknt_init(&r);

    r.oid = (long)k;
    r.cid = cmgr_get_cid();
    Assert(r.cid);

    pr = knto_get_bankname_1(&r, cl);
    Assert(pr && (pr->rc == OK));

    s = strg_new(MAX_BANKNAME); /* Wer gibt das wieder frei ? */
    strg_in(s, pr->bankname);

    xdr_free((xdrproc_t) xdr_rknt, (char *) pr);
    return s;
}



void knto_set_betrag(knto* k, double betrag)
{
    rknt r;
    rknt * pr;

    Assert(k);

    cl = sadm_get_serverhandle(KNTO_SVC);
    Assert(cl);

    rknt_init(&r);
    r.oid  = (long)k;
    r.cid = cmgr_get_cid();
    r.betrag = betrag;
    Assert(r.cid);

    pr = knto_set_betrag_1(&r, cl);
    Assert(pr && (pr->rc == OK));

    xdr_free((xdrproc_t) xdr_rknt, (char *) pr);
}


double knto_get_betrag(knto* k)
{
    rknt  r;
    rknt* pr;
    long  betrag;

    Assert(k);

    cl = sadm_get_serverhandle(KNTO_SVC);
    Assert(cl);

    rknt_init(&r);

    r.oid = (long)k;
    r.cid = cmgr_get_cid();
    Assert(r.cid);

    pr = knto_get_betrag_1(&r, cl);
    Assert(pr && (pr->rc == OK));

    betrag = pr->betrag;

    xdr_free((xdrproc_t) xdr_rknt, (char *) pr);
    return betrag;
}


long knto_get_rid(knto* k)
{
    rknt  r;
    rknt* pr;
    long  rid;

    Assert(k);

    cl = sadm_get_serverhandle(KNTO_SVC);
    Assert(cl);

    rknt_init(&r);

    r.oid = (long)k;
    r.cid = cmgr_get_cid();
    Assert(r.cid);

    pr = knto_get_rid_1(&r, cl);
    Assert(pr && (pr->rc == OK));

    rid = pr->konto_id;

    xdr_free((xdrproc_t) xdr_rknt, (char *) pr);
    return rid;
}


void knto_register(knto* k, OID* oid)

{
    rknt r;
    rknt * pr;

    Assert (k);

    cl = sadm_get_serverhandle (KNTO_SVC);
    Assert (cl);

    rknt_init (&r);
    r.oid = (long)  k;
    r.cid = cmgr_get_cid ();
    Assert (r.cid);

    pr = knto_register_1 (&r, cl);
    Assert (pr && (pr->rc == OK));

    *oid = pr->oid;

    xdr_free ((xdrproc_t) xdr_rknt, (char *) pr);
}


void knto_unregister(knto* k)
{
    rknt r;
    rknt * pr;

    Assert (k);

    cl = sadm_get_serverhandle (KNTO_SVC);
    Assert (cl);

    rknt_init (&r);
    r.oid = (long)  k;
    r.cid = cmgr_get_cid ();
    Assert (r.cid);

    pr = knto_unregister_1 (&r, cl);
    Assert (pr && (pr->rc == OK));

    xdr_free ((xdrproc_t) xdr_rknt, (char *) pr);
}



/* Aktionen */
void knto_einzahlen(knto* k, double betrag)
{
}


void knto_auszahlen(knto* k, double betrag)
{
}



/* Drucken */
void knto_print(knto * k)
{
    Assert (k);
    LOG ("Konto::KontoNr: %ld, BLZ: %ld, Bank: %s\n",   knto_get_konto_nummer(k),
                                                        knto_get_blz(k),
                                                        strg_out(knto_get_bankname(k)) );
}


/* DB */
knto * knto_find_by_key (long key, RC * rc)
{
    knto *  k;
    rknt r;
    rknt * pr;

    Assert (rc && (key >= 0));

    cl = sadm_get_serverhandle (KNTO_SVC);
    Assert (cl);

    rknt_init (&r);
    r.rid = key;
    r.cid = cmgr_get_cid ();
    Assert (r.cid);

    pr = knto_find_by_key_1 (&r, cl);
    Assert (pr);

    *rc = pr->rc;

    if (*rc == OK)
    {
        return (knto *) pr->oid;
    }

    return NULL;
}


list* knto_find_by_kunde(knde * k, long kunde_rid, RC* rc)
{
    rknt   r;
    rknt * pr;
    list * l;
    long * ko;
    int i;

    Assert (k);

    cl = sadm_get_serverhandle (KNTO_SVC);
    Assert (cl);

    rknt_init (&r);
 
    r.oid = (long) k;
    r.cid = cmgr_get_cid ();
    Assert (r.cid);
    r.kunde_oid = (long) k;   
    r.kunde_rid = kunde_rid; 

    pr = knto_find_by_kunde_1 (&r, cl);
    Assert (pr && (pr->rc == OK));

    l = list_new ();
    Assert (l);

    for (i = 0; i < pr->list_of_knto.list_of_knto_len; i++) {
        ko = (long *) pr->list_of_knto.list_of_knto_val [i];
        list_append (l, ko);
    }

    xdr_free ((xdrproc_t) xdr_rknt, (char *) pr);
    
    return l;
}


list * knto_find_unassigned ()
{
    rknt   r;
    rknt * pr;
    list * l;
    long * ko;
    int i;

    cl = sadm_get_serverhandle (KNTO_SVC);
    Assert (cl);

    rknt_init (&r);
 
    r.cid = cmgr_get_cid ();
    Assert (r.cid);

    pr = knto_find_unassigned_1 (&r, cl);
    Assert (pr && (pr->rc == OK));

    l = list_new ();
    Assert (l);

    for (i = 0; i < pr->list_of_knto.list_of_knto_len; i++) {
        ko = (long *) pr->list_of_knto.list_of_knto_val [i];
        list_append (l, ko);
    }

    xdr_free ((xdrproc_t) xdr_rknt, (char *) pr);
    
    return l;

}

