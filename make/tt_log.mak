# -----------------------------------------------------------------------
#	Dateiname:		$RCSfile: tt_log.mak,v $								
#	Version:		$Revision: 1 $									
#	Erstellt am:	00.00.96											
#	Geaendert am:	$Date: 4/13/97 1:18p $							
#	Komponente:		UTIL LOG										
#	Erstellt von:	Johannes Weigend
#	Geandert von:	$Author: Hannes $										
#	Copyright:		Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
#	Bemerkung:		Tabstop = 4												
# ------------------------------------------------------------------------

tt_log : $(ROSA)/src/util/log/tt_log.o
	$(CC) $(CFLAGS) -L$(LIBDIR) $(ROSA)/src/util/log/tt_log.o -lutil $(LIBS) $(LDLIBS)
	mv a.out ../exe/$@ 

$(ROSA)/src/util/log/tt_log.o : $(ROSA)/src/util/log/tt_log.c
	$(CC) $(CFLAGS) -DLOCAL -I$(INCLUDE) -I$(ROSA)/include $< -c -o $@

