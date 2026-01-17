/* ------------------------------------------------------------------------
|   Dateiname:      $RCSfile: r_knde.c,v $
|   Version:        $Revision: 1 $
|   Erstellt am:    00.00.96
|   Geaendert am:   $Date: 19.11.97 9:36 $
|   Komponente:     KNDE_RPC_PROXY Serverstubs
|   Erstellt von:   Johannes Weigend
|   Geandert von:   $Author: Johannes $
|   Copyright:      Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
|   Bermerkung:     Tabstop = 4
---------------------------------------------------------------------------*/

#ifdef KNDE_PROXY
#error "Serverstub must be compiled with -UKNDE_PROXY"
#endif

#ifndef KNTO_PROXY
#error "Serverstub must be compiled with -DKNTO_PROXY"
#endif

#include "r_knde.h"

#include "otab.h"
#include "ctab.h"
#include "cmgr.h"
#include "knto.h"



rknd * knde_new_1_svc(rknd *argp, struct svc_req *rqstp) {

    static rknd  result;
    knde * k;

    Assert (argp && rqstp);

    LOG ("[KNDE_SVC]: knde_new() aufgerufen von %s ... ", argp->cid);

    rknd_init (&result);
    cmgr_set_cid (argp->cid);

    k = knde_new ();
    Assert (k);

    LOG ("(OK).\n");

    ctab_register (argp->cid, &result.oid, NULL, k, NULL, NULL, NULL);

    ctab_print ();

    result.rc  = OK;

    return (&result);
}

rknd * knde_init_1_svc(rknd *argp, struct svc_req *rqstp) {

    static rknd  result;
    static knde * k;

    Assert (argp);

    LOG ("[KNDE_SVC]: knde_init() aufgerufen von %s ... ", argp->cid);

    rknd_init (&result);
    cmgr_set_cid (argp->cid);

    k = ctab_get_obj (argp->cid, argp->oid);
    if (!k) {
      result.rc = NOK_PROXY_NOT_FOUND;
      LOG ("(NOK) -> Proxy nicht gefunden.\n");

      return &result;
    }

    knde_init (k);

    LOG ("(OK).\n");

    result.rc = OK;
    return (&result);
}

rknd * knde_delete_1_svc(rknd *argp, struct svc_req *rqstp) {

    static rknd result;
    static knde * k;

    Assert (argp);

    LOG ("[KNDE_SVC]: knde_delete() aufgerufen von %s ... ", argp->cid);

    rknd_init (&result);
    cmgr_set_cid (argp->cid);
 
    k = ctab_get_obj (argp->cid, argp->oid);
    if (!k) {
      result.rc = NOK_PROXY_NOT_FOUND;
      LOG ("(NOK) -> Proxy nicht gefunden.\n");

      return &result;
    }
    
    if (knde_is_persistent (k)) {
        
        knde_unregister (k);
    }
    else {
        ctab_unregister (argp->cid, argp->oid);
    }

    knde_delete (k);

    LOG ("(OK)\n");
    ctab_print ();

    result.rc = OK;
    return &result;
}

rknd * knde_clear_1_svc(rknd *argp, struct svc_req *rqstp) {

    static rknd  result;
    static knde * k;

    Assert (argp);

    LOG ("[KNDE_SVC]: knde_clear() aufgerufen von %s ... ", argp->cid);

    rknd_init (&result);
    cmgr_set_cid (argp->cid);

    k = ctab_get_obj (argp->cid, argp->oid);
    if (!k) {
      result.rc = NOK_PROXY_NOT_FOUND;
      LOG ("(NOK) -> Proxy nicht gefunden.\n");

      return &result;
    }

    knde_clear (k);

    LOG ("(OK).\n");

    result.rc = OK;
    return (&result);
}


rknd * knde_set_name_1_svc(rknd *argp, struct svc_req *rqstp) {

    static rknd  result;
    static knde * k;
    strg s;

    Assert (argp);

    LOG ("[KNDE_SVC]: knde_set_name() aufgerufen von %s ... ", argp->cid);

    rknd_init (&result);
    cmgr_set_cid (argp->cid);

    strg_init (&s, MAX_KUNDENNAME);

    k = ctab_get_obj (argp->cid, argp->oid);
    if (!k) {
      result.rc = NOK_PROXY_NOT_FOUND;
      LOG ("(NOK) -> Proxy nicht gefunden.\n");

      return &result;
    }

    strg_in (&s, argp->name);

    knde_set_name (k, &s);

    strg_clear (&s);

    LOG ("(OK).\n");

    result.rc = OK;
    return (&result);
}


rknd * knde_set_vorname_1_svc(rknd *argp, struct svc_req *rqstp) {

    static rknd  result;
    static knde * k;
    strg s;

    Assert (argp);

    LOG ("[KNDE_SVC]: knde_set_vorname() aufgerufen von %s ... ", argp->cid);

    rknd_init (&result);
    cmgr_set_cid (argp->cid);

    strg_init (&s, MAX_KUNDENNAME);

    k = ctab_get_obj (argp->cid, argp->oid);
    if (!k) {
      result.rc = NOK_PROXY_NOT_FOUND;
      LOG ("(NOK) -> Proxy nicht gefunden.\n");

      return &result;
    }
    strg_in (&s, argp->vorname);

    knde_set_vorname (k, &s);

    strg_clear (&s);

    LOG ("(OK).\n");

    result.rc = OK;
    return (&result);
}


rknd * knde_set_adresse_1_svc(rknd *argp, struct svc_req *rqstp) {

    static rknd  result;
    static knde * k;
    static adrs a;

    Assert (argp);

    LOG ("[KNDE_SVC]: knde_set_adresse() aufgerufen von %s ... ", argp->cid);

    adrs_init (&a);
    rknd_init (&result);
    cmgr_set_cid (argp->cid);

    k = ctab_get_obj (argp->cid, argp->oid);
    if (!k) {
      result.rc = NOK_PROXY_NOT_FOUND;
      LOG ("(NOK) -> Proxy nicht gefunden.\n");

      return &result;
    }
    adrs_in (&a, argp->adresse.strasse,
                 argp->adresse.hausnr,
                 argp->adresse.plz,
                 argp->adresse.ort,
                 argp->adresse.land);

    knde_set_adresse (k, &a);

    adrs_clear (&a);

    LOG ("(OK).\n");

    result.rc = OK;
    return (&result);
}

rknd * knde_set_anrede_1_svc(rknd *argp, struct svc_req *rqstp) {

    static rknd  result;
    static knde * k;
    static anrd a;
    RC rc;

    Assert (argp);

    LOG ("[KNDE_SVC]: knde_set_anrede() aufgerufen von %s ... ", argp->cid);

    rknd_init (&result);
    cmgr_set_cid (argp->cid);

    k = ctab_get_obj (argp->cid, argp->oid);
    if (!k) {
      result.rc = NOK_PROXY_NOT_FOUND;
      LOG ("(NOK) -> Proxy nicht gefunden.\n");

      return &result;
    }
    anrd_in (&a, &rc, LANG, argp->anrede);
    knde_set_anrede (k, &a);

    LOG ("(OK).\n");

    result.rc = OK;
    return (&result);
}

rknd * knde_get_name_1_svc(rknd *argp, struct svc_req *rqstp) {

    static rknd  result;
    static knde * k;
    strg * s;

    Assert (argp);

    LOG ("[KNDE_SVC]: knde_get_name() aufgerufen von %s ... ", argp->cid);

    rknd_init (&result);
    cmgr_set_cid (argp->cid);

    k = ctab_get_obj (argp->cid, argp->oid);
    if (!k) {
      result.rc = NOK_PROXY_NOT_FOUND;
      LOG ("(NOK) -> Proxy nicht gefunden.\n");

      return &result;
    }
    s = knde_get_name (k);
    Assert (s);

    result.name = strg_out (s);

    LOG ("(OK).\n");

    result.rc = OK;
    return (&result);
}


rknd * knde_get_rid_1_svc(rknd *argp, struct svc_req *rqstp) {

    static rknd  result;
    static knde * k;

    Assert (argp);

    LOG ("[KNDE_SVC]: knde_get_rid() aufgerufen von %s ... ", argp->cid);

    rknd_init (&result);
    cmgr_set_cid (argp->cid);

    k = ctab_get_obj (argp->cid, argp->oid);
    if (!k) {
      result.rc = NOK_PROXY_NOT_FOUND;
      LOG ("(NOK) -> Proxy nicht gefunden.\n");

      return &result;
    }
    result.rid = knde_get_rid (k);

    LOG ("(OK).\n");

    result.rc = OK;
    return (&result);
}


rknd * knde_get_adresse_1_svc(rknd *argp, struct svc_req *rqstp) {

    static rknd  result;
    static knde * k;
    adrs * a;

    Assert (argp);

    LOG ("[KNDE_SVC]: knde_get_adresse() aufgerufen von %s ... ", argp->cid);

    rknd_init (&result);
    cmgr_set_cid (argp->cid);

    k = ctab_get_obj (argp->cid, argp->oid);
    if (!k) {
      result.rc = NOK_PROXY_NOT_FOUND;
      LOG ("(NOK) -> Proxy nicht gefunden.\n");

      return &result;
    }
    a = knde_get_adresse (k);
    Assert (a);

    result.adresse.strasse =  adrs_get_strasse (a);
    result.adresse.hausnr  =  adrs_get_hausnr  (a);
    result.adresse.ort   =  adrs_get_ort     (a);
    result.adresse.plz   =  adrs_get_plz     (a);
    result.adresse.land  =  adrs_get_land    (a);

    LOG ("(OK).\n");

    result.rc = OK;
    return (&result);
}


rknd * knde_get_vorname_1_svc(rknd *argp, struct svc_req *rqstp) {

    static rknd  result;
    static knde * k;
    strg * s;

    Assert (argp);

    LOG ("[KNDE_SVC]: knde_get_vorname() aufgerufen von %s ... ", argp->cid);

    rknd_init (&result);
    cmgr_set_cid (argp->cid);

    k = ctab_get_obj (argp->cid, argp->oid);
    if (!k) {
      result.rc = NOK_PROXY_NOT_FOUND;
      LOG ("(NOK) -> Proxy nicht gefunden.\n");

      return &result;
    }
    s = knde_get_vorname (k);
    Assert (s);

    result.vorname = strg_out (s);

    LOG ("(OK).\n");

    result.rc = OK;
    return (&result);
}


rknd * knde_get_anrede_1_svc(rknd *argp, struct svc_req *rqstp) {

    static rknd  result;
    static knde * k;
    char * s;

    Assert (argp);

    LOG ("[KNDE_SVC]: knde_get_anrede() aufgerufen von %s ... ", argp->cid);

    rknd_init (&result);
    cmgr_set_cid (argp->cid);

    k = ctab_get_obj (argp->cid, argp->oid);
    if (!k) {
      result.rc = NOK_PROXY_NOT_FOUND;
      LOG ("(NOK) -> Proxy nicht gefunden.\n");

      return &result;
    }
    s = anrd_out (&k->anrede, LANG);
    Assert (s);

    result.anrede = s;

    LOG ("(OK).\n");

    result.rc = OK;
    return (&result);
}


rknd * knde_find_by_key_1_svc(rknd *argp, struct svc_req *rqstp) {

    static rknd  result;
    knde * k;
    RC rc;

    Assert (argp);

    LOG ("[KNDE_SVC]: knde_find_by_key() aufgerufen von %s ... ", argp->cid);

    rknd_init (&result);
    cmgr_set_cid (argp->cid);

    k = knde_find_by_key (argp->rid, &rc);

    if (rc != OK) {

        result.rc = rc;
        return &result;
    }
    result.rc = OK;
    result.oid = pkrn_get_oid (&k->persistent);

    LOG ("(OK).\n");

    return (&result);
}

rknd * knde_register_1_svc(rknd *argp, struct svc_req *rqstp) {

    static rknd  result;
    static knde * k;

    Assert (argp);

    LOG ("[KNDE_SVC]: knde_register() aufgerufen von %s ... ", argp->cid);

    rknd_init (&result);
    cmgr_set_cid (argp->cid);

    k = ctab_get_obj (argp->cid, argp->oid);
    if (!k) {
      result.rc = NOK_PROXY_NOT_FOUND;
      LOG ("(NOK) -> Proxy nicht gefunden.\n");

      return &result;
    }
    knde_register (k, &result.oid);

    LOG ("(OK).\n");

    result.rc = OK;
    return (&result);
}

rknd * knde_unregister_1_svc(rknd *argp, struct svc_req *rqstp) {

    static rknd  result;
    static knde * k;

    Assert (argp);

    LOG ("[KNDE_SVC]: knde_unregister() aufgerufen von %s ... ", argp->cid);

    rknd_init (&result);
    cmgr_set_cid (argp->cid);

    k = ctab_get_obj (argp->cid, argp->oid);
    if (!k) {
      result.rc = NOK_PROXY_NOT_FOUND;
      LOG ("(NOK) -> Proxy nicht gefunden.\n");

      return &result;
    }

    pkrn_init (&k->persistent);

    LOG ("(OK).\n");

    result.rc = OK;
    return (&result);
}



rknd * knde_get_konten_1_svc(rknd *argp, struct svc_req *rqstp) {
    
    static long  knto_list [MAX_KNTO_LIST];
    static rknd  result;
    static knde * k;
    knto * ko;
    list * l;
    int i = 0;

    Assert (argp);

    LOG ("[KNDE_SVC]: knde_get_konten() aufgerufen von %s ... ", argp->cid);

    rknd_init (&result);
    cmgr_set_cid (argp->cid);

    k = ctab_get_obj (argp->cid, argp->oid);
    if (!k) {
      result.rc = NOK_PROXY_NOT_FOUND;
      LOG ("(NOK) -> Proxy nicht gefunden.\n");

      return &result;
    }

    l = knde_get_konten (k);
    Assert (l);
 
    list_rewind (l);
    while (ko = list_getnext (l)) knto_list [i++] = (long) ko;  

    Assert (i < MAX_KNTO_LIST); 

    result.list_of_konten.list_of_konten_val = knto_list;
    result.list_of_konten.list_of_konten_len = i;

    LOG ("(OK).\n");

    result.rc = OK;
    return (&result);
}
