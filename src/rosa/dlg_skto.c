/* ------------------------------------------------------------------------
|	Dateiname:		$RCSfile: dlg_pfku.c,v $											
|	Version:		$Revision: 1 $										
|	Erstellt am:	00.00.96												
|	Geaendert am:	$Date: 19.11.97 9:36 $											
|	Komponente:		DLG												
|	Erstellt von:	Christian Stoellinger												
|	Geandert von:	$Author: Johannes $												
|	Copyright:		Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
|	Bermerkung:		Tabstop = 4												
---------------------------------------------------------------------------*/

#include "tk.h"
#include "dlg_pfku.h"
#include <string.h>
#include <stdlib.h>
#include "knto.h"
#include "ctab.h"
#include "cmgr.h"
#include "dbms.h"

static knto* __global_konto_sel = NULL;


knto* SKTO_get_Konto()
{
    return __global_konto_sel;
}


typedef struct 
{
    list* die_kontenliste;
    int   cur_selection;
} DLG_Skto;


/*---------------------------------------------------------------------------
 * Fuellen der Listbox mit den Konten
 *-------------------------------------------------------------------------*/
static void Fuelle_Kontenliste(HWND* hwnd)
{
    list*	  l;    
    char*     tcl_cmd;
    int       count, i;
    knto*     k;
    DLG_Skto* dlg;
    
    dlg = (DLG_Skto*)GetWindowLong(hwnd, 0);   
    
    if (dlg->die_kontenliste)
    {
        count = list_nbr_of_el(l);
        for(i=0; i<count; i++)
        {
            k = (knto*)list_get_at(dlg->die_kontenliste, i);
            knto_unregister(k);
            knto_delete(k);
        }
        list_delete(dlg->die_kontenliste);
        dlg->die_kontenliste = NULL;
    }
    
    l = knto_find_unassigned();
    if (!l) return;
    
    dlg->die_kontenliste = l;
    dlg->cur_selection = -1;
    
    count = list_nbr_of_el(l);
    
    tcl_cmd = (char*)malloc(sizeof(char)*300);
    for (i=0; i<count; i++)
    {
        k = (knto*)list_get_at(l, i);
        
        sprintf(tcl_cmd, "%s.lbx_konten insert end \"KTO: %i %s(BLZ: %i)\"", 
                         hwnd->window_name,
                         knto_get_konto_nummer(k),
                         strg_out(knto_get_bankname(k)),
                         knto_get_blz(k) );
                         
        Tcl_Eval(hwnd->interp, tcl_cmd);
    }
}


/*---------------------------------------------------------------------------
 * Selektion der Listbox geaendert
 *-------------------------------------------------------------------------*/
static void SelChange(HWND* hwnd)
{
    char*      sel_knto;
    DLG_Skto*  dlg;
    
    dlg = (DLG_Skto*)GetWindowLong(hwnd, 0);
   
    dlg->cur_selection = -1;
    sel_knto = Tcl_GetVar(hwnd->interp, "konto_sel_index", 0);
    
    if (!sel_knto) return;   
    if (!dlg->die_kontenliste) return;

    dlg->cur_selection = atoi(sel_knto);
    
    LOG("Selektion: %i\n", dlg->cur_selection);
}


/*---------------------------------------------------------------------------
 * OK
 *-------------------------------------------------------------------------*/
static void Ok(HWND* hwnd)
{
    DLG_Skto* dlg;
    
    dlg = GetWindowLong(hwnd, 0);
        
    __global_konto_sel = list_get_at(dlg->die_kontenliste, dlg->cur_selection);
}


/*---------------------------------------------------------------------------
 * Abbruch des Dialoges
 *-------------------------------------------------------------------------*/
static void Cancel(HWND* hwnd)
{
   DLG_Skto*  dlg;
 
   LOG("Cancel...\n");  
   dlg = (DLG_Skto*)GetWindowLong(hwnd, 0);
   
   dlg->cur_selection = -1;
   __global_konto_sel = NULL;
}


/*---------------------------------------------------------------------------
 * Init des Dialoges
 *-------------------------------------------------------------------------*/
static int Init_Dlg(HWND* hwnd)
{
   DLG_Skto* dlg;
   dlg = (DLG_Skto*)malloc(sizeof(DLG_Skto));
   dlg->die_kontenliste = NULL;
   dlg->cur_selection   = -1;
      
   SetWindowLong(hwnd, 0, (void*)dlg);
}


/*---------------------------------------------------------------------------
 * Anzeigen des Dialoges
 *-------------------------------------------------------------------------*/
static void Show(HWND* hwnd)
{
    Fuelle_Kontenliste(hwnd);
}


/*---------------------------------------------------------------------------
 * Freigabe des Dialoges
 *-------------------------------------------------------------------------*/
static int Destroy_Dlg(HWND* hwnd)
{
   DLG_Skto* dlg;
   knto*	 k;
   int       i, count;
   
   LOG("Destroy..\n");
   
   dlg = (DLG_Skto*)GetWindowLong(hwnd, 0);
   __global_konto_sel = NULL;
   
   if (dlg->die_kontenliste) 
   {
       count = list_nbr_of_el(dlg->die_kontenliste);
       for (i=0; i<count; i++)
       {
       	   k = (knto*)list_get_at(dlg->die_kontenliste, i);
           if (i!=dlg->cur_selection)
           {
               knto_unregister(k);
               knto_delete(k);
           }
           else __global_konto_sel = k; 
       }
       list_delete(dlg->die_kontenliste);
   }
   
   SetWindowLong(hwnd, 0, NULL);
   free(dlg);
   
   LOG("Done Destroy...\n");
}


/*---------------------------------------------------------------------------
 * Dialogprocedure (Event-Dispatcher)
 *-------------------------------------------------------------------------*/
int DLGProc_SucheKonto(HWND* hwnd, char* msg, void* param)
{
    if (strcmp(msg, "ev_show")==0)		Show(hwnd);
    if (strcmp(msg, "ev_selchange")==0)	SelChange(hwnd);
    if (strcmp(msg, "ev_ok")==0)		Ok(hwnd);
    if (strcmp(msg, "ev_cancel")==0)    Cancel(hwnd);
    if (strcmp(msg, DLG_INIT)==0)       Init_Dlg(hwnd);
    if (strcmp(msg, DLG_DESTROY)==0)    Destroy_Dlg(hwnd);

    return 0;
}

