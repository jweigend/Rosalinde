/* ------------------------------------------------------------------------
|   Dateiname:      $RCSfile: dlg_main.c,v $
|   Version:        $Revision: 1 $
|   Erstellt am:    00.00.96
|   Geaendert am:   $Date: 19.11.97 9:36 $
|   Komponente:     DLG
|   Erstellt von:   Christian Stoellinger
|   Geandert von:   $Author: Johannes $
|   Copyright:      Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
|   Bermerkung:     Tabstop = 4
---------------------------------------------------------------------------*/


#include "tk.h"
#include "dlg_main.h"
#include <string.h>
#include <stdlib.h>
#include "knde.h"
#include "ctab.h"
#include "cmgr.h"

typedef struct
{
   int info;
} DLG_Main;


static int MAIN_Pflege_Kunde(HWND* hwnd)
{
   return 0;
}

static int MAIN_Pflege_Konto(HWND* hwnd)
{
   return 0;
}

static int MAIN_Server_Admin(HWND* hwnd)
{
    Tcl_EvalFile(hwnd->interp, "dlg_sknt.dlg");
    return 0;
}

static int MAIN_Auswahl_Broker(HWND* hwnd)
{
   return 0;
}

static int MAIN_Init_Dlg(HWND* hwnd)
{
   return 0;
}

static int MAIN_Destroy_Dlg(HWND* hwnd)
{
   return 0;
}

char xdr_required_nullstring = '\0';

int DLGProc_Main(HWND* hwnd, char* msg, void* param)
{
    if (strcmp(msg, "pflege_kunde")==0)    MAIN_Pflege_Kunde(hwnd);
    if (strcmp(msg, "pflege_konto")==0)    MAIN_Pflege_Konto(hwnd);
    if (strcmp(msg, "server_admin")==0)    MAIN_Server_Admin(hwnd);
    if (strcmp(msg, "select_broker")==0)   MAIN_Auswahl_Broker(hwnd);
    if (strcmp(msg, DLG_INIT)==0)          MAIN_Init_Dlg(hwnd);
    if (strcmp(msg, DLG_DESTROY)==0)       MAIN_Destroy_Dlg(hwnd);

    return 0;
}

