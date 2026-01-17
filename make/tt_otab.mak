# -----------------------------------------------------------------------
#	Dateiname:		$RCSfile: tt_otab.mak,v $								
#	Version:		$Revision: 1 $									
#	Erstellt am:	00.00.96											
#	Geaendert am:	$Date: 4/13/97 1:18p $							
#	Komponente:		GLOB											
#	Erstellt von:	Johannes Weigend
#	Geandert von:	$Author: Hannes $										
#	Copyright:		Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
#	Bermerkung:		Tabstop = 4												
# ------------------------------------------------------------------------

tt_otab : $(ROSA)/src/otab/tt_otab.o
	$(CC) $(CFLAGS) -L$(LIBDIR) $(ROSA)/src/otab/tt_otab.o -lotab_local -lutil 
	mv a.out ../exe/$@ 

