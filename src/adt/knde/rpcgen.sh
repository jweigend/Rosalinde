#
# Codegenerierung fuer knde 
#
rpcgen -C r_knde.x

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

