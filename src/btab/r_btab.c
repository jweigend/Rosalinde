/* ------------------------------------------------------------------------
|   Dateiname:      $RCSfile: r_btab.c,v $
|   Version:        $Revision: 1 $
|   Erstellt am:    00.00.96
|   Geaendert am:   $Date: 19.11.97 9:36 $
|   Komponente:     BTAB_RPC_PROXY
|   Erstellt von:   Johannes Weigend
|   Geandert von:   $Author: Johannes $
|   Copyright:      Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
|   Bermerkung:     Tabstop = 4
---------------------------------------------------------------------------*/

#ifdef BTAB_PROXY
#pragma message("Serverstub must be compiled with -UPROXY")
#endif

#include "r_btab.h"

#include "otab.h"
#include "ctab.h"
#include "cmgr.h"


rtab * btab_new_1_svc(rtab *argp, struct svc_req *rqstp) {

    static rtab  result;
    static btab * b;

    Assert (argp && rqstp);

    LOG ("[BTAB_SVC]: btab_new() aufgerufen von %s ... ", argp->cid);

    rtab_init (&result);
    cmgr_set_cid (argp->cid);

    b = btab_new ();
    Assert (b);

    ctab_register (argp->cid, &result.oid, NULL, b, NULL, NULL, NULL);

    result.rc  = OK;

    LOG ("(OK).\n");
    ctab_print ();

    return (&result);
}

rtab * btab_init_1_svc(rtab *argp, struct svc_req *rqstp) {

    static rtab  result;
    static btab * b;

    Assert (argp);

    LOG ("[BTAB_SVC]: btab_init() aufgerufen von %s ... ", argp->cid);

    rtab_init (&result);
    cmgr_set_cid (argp->cid);

    b = ctab_get_obj (argp->cid, argp->oid);
    if (!b) {
      result.rc = NOK_PROXY_NOT_FOUND;
      LOG ("(NOK) -> Proxy nicht gefunden.\n");

      return &result;
    }


    btab_init (b);

    result.rc = OK;

    LOG ("(OK).\n");

    return (&result);
}

rtab * btab_delete_1_svc(rtab *argp, struct svc_req *rqstp) {

    static rtab  result;
    static btab * b;

    Assert (argp);
 
    LOG ("[BTAB_SVC]: btab_delete() aufgerufen von %s ... ", argp->cid);

    rtab_init (&result);
    cmgr_set_cid (argp->cid);

    b = ctab_get_obj (argp->cid, argp->oid);
    if (!b) {
      result.rc = NOK_PROXY_NOT_FOUND;
      LOG ("(NOK) -> Proxy nicht gefunden.\n");

      return &result;
    }

    LOG ("(OK).\n");

    btab_delete (b);

    ctab_unregister (argp->cid, argp->oid);
    
    LOG ("(OK).\n");
    ctab_print ();

    result.rc = OK;
    return(&result);
}

rtab * btab_clear_1_svc(rtab *argp, struct svc_req *rqstp) {

    static rtab  result;
    static btab * b;

    Assert (argp);
 
    LOG ("[BTAB_SVC]: btab_clear() aufgerufen von %s ... ", argp->cid);

    rtab_init (&result);
    cmgr_set_cid (argp->cid);

    b = ctab_get_obj (argp->cid, argp->oid);
    if (!b) {
      result.rc = NOK_PROXY_NOT_FOUND;
      LOG ("(NOK) -> Proxy nicht gefunden.\n");

      return &result;
    }


    btab_clear (b);

    LOG ("(OK).\n");

    result.rc = OK;
    return (&result);
}

rtab * btab_open_1_svc(rtab *argp, struct svc_req *rqstp) {

    static rtab  result;
    static btab * b;

    Assert (argp);
    
    LOG ("[BTAB_SVC]: btab_open() aufgerufen von %s ... ", argp->cid);

    rtab_init (&result);
    cmgr_set_cid (argp->cid);

    b = ctab_get_obj (argp->cid, argp->oid);
    if (!b) {
      result.rc = NOK_PROXY_NOT_FOUND;
      LOG ("(NOK) -> Proxy nicht gefunden.\n");

      return &result;
    }

    btab_open (b, argp->path,
            argp->rec_length_param, argp->base_param);

    LOG ("(OK).\n");

    result.rc = OK;
    return (&result);
}

rtab * btab_close_1_svc(rtab *argp, struct svc_req *rqstp) {

    static rtab  result;
    static btab * b;

    Assert (argp);

    LOG ("[BTAB_SVC]: btab_close() aufgerufen von %s ... ", argp->cid);

    rtab_init (&result);
    cmgr_set_cid (argp->cid);

    b = ctab_get_obj (argp->cid, argp->oid);
    if (!b) {
      result.rc = NOK_PROXY_NOT_FOUND;
      LOG ("(NOK) -> Proxy nicht gefunden.\n");

      return &result;
    }


    btab_close (b);

    LOG ("(OK).\n");

    result.rc = OK;
    return (&result);
}

rtab * btab_rewind_1_svc(rtab *argp, struct svc_req *rqstp) {

    static rtab  result;
    static btab * b;

    Assert (argp);
 
    LOG ("[BTAB_SVC]: btab_rewind() aufgerufen von %s ... ", argp->cid);

    rtab_init (&result);
    cmgr_set_cid (argp->cid);

    b = ctab_get_obj (argp->cid, argp->oid);
    if (!b) {
      result.rc = NOK_PROXY_NOT_FOUND;
      LOG ("(NOK) -> Proxy nicht gefunden.\n");

      return &result;
    }


    btab_rewind (b);

    LOG ("(OK).\n");

    result.rc = OK;
    return (&result);
}

rtab * btab_get_next_1_svc(rtab *argp, struct svc_req *rqstp) {

    static rtab  result;
    static btab * b;
    static char record_buffer [MAX_RECORD];

    Assert (argp);

    LOG ("[BTAB_SVC]: btab_get_next() aufgerufen von %s ... ", argp->cid);

    rtab_init (&result);
    cmgr_set_cid (argp->cid);

    b = ctab_get_obj (argp->cid, argp->oid);
    if (!b) {
      result.rc = NOK_PROXY_NOT_FOUND;
      LOG ("(NOK) -> Proxy nicht gefunden.\n");

      return &result;
    }

    result.rc = btab_get_next (b, record_buffer);

    result.record = record_buffer;

    LOG ("(OK).\n");
 
    return (&result);
}

rtab * btab_get_at_1_svc(rtab *argp, struct svc_req *rqstp) {

    static rtab  result;
    static btab * b;
    static char record_buffer [MAX_RECORD];

    Assert (argp);

    LOG ("[BTAB_SVC]: btab_get_at() aufgerufen von %s ... ", argp->cid);
    
    rtab_init (&result);
    cmgr_set_cid (argp->cid);

    b = ctab_get_obj (argp->cid, argp->oid);
    if (!b) {
      result.rc = NOK_PROXY_NOT_FOUND;
      LOG ("(NOK) -> Proxy nicht gefunden.\n");

      return &result;
    }
    
    result.rc = btab_get_at (b, argp->rid, record_buffer);

    result.record = record_buffer;

    LOG ("(OK).\n");

    return (&result);
}

rtab * btab_get_previous_1_svc(rtab *argp, struct svc_req *rqstp) {

    static rtab  result;
    static btab * b;
    static char record_buffer [MAX_RECORD];

    Assert (argp);

    LOG ("[BTAB_SVC]: btab_get_previous() aufgerufen von %s ... ", argp->cid);

    rtab_init (&result);
    cmgr_set_cid (argp->cid);

    b = ctab_get_obj (argp->cid, argp->oid);
    if (!b) {
      result.rc = NOK_PROXY_NOT_FOUND;
      LOG ("(NOK) -> Proxy nicht gefunden.\n");

      return &result;
    }

    result.rc = btab_get_previous (b, record_buffer);

    result.record = record_buffer;

    LOG ("(OK).\n");

    return (&result);
}

rtab * btab_put_at_1_svc(rtab *argp, struct svc_req *rqstp) {

    static rtab  result;
    static btab * b;

    Assert (argp);

    LOG ("[BTAB_SVC]: btab_put_at() aufgerufen von %s ... ", argp->cid);

    rtab_init (&result);
    cmgr_set_cid (argp->cid);

    b = ctab_get_obj (argp->cid, argp->oid);
    if (!b) {
      result.rc = NOK_PROXY_NOT_FOUND;
      LOG ("(NOK) -> Proxy nicht gefunden.\n");

      return &result;
    }


    btab_put_at (b, argp->record);

    result.rc = OK;

    LOG ("(OK).\n");

    return (&result);
}

rtab * btab_append_1_svc(rtab *argp, struct svc_req *rqstp) {

    static rtab  result;
    static btab * b;
    static char record_buffer [MAX_RECORD];

    Assert (argp);

    LOG ("[BTAB_SVC]: btab_append() aufgerufen von %s ... ", argp->cid);

    rtab_init (&result);
    cmgr_set_cid (argp->cid);

    b = ctab_get_obj (argp->cid, argp->oid);
    if (!b) {
      result.rc = NOK_PROXY_NOT_FOUND;
      LOG ("(NOK) -> Proxy nicht gefunden.\n");

      return &result;
    }

    btab_append (b, argp->record, &argp->rid);

    strcpy (record_buffer, argp->record);

    result.record = record_buffer;

    result.rid = argp->rid;

    result.rc = OK;

    LOG ("(OK).\n");

    return (&result);
}

short * btab_is_empty_1_svc(rtab *argp, struct svc_req *rqstp) {

    static rtab  result;
    static btab * b;

    Assert (argp);

    LOG ("[BTAB_SVC]: btab_is_empty() aufgerufen von %s ... ", argp->cid);

    cmgr_set_cid (argp->cid);

    b = ctab_get_obj (argp->cid, argp->oid);
    if (!b) {
      result.rc = NOK_PROXY_NOT_FOUND;
      LOG ("(NOK) -> Proxy nicht gefunden.\n");

      return &result.rc;
    }

    result.rc = btab_is_empty (b);

    LOG ("(OK).\n");

    return &result.rc;
}

short * btab_is_not_empty_1_svc(rtab *argp, struct svc_req *rqstp) {

    static rtab  result;
    static btab * b;

    Assert (argp);
 
    LOG ("[BTAB_SVC]: btab_is_not_empty() aufgerufen von %s ... ", argp->cid);
    
    cmgr_set_cid (argp->cid);

    b = ctab_get_obj (argp->cid, argp->oid);
    if (!b) {
      result.rc = NOK_PROXY_NOT_FOUND;
      LOG ("(NOK) -> Proxy nicht gefunden.\n");

      return &result.rc;
    }

    result.rc = btab_is_not_empty (b);

    LOG ("(OK).\n");

    return (&result.rc);
}
