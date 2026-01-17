/* ------------------------------------------------------------------------
|   Dateiname:      $RCSfile: r_knto.c,v $
|   Version:        $Revision: 1 $
|   Erstellt am:    00.00.96
|   Geaendert am:   $Date: 19.11.97 9:36 $
|   Komponente:     Konto
|   Erstellt von:   Christian Stoellinger / Johannes Weigend
|   Geandert von:   $Author: Johannes $
|   Copyright:      Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
|   Bermerkung:     Tabstop = 4
---------------------------------------------------------------------------*/

#ifdef KNTO_PROXY
#error "KNTO Serverstub must be compiled with -UKNTO_PROXY"
#endif

#ifndef KNDE_PROXY
#error "KNTO Serverstub must be compiled with -DKNDE_PROXY"
#endif

#include "knto.h"
#include "r_knto.h"
#include "otab.h"
#include "ctab.h"
#include "cmgr.h"


rknt * knto_new_1_svc(rknt *argp, struct svc_req *rqstp)
{
    static rknt  result;
    knto * k;

    Assert (argp && rqstp);

    LOG ("[KNTO_SVC]: knto_new() aufgerufen von %s ... ", argp->cid);

    rknt_init (&result);
    cmgr_set_cid (argp->cid);

    k = knto_new ();
    Assert (k);
   
    LOG ("(OK).\n");
    
    ctab_register (argp->cid, &result.oid, NULL, k, NULL, NULL, NULL);
    ctab_print ();
    result.rc  = OK;
    return (&result);
}


rknt * knto_init_1_svc(rknt *argp, struct svc_req *rqstp)
{
    static rknt  result;
    static knto * k;

    Assert (argp);

    LOG ("[KNTO_SVC]: knto_init() aufgerufen von %s ... ", argp->cid);

    rknt_init (&result);
    cmgr_set_cid (argp->cid);

    k = ctab_get_obj (argp->cid, argp->oid);
    if (!k) {
      result.rc = NOK_PROXY_NOT_FOUND;
      LOG ("(NOK) -> Proxy nicht gefunden.\n");

      return &result;
    }

    knto_init (k);

    LOG ("(OK).\n");
    
    result.rc = OK;
    return (&result);
}


rknt * knto_delete_1_svc(rknt *argp, struct svc_req *rqstp)
{
    static rknt result;
    static knto * k;

    Assert (argp);

    LOG ("[KNTO_SVC]: knto_delete() aufgerufen von %s ... ", argp->cid);

    rknt_init (&result);
    cmgr_set_cid (argp->cid);

    k = ctab_get_obj (argp->cid, argp->oid);
    if (!k) {
      result.rc = NOK_PROXY_NOT_FOUND;
      LOG ("(NOK) -> Proxy nicht gefunden.\n");

      return &result;
    }
    
    if (knto_is_persistent (k)) {
        
        knto_unregister (k);
    }
    else {
        ctab_unregister (argp->cid, argp->oid);
    }

    knto_delete (k);
    LOG ("(OK).\n");

    result.rc = OK;
    return &result;
}


rknt * knto_clear_1_svc(rknt *argp, struct svc_req *rqstp)
{
    static rknt  result;
    static knto * k;

    Assert (argp);

    LOG ("[KNTO_SVC]: knto_clear() aufgerufen von %s ... ", argp->cid);

    rknt_init (&result);
    cmgr_set_cid (argp->cid);

    k = ctab_get_obj (argp->cid, argp->oid);
    if (!k) {
      result.rc = NOK_PROXY_NOT_FOUND;
      LOG ("(NOK) -> Proxy nicht gefunden.\n");

      return &result;
    }

    knto_clear (k);

    LOG ("(OK).\n");

    result.rc = OK;
    return (&result);
}


rknt * knto_set_unassigned_1_svc(rknt *argp, struct svc_req *rqstp)
{
    static rknt  result;
    static knto * k;

    Assert (argp);

    LOG ("[KNTO_SVC]: knto_set_unassigned() aufgerufen von %s ... ", argp->cid);

    rknt_init (&result);
    cmgr_set_cid (argp->cid);

    k = ctab_get_obj (argp->cid, argp->oid);
    if (!k) {
      result.rc = NOK_PROXY_NOT_FOUND;
      LOG ("(NOK) -> Proxy nicht gefunden.\n");

      return &result;
    }

    knto_set_unassigned (k);
    LOG ("(OK).\n");
    
    result.rc = OK;
    return (&result);
}


rknt* knto_set_kunde_1_svc(rknt* argp, struct svc_req* rqstp)
{
    static rknt  result;
    static knto * k;

    Assert (argp);

    LOG ("[KNTO_SVC]: knto_set_kunde() aufgerufen von %s ... ", argp->cid);

    rknt_init (&result);
    cmgr_set_cid (argp->cid);

    k = ctab_get_obj (argp->cid, argp->oid);
    if (!k) {
      result.rc = NOK_PROXY_NOT_FOUND;
      LOG ("(NOK) -> Proxy nicht gefunden.\n");

      return &result;
    }

    /* Dies klappt nur wenn Kundenproxies verwendet werden ... */
    knto_set_kunde (k, (knde *) argp->kunde_oid);

    LOG ("(OK).\n");

    result.rc = OK;
    return (&result);
}

rknt* knto_get_kunde_1_svc(rknt* argp, struct svc_req* rqstp)
{
    static rknt  result;
    static knto * k;

    Assert (argp);

    LOG ("[KNTO_SVC]: knto_get_kunde() aufgerufen von %s ... ", argp->cid);

    rknt_init (&result);
    cmgr_set_cid (argp->cid);

    k = ctab_get_obj (argp->cid, argp->oid);
    if (!k) {
      result.rc = NOK_PROXY_NOT_FOUND;
      LOG ("(NOK) -> Proxy nicht gefunden.\n");

      return &result;
    }
    /* Dies klappt nur wenn Kundenproxies verwendet werden ... */
    result.kunde_oid = (long) knto_get_kunde (k);

    LOG ("(OK).\n");

    result.rc = OK;
    return (&result);
}


rknt* knto_set_konto_nummer_1_svc(rknt* argp, struct svc_req* rqstp)
{
    static rknt  result;
    static knto * k;

    Assert (argp);

    LOG ("[KNTO_SVC]: knto_set_konto_nummer() aufgerufen von %s ... ", argp->cid);

    rknt_init (&result);
    cmgr_set_cid (argp->cid);

    k = ctab_get_obj (argp->cid, argp->oid);
    if (!k) {
      result.rc = NOK_PROXY_NOT_FOUND;
      LOG ("(NOK) -> Proxy nicht gefunden.\n");

      return &result;
    }
    knto_set_konto_nummer(k, argp->konto_nummer);
    LOG ("(OK).\n");
    result.rc = OK;
    return (&result);
}


rknt* knto_get_konto_nummer_1_svc(rknt* argp, struct svc_req* rqstp)
{
    static rknt  result;
    static knto * k;

    Assert (argp);

    LOG ("[KNTO_SVC]: knto_get_konto_nummer() aufgerufen von %s ... ", argp->cid);

    rknt_init (&result);
    cmgr_set_cid (argp->cid);

    k = ctab_get_obj (argp->cid, argp->oid);
    if (!k) {
      result.rc = NOK_PROXY_NOT_FOUND;
      LOG ("(NOK) -> Proxy nicht gefunden.\n");

      return &result;
    }
    result.konto_nummer = knto_get_konto_nummer(k);
    LOG ("(OK).\n");
    result.rc = OK;
    return (&result);
}


rknt* knto_set_blz_1_svc(rknt* argp, struct svc_req* rqstp)
{
    static rknt  result;
    static knto * k;

    Assert (argp);

    LOG ("[KNTO_SVC]: knto_set_blz() aufgerufen von %s ... ", argp->cid);

    rknt_init (&result);
    cmgr_set_cid (argp->cid);

    k = ctab_get_obj (argp->cid, argp->oid);
    if (!k) {
      result.rc = NOK_PROXY_NOT_FOUND;
      LOG ("(NOK) -> Proxy nicht gefunden.\n");

      return &result;
    }

    knto_set_blz(k, argp->blz);
    LOG ("(OK).\n");
    result.rc = OK;
    return (&result);
}


rknt* knto_get_blz_1_svc(rknt* argp, struct svc_req* rqstp)
{
    static rknt  result;
    static knto * k;

    Assert (argp);

    LOG ("[KNTO_SVC]: knto_get_blz() aufgerufen von %s ... ", argp->cid);

    rknt_init (&result);
    cmgr_set_cid (argp->cid);

    k = ctab_get_obj (argp->cid, argp->oid);
    if (!k) {
      result.rc = NOK_PROXY_NOT_FOUND;
      LOG ("(NOK) -> Proxy nicht gefunden.\n");

      return &result;
    }
    result.blz = knto_get_blz(k);
    LOG ("(OK).\n");
    result.rc = OK;
    return (&result);
}


rknt * knto_set_bankname_1_svc(rknt *argp, struct svc_req *rqstp)
{
    static rknt  result;
    static knto * k;
    strg s;

    Assert (argp);

    LOG ("[KNTO_SVC]: knto_set_bankname() aufgerufen von %s ... ", argp->cid);

    rknt_init (&result);
    cmgr_set_cid (argp->cid);

    k = ctab_get_obj (argp->cid, argp->oid);
    if (!k) {
      result.rc = NOK_PROXY_NOT_FOUND;
      LOG ("(NOK) -> Proxy nicht gefunden.\n");

      return &result;
    }
    strg_init (&s, MAX_BANKNAME);
    strg_in (&s, argp->bankname);
    knto_set_bankname(k, &s);
    strg_clear (&s);
    LOG ("(OK).\n");
    result.rc = OK;
    return (&result);
}


rknt * knto_get_bankname_1_svc(rknt *argp, struct svc_req *rqstp)
{
    static rknt  result;
    static knto * k;
    strg * s;

    Assert (argp);

    LOG ("[KNTO_SVC]: knto_get_bankname() aufgerufen von %s ... ", argp->cid);

    rknt_init (&result);
    cmgr_set_cid (argp->cid);

    k = ctab_get_obj (argp->cid, argp->oid);
    if (!k) {
      result.rc = NOK_PROXY_NOT_FOUND;
      LOG ("(NOK) -> Proxy nicht gefunden.\n");

      return &result;
    }
    s = knto_get_bankname (k);
    Assert (s);

    result.bankname = strg_out (s);
    LOG ("(OK).\n");
    result.rc = OK;
    return (&result);
}


rknt* knto_set_betrag_1_svc(rknt* argp, struct svc_req* rqstp)
{
    static rknt  result;
    static knto * k;

    Assert (argp);

    LOG ("[KNTO_SVC]: knto_set_betrag() aufgerufen von %s ... ", argp->cid);

    rknt_init (&result);
    cmgr_set_cid (argp->cid);

    k = ctab_get_obj (argp->cid, argp->oid);
    if (!k) {
      result.rc = NOK_PROXY_NOT_FOUND;
      LOG ("(NOK) -> Proxy nicht gefunden.\n");

      return &result;
    }
    knto_set_betrag(k, argp->betrag);
    LOG ("(OK).\n");
    result.rc = OK;
    return (&result);
}


rknt* knto_get_betrag_1_svc(rknt* argp, struct svc_req* rqstp)
{
    static rknt  result;
    static knto * k;

    Assert (argp);

    LOG ("[KNTO_SVC]: knto_get_betrag() aufgerufen von %s ... ", argp->cid);

    rknt_init (&result);
    cmgr_set_cid (argp->cid);

    k = ctab_get_obj (argp->cid, argp->oid);
    if (!k) {
      result.rc = NOK_PROXY_NOT_FOUND;
      LOG ("(NOK) -> Proxy nicht gefunden.\n");

      return &result;
    }
    result.betrag = knto_get_betrag(k);
    LOG ("(OK).\n");
    result.rc = OK;
    return (&result);
}


rknt* knto_get_rid_1_svc(rknt* argp, struct svc_req* rqstp)
{
    static rknt  result;
    static knto * k;

    Assert (argp);

    LOG ("[KNTO_SVC]: knto_get_rid() aufgerufen von %s ... ", argp->cid);

    rknt_init (&result);
    cmgr_set_cid (argp->cid);

    k = ctab_get_obj (argp->cid, argp->oid);
    if (!k) {
      result.rc = NOK_PROXY_NOT_FOUND;
      LOG ("(NOK) -> Proxy nicht gefunden.\n");

      return &result;
    }
    result.konto_id = knto_get_rid(k);
    LOG ("(OK).\n");
    result.rc = OK;
    return (&result);
}


rknt * knto_find_by_key_1_svc(rknt *argp, struct svc_req *rqstp)
{
    static rknt  result;
    knto * k;
    RC rc;

    Assert (argp);

    LOG ("[KNTO_SVC]: knto_find_by_key() aufgerufen von %s ... ", argp->cid);

    rknt_init (&result);
    cmgr_set_cid (argp->cid);

    k = knto_find_by_key (argp->rid, &rc);

    if (rc != OK) {
        result.rc = rc;
        return &result;
    }
    LOG ("(OK).\n");
    result.oid = pkrn_get_oid (&k->persistent);
    result.rc  = OK;
    return (&result);
}


rknt * knto_register_1_svc(rknt *argp, struct svc_req *rqstp)
{
    static rknt  result;
    static knto * k;

    Assert (argp);

    LOG ("[KNTO_SVC]: knto_register() aufgerufen von %s ... ", argp->cid);

    rknt_init (&result);
    cmgr_set_cid (argp->cid);

    k = ctab_get_obj (argp->cid, argp->oid);
    if (!k) {
      result.rc = NOK_PROXY_NOT_FOUND;
      LOG ("(NOK) -> Proxy nicht gefunden.\n");

      return &result;
    }
    knto_register (k, &result.oid);
    result.rc = OK;
    LOG ("(OK).\n");
    return (&result);
}


rknt * knto_unregister_1_svc(rknt *argp, struct svc_req *rqstp)
{
    static rknt  result;
    static knto * k;

    Assert (argp);
 
    LOG ("[KNTO_SVC]: knto_unregister() aufgerufen von %s ... ", argp->cid);

    rknt_init (&result);
    cmgr_set_cid (argp->cid);

    k = ctab_get_obj (argp->cid, argp->oid);
    if (!k) {
      result.rc = NOK_PROXY_NOT_FOUND;
      LOG ("(NOK) -> Proxy nicht gefunden.\n");

      return &result;
    }
    /* Der lokale unregister loescht das Obj aus der OTAB ...
    knto_unregister (k); CHECK */

    pkrn_init (&k->persistent);
    LOG ("(OK).\n");
    result.rc = OK;
    return (&result);
}


rknt* knto_find_by_kunde_1_svc(rknt* argp, struct svc_req* rqstp)
{
    static long  knto_list [MAX_KNTO_LIST];
    static rknt  result;
    knde * ku;
    knto * ko;
    list * l;
    int i = 0;
    RC rc;

    Assert (argp);

    LOG ("[KNTO_SVC]: knto_find_by_kunde() aufgerufen von %s ... ", argp->cid);

    rknt_init (&result);
    cmgr_set_cid (argp->cid);
     
    ku = (knde *)  argp->kunde_oid;
    Assert (ku);

    l = knto_find_by_kunde (ku, argp->kunde_rid, &rc);
    Assert (l);
 
    list_rewind (l);
    while (ko = list_getnext (l)) 
        knto_list [i++] = pkrn_get_oid (&ko->persistent );

    Assert (i < MAX_KNTO_LIST); 

    result.list_of_knto.list_of_knto_val = knto_list;
    result.list_of_knto.list_of_knto_len = i;
    LOG ("(OK).\n");
    result.rc = OK;
    return (&result);
}


rknt* knto_find_unassigned_1_svc(rknt * argp, struct svc_req* rqst)
{
    static long  knto_list [MAX_KNTO_LIST];
    static rknt  result;
    knde * ku;
    knto * ko;
    list * l;
    int i = 0;

    Assert (argp);

    LOG ("[KNTO_SVC]: knto_find_unassigned() aufgerufen von %s ... ", argp->cid);

    rknt_init (&result);
    cmgr_set_cid (argp->cid);
     
    l = knto_find_unassigned ();
    Assert (l);
 
    list_rewind (l);
    while (ko = list_getnext (l)) 
        knto_list [i++] = pkrn_get_oid (&ko->persistent );

    Assert (i < MAX_KNTO_LIST); 

    result.list_of_knto.list_of_knto_val = knto_list;
    result.list_of_knto.list_of_knto_len = i;
    LOG ("(OK).\n");
    result.rc = OK;
    return (&result);
}


rknt* knto_einzahlen_1_svc(rknt *argp, struct svc_req * rqstp)
{
}


rknt* knto_auszahlen_1_svc(rknt *argp, struct svc_req * rqstp)
{
}
