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

tt_btab : $(ROSA)/src/btab/tt_btab.o
	$(CC) $(CFLAGS) -L$(LIBDIR) $(ROSA)/src/btab/tt_btab.o -lbtab_local -lsadm_local -lbrok_local -lutil $(LIBS) $(LDLIBS)
	mv a.out ../exe/$@ 

$(ROSA)/src/btab/tt_btab.o : $(ROSA)/src/btab/tt_btab.c
	$(CC) $(CFLAGS) -DLOCAL -I$(INCLUDE) $< -c -o $@
