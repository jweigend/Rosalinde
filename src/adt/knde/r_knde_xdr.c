/* Handwritten XDR for rknd/radrs because rpcgen did not generate xdr sources */
#include "r_knde.h"
#include <rpc/rpc.h>

bool_t
xdr_radrs(XDR *xdrs, radrs *objp)
{
    if (!xdr_string(xdrs, &objp->strasse, MAX_STRASSE)) return FALSE;
    if (!xdr_string(xdrs, &objp->hausnr, MAX_HAUSNR)) return FALSE;
    if (!xdr_string(xdrs, &objp->plz, MAX_PLZ)) return FALSE;
    if (!xdr_string(xdrs, &objp->ort, MAX_ORT)) return FALSE;
    if (!xdr_string(xdrs, &objp->land, MAX_LAND)) return FALSE;
    return TRUE;
}

bool_t
xdr_rknd(XDR *xdrs, rknd *objp)
{
    if (!xdr_long(xdrs, &objp->oid)) return FALSE;
    if (!xdr_string(xdrs, &objp->cid, MAX_CIDLENGTH)) return FALSE;
    if (!xdr_string(xdrs, &objp->name, MAX_KUNDENNAME)) return FALSE;
    if (!xdr_string(xdrs, &objp->vorname, MAX_KUNDENNAME)) return FALSE;
    if (!xdr_string(xdrs, &objp->anrede, MAX_ANREDE)) return FALSE;
    if (!xdr_array(xdrs, (char **)&objp->list_of_konten.list_of_konten_val,
                   (u_int *)&objp->list_of_konten.list_of_konten_len,
                   ~0, sizeof(long), (xdrproc_t)xdr_long)) return FALSE;
    if (!xdr_radrs(xdrs, &objp->adresse)) return FALSE;
    if (!xdr_long(xdrs, &objp->rid)) return FALSE;
    if (!xdr_short(xdrs, &objp->rc)) return FALSE;
    return TRUE;
}
