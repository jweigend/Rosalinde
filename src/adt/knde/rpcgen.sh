#
# Codegenerierung fuer knde 
#
cp r_knde.x r_knde.x.orig
tmp=$(mktemp /tmp/r_knde.XXXXXX.x)
sed -E 's/^[[:space:]]*%//' r_knde.x.orig | sed '/^#include "/d' | sed '/^#ifdef RPC_HDR/,/^#endif/ d' > "$tmp"
if rpcgen -C "$tmp"; then
	echo rpcgen succeeded
	mv r_knde.h ../../include 2>/dev/null || true
	mv r_knde_clnt.c . 2>/dev/null || true
	mv r_knde_svc.c . 2>/dev/null || true
	mv r_knde_xdr.c . 2>/dev/null || true
else
	echo rpcgen failed; rm -f "$tmp"; mv r_knde.x.orig r_knde.x; exit 1
fi
rm -f "$tmp"

# generiertes main () durch rpcgen_main() ersetzen ...

sed s/main/rpcgen_main/ r_knde_svc.c >/tmp/out 
mv /tmp/out r_knde_svc.c

mv r_knde.h ../../../include

# Richtige CASTS um Warnungen unter Linux zu vermeiden ...
sed s/xdr_/"(xdrproc_t) xdr_"/1 r_knde_clnt.c >/tmp/out
mv /tmp/out r_knde_clnt.c
sed s/xdr_/"(xdrproc_t) xdr_"/2 r_knde_clnt.c >/tmp/out
mv /tmp/out r_knde_clnt.c

echo Code generiert fuer normalen RPC - Support.

