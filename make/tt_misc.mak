# -----------------------------------------------------------------------
#	Dateiname:		$RCSfile: tt_misc.mak,v $								
#	Version:		$Revision: 1 $									
#	Erstellt am:	00.00.96											
#	Geaendert am:	$Date: 4/13/97 1:18p $							
#	Komponente:		UTIL MISC										
#	Erstellt von:	Johannes Weigend
#	Geandert von:	$Author: Hannes $										
#	Copyright:		Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
#	Bemerkung:		Tabstop = 4												
# ------------------------------------------------------------------------

tt_misc : $(ROSA)/src/util/misc/tt_misc.o
	$(CC) $(CFLAGS) -L$(LIBDIR) $(ROSA)/src/util/misc/tt_misc.o -lutil $(LIBS) $(LDLIBS)
	mv a.out ../exe/$@ 

$(ROSA)/src/util/misc/tt_misc.o : $(ROSA)/src/util/misc/tt_misc.c
	$(CC) $(CFLAGS) -DLOCAL -I$(INCLUDE) -I$(ROSA)/include $< -c -o $@

