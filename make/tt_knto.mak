# -----------------------------------------------------------------------
#	Dateiname:		$RCSfile: tt_knto.mak,v $								
#	Version:		$Revision: 1 $									
#	Erstellt am:	00.00.96											
#	Geaendert am:	$Date: 4/13/97 1:18p $							
#	Komponente:		GLOB											
#	Erstellt von:	Johannes Weigend
#	Geandert von:	$Author: Hannes $										
#	Copyright:		Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
#	Bermerkung:		Tabstop = 4												
# ------------------------------------------------------------------------


KNTO_FILES = $(ROSA)/src/adt/knto/knto.o \
             $(ROSA)/src/adt/knto/tt_knto.o

tt_knto : $(KNTO_FILES)
	$(CC) $(CFLAGS) -L$(LIBDIR) $(KNTO_FILES) -lbtab_local -lotab_local -lsadm_local -lbrok_local -llocal -ldbms_local -lknde_local -lknto_local -ladrs_local -lutil $(LIBS) $(LDLIBS) 
	mv a.out ../exe/$@ 


$(ROSA)/src/adt/knto/tt_knto.o : $(ROSA)/src/adt/knto/tt_knto.c
	$(CC) $(CFLAGS) $(INCLUDE) -DLOCAL -c $(ROSA)/src/adt/knto/tt_knto.c -o $@
