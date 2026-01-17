# -----------------------------------------------------------------------
#	Dateiname:		$RCSfile: lib.mak,v $									
#	Version:		$Revision: 1 $									
#	Erstellt am:	00.00.96											
#	Geaendert am:	$Date: 4/13/97 1:18p $							
#	Komponente:		GLOB											
#	Erstellt von:	Johannes Weigend
#	Geandert von:	$Author: Hannes $										
#	Copyright:		Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
#	Bermerkung:		Tabstop = 4												
# ------------------------------------------------------------------------


include env.mak

# ranlib fuer alte SUN-Versionen

libs : server_libs client_libs local_libs dlg_libs
	ranlib ../lib/*

server_libs : dbms_rpc_server brok_rpc_server btab_rpc_server knde_rpc_server knto_rpc_server sadm_rpc
	ranlib ../lib/*

client_libs : dbms_rpc_clnt brok_rpc_clnt btab_rpc_clnt knde_rpc_clnt knto_rpc_clnt sadm_rpc
	ranlib ../lib/*

dlg_libs : tcl_dlg
	ranlib ../lib/*

local_libs : util brok_local sadm_local otab_local btab_local local_local cmgr_local knde_local adrs_local knto_local dbms_local
	ranlib ../lib/*


brok : brok_local brok_rpc_clnt brok_rpc_server

btab : btab_local btab_rpc_clnt btab_rpc_server

knde : knde_local knde_rpc_clnt knde_rpc_server

knto : knto_local knto_rpc_clnt knto_rpc_server

dbms : dbms_local dbms_rpc_clnt dbms_rpc_server

sadm : sadm_local sadm_rpc

otab : otab_local

cmgr : cmgr_local

adrs : adrs_local

UTIL_LIB = $(ROSA)/src/util/list/list.o			\
           $(ROSA)/src/util/strg/strg.o			\
           $(ROSA)/src/util/hash/hash.o			\
           $(ROSA)/src/util/log/log.o			\
		   $(ROSA)/src/util/misc/misc.o 		\
		   $(ROSA)/src/util/mmgr/mmgr.o			\
		   $(ROSA)/src/util/enum/enum.o			
 
BROK_RPC_CLNT_LIB =								\
           $(ROSA)/src/brok/bent.o				\
           $(ROSA)/src/brok/brok_clnt.o			\
           $(ROSA)/src/brok/r_brok_clnt.o		\
           $(ROSA)/src/brok/r_brok_xdr.o

BROK_RPC_SERVER_LIB =							\
           $(ROSA)/src/brok/brok.o				\
           $(ROSA)/src/brok/bent.o				\
           $(ROSA)/src/brok/r_brok.o			\
           $(ROSA)/src/brok/r_brok_xdr.o		\
	       $(ROSA)/src/brok/r_brok_svc.o		\
		   $(ROSA)/src/brok/r_brok_svc_main.o 

BROK_LOCAL_LIB =								\
           $(ROSA)/src/brok/brok.o				\
           $(ROSA)/src/brok/bent.o     

OTAB_LOCAL_LIB =								\
		   $(ROSA)/src/otab/oent.o				\
           $(ROSA)/src/otab/otab.o				\
           $(ROSA)/src/pkrn/pkrn.o				\
		   $(ROSA)/src/otab/cent.o				\
		   $(ROSA)/src/otab/ctab.o				

SADM_LOCAL_LIB =								\
		   $(ROSA)/src/sadm/sadm.o				\
		   $(ROSA)/src/sadm/sent.o	
SADM_RPC_LIB =									\
		   $(ROSA)/src/sadm/sadm_rpc.o 			\
		   $(ROSA)/src/sadm/sent.o

BTAB_LOCAL_LIB =								\
		   $(ROSA)/src/btab/btab.o  

BTAB_RPC_CLNT_LIB =								\
		   $(ROSA)/src/btab/btab_clnt_prx.o		\
	       $(ROSA)/src/btab/r_btab_clnt_prx.o	\
           $(ROSA)/src/btab/r_btab_xdr_prx.o    
			
BTAB_RPC_SERVER_LIB =							\
		   $(ROSA)/src/btab/btab.o				\
		   $(ROSA)/src/btab/r_btab.o			\
		   $(ROSA)/src/btab/r_btab_svc.o		\
	       $(ROSA)/src/btab/r_btab_xdr.o	    \
		   $(ROSA)/src/btab/r_btab_svc_main.o   

KNDE_RPC_CLNT_LIB =								\
           $(ROSA)/src/adt/knde/knde_clnt_prx.o	\
           $(ROSA)/src/adt/knde/r_knde_clnt_prx.o\
           $(ROSA)/src/adt/knde/r_knde_xdr_prx.o

KNDE_RPC_SERVER_LIB =							\
           $(ROSA)/src/adt/knde/knde_btab_prx.o	\
           $(ROSA)/src/adt/knde/r_knde.o		\
           $(ROSA)/src/adt/knde/r_knde_xdr.o    \
		   $(ROSA)/src/adt/knde/r_knde_svc.o    \
		   $(ROSA)/src/adt/knde/r_knde_svc_main.o	

KNDE_LOCAL_LIB =								\
           $(ROSA)/src/adt/knde/knde.o        

LOCAL_LIB =                                     \
		   $(ROSA)/src/local/local.o

CMGR_LOCAL_LIB =                                \
		   $(ROSA)/src/cmgr/cmgr.o

TCL_DLG_LIB =                                   \
		   $(ROSA)/src/tk/tcl_dlg.o    

ADRS_LOCAL_LIB =								\
		   $(ROSA)/src/adt/adrs/adrs.o          


KNTO_RPC_CLNT_LIB =								\
           $(ROSA)/src/adt/knto/knto_clnt_prx.o	\
           $(ROSA)/src/adt/knto/r_knto_clnt_prx.o\
           $(ROSA)/src/adt/knto/r_knto_xdr_prx.o

KNTO_RPC_SERVER_LIB =							\
           $(ROSA)/src/adt/knto/knto_btab_prx.o	\
           $(ROSA)/src/adt/knto/r_knto.o		\
           $(ROSA)/src/adt/knto/r_knto_xdr.o    \
		   $(ROSA)/src/adt/knto/r_knto_svc.o    \
		   $(ROSA)/src/adt/knto/r_knto_svc_main.o

KNTO_LOCAL_LIB =								\
           $(ROSA)/src/adt/knto/knto.o        

DBMS_LOCAL_LIB =								\
		   $(ROSA)/src/dbms/dbms.o

DBMS_RPC_SERVER_LIB =							\
		   $(ROSA)/src/dbms/r_dbms.o			\
		   $(ROSA)/src/dbms/dbms.o				

DBMS_RPC_CLNT_LIB =								\
		   $(ROSA)/src/dbms/dbms_clnt.o

#
# PROXYS muessen mit -DADT_PROXY uebersetzt werden !
#

#
# BTAB - Proxys
#
$(ROSA)/src/btab/btab_clnt_prx.o : $(ROSA)/src/btab/btab_clnt.c 
	$(CC) $(CFLAGS) -DBTAB_PROXY -I$(INCLUDE) -c $(ROSA)/src/btab/btab_clnt.c -o $(ROSA)/src/btab/btab_clnt_prx.o

$(ROSA)/src/btab/r_btab_clnt_prx.o : $(ROSA)/src/btab/r_btab_clnt.c
	$(CC) $(CFLAGS) -DBTAB_PROXY -I$(INCLUDE) -c $(ROSA)/src/btab/r_btab_clnt.c -o $(ROSA)/src/btab/r_btab_clnt_prx.o

$(ROSA)/src/btab/r_btab_xdr_prx.o : $(ROSA)/src/btab/r_btab_xdr.c
	$(CC) $(CFLAGS) -DBTAB_PROXY -I$(INCLUDE) -c $(ROSA)/src/btab/r_btab_xdr.c -o $(ROSA)/src/btab/r_btab_xdr_prx.o

#
# KNDE - Proxys
#
# client

$(ROSA)/src/adt/knde/knde_clnt_prx.o : $(ROSA)/src/adt/knde/knde_clnt.c 
	$(CC) $(CFLAGS) -DKNDE_PROXY -DKNTO_PROXY -I$(INCLUDE) -c $(ROSA)/src/adt/knde/knde_clnt.c -o $@

$(ROSA)/src/adt/knde/r_knde_clnt_prx.o : $(ROSA)/src/adt/knde/r_knde_clnt.c
	$(CC) $(CFLAGS) -DKNDE_PROXY -DKNTO_PROXY -I$(INCLUDE) -c $(ROSA)/src/adt/knde/r_knde_clnt.c -o $@

$(ROSA)/src/adt/knde/r_knde_xdr_prx.o : $(ROSA)/src/adt/knde/r_knde_xdr.c
	$(CC) $(CFLAGS) -DKNDE_PROXY -DKNTO_PROXY -I$(INCLUDE) -c $(ROSA)/src/adt/knde/r_knde_xdr.c -o $@

# server

$(ROSA)/src/adt/knde/knde_btab_prx.o : $(ROSA)/src/adt/knde/knde.c
	$(CC) $(CFLAGS) -DBTAB_PROXY -DKNTO_PROXY -I$(INCLUDE) -c $(ROSA)/src/adt/knde/knde.c -o $@

$(ROSA)/src/adt/knde/r_knde.o : $(ROSA)/src/adt/knde/r_knde.c
	$(CC) $(CFLAGS) -DKNTO_PROXY -I$(INCLUDE) -c $(ROSA)/src/adt/knde/r_knde.c -o $@

#
# KNTO - Proxys
#
# client 

$(ROSA)/src/adt/knto/knto_clnt_prx.o : $(ROSA)/src/adt/knto/knto_clnt.c 
	$(CC) $(CFLAGS) -DKNTO_PROXY -DKNDE_PROXY -I$(INCLUDE) -c $(ROSA)/src/adt/knto/knto_clnt.c -o $@

$(ROSA)/src/adt/knto/r_knto_clnt_prx.o : $(ROSA)/src/adt/knto/r_knto_clnt.c
	$(CC) $(CFLAGS) -DKNTO_PROXY -DKNDE_PROXY -I$(INCLUDE) -c $(ROSA)/src/adt/knto/r_knto_clnt.c -o $@

$(ROSA)/src/adt/knto/r_knto_xdr_prx.o : $(ROSA)/src/adt/knto/r_knto_xdr.c
	$(CC) $(CFLAGS) -DKNTO_PROXY -DKNDE_PROXY -I$(INCLUDE) -c $(ROSA)/src/adt/knto/r_knto_xdr.c -o $@

# server

$(ROSA)/src/adt/knto/knto_btab_prx.o : $(ROSA)/src/adt/knto/knto.c
	$(CC) $(CFLAGS) -DBTAB_PROXY -DKNDE_PROXY -I$(INCLUDE) -c $(ROSA)/src/adt/knto/knto.c -o $@

$(ROSA)/src/adt/knto/r_knto.o : $(ROSA)/src/adt/knto/r_knto.c
	$(CC) $(CFLAGS) -DKNDE_PROXY -I$(INCLUDE) -c $(ROSA)/src/adt/knto/r_knto.c -o $@

#
# SADM - RPC Version
#
$(ROSA)/src/sadm/sadm_rpc.o : $(ROSA)/src/sadm/sadm.c
	$(CC) $(CFLAGS) -DRPC -I$(INCLUDE) -c $(ROSA)/src/sadm/sadm.c -o $@


#
# Die libs ...
#

util : $(UTIL_LIB)
	$(AR) $(ARFLAGS) $(LIBDIR)/lib$@.a $(UTIL_LIB) 

brok_local : $(BROK_LOCAL_LIB)
	$(AR) $(ARFLAGS) $(LIBDIR)/lib$@.a $(BROK_LOCAL_LIB)

brok_rpc_clnt : $(BROK_RPC_CLNT_LIB)
	$(AR) $(ARFLAGS) $(LIBDIR)/lib$@.a $(BROK_RPC_CLNT_LIB);

brok_rpc_server : $(BROK_RPC_SERVER_LIB)
	$(AR) $(ARFLAGS) $(LIBDIR)/lib$@.a $(BROK_RPC_SERVER_LIB)

otab_local : $(OTAB_LOCAL_LIB)
	$(AR) $(ARFLAGS) $(LIBDIR)/lib$@.a $(OTAB_LOCAL_LIB)

sadm_local : $(SADM_LOCAL_LIB)
	$(AR) $(ARFLAGS) $(LIBDIR)/lib$@.a $(SADM_LOCAL_LIB)

sadm_rpc : $(SADM_RPC_LIB)
	$(AR) $(ARFLAGS) $(LIBDIR)/lib$@.a $(SADM_RPC_LIB)
 
btab_local : $(BTAB_LOCAL_LIB)
	$(AR) $(ARFLAGS) $(LIBDIR)/lib$@.a $(BTAB_LOCAL_LIB)

btab_rpc_server : $(BTAB_RPC_SERVER_LIB)
	$(AR) $(ARFLAGS) $(LIBDIR)/lib$@.a $(BTAB_RPC_SERVER_LIB)

btab_rpc_clnt : $(BTAB_RPC_CLNT_LIB)
	$(AR) $(ARFLAGS) $(LIBDIR)/lib$@.a $(BTAB_RPC_CLNT_LIB)

knde_local : $(KNDE_LOCAL_LIB)
	$(AR) $(ARFLAGS) $(LIBDIR)/lib$@.a $(KNDE_LOCAL_LIB)

knde_rpc_clnt : $(KNDE_RPC_CLNT_LIB)
	$(AR) $(ARFLAGS) $(LIBDIR)/lib$@.a $(KNDE_RPC_CLNT_LIB)

knde_rpc_server : $(KNDE_RPC_SERVER_LIB)
	$(AR) $(ARFLAGS) $(LIBDIR)/lib$@.a $(KNDE_RPC_SERVER_LIB)

local_local : $(LOCAL_LIB)
	$(AR) $(ARFLAGS) $(LIBDIR)/liblocal.a $(LOCAL_LIB)

cmgr_local : $(CMGR_LOCAL_LIB)
	$(AR) $(ARFLAGS) $(LIBDIR)/lib$@.a $(CMGR_LOCAL_LIB)

tcl_dlg : $(TCL_DLG_LIB)
	$(AR) $(ARFLAGS) $(LIBDIR)/lib$@.a $(TCL_DLG_LIB)

adrs_local : $(ADRS_LOCAL_LIB) 
	$(AR) $(ARFLAGS) $(LIBDIR)/lib$@.a $(ADRS_LOCAL_LIB)

knto_local : $(KNTO_LOCAL_LIB)
	$(AR) $(ARFLAGS) $(LIBDIR)/lib$@.a $(KNTO_LOCAL_LIB)

knto_rpc_clnt : $(KNTO_RPC_CLNT_LIB)
	$(AR) $(ARFLAGS) $(LIBDIR)/lib$@.a $(KNTO_RPC_CLNT_LIB)

knto_rpc_server : $(KNTO_RPC_SERVER_LIB)
	$(AR) $(ARFLAGS) $(LIBDIR)/lib$@.a $(KNTO_RPC_SERVER_LIB)

dbms_local : $(DBMS_LOCAL_LIB)
	$(AR) $(ARFLAGS) $(LIBDIR)/lib$@.a $(DBMS_LOCAL_LIB)

dbms_rpc_clnt : $(DBMS_RPC_CLNT_LIB)
	$(AR) $(ARFLAGS) $(LIBDIR)/lib$@.a $(DBMS_RPC_CLNT_LIB)

dbms_rpc_server : $(DBMS_RPC_SERVER_LIB)
	$(AR) $(ARFLAGS) $(LIBDIR)/lib$@.a $(DBMS_RPC_SERVER_LIB)

$(ROSA)/src/local/local.o : $(ROSA)/src/local/local.c
	$(CC) $(CFLAGS) $(INCLUDE) -DLOCAL -c $(ROSA)/src/local/local.c -o $@



