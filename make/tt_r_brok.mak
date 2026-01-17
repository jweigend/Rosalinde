# -----------------------------------------------------------------------
#	Dateiname:		$RCSfile: tt_brok_rpc.mak,v $									
#	Version:		$Revision: 1 $									
#	Erstellt am:	00.00.96											
#	Geaendert am:	$Date: 4/13/97 1:19p $							
#	Komponente:		GLOB											
#	Erstellt von:	Johannes Weigend
#	Geandert von:	$Author: Hannes $										
#	Copyright:		Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
#	Bermerkung:		Tabstop = 4												
# ------------------------------------------------------------------------


r_brok_svc : $(ROSA)/src/brok/r_brok_svc.o
	$(CC) $(CFLAGS) $(LIBS) -L$(LIBDIR) $(ROSA)/src/brok/r_brok_svc.o -lbrok_rpc_server -lutil $(LDLIBS)
	mv a.out ../exe/$@ 



