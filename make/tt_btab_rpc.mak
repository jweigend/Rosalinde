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


tt_r_btab : libs r_brok_svc r_btab_svc $(AE10)/src/btab/tt_r_btab.o
	$(CC) $(CFLAGS) $(LIBS) -L$(LIBDIR) $(AE10)/src/btab/tt_r_btab.o -o../exe/$@ -lutil -lbtab_rpc_clnt -lknde_rpc_clnt -ladrs_local -lotab_local -lsadm_local -lbrok_rpc_clnt $(LDLIBS)

$(AE10)/src/btab/tt_r_btab.o : $(AE10)/src/btab/tt_btab.c
	$(CC) $(CFLAGS) $(INCLUDE) -DBTAB_PROXY -c $(AE10)/src/btab/tt_btab.c -o $(AE10)/src/btab/tt_r_btab.o -lutil

