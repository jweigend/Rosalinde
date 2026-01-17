/* Handwritten XDR for rtab to satisfy build (generated rpcgen XDR missing) */
#include "r_btab.h"
#include <rpc/rpc.h>

bool_t
xdr_rtab(XDR *xdrs, rtab *objp)
{
    if (!xdr_long(xdrs, &objp->oid))
        return FALSE;
    if (!xdr_string(xdrs, &objp->cid, MAX_CIDLENGTH))
        return FALSE;
    if (!xdr_string(xdrs, &objp->path, MAX_PATH))
        return FALSE;
    if (!xdr_string(xdrs, &objp->record, MAX_RECORD))
        return FALSE;
    if (!xdr_long(xdrs, &objp->base_param))
        return FALSE;
    if (!xdr_long(xdrs, &objp->rid))
        return FALSE;
    if (!xdr_short(xdrs, &objp->rc))
        return FALSE;
    if (!xdr_int(xdrs, &objp->rec_length_param))
        return FALSE;
    return TRUE;
}
