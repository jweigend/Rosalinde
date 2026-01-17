# -----------------------------------------------------------------------
#	Dateiname:		$RCSfile:  $									
#	Version:		$Revision: 1 $									
#	Erstellt am:	00.00.96											
#	Geaendert am:	$Date: 4/13/97 1:19p $							
#	Komponente:		GLOB											
#	Erstellt von:	
#	Geandert von:	$Author: Hannes $										
#	Copyright:		Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
#	Bermerkung:		Tabstop = 4												
# ------------------------------------------------------------------------

include ../../make/env.mak


#-------------------------------------------------------------------------
# main-Programme
#-------------------------------------------------------------------------

rosa_local	: dlg_sbro.o dlg_main.o dlg_pfku.o dlg_admi.o dlg_pfko.o dlg_skto.o rosa.c
	$(CC) $(CFLAGS) -DLOCAL -I$(TCL_INCLUDE) -L$(TCL_LIBDIR) dlg_sbro.o dlg_pfko.o dlg_skto.o dlg_main.o dlg_pfku.o dlg_admi.o rosa.c -o $@ -ltcl_dlg -lotab_local -lbtab_local -lsadm_local -lbrok_local -lknde_local -lknto_local -llocal -ladrs_local -lutil -ldbms_local $(TCL_LIBS) $(LDLIBS)

rosa_rpc	: dlg_sbro.o dlg_main.o dlg_pfku_prx.o dlg_admi.o dlg_pfko.o dlg_skto.o rosa.c
	$(CC) $(CFLAGS) -I$(TCL_INCLUDE) -L$(TCL_LIBDIR) dlg_sbro.o dlg_main.o dlg_pfko.o dlg_skto.o dlg_pfku_prx.o dlg_admi.o rosa.c -o $@  -ltcl_dlg -lutil -lotab_local -lbtab_rpc_clnt -lsadm_rpc -lbrok_rpc_clnt -lknde_rpc_clnt -lknto_rpc_clnt -ladrs_local -lcmgr_local -ldbms_rpc_clnt -lutil $(TCL_LIBS) $(LDLIBS)


#-------------------------------------------------------------------------
# Dialoge
#-------------------------------------------------------------------------

dlg_main.o	: dlg_main.c $(ROSA)/include/dlg_main.h
	$(CC) $(CFLAGS) -I$(TCL_INCLUDE) -DLOCAL -c dlg_main.c -o dlg_main.o

dlg_pfku.o	: dlg_pfku.c $(ROSA)/include/dlg_pfku.h
	$(CC) $(CFLAGS) -I$(TCL_INCLUDE) -DLOCAL -c dlg_pfku.c -o dlg_pfku.o

dlg_admi.o	: dlg_admi.c $(ROSA)/include/dlg_admi.h
	$(CC) $(CFLAGS) -I$(TCL_INCLUDE) -c dlg_admi.c -o dlg_admi.o

dlg_pfko.o	: dlg_pfko.c $(ROSA)/include/dlg_pfko.h
	$(CC) $(CFLAGS) -I$(TCL_INCLUDE) -c dlg_pfko.c -o dlg_pfko.o

dlg_skto.o	: dlg_skto.c $(ROSA)/include/dlg_skto.h
	$(CC) $(CFLAGS) -I$(TCL_INCLUDE) -c dlg_skto.c -o dlg_skto.o

dlg_sbro.o	: dlg_sbro.c $(ROSA)/include/dlg_sbro.h
	$(CC) $(CFLAGS) -I$(TCL_INCLUDE) -c dlg_sbro.c -o dlg_sbro.o

dlg_pfku_prx.o	: dlg_pfku.c $(ROSA)/include/dlg_pfku.h
	$(CC) $(CFLAGS) -I$(TCL_INCLUDE) -DKNDE_PROXY -DKNTO_PROXY -DBTAB_PROXY -c dlg_pfku.c -o $@


#------------------------------------------------------------------------
# Sonstiges
#------------------------------------------------------------------------

all	: rosa_local rosa_rpc

clean	:
	rm -f a.out *.o rosa_local rosa_rpc
