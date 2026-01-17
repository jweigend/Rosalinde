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


gen : $(ROSA)/gen/gen.o 
	$(CC) $(CFLAGS) -L$(LIBDIR) $(ROSA)/gen/gen.o -lknde_local -ldbms_local -lsadm_local -lbtab_local -lotab_local -lutil -lbrok_local -llocal -ladrs_local -lknto_local $(LIBS) 
	mv a.out ../gen/gen
