#
# Codegenerierung fuer konto 
#
rpcgen -C r_knto.x

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

