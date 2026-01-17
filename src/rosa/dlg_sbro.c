/* ------------------------------------------------------------------------
|   Dateiname:      $RCSfile: dlg_admi.c,v $
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
#include "dlg_sbro.h"
#include <string.h>
#include <stdlib.h>
#include "brok.h"
#include "sadm.h"
#include "r_knde.h"
#include "dbms.h"

char der_broker_host[200];

typedef struct
{
   int irgendwas;
} DLG_Sbro;


/*---------------------------------------------------------------------------
 * Setzen der Statuszeile
 *-------------------------------------------------------------------------*/
static void Setze_Status(HWND* hwnd, char* msg)
{
    Tcl_SetVar(hwnd->interp, "stc_status", msg, 0);
}


/*---------------------------------------------------------------------------
 * Informations-Box
 *-------------------------------------------------------------------------*/
static void MessageBox(HWND* hwnd, char* head, char* msg)
{
    char* tcl_cmd;
    
    tcl_cmd = (char*)malloc(sizeof(char)*1000);
    
    sprintf(tcl_cmd, "dialog .dlg_msgbox {%s} {%s} {} {} OK", head, msg);
    Tcl_Eval(hwnd->interp, tcl_cmd);
    
    free(tcl_cmd);
}

/*---------------------------------------------------------------------------
 * Broker waehlen
 *-------------------------------------------------------------------------*/
static void AcceptBroker(HWND* hwnd)
{
    char* new_broker;
    
    new_broker = Tcl_GetVar(hwnd->interp, "broker", 0);
    Assert(new_broker);
    
    sadm_clear();
    sadm_init(new_broker);
    
    strcpy(der_broker_host, new_broker);
    /* RC??? TODO */	
}


/*---------------------------------------------------------------------------
 * Init des Dialoges
 *-------------------------------------------------------------------------*/
static int Init_Dlg(HWND* hwnd)
{
   DLG_Sbro* dlg;
   dlg = (DLG_Sbro*)malloc(sizeof(DLG_Sbro));
   SetWindowLong(hwnd, 0, (void*)dlg);
   return 0;
}


/*---------------------------------------------------------------------------
 * Show
 *-------------------------------------------------------------------------*/
static void Show(HWND* hwnd)
{
    Tcl_SetVar(hwnd->interp, "broker", der_broker_host, 0);  
}


/*---------------------------------------------------------------------------
 * Free des Dialoges
 *-------------------------------------------------------------------------*/
static int Destroy_Dlg(HWND* hwnd)
{
    DLG_Sbro* dlg;
    dlg = (DLG_Sbro*)GetWindowLong(hwnd, 0);
    SetWindowLong(hwnd, 0, NULL);
    free(dlg);
    return 0;
}


/*---------------------------------------------------------------------------
 * Dialogprocedure (Dispatcher)
 *-------------------------------------------------------------------------*/
int DLGProc_SelectBroker(HWND* hwnd, char* msg, void* param)
{
    if (strcmp(msg, "ev_ok")==0)                AcceptBroker(hwnd);
    if (strcmp(msg, "ev_show")==0)				Show(hwnd);
    if (strcmp(msg, DLG_INIT)==0)               Init_Dlg(hwnd);
    if (strcmp(msg, DLG_DESTROY)==0)            Destroy_Dlg(hwnd);

    return 0;
}

