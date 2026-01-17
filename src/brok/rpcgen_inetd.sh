#
# Codegenerierung fuer broker der von inetd gestartet wird. 
#
rpcgen -C -I -K -1 r_brok.x

# generiertes main () durch rpcgen_main() ersetzen ...

sed s/main/rpcgen_main/ r_brok_svc.c >/tmp/out 
mv /tmp/out r_brok_svc.c

echo Es wurden RPC - Stubs und Servermaincode fuer inetd generiert.
