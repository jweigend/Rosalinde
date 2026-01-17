# -----------------------------------------------------------------------
#	Dateiname:		$RCSfile: tt_brok.mak,v $								
#	Version:		$Revision: 1 $									
#	Erstellt am:	00.00.96											
#	Geaendert am:	$Date: 4/13/97 1:18p $							
#	Komponente:		GLOB											
#	Erstellt von:	Johannes Weigend
#	Geandert von:	$Author: Hannes $										
#	Copyright:		Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
#	Bermerkung:		Tabstop = 4												
# ------------------------------------------------------------------------

tt_brok : $(ROSA)/src/brok/tt_brok.o
	$(CC) $(CFLAGS) -L$(LIBDIR)  $(ROSA)/src/brok/tt_brok.o -lbrok_local -lutil
	mv a.out ../exe/tt_brok 
