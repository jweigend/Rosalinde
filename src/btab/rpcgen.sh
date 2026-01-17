#
# Codegenerierung fuer btab 
#
cp r_btab.x r_btab.x.orig
# Create a cleaned temporary .x removing legacy '%' lines and local includes
tmp=$(mktemp /tmp/r_btab.XXXXXX.x)
sed -E 's/^[[:space:]]*%//' r_btab.x.orig | sed '/^#include "/d' | sed '/^#ifdef RPC_HDR/,/^#endif/ d' > "$tmp"
if rpcgen -C "$tmp"; then
	echo rpcgen succeeded
	# move generated files into place if present
	mv r_btab.h ../../include 2>/dev/null || true
	mv r_btab_clnt.c . 2>/dev/null || true
	mv r_btab_svc.c . 2>/dev/null || true
	mv r_btab_xdr.c . 2>/dev/null || true
else
	echo rpcgen failed; rm -f "$tmp"; mv r_btab.x.orig r_btab.x; exit 1
fi
rm -f "$tmp"

# generiertes main () durch rpcgen_main() ersetzen ...

sed s/main/rpcgen_main/ r_btab_svc.c >/tmp/out 
mv /tmp/out r_btab_svc.c

mv r_btab.h ../../include

cp r_btab_svc.c r_btab_knde_svc.c
cp r_btab_svc.c r_btab_knto_svc.c

# generierte Programmnummer ersetzen
# um weitere Dateien zu vermeiden wird die Programmnummer ersetzt.

sed s/R_BTAB/R_BTAB_KNDE/ r_btab_knde_svc.c >/tmp/out
mv /tmp/out r_btab_knde_svc.c

sed s/R_BTAB/R_BTAB_KNTO/ r_btab_knto_svc.c > /tmp/out
mv /tmp/out r_btab_knto_svc.c

# Richtige CASTS um Warnungen unter Linux zu vermeiden ...
# sed s/xdr_/"(xdrproc_t) xdr_"/1 r_btab_clnt.c >/tmp/out
# mv /tmp/out r_btab_clnt.c
# sed s/xdr_/"(xdrproc_t) xdr_"/2 r_btab_clnt.c >/tmp/out
# mv /tmp/out r_btab_clnt.c


echo Code generiert fuer normalen RPC - Support.

