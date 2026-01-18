# -----------------------------------------------------------------------
#	Dateiname:		$RCSfile: Makefile $									
#	Version:		$Revision: 1 $									
#	Erstellt am:	00.00.96											
#	Geaendert am:	$Date: 4/13/97 1:18p $							
#	Komponente:		GLOB											
#	Erstellt von:	Johannes Weigend
#	Geandert von:	$Author: Hannes $										
#	Copyright:		Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
#	Bermerkung:		Tabstop = 4												
# ------------------------------------------------------------------------

# Usage:
# make server : Makes only server_main - Programms
# make clients: Testclients
# make rpc    : Server and Clients
# make tt     : local Tests 
# make dlg    : Rosa Dialog-Program (TCL/TK)
# make all    : Everything
# make data   : Test-Data


include lib.mak
include tt_r_knde.mak
include tt_knde.mak
include tt_knto.mak
include tt_r_knto.mak
include tt_r_btab.mak
include tt_btab.mak
include tt_otab.mak
include tt_brok.mak
include tt_r_brok.mak
include tt_gen.mak
include tt_knde_knto.mak
include tt_r_knde_knto.mak
include tt_strg.mak
include tt_hash.mak
include tt_list.mak
include tt_log.mak
include tt_misc.mak
include test_data.mak

#
#	make all (makes everything for normal use)
#
all :  libs clients server dlg data
	@echo Done. \(ALL\)

#
#	make rpc (makes only networking components)
#
rpc : clients server

#
#	make local (makes local stuff) 
#
local : local_libs tt

#
# Testtreiber (Programs for systemtesting) (make tt)
#
tt : libs tt_otab tt_btab tt_knde tt_brok tt_knto tt_knde_knto gen tt_strg tt_hash tt_list tt_log tt_misc

#
# Test-Daten
#
data: test_data_de test_data_fr


#
#  Dialog Client 
#
dlg : dlg_libs 
	@$(MAKE) -C ../src/rosa all

#
#  Clients without Dialog
#	 

clients : client_libs local_libs tt_r_knde tt_r_btab tt_r_knto tt_r_knde_knto

#
#  Server
#

server : server_libs client_libs local_libs r_knde_svc r_knto_svc r_btab_knde_svc r_btab_knto_svc r_brok_svc


#
# clean
#

clean :
	find $(ROSA)/* -name '*.o' -exec rm {} \;
	find $(ROSA)/* -name '*~' -exec rm {} \;
	find $(ROSA)/* -name '*%'  -exec rm {} \;
	find $(ROSA)/* -name '*.bak' -exec rm {} \;
	find $(ROSA)/* -name '*.proj' -exec rm {} \;
	find $(ROSA)/* -name '.sniffdir' -exec rm -rf {} \;
	find $(ROSA)/* -name '.sb' -exec rm -rf {} \;
	find $(ROSA)/* -name '*.DAT' -exec rm -rf {} \;
	find $(ROSA)/* -name '*.log' -exec rm -rf {} \;
	rm -f $(LIBDIR)/*.a
	rm -f $(ROSA)/exe/*
	rm -f $(ROSA)/gen/gen
	@$(MAKE) -C $(ROSA)/src/rosa clean

