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
#include "dlg_admi.h"
#include <string.h>
#include <stdlib.h>
#include "brok.h"
#include "sadm.h"
#include "r_knde.h"
#include "dbms.h"
#include "knto.h"
#include "knde.h"	

typedef struct
{
   bent   der_broker_entry;
} DLG_Admin;


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
 * Fuellen der Listbox mit den Services
 *-------------------------------------------------------------------------*/
static void Fuelle_Serviceliste(HWND* hwnd)
{
    char tcl_cmd[200];
    
    sprintf(tcl_cmd, "%s.lbx_service insert end \"%s\"", hwnd->window_name, KNDE_SVC);
    Tcl_Eval(hwnd->interp, tcl_cmd);
    
    sprintf(tcl_cmd, "%s.lbx_service insert end \"%s\"", hwnd->window_name, KNDE_BTAB_SVC);
    Tcl_Eval(hwnd->interp, tcl_cmd);
    
    sprintf(tcl_cmd, "%s.lbx_service insert end \"%s\"", hwnd->window_name, KNTO_SVC);
    Tcl_Eval(hwnd->interp, tcl_cmd);
    
    sprintf(tcl_cmd, "%s.lbx_service insert end \"%s\"", hwnd->window_name, KNTO_BTAB_SVC);
    Tcl_Eval(hwnd->interp, tcl_cmd);
}


/*---------------------------------------------------------------------------
 * Service wurde selektiert
 *-------------------------------------------------------------------------*/
static int SelService(HWND* hwnd)
{
    DLG_Admin*  dlg;
    char*       svcn;  /* = TCL Get ... */
    char*       proto;
    char*       host;
    long        prgnr;
    long        versnr;
    RC          rc;
    char        s[] = "";

    dlg = (DLG_Admin*)GetWindowLong(hwnd, 0);

    svcn = (char*)malloc(128);
    strcpy(svcn, Tcl_GetVar(hwnd->interp, "svc_name", 0));
    LOG("Service: %s\n", svcn);
    rc = brok_bind (svcn, &(dlg->der_broker_entry));
    if (rc != OK) 
    {
        /* In Felder UNDEF eintragen */
        bent_init (&(dlg->der_broker_entry));
        svcn  = s;
        proto = s;
        host  = s;
        Setze_Status(hwnd, "Service nicht gefunden!");
    }
    else 
    {
        svcn  = bent_get_svcn  (&(dlg->der_broker_entry));
        proto = bent_get_proto (&(dlg->der_broker_entry));
        host  = bent_get_host  (&(dlg->der_broker_entry));
        Setze_Status(hwnd, "Service selektiert");   
    }
    
     /* Eintragen in Maske Servicename, Protokoll, Hostname */
    Tcl_SetVar(hwnd->interp, "svc_name",  svcn, 0);
    Tcl_SetVar(hwnd->interp, "svc_proto", proto, 0);
    Tcl_SetVar(hwnd->interp, "svc_host",  host, 0);
    
    return 0;
}


static void Service_changed(HWND* hwnd)
{
    Setze_Status(hwnd, "Host geaendert");
}

/*---------------------------------------------------------------------------
 * Uebernehmen eines Services
 *-------------------------------------------------------------------------*/
static int Change_SvcHost(HWND* hwnd)
{
   DLG_Admin*  dlg;
   char*       newhost;
   char*       svcn;
   bent        old_entry;
   CLIENT*     cl;
   RC          rc;

   dlg = (DLG_Admin*)GetWindowLong(hwnd, 0);

   bent_init (&old_entry);
   bent_copy (&(dlg->der_broker_entry), &old_entry);

   /* Setze newhost ... */
   newhost = Tcl_GetVar(hwnd->interp, "svc_host", 0);
   Assert (newhost);

   svcn    = Tcl_GetVar(hwnd->interp, "svc_name", 0);
   Assert (svcn);

   rc = sadm_ping        (newhost,
                          bent_get_prgnr    (&dlg->der_broker_entry),
                          bent_get_versnr   (&dlg->der_broker_entry),
                          bent_get_proto    (&dlg->der_broker_entry));
   if (rc != OK) 
   {
       LOG ("[ROSA]: Cannot connect to host (ignored)\n");
       Setze_Status(hwnd, "Ping fehlgeschlagen! Service NICHT geaendert!");
       return 0;
   }
 
   bent_set_host (&(dlg->der_broker_entry), newhost);

   rc = brok_register (&(dlg->der_broker_entry));
   if (rc == OK) 
   {
       Setze_Status(hwnd, "Service geaendert!");
       dbms_data_server_changed ();
   }
   else 
   {
       /* Alten Eintrag wiederherstellen */
       Setze_Status(hwnd, "Gleicher Host! Service NICHT geändert!");
       bent_copy (&old_entry, &dlg->der_broker_entry);
   }

   return 0;
}


/*---------------------------------------------------------------------------
 * Init des Dialoges
 *-------------------------------------------------------------------------*/
static int Init_Dlg(HWND* hwnd)
{
   DLG_Admin* dlg;
   dlg = (DLG_Admin*)malloc(sizeof(DLG_Admin));
   SetWindowLong(hwnd, 0, (void*)dlg);
   bent_init (&dlg->der_broker_entry);
   return 0;
}


/*---------------------------------------------------------------------------
 * Show
 *-------------------------------------------------------------------------*/
static void Show(HWND* hwnd)
{
    Fuelle_Serviceliste(hwnd);
    Tcl_SetVar(hwnd->interp, "svc_broker", sadm_get_broker(), 0);
}


/*---------------------------------------------------------------------------
 * Free des Dialoges
 *-------------------------------------------------------------------------*/
static int Destroy_Dlg(HWND* hwnd)
{
    DLG_Admin* dlg;
    dlg = (DLG_Admin*)GetWindowLong(hwnd, 0);
    SetWindowLong(hwnd, 0, NULL);
    free(dlg);
    return 0;
}


/*---------------------------------------------------------------------------
 * Dialogprocedure (Dispatcher)
 *-------------------------------------------------------------------------*/
int DLGProc_Administration(HWND* hwnd, char* msg, void* param)
{
    if (strcmp(msg, "ev_svc_sel_service")==0)   SelService(hwnd);
    if (strcmp(msg, "ev_svc_accept")==0)        Change_SvcHost(hwnd);
    if (strcmp(msg, "ev_show")==0)				Show(hwnd);
    if (strcmp(msg, "ev_svc_change")==0)		Service_changed(hwnd);
    if (strcmp(msg, DLG_INIT)==0)               Init_Dlg(hwnd);
    if (strcmp(msg, DLG_DESTROY)==0)            Destroy_Dlg(hwnd);

    return 0;
}

