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


tt_knde_knto : $(ROSA)/src/adt/knto/tt_knde_knto.o
	$(CC) $(CFLAGS) -L$(LIBDIR) $(ROSA)/src/adt/knto/tt_knde_knto.o -lotab_local -lutil -lsadm_local -lbrok_local -llocal -ladrs_local -ldbms_local -lknto_local -lknde_local -lbtab_local $(LIBS) $(LDLIBS) 
	mv a.out ../exe/$@


