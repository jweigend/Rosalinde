# -----------------------------------------------------------------------
#	Dateiname:		$RCSfile: env.mak,v $									
#	Version:		$Revision: 1 $									
#	Erstellt am:	00.00.96											
#	Geaendert am:	$Date: 4/13/97 1:18p $							
#	Komponente:		GLOB											
#	Erstellt von:	Johannes Weigend
#	Geandert von:	$Author: Hannes $										
#	Copyright:		Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
#	Bermerkung:		Tabstop = 4												
# ------------------------------------------------------------------------


#
# ROOT - Directory (automatically determined)

# Set ROSA to the project root directory
# This file is located in the make/ subdirectory, so we go one level up
# $(dir $(abspath $(firstword $(MAKEFILE_LIST)))) gets the directory of this file
# Using $(abspath ...) ensures we handle both absolute and relative paths
# The patsubst removes any trailing slash
ROSA = $(patsubst %/,%,$(abspath $(dir $(lastword $(MAKEFILE_LIST)))..))

LIBDIR 	= $(ROSA)/lib

#TCL_LIBDIR = $(LIBDIR) -L /usr/lib -L /usr/X11R6/lib
TCL_LIBDIR = $(LIBDIR) -L/usr/local/lib -L/usr/openwin/lib


INCLUDE = . -I$(ROSA)/include

#TCL_INCLUDE = $(INCLUDE) -I/usr/include/tcl
TCL_INCLUDE = $(INCLUDE) -I/usr/local/include -I/usr/openwin/include 
# ------------------------------------------------------------------------

#
# TOOLS
#

# ------------------------------------------------------------------------

#
# C-Compiler
#
#CC 	= purify cc 
# Use gcc on modern Linux hosts for better diagnostics
CC		= gcc

# -D_DEBUG fuer Memory-Debugging
# -DRPC_SVC_FG  fuer SUN Foreground process
CFLAGS 	= -g -DRPC_SVC_FG

#
# Librarian
#
AR		= ar

ARFLAGS = r

# Static - libs
LIBS 	=

TCL_LIBS =  $(LIBS) -ltk8.6 -ltcl8.6 -lX11 -lm 
#TCL_LIBS = -ltk -ltcl -lX11 -lm
# ------------------------------------------------------------------------

#
# Suffix Rules
#
.c.o :
	$(CC) $(CFLAGS) -I$(TCL_INCLUDE) -c $< -o $@

.a:
	$(AR) $(ARFLAGS) $@ $<


CFLAGS += -I/usr/include/tirpc
LDLIBS += -ltirpc

CFLAGS += -I/usr/include/tcl8.6
LDLIBS += -ltk8.6 -ltcl8.6


# Ensure legacy $(LIBS) includes modern LDLIBS (e.g. -ltirpc)
LIBS += $(LDLIBS)
# ------------------------------------------------------------------------
