# -----------------------------------------------------------------------
#	Dateiname:		$RCSfile: tt_hash.mak,v $								
#	Version:		$Revision: 1 $									
#	Erstellt am:	00.00.96											
#	Geaendert am:	$Date: 4/13/97 1:18p $							
#	Komponente:		UTIL HASH										
#	Erstellt von:	Johannes Weigend
#	Geandert von:	$Author: Hannes $										
#	Copyright:		Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
#	Bermerkung:		Tabstop = 4												
# ------------------------------------------------------------------------

tt_hash : $(ROSA)/src/util/hash/tt_hash.o
	$(CC) $(CFLAGS) -L$(LIBDIR) $(ROSA)/src/util/hash/tt_hash.o -lutil $(LIBS) $(LDLIBS)
	mv a.out ../exe/$@ 

$(ROSA)/src/util/hash/tt_hash.o : $(ROSA)/src/util/hash/tt_hash.c
	$(CC) $(CFLAGS) -DLOCAL -I$(INCLUDE) -I$(ROSA)/include $< -c -o $@

