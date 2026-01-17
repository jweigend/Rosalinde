/* Handwritten XDR for rknt because rpcgen did not generate xdr sources */
#include "r_knto.h"
#include <rpc/rpc.h>

bool_t
xdr_rknt(XDR *xdrs, rknt *objp)
{
    if (!xdr_long(xdrs, &objp->oid)) return FALSE;
    if (!xdr_string(xdrs, &objp->cid, MAX_CIDLENGTH)) return FALSE;
    if (!xdr_long(xdrs, &objp->kunde_oid)) return FALSE;
    if (!xdr_long(xdrs, &objp->kunde_rid)) return FALSE;
    if (!xdr_long(xdrs, &objp->konto_id)) return FALSE;
    if (!xdr_long(xdrs, &objp->konto_nummer)) return FALSE;
    if (!xdr_long(xdrs, &objp->blz)) return FALSE;
    if (!xdr_string(xdrs, &objp->bankname, MAX_BANKNAME)) return FALSE;
    if (!xdr_array(xdrs, (char **)&objp->list_of_knto.list_of_knto_val,
                   (u_int *)&objp->list_of_knto.list_of_knto_len,
                   ~0, sizeof(long), (xdrproc_t)xdr_long)) return FALSE;
    if (!xdr_double(xdrs, &objp->betrag)) return FALSE;
    if (!xdr_long(xdrs, &objp->rid)) return FALSE;
    if (!xdr_short(xdrs, &objp->rc)) return FALSE;
    return TRUE;
}
