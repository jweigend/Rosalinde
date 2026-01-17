# -----------------------------------------------------------------------
#	Dateiname:		$RCSfile: tt_knde.mak,v $								
#	Version:		$Revision: 1 $									
#	Erstellt am:	00.00.96											
#	Geaendert am:	$Date: 4/13/97 1:18p $							
#	Komponente:		GLOB											
#	Erstellt von:	Johannes Weigend
#	Geandert von:	$Author: Hannes $										
#	Copyright:		Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
#	Bermerkung:		Tabstop = 4												
# ------------------------------------------------------------------------


KNDE_FILES = $(ROSA)/src/adt/knde/knde.o \
             $(ROSA)/src/adt/knde/tt_knde.o

tt_knde : $(KNDE_FILES)
	$(CC) $(CFLAGS) -L$(LIBDIR) $(KNDE_FILES) -lbtab_local -lotab_local -lutil -lsadm_local -lbrok_local -llocal -ladrs_local -ldbms_local -lknto_local $(LIBS) 
	mv a.out ../exe/$@ 


$(ROSA)/src/adt/knde/tt_knde.o : $(ROSA)/src/adt/knde/tt_knde.c
	$(CC) $(CFLAGS) $(INCLUDE) -DLOCAL -c $(ROSA)/src/adt/knde/tt_knde.c -o $@
