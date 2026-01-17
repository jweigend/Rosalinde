# -----------------------------------------------------------------------
#	Dateiname:		$RCSfile: tt_knde_rpc.mak,v $								
#	Version:		$Revision: 1 $									
#	Erstellt am:	00.00.96											
#	Geaendert am:	$Date: 4/13/97 1:19p $							
#	Komponente:		GLOB											
#	Erstellt von:	Johannes Weigend
#	Geandert von:	$Author: Hannes $										
#	Copyright:		Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
#	Bermerkung:		Tabstop = 4												
# ------------------------------------------------------------------------


tt_r_knde : $(ROSA)/src/adt/knde/tt_r_knde.o 
	$(CC) $(CFLAGS) -L$(LIBDIR) $(ROSA)/src/adt/knde/tt_r_knde.o $(LIBS) -lbtab_rpc_clnt -lotab_local -lsadm_rpc -lbrok_rpc_clnt -lknde_rpc_clnt -lutil -ladrs_local -lknto_rpc_clnt -lcmgr_local -ldbms_rpc_clnt $(LDLIBS)
	mv a.out ../exe/$@ 

$(ROSA)/src/adt/knde/tt_r_knde.o : $(ROSA)/src/adt/knde/tt_knde.c
	$(CC) $(CFLAGS) $(INCLUDE) -DBTAB_PROXY -DKNDE_PROXY -DKNTO_PROXY -c $(ROSA)/src/adt/knde/tt_knde.c  -o $@

r_knde_svc : $(ROSA)/src/adt/knde/r_knde_svc_main.o
	$(CC) $(CFLAGS) $(LIBS) -L$(LIBDIR) -DBTAB_PROXY -DKNTO_PROXY $(ROSA)/src/adt/knde/r_knde_svc_main.o -lknde_rpc_server -lotab_local -lutil -lbtab_rpc_clnt -lsadm_rpc -lbrok_rpc_clnt -lknto_rpc_clnt -ladrs_local -lcmgr_local -ldbms_rpc_server $(LDLIBS)
	mv a.out ../exe/$@ 



