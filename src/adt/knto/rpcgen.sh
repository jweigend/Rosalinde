#
# Codegenerierung fuer konto 
#
cp r_knto.x r_knto.x.orig
tmp=$(mktemp /tmp/r_knto.XXXXXX.x)
sed -E 's/^[[:space:]]*%//' r_knto.x.orig | sed '/^#include "/d' | sed '/^#ifdef RPC_HDR/,/^#endif/ d' > "$tmp"
if rpcgen -C "$tmp"; then
	echo rpcgen succeeded
	mv r_knto.h ../../include 2>/dev/null || true
	mv r_knto_clnt.c . 2>/dev/null || true
	mv r_knto_svc.c . 2>/dev/null || true
	mv r_knto_xdr.c . 2>/dev/null || true
else
	echo rpcgen failed; rm -f "$tmp"; mv r_knto.x.orig r_knto.x; exit 1
fi
rm -f "$tmp"

# generiertes main () durch rpcgen_main() ersetzen ...

sed s/main/rpcgen_main/ r_knto_svc.c >/tmp/out 
mv /tmp/out r_knto_svc.c

mv r_knto.h ../../../include

# Richtige CASTS um Warnungen unter Linux zu vermeiden ...
sed s/xdr_/"(xdrproc_t) xdr_"/1 r_knto_clnt.c >/tmp/out
mv /tmp/out r_knto_clnt.c
sed s/xdr_/"(xdrproc_t) xdr_"/2 r_knto_clnt.c >/tmp/out
mv /tmp/out r_knto_clnt.c


echo Code generiert fuer normalen RPC - Support.

