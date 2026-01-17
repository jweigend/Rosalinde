/* ------------------------------------------------------------------------
|	Dateiname:		$RCSfile: rosa.c,v $											
|	Version:		$Revision: 1 $										
|	Erstellt am:	00.00.96												
|	Geaendert am:	$Date: 19.11.97 9:36 $											
|	Komponente:		DLG												
|	Erstellt von:	Christian Stoellinger												
|	Geandert von:	$Author: Johannes $												
|	Copyright:		Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
|	Bermerkung:		Tabstop = 4												
---------------------------------------------------------------------------*/


#ifndef lint
static char sccsid[] = "@(#) tkAppInit.c 1.15 95/06/28 13:14:28";
#endif /* not lint */

#include "tk.h"
#include "tcl_dlg.h"

#include "dlg_main.h"
#include "dlg_pfku.h"
#include "dlg_admi.h"
#include "dlg_pfko.h"
#include "dlg_skto.h"
#include "dlg_sbro.h"

#include "sadm.h"
#include "btab.h"
#include "ctab.h"
#include "knde.h"


ENABLE_ERROR_HANDLING;

char * brokerhost;

#ifdef LOCAL
btab* knde_database;
#endif

/*
 * The following variable is a special hack that is needed in order for
 * Sun shared libraries to be used for Tcl.
 */

#ifdef NEED_MATHERR
extern int matherr();
int *tclDummyMathPtr = (int *) matherr;
#endif

/*
 *----------------------------------------------------------------------
 *
 * main --
 *
 *	This is the main program for the application.
 *
 * Results:
 *	None: Tk_Main never returns here, so this procedure never
 *	returns either.
 *
 * Side effects:
 *	Whatever the application does.
 *
 *----------------------------------------------------------------------
 */

char* broker;

int
main(argc, argv)
    int argc;			/* Number of command-line arguments. */
    char **argv;		/* Values of command-line arguments. */
{
    if (argc!=3) 
    {
    	LOG("Broker mu� angegeben werden!\n");
    	exit(-1);
    }
    broker = argv[2];
    /* Adjust argc and argv for Tk_Main: pass program name and startup script */
    /* argv[0] = program name, argv[1] = startup script (rosa.tk) */
    argv[1] = "rosa.tk";
    argc = 2;
    Tk_Main(argc, argv, Tcl_AppInit);
    return 0;			/* Needed only to prevent compiler warning. */
}

/*
 *----------------------------------------------------------------------
 *
 * Tcl_AppInit --
 *
 *	This procedure performs application-specific initialization.
 *	Most applications, especially those that incorporate additional
 *	packages, will have their own version of this procedure.
 *
 * Results:
 *	Returns a standard Tcl completion code, and leaves an error
 *	message in interp->result if an error occurs.
 *
 * Side effects:
 *	Depends on the startup script.
 *
 *----------------------------------------------------------------------
 */

int
Tcl_AppInit(interp)
    Tcl_Interp *interp;		/* Interpreter for application. */
{
    Tk_Window main;

    if (Tcl_Init(interp) == TCL_ERROR) {
	return TCL_ERROR;
    }
    if (Tk_Init(interp) == TCL_ERROR) {
	return TCL_ERROR;
    }

    /*
     * Call the init procedures for included packages.  Each call should
     * look like this:
     *
     * if (Mod_Init(interp) == TCL_ERROR) {
     *     return TCL_ERROR;
     * }
     *
     * where "Mod" is the name of the module.
     */

    /*
     * Call Tcl_CreateCommand for application-specific commands, if
     * they weren't already created by the init procedures called above.
     */
     
/***************************************************************************/
/* HIER SIND DIE EIGENEN KOMMANDOS */


sadm_init(broker);

/* Fuer den Dialog Broker-Auswahl */
strcpy(der_broker_host, broker);

#ifdef LOCAL
knde_database = btab_new();
btab_open(knde_database, "KNDE.DAT", KNDE_DB_RECORDLENGTH, 100);
#endif

ctab_init();

    Tcl_CreateCommand(interp, "DIALOG", (Tcl_CmdProc*)TCL_Dialog_cmd, (ClientData)NULL, (Tcl_CmdDeleteProc*)NULL);

RegisterDLGProc("MAIN",  DLGProc_Main);
RegisterDLGProc("PFKU",  DLGProc_PflegeKunde);
RegisterDLGProc("ADMIN", DLGProc_Administration);
RegisterDLGProc("PFKO",  DLGProc_PflegeKonto);
RegisterDLGProc("SKTO",  DLGProc_SucheKonto);
RegisterDLGProc("SBRO",  DLGProc_SelectBroker);


/****************************************************************************/

    /*
     * Specify a user-specific startup file to invoke if the application
     * is run interactively.  Typically the startup file is "~/.apprc"
     * where "app" is the name of the application.  If this line is deleted
     * then no user-specific startup file will be run under any conditions.
     */

    /* modern Tcl may not export tcl_RcFileName symbol; set rc filename via Tcl variable */
    Tcl_SetVar(interp, "tcl_rcFileName", "~/.wishrc", TCL_GLOBAL_ONLY);
    return TCL_OK;
}
