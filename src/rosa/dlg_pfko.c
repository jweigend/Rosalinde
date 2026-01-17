/* ------------------------------------------------------------------------
|	Dateiname:		$RCSfile: dlg_pfko.c,v $											
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
#include "dlg_pfko.h"
#include <string.h>
#include <stdlib.h>
#include "knto.h"
#include "ctab.h"
#include "cmgr.h"
#include "dbms.h"

typedef enum { neuanlage, bearbeiten } PFKO_Zustand;

typedef struct 
{
   knto*	     das_Konto;
   PFKO_Zustand	 der_Zustand;
} DLG_Pfko;


/*---------------------------------------------------------------------------
 * Hilfsfunktion um aus char einen long zu bekommen
 *-------------------------------------------------------------------------*/
static long MakeLong(char* s)
{
    char tmp[50];
    int  i, x;
    
    x=0;
    for (i=0; i<strlen(s); i++)
    {
        if ( (s[i]>='0') && (s[i]<='9') )
        {
            tmp[x]=s[i];
            x++;            
        }
    }
    tmp[x] = 0;
    return atoi(tmp);
}


/*---------------------------------------------------------------------------
 * Loeschen der Eingabemaske
 *-------------------------------------------------------------------------*/
static int Loesche_Maske(HWND* hwnd)
{
    Tcl_SetVar(hwnd->interp, "knto_rid",  "", 0);
    Tcl_SetVar(hwnd->interp, "knto_nr",   "", 0);
    Tcl_SetVar(hwnd->interp, "knto_bank", "", 0);
    Tcl_SetVar(hwnd->interp, "knto_blz",  "", 0);
}


/*---------------------------------------------------------------------------
 * Informations-Box
 *-------------------------------------------------------------------------*/
static int MessageBox(HWND* hwnd, char* head, char* msg)
{
    char* tcl_cmd;
    
    tcl_cmd = (char*)malloc(sizeof(char)*1000);
    
    sprintf(tcl_cmd, "dialog .dlg_msgbox {%s} {%s} {} {} OK", head, msg);
    Tcl_Eval(hwnd->interp, tcl_cmd);
    
    free(tcl_cmd);
}


/*---------------------------------------------------------------------------
 * Setzen der Statuszeile
 *-------------------------------------------------------------------------*/
static int Setze_Status(HWND* hwnd, char* msg)
{
    Tcl_SetVar(hwnd->interp, "stc_status", msg, 0);
}


/*---------------------------------------------------------------------------
 * Suchen des Kontos
 *-------------------------------------------------------------------------*/
static int Suche_Konto(HWND* hwnd)
{
   knto*      k;
   char*      tcl_cmd;
   long int   rid;
   char       blz[30];
   RC         rc;
   DLG_Pfko*  dlg;
   
   dlg = (DLG_Pfko*)GetWindowLong(hwnd, 0);
   
   rid = atol(Tcl_GetVar(hwnd->interp, "knto_rid", 0));
   if (rid < KNTO_DB_RID_BASE)
   {
       Loesche_Maske(hwnd);
       Setze_Status(hwnd, "Ungueltige Kontonummer");
       MessageBox(hwnd, "Information", "Die Kontonummer ist ungueltig!");
       return 0;
   }
   
   if (dlg->der_Zustand==bearbeiten) knto_unregister(dlg->das_Konto);
   knto_delete(dlg->das_Konto);
   
   k = knto_find_by_key(rid, &rc);
   
   if (k==NULL)
   {
       Setze_Status(hwnd, "Konto wurde nicht gefunden!");
       Loesche_Maske(hwnd);
       MessageBox(hwnd, "Information", "Das Konto konnte nicht gefunden werden!");
       dlg->das_Konto = knto_new();
       dlg->der_Zustand = neuanlage;
   }
   else
   {
       Setze_Status(hwnd, "Konto wurde gefunden!");
       
       Tcl_SetVar(hwnd->interp, "knto_bank",  strg_out(knto_get_bankname(k)), 0);
       sprintf(blz, "%ld", knto_get_blz(k));
       Tcl_SetVar(hwnd->interp, "knto_blz", blz, 0);
       sprintf(blz, "%ld", knto_get_konto_nummer(k));
       Tcl_SetVar(hwnd->interp, "knto_nr", blz, 0);
       
       dlg->das_Konto = k;
       dlg->der_Zustand = bearbeiten;
   }
}


/*---------------------------------------------------------------------------
 * Anlegen/Speichern des aktuellen Kontos
 *-------------------------------------------------------------------------*/
static int Anlegen_Konto(HWND* hwnd)
{
   long      oid;
   long      blz;
   long      konto_nr;
   strg      bank_name;
   RC        rc;
   DLG_Pfko* dlg;
   long		 rid;
   char      msg[70];
   
   dlg = (DLG_Pfko*)GetWindowLong(hwnd, 0);

   strg_init(&bank_name, 0);
  
   if (dlg->der_Zustand==neuanlage)
   {
       knto_register(dlg->das_Konto, &oid);
   }

   strg_in(&bank_name,    Tcl_GetVar(hwnd->interp, "knto_bank", 0));
   blz = MakeLong(Tcl_GetVar(hwnd->interp, "knto_blz", 0));
   konto_nr = MakeLong(Tcl_GetVar(hwnd->interp, "knto_nr", 0));
    
   knto_set_konto_nummer(dlg->das_Konto, konto_nr);
   knto_set_bankname(dlg->das_Konto, &bank_name);
   knto_set_blz(dlg->das_Konto, blz);

   try {	
		dbms_commit();
   }
   catch (DB_CHANGED) {

       Setze_Status(hwnd, "Fehler: Konto wurde schon verändert (Rollback)");
       dbms_rollback ();
   }
   end_try;
   
   rid = knto_get_rid(dlg->das_Konto);
   sprintf(msg, "Konto gespeichert! Konto-ID: %i", rid);
   Setze_Status(hwnd, msg);

   
   strg_clear(&bank_name);
  
   Loesche_Maske(hwnd);

   knto_unregister (dlg->das_Konto);  /* HW !! */
   knto_delete(dlg->das_Konto);
   dlg->das_Konto = knto_new();
   dlg->der_Zustand = neuanlage;

   return 0;
}


/*---------------------------------------------------------------------------
 * Callback bei Aenderung der Maske
 *-------------------------------------------------------------------------*/
static int Konto_veraendert(HWND* hwnd)
{
    DLG_Pfko* dlg;
    dlg = GetWindowLong(hwnd, 0);
    
    if (dlg->der_Zustand==neuanlage)
    {
        Setze_Status(hwnd, "Neu: <geaendert>");
    }
    else
    {
        Setze_Status(hwnd, "Bearbeitung: <geaendert>");
    }
    return 0;
}


/*---------------------------------------------------------------------------
 * Init des Dialoges (vor dem Anzeigen)
 *-------------------------------------------------------------------------*/
static int Init_Dlg(HWND* hwnd)
{
   DLG_Pfko* dlg;
   dlg = (DLG_Pfko*)malloc(sizeof(DLG_Pfko));
   dlg->das_Konto   = knto_new();
   dlg->der_Zustand = neuanlage;
   SetWindowLong(hwnd, 0, (void*)dlg);
   
   Loesche_Maske(hwnd);
   Setze_Status(hwnd, "");
}


/*---------------------------------------------------------------------------
 * Free des Dialoges (nach dem Anzeigen)
 *-------------------------------------------------------------------------*/
static int Destroy_Dlg(HWND* hwnd)
{
   DLG_Pfko* dlg;
   dlg = (DLG_Pfko*)GetWindowLong(hwnd, 0);
   knto_unregister (dlg->das_Konto); /* HW */
   knto_delete(dlg->das_Konto);
   SetWindowLong(hwnd, 0, NULL);
   free(dlg);
}


/*---------------------------------------------------------------------------
 * Dialogfunktion (Event dispatcher)
 *-------------------------------------------------------------------------*/
int DLGProc_PflegeKonto(HWND* hwnd, char* msg, void* param)
{
    if (strcmp(msg, "ev_knto_suchen")==0)       Suche_Konto(hwnd);
    if (strcmp(msg, "ev_knto_anlegen")==0)      Anlegen_Konto(hwnd);
    if (strcmp(msg, "ev_knto_change")==0)       Konto_veraendert(hwnd);
    if (strcmp(msg, DLG_INIT)==0)               Init_Dlg(hwnd);
    if (strcmp(msg, DLG_DESTROY)==0)            Destroy_Dlg(hwnd);

    return 0;
}


/* EOF */
