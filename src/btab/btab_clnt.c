/* ------------------------------------------------------------------------
|   Dateiname:      $RCSfile: btab_clnt.c,v $
|   Version:        $Revision: 1 $
|   Erstellt am:    00.00.96
|   Geaendert am:   $Date: 19.11.97 9:36 $
|   Komponente:     BTAB_RPC_PROXY
|   Erstellt von:   Johannes Weigend
|   Geandert von:   $Author: Johannes $
|   Copyright:      Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
|   Bermerkung:     Tabstop = 4
---------------------------------------------------------------------------*/


/* Bemerkungungen:
   ---------------

    Alle Funktionen sind bis auf btab_new im Prinzip identisch. Es werden
    folgende Schritte durchgefuehrt:
    0. Der CLIENT * Serverhandle wird vom sadm geholt.
    1. Die automatisch allokierte rtab-Struktur (r) wird vollstaendig mit
       Nullen gefuellt, und die char * Pointer auf einen globalen Nullstring
       gesetzt. (XDR-String muss Zeiger auf gueltigen Speicher erhalten)
    2. Aufbau der zu uebergebenden RTAB-Struktur durch kopieren der fuer
       die jeweiligen Funktionen benoetigten Parameter.
    3. Der uebergebene BTAB-Proxy wird in die lokale RTAB-Struktur ko-
       piert.
    4. RPC-Call der Form  rtab * rpccall (rtab *, serverhandle).
    5. Zurueckkopieren der zurueckgegebenen Parameter
    6. Freigeben des durch XDR zusaetlich allokierten Speichers.

    Ueber das Netz gehen nur RTAB-Strukturen.
*/

#ifndef BTAB_PROXY
#pragma message("Clientstub must be compiled with -DBTAB_PROXY")
#endif

#include "r_btab.h"
#include "sadm.h"
#include "cmgr.h"

static CLIENT * cl = NULL;

static char btab_svc [MAX_SVCNNAME] = BTAB_SVC;

/* Der Kundenserver aendert den SVCN auf KNDE_BTAB_SVC
   Der Kontenserver aendert den SVCN auf KNTO_BTAB_SVC
   der default ist BTAB_SVC
   ( Darf nur innerhalb des Servers verwendet werden ) */

void btab_clnt_stub_chge_svcn (char *  svcn) {

    Assert (svcn);
    strcpy (btab_svc, svcn);
}


btab * btab_new () {

    rtab * rtb;
    rtab r;

    cl = sadm_get_serverhandle (btab_svc);
    Assert (cl);

    rtab_init (&r);

    r.cid = cmgr_get_sid ();

    rtb = btab_new_1 (&r, cl);
    Assert (rtb);

    return (btab *) rtb->oid;
}


void btab_init (btab * b) {

    rtab r;
    rtab * rtb;

    Assert (b);

    cl = sadm_get_serverhandle (btab_svc);
    Assert (cl);

    rtab_init (&r);
        /* No additional Args */

        /* Die btab ist nur ein Proxy */
    r.oid = (long)  b;
    r.cid = cmgr_get_sid ();

        /* Call Server */
    rtb = btab_init_1 (&r, cl);
    Assert (rtb && (rtb->rc == OK));

    xdr_free ((xdrproc_t) xdr_rtab, (char *) rtb);
}


void btab_clear (btab * b) {

    rtab r;
    rtab * rtb;

    Assert (b);

    cl = sadm_get_serverhandle (btab_svc);
    Assert (cl);

    rtab_init (&r);
        /* No additional Args */

    r.oid = (long) b;
    r.cid = cmgr_get_sid ();

        /* Call Server */
    rtb = btab_clear_1 (&r, cl);
    Assert (rtb && (rtb->rc == OK));

    xdr_free ((xdrproc_t) xdr_rtab, (char *) rtb);
}


btab * btab_delete (btab * b) {

    rtab * rtb;
    rtab r;

    Assert (b);

    cl = sadm_get_serverhandle (btab_svc);
    Assert (cl);

    rtab_init (&r);
        /* No additional Args */

    r.oid = (long) b;
    r.cid = cmgr_get_sid ();

        /* Call Server */
    rtb = btab_delete_1 (&r, cl);
    Assert (rtb);
    Assert (rtb->rc == OK);

    xdr_free ((xdrproc_t) xdr_rtab, (char *) rtb);

    return NULL;
}


void btab_open (btab * b, char * path, int rec_length, long base) {

    rtab r;
    rtab * rtb;

    Assert (b);
    Assert (path);

    cl = sadm_get_serverhandle (btab_svc);
    Assert (cl);

    rtab_init (&r);
        /* Create Args */
    r.path = path;
    r.rec_length_param = rec_length;
    r.base_param = base;

    r.oid = (long) b;
    r.cid = cmgr_get_sid ();

        /* Call Server */
    rtb = btab_open_1 (&r, cl);
    Assert (rtb);
    Assert (rtb->rc == OK);

    xdr_free ((xdrproc_t) xdr_rtab, (char *) rtb);
}

void btab_close (btab * b) {
    rtab r;
    rtab * rtb;

    Assert (b);

    cl = sadm_get_serverhandle (btab_svc);
    Assert (cl);

    rtab_init (&r);
        /* No additional Args */

    r.oid = (long) b;
    r.cid = cmgr_get_sid ();

        /* Call Server */
    rtb = btab_close_1 (&r, cl);
    Assert (rtb);
    Assert (rtb->rc == OK);

    xdr_free ((xdrproc_t) xdr_rtab, (char *) rtb);
}

void btab_rewind (btab * b) {
    rtab r;
    rtab * rtb;

    Assert (b);

    cl = sadm_get_serverhandle (btab_svc);
    Assert (cl);

    rtab_init (&r);
        /* No additional Args */

    r.oid = (long) b;
    r.cid = cmgr_get_sid ();

        /* Call Server */
    rtb = btab_rewind_1 (&r, cl);
    Assert (rtb);
    Assert (rtb->rc == OK);

    xdr_free ((xdrproc_t) xdr_rtab, (char *) rtb);
}


RC   btab_get_next (btab * b, char * record) {
    RC rc;
    rtab r;
    rtab * rtb;

    Assert (b);
    Assert (record);

    cl = sadm_get_serverhandle (btab_svc);
    Assert (cl);

    rtab_init (&r);

    r.oid = (long) b;
    r.cid = cmgr_get_sid ();

        /* Call Server */
    rtb = btab_get_next_1 (&r, cl);
    Assert (rtb);

    rc = rtb->rc;

    strcpy (record, rtb->record);

    xdr_free ((xdrproc_t) xdr_rtab, (char *) rtb);

    return rc;
}


RC   btab_get_previous (btab * b, char * record) {
    RC rc;
    rtab r;
    rtab * rtb;

    Assert (b);
    Assert (record);

    cl = sadm_get_serverhandle (btab_svc);
    Assert (cl);

    rtab_init (&r);

    r.oid = (long) b;
    r.cid = cmgr_get_sid ();

        /* Call Server */
    rtb = btab_get_previous_1 (&r, cl);
    Assert (rtb);

    rc = rtb->rc;

    strcpy (record, rtb->record);

    xdr_free ((xdrproc_t) xdr_rtab, (char *) rtb);

    return rc;
}


RC   btab_get_at (btab * b, long rid, char * record) {
    RC rc;
    rtab r;
    rtab * rtb;

    Assert (b);
    Assert (record);

    cl = sadm_get_serverhandle (btab_svc);
    Assert (cl);

    rtab_init (&r);

    r.rid = rid;

    r.oid = (long) b;
    r.cid = cmgr_get_sid ();

        /* Call Server */
    rtb = btab_get_at_1 (&r, cl);
    Assert (rtb);

    rc = rtb->rc;

    strcpy (record, rtb->record);

    xdr_free ((xdrproc_t) xdr_rtab, (char *) rtb);

    return rc;
}

void btab_put_at (btab * b, char * record) {
    rtab r;
    rtab * rtb;

    Assert (b);
    Assert (record);

    cl = sadm_get_serverhandle (btab_svc);
    Assert (cl);

    rtab_init (&r);
        /* Additional Args */
    r.record = record;

    r.oid = (long) b;
    r.cid = cmgr_get_sid ();

        /* Call Server */
    rtb = btab_put_at_1 (&r, cl);
    Assert (rtb);
    Assert (rtb->rc == OK);

        /* record ueberschrieben ? */
    xdr_free ((xdrproc_t) xdr_rtab, (char *) rtb);
}

void btab_append (btab * b, char * record, long * rid) {
    rtab r;
    rtab * rtb;

    Assert (b);
    Assert (record);
    Assert (rid);

    cl = sadm_get_serverhandle (btab_svc);
    Assert (cl);

    rtab_init (&r);
        /* Additional Args */
    r.record = record;

    r.oid = (long) b;
    r.cid = cmgr_get_sid ();

        /* Call Server */
    rtb = btab_append_1 (&r, cl);
    Assert (rtb);
    Assert (rtb->rc == OK);

    *rid = rtb->rid;

    xdr_free ((xdrproc_t) xdr_rtab, (char *) rtb);
}

BOOL btab_is_empty (btab * b) {
    rtab r;
    short * rc;
    BOOL result;

    Assert (b);

    cl = sadm_get_serverhandle (btab_svc);
    Assert (cl);

    rtab_init (&r);
        /* No Additional Args */

    r.oid = (long) b;
    r.cid = cmgr_get_sid ();

        /* Call Server */
    rc = btab_is_empty_1 (&r, cl);
    Assert (rc);

    result = *rc;

    return result;
}

BOOL btab_is_not_empty (btab * b) {
    rtab r;
    short * rc;
    BOOL result;

    Assert (b);

    cl = sadm_get_serverhandle (btab_svc);
    Assert (cl);

    rtab_init (&r);
        /* No Additional Args */

    r.oid = (long) b;
    r.cid = cmgr_get_sid ();

        /* Call Server */
    rc = btab_is_empty_1 (&r, cl);
    Assert (rc);

    result = *rc;
    return result;
}
