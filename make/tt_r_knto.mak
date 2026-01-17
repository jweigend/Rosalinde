# -----------------------------------------------------------------------
#	Dateiname:		$RCSfile: tt_knto_rpc.mak,v $								
#	Version:		$Revision: 1 $									
#	Erstellt am:	00.00.96											
#	Geaendert am:	$Date: 4/13/97 1:19p $							
#	Komponente:		GLOB											
#	Erstellt von:	Johannes Weigend
#	Geandert von:	$Author: Hannes $										
#	Copyright:		Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
#	Bermerkung:		Tabstop = 4												
# ------------------------------------------------------------------------


r_knto_svc : $(ROSA)/src/adt/knto/r_knto_svc_main.o
	$(CC) $(CFLAGS) $(LIBS) -L$(LIBDIR) -DBTAB_PROXY $(ROSA)/src/adt/knto/r_knto_svc_main.o -lknto_rpc_server -lknde_rpc_clnt -ldbms_rpc_server -lotab_local -lutil -lbtab_rpc_clnt -lsadm_rpc -lbrok_rpc_clnt -ladrs_local -lcmgr_local
	mv a.out ../exe/$@ 


tt_r_knto : $(ROSA)/src/adt/knto/tt_r_knto.o 
	$(CC) $(CFLAGS) -L$(LIBDIR) $(ROSA)/src/adt/knto/tt_r_knto.o $(LIBS) -lbtab_rpc_clnt -lotab_local -lsadm_rpc -lbrok_rpc_clnt -lutil -lknto_rpc_clnt -lcmgr_local -ldbms_rpc_clnt -lknde_rpc_clnt
	mv a.out ../exe/$@ 

$(ROSA)/src/adt/knto/tt_r_knto.o : $(ROSA)/src/adt/knto/tt_knto.c
	$(CC) $(CFLAGS) $(INCLUDE) -DBTAB_PROXY -DKNDE_PROXY -DKNTO_PROXY -c $(ROSA)/src/adt/knto/tt_knto.c  -o $@

