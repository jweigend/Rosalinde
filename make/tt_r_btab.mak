# -----------------------------------------------------------------------
#	Dateiname:		$RCSfile: tt_btab_rpc.mak,v $									
#	Version:		$Revision: 1 $									
#	Erstellt am:	00.00.96											
#	Geaendert am:	$Date: 4/13/97 1:18p $							
#	Komponente:		GLOB											
#	Erstellt von:	Johannes Weigend
#	Geandert von:	$Author: Hannes $										
#	Copyright:		Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
#	Bermerkung:		Tabstop = 4												
# ------------------------------------------------------------------------


tt_r_btab : $(ROSA)/src/btab/tt_r_btab.o
	$(CC) $(CFLAGS) $(LIBS) -L$(LIBDIR) $(ROSA)/src/btab/tt_r_btab.o -o../exe/$@ -lbtab_rpc_clnt -lknde_rpc_clnt -ladrs_local -lotab_local -lsadm_rpc -lbrok_rpc_clnt -lcmgr_local -lutil

$(ROSA)/src/btab/tt_r_btab.o : $(ROSA)/src/btab/tt_btab.c
	$(CC) $(CFLAGS) $(INCLUDE) -DBTAB_PROXY -c $(ROSA)/src/btab/tt_btab.c -o $(ROSA)/src/btab/tt_r_btab.o -lutil

r_btab_svc : $(ROSA)/src/btab/r_btab_svc_main.o
	$(CC) $(CFLAGS) $(LIBS) -L$(LIBDIR) $(ROSA)/src/btab/r_btab_svc_main.o  -lbtab_rpc_server -lotab_local -lsadm_rpc -lbrok_rpc_clnt -lutil -lcmgr_local
	mv a.out ../exe/$@ 


r_btab_knde_svc : $(ROSA)/src/btab/r_btab_knde_svc_main.o $(ROSA)/src/btab/r_btab_knde_svc.o
	$(CC) $(CFLAGS) $(LIBS) -L$(LIBDIR) $(ROSA)/src/btab/r_btab_knde_svc_main.o  $(ROSA)/src/btab/r_btab_knde_svc.o -lbtab_rpc_server -lotab_local -lsadm_rpc -lbrok_rpc_clnt -lutil -lcmgr_local
	mv a.out ../exe/$@ 


r_btab_knto_svc : $(ROSA)/src/btab/r_btab_knto_svc_main.o  $(ROSA)/src/btab/r_btab_knto_svc.o
	$(CC) $(CFLAGS) $(LIBS) -L$(LIBDIR) $(ROSA)/src/btab/r_btab_knto_svc_main.o $(ROSA)/src/btab/r_btab_knto_svc.o -lbtab_rpc_server -lotab_local -lsadm_rpc -lbrok_rpc_clnt -lutil -lcmgr_local
	mv a.out ../exe/$@ 


