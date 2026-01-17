#
# Codegenerierung fuer broker 
#
rpcgen -C r_brok.x

# generiertes main () durch rpcgen_main() ersetzen ...

sed s/main/rpcgen_main/ r_brok_svc.c >/tmp/out 
mv /tmp/out r_brok_svc.c

mv r_brok.h ../../include

# Richtige CASTS um Warnungen unter Linux zu vermeiden ...
sed s/xdr_/"(xdrproc_t) xdr_"/1 r_brok_clnt.c >/tmp/out
mv /tmp/out r_brok_clnt.c
sed s/xdr_/"(xdrproc_t) xdr_"/2 r_brok_clnt.c >/tmp/out
mv /tmp/out r_brok_clnt.c

echo Code generiert fuer normalen RPC - Support.

