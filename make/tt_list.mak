# -----------------------------------------------------------------------
#	Dateiname:		$RCSfile: tt_list.mak,v $								
#	Version:		$Revision: 1 $									
#	Erstellt am:	00.00.96											
#	Geaendert am:	$Date: 4/13/97 1:18p $							
#	Komponente:		UTIL LIST										
#	Erstellt von:	Johannes Weigend
#	Geandert von:	$Author: Hannes $										
#	Copyright:		Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
#	Bemerkung:		Tabstop = 4												
# ------------------------------------------------------------------------

tt_list : $(ROSA)/src/util/list/tt_list.o
	$(CC) $(CFLAGS) -L$(LIBDIR) $(ROSA)/src/util/list/tt_list.o -lutil $(LIBS) $(LDLIBS)
	mv a.out ../exe/$@ 

$(ROSA)/src/util/list/tt_list.o : $(ROSA)/src/util/list/tt_list.c
	$(CC) $(CFLAGS) -DLOCAL -I$(INCLUDE) -I$(ROSA)/include $< -c -o $@

