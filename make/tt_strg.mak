# -----------------------------------------------------------------------
#	Dateiname:		$RCSfile: tt_strg.mak,v $								
#	Version:		$Revision: 1 $									
#	Erstellt am:	00.00.96											
#	Geaendert am:	$Date: 4/13/97 1:18p $							
#	Komponente:		UTIL STRG										
#	Erstellt von:	Johannes Weigend
#	Geandert von:	$Author: Hannes $										
#	Copyright:		Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
#	Bermerkung:		Tabstop = 4												
# ------------------------------------------------------------------------

tt_strg : $(ROSA)/src/util/strg/tt_strg.o
	$(CC) $(CFLAGS) -L$(LIBDIR) $(ROSA)/src/util/strg/tt_strg.o -lutil $(LIBS) $(LDLIBS)
	mv a.out ../exe/$@ 

$(ROSA)/src/util/strg/tt_strg.o : $(ROSA)/src/util/strg/tt_strg.c
	$(CC) $(CFLAGS) -DLOCAL -I$(INCLUDE) -I$(ROSA)/include $< -c -o $@

