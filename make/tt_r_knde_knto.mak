# -----------------------------------------------------------------------
#	Dateiname:		$RCSfile: tt_knde.mak,v $								
#	Version:		$Revision: 1 $									
#	Erstellt am:	00.00.96											
#	Geaendert am:	$Date: 4/13/97 1:19p $							
#	Komponente:		GLOB											
#	Erstellt von:	Johannes Weigend
#	Geandert von:	$Author: Hannes $										
#	Copyright:		Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
#	Bermerkung:		Tabstop = 4												
# ------------------------------------------------------------------------

# Solaris -zmuldefs
# Wenn Linker doppelte Symbole findet muessen folgende Funktionen
# aus r_knto_clnt.c herausgenommen werden:
# dbms_commit, dbms_rollback, dbms_data_server_changed

tt_r_knde_knto : $(ROSA)/src/adt/knto/tt_r_knde_knto.o
	$(CC) $(CFLAGS) -L$(LIBDIR) $(ROSA)/src/adt/knto/tt_r_knde_knto.o -lotab_local -lutil -lsadm_rpc -lbrok_rpc_clnt -ladrs_local -ldbms_rpc_clnt -lknto_rpc_clnt -lknde_rpc_clnt -lbtab_rpc_clnt -lcmgr_local $(LIBS) $(LDLIBS)
	mv a.out ../exe/$@ 


$(ROSA)/src/adt/knto/tt_r_knde_knto.o : $(ROSA)/src/adt/knto/tt_knde_knto.c
	$(CC) $(CFLAGS) -I$(INCLUDE) -DKNDE_PROXY -DKNTO_PROXY -c $(ROSA)/src/adt/knto/tt_knde_knto.c -o $@
