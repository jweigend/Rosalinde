# -----------------------------------------------------------------------
#	Dateiname:		$RCSfile: tt_knde.mak,v $								
#	Version:		$Revision: 1 $									
#	Erstellt am:	00.00.96											
#	Geaendert am:	$Date: 4/13/97 1:19p $							
#	Komponente:		GLOB											
#	Erstellt von:	Johannes Weigend
#	Geandert von:	$Author: Hannes $										
#	Copyright:		Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
#	Bermerkung:		Tabstop = 4												
# ------------------------------------------------------------------------


TEST_DATA_DE_FILES = $(ROSA)/src/adt/knde/knde.o \
                     $(ROSA)/src/adt/knto/knto.o \
                     $(ROSA)/src/data/test_data_de.o

TEST_DATA_FR_FILES = $(ROSA)/src/adt/knde/knde.o \
                     $(ROSA)/src/adt/knto/knto.o \
                     $(ROSA)/src/data/test_data_fr.o


test_data_de : $(TEST_DATA_DE_FILES)
	$(CC) $(CFLAGS) -L$(LIBDIR) $(TEST_DATA_DE_FILES) -lbtab_local -lotab_local -lutil -lsadm_local -lbrok_local -llocal -ladrs_local -ldbms_local -lknto_local $(LIBS) 
	mv a.out ../exe/$@ 

test_data_fr : $(TEST_DATA_FR_FILES)
	$(CC) $(CFLAGS) -L$(LIBDIR) $(TEST_DATA_FR_FILES) -lbtab_local -lotab_local -lutil -lsadm_local -lbrok_local -llocal -ladrs_local -ldbms_local -lknto_local $(LIBS) 
	mv a.out ../exe/$@ 

$(ROSA)/src/data/test_data_de.o : $(ROSA)/src/data/test_data_de.c
	$(CC) $(CFLAGS) $(INCLUDE) -DLOCAL -c $(ROSA)/src/data/test_data_de.c -o $@

$(ROSA)/src/data/test_data_fr.o : $(ROSA)/src/data/test_data_fr.c
	$(CC) $(CFLAGS) $(INCLUDE) -DLOCAL -c $(ROSA)/src/data/test_data_fr.c -o $@