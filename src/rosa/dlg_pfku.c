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
#include "dlg_skto.h"
#include <string.h>
#include <stdlib.h>
#include "knde.h"
#include "ctab.h"
#include "cmgr.h"
#include "dbms.h"

typedef enum { neuanlage, bearbeiten } PFKU_Zustand;

typedef struct 
{
   knde*	     der_Kunde;
   list*         die_Konten_Liste;
   int           der_Konten_Index;
   PFKU_Zustand	 der_Zustand;
} DLG_Pfku;


/*---------------------------------------------------------------------------
 * Loeschen der Eingabemaske
 *-------------------------------------------------------------------------*/
static void Loesche_Maske(HWND* hwnd)
{
    char tcl_cmd[100];
    DLG_Pfku* dlg;
    
    dlg = GetWindowLong(hwnd, 0);
    
    Tcl_SetVar(hwnd->interp, "knde_name",    "", 0);
    Tcl_SetVar(hwnd->interp, "knde_vorname", "", 0);
    Tcl_SetVar(hwnd->interp, "knde_anrede",  "", 0);
    Tcl_SetVar(hwnd->interp, "knde_strasse", "", 0);
    Tcl_SetVar(hwnd->interp, "knde_hausnr",  "", 0);
    Tcl_SetVar(hwnd->interp, "knde_plz",     "", 0);
    Tcl_SetVar(hwnd->interp, "knde_ort",     "", 0);
    Tcl_SetVar(hwnd->interp, "knde_land",    "", 0);
    Tcl_SetVar(hwnd->interp, "knde_rid",     "", 0);

    sprintf(tcl_cmd, "%s.lbx_knto delete 0 1000", hwnd->window_name);
    Tcl_Eval(hwnd->interp, tcl_cmd);
}


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
 * Loeschen der Kontenliste
 *-------------------------------------------------------------------------*/
static void Loesche_Kontenliste(HWND* hwnd)
{
    DLG_Pfku* dlg;
    int       count, i;
    knto*     ko;
    
    dlg = (DLG_Pfku*)GetWindowLong(hwnd, 0);
    
    if (dlg->die_Konten_Liste)
    {
        count = list_nbr_of_el(dlg->die_Konten_Liste);
        for (i=0; i<count; i++)
        {
            ko = list_get_at(dlg->die_Konten_Liste, i);
            Assert(ko);
            
            knto_unregister(ko);
            knto_delete(ko);
        }
        
        list_delete(dlg->die_Konten_Liste);
        dlg->die_Konten_Liste = NULL;
        dlg->der_Konten_Index = -1;
    }
}

/*---------------------------------------------------------------------------
 * Fuellen der Listbox mit den Konten
 *-------------------------------------------------------------------------*/
static void Fuelle_Kontenliste(HWND* hwnd, knde* k)
{
    char      tcl_cmd[200];
    list*     l;
    int       count, i;
    DLG_Pfku* dlg;
    knto*     ko;
    
    dlg = GetWindowLong(hwnd, 0);
    
    sprintf(tcl_cmd, "%s.lbx_knto delete 0 1000", hwnd->window_name);
    Tcl_Eval(hwnd->interp, tcl_cmd);
    
    Loesche_Kontenliste(hwnd);
    
    LOG("knde_get_konten\n");
    l = knde_get_konten(k);
    LOG("konten geholt\n");
    if (!l) return;
    
    dlg->die_Konten_Liste = l;
    
    count = list_nbr_of_el(l);
    
    for (i=0; i<count; i++)
    {
        ko = (knto*)list_get_at(l, i);
        
        sprintf(tcl_cmd, "%s.lbx_knto insert end \"KTO: %i %s\"", 
                         hwnd->window_name,
                         knto_get_konto_nummer(ko),
                         strg_out(knto_get_bankname(ko)) );
        
        Tcl_Eval(hwnd->interp, tcl_cmd);
    }
}


/*---------------------------------------------------------------------------
 * Suchen des Kunden
 *-------------------------------------------------------------------------*/
static int Suche_Kunde(HWND* hwnd)
{
   knde*      k;
   adrs*      a;
   char*      tcl_cmd;
   long int   rid;
   RC         rc;
   DLG_Pfku*  dlg;
   
   dlg = (DLG_Pfku*)GetWindowLong(hwnd, 0);
   
   rid = atol(Tcl_GetVar(hwnd->interp, "knde_rid", 0));
   if (rid<KNDE_DB_RID_BASE)
   {
       Loesche_Maske(hwnd);
       Setze_Status(hwnd, "Ungueltige Kundennummer!");
       MessageBox(hwnd, "Information", "Die eingegebene Kundennummer ist ungueltig!");
       return 0;
   }
   
   LOG("Lösche Konten...\n");
   Loesche_Kontenliste(hwnd);
   if (dlg->der_Zustand==bearbeiten) knde_unregister(dlg->der_Kunde);
   LOG("knde_delete\n");
   knde_delete (dlg->der_Kunde);
   
   LOG("Find by Key\n");
   k = knde_find_by_key(rid, &rc);
   
   if (k==NULL)
   {
      MessageBox(hwnd, "Information", "Kunde wurde nicht gefunden!");      
      Setze_Status(hwnd, "Kunde wurde nicht gefunden!");
      Loesche_Maske(hwnd);      
   
      dlg->der_Kunde = knde_new();
      dlg->der_Zustand = neuanlage;
   }
   else
   {
       Setze_Status(hwnd, "Kunde wurde gefunden!");
       
       LOG("Set1\n");
       Tcl_SetVar(hwnd->interp, "knde_anrede",  anrd_out(knde_get_anrede(k), LANG),0);
       Tcl_SetVar(hwnd->interp, "knde_name",    strg_out(knde_get_name(k)), 0);
       Tcl_SetVar(hwnd->interp, "knde_vorname", strg_out(knde_get_vorname(k)), 0);
       
       LOG("Adresse\n");
       a = knde_get_adresse (k);

   	   LOG("Get2\n");
       Tcl_SetVar(hwnd->interp, "knde_strasse", adrs_get_strasse (a), 0);
       Tcl_SetVar(hwnd->interp, "knde_hausnr",  adrs_get_hausnr  (a), 0);
       Tcl_SetVar(hwnd->interp, "knde_plz",     adrs_get_plz     (a), 0);
       Tcl_SetVar(hwnd->interp, "knde_ort",     adrs_get_ort     (a), 0);
       Tcl_SetVar(hwnd->interp, "knde_land",    adrs_get_land    (a), 0);
  
       dlg->der_Kunde = k;
       dlg->der_Zustand = bearbeiten;

   	   LOG("Fuelle Kontenliste\n");
       Fuelle_Kontenliste(hwnd, k);
       LOG("Kontenliste gefuellt\n");   
   }
}

/*---------------------------------------------------------------------------
 * Anlegen/Speichern des Kunden
 *-------------------------------------------------------------------------*/
static int Anlegen_Kunde(HWND* hwnd)
{
   long      oid;
   long      rid;
   strg      name;
   strg      vorname;
   adrs      adresse;   
   anrd      anrede;
   RC        rc;
   DLG_Pfku* dlg;
   char      msg[70];
   
   dlg = GetWindowLong(hwnd, 0);

   strg_init(&name, 0);
   strg_init(&vorname, 0);
   adrs_init(&adresse); 
   anrd_init(&anrede);
  
   if (dlg->der_Zustand==neuanlage)
   { 
       knde_register(dlg->der_Kunde, &oid);
   }

   strg_in(&name,     Tcl_GetVar(hwnd->interp, "knde_name", 0));
   strg_in(&vorname,  Tcl_GetVar(hwnd->interp, "knde_vorname", 0)); 
   anrd_in(&anrede,   &rc, LANG, Tcl_GetVar(hwnd->interp, "knde_anrede", 0));
   adrs_in(&adresse,  Tcl_GetVar(hwnd->interp, "knde_strasse", 0),
                      Tcl_GetVar(hwnd->interp, "knde_hausnr", 0),
                      Tcl_GetVar(hwnd->interp, "knde_plz", 0),
                      Tcl_GetVar(hwnd->interp, "knde_ort", 0),
 		              Tcl_GetVar(hwnd->interp, "knde_land", 0));

   knde_set_name   (dlg->der_Kunde, &name);
   knde_set_vorname(dlg->der_Kunde, &vorname);
   knde_set_anrede (dlg->der_Kunde, &anrede);
   knde_set_adresse(dlg->der_Kunde, &adresse);        

   Setze_Status(hwnd, "Kunde gespeichert!");

   try {	
		dbms_commit();
   }
   catch (DB_CHANGED) {

       Setze_Status(hwnd, "Fehler: Kunde wurde schon verändert (Rollback)");
       dbms_rollback ();
   }
   end_try;

   rid = knde_get_rid(dlg->der_Kunde);
   sprintf(msg, "Kunde gespeichert! Kd-Nr: %i", rid);
   Setze_Status(hwnd, msg);
   
   
   strg_clear(&name);
   strg_clear(&vorname);
   adrs_clear(&adresse);
  
   Loesche_Maske(hwnd);

   knde_unregister (dlg->der_Kunde);  /* HW !! */
   knde_delete(dlg->der_Kunde);
   dlg->der_Kunde = knde_new();
   dlg->der_Zustand = neuanlage;

   return 0;
}


/*---------------------------------------------------------------------------
 * Einhaengen eines Kontos
 *-------------------------------------------------------------------------*/
static int Konto_einhaengen(HWND* hwnd)
{
    DLG_Pfku*  dlg;
    char       tmp[100];
    long	   kunde_rid;
    RC		   rc;
    
    dlg = GetWindowLong(hwnd, 0);
    
    if (dlg->der_Zustand==neuanlage)
    {
        MessageBox(hwnd, "Information", "Konten koennen nur bei Persistenten Kunden eingehaengt werden!");
        return 0;
    }
    
    sprintf(tmp, "DLG_Suche_Konto %s.dlg_skonto", hwnd->window_name);
    
    Tcl_Eval(hwnd->interp, tmp);
    
    if (SKTO_get_Konto()!=NULL)
    {
        knto_set_kunde(SKTO_get_Konto(), dlg->der_Kunde);
        try {	
		    dbms_commit();
        }
        catch (DB_CHANGED) {

            Setze_Status(hwnd, "Fehler: Konto wurde schon verändert (Rollback)");
            dbms_rollback ();
        }
        end_try;
        
        Setze_Status(hwnd, "Konto wurde eingehaengt!");

        knto_unregister(SKTO_get_Konto());
        knto_delete(SKTO_get_Konto());
        
        Loesche_Kontenliste(hwnd);
        LOG("Konten geloescht\n");
        /* Wegwerfen des Kunden und neu Suchen */
        kunde_rid = knde_get_rid(dlg->der_Kunde);
        LOG("Rid geholt");
        
        LOG("Kunde unregister\n");
        knde_unregister(dlg->der_Kunde);
        LOG("Kunde delete\n");
        knde_delete(dlg->der_Kunde);
        
        dlg->der_Kunde = knde_find_by_key(kunde_rid, &rc);
        
        Fuelle_Kontenliste(hwnd, dlg->der_Kunde);
    }
    else
    {
        Setze_Status(hwnd, "Konto wurde NICHT eingehaengt!");
    }
    
    return 0;
}


/*---------------------------------------------------------------------------
 * Aushaengen eines Kontos
 *-------------------------------------------------------------------------*/
static int Konto_aushaengen(HWND* hwnd)
{
    DLG_Pfku* dlg;
    knto*     ko;
    long      kunde_rid;
    RC        rc;
    
    dlg = (DLG_Pfku*)GetWindowLong(hwnd, 0);
    
    if ( (dlg->der_Konten_Index==-1) || (dlg->die_Konten_Liste==NULL) )
    {
        MessageBox(hwnd, "Information", "Es ist kein Konto selektiert, dass ausgehaengt werden kann.");
        Setze_Status(hwnd, "Konto NICHT ausgehaengt!");
        return 0;
    }   
    
    ko = (knto*)list_get_at(dlg->die_Konten_Liste, dlg->der_Konten_Index);
    Assert(ko);
    
    knto_set_unassigned(ko);
    try {	
	    dbms_commit();
    }
    catch (DB_CHANGED) {

        Setze_Status(hwnd, "Fehler: Konto wurde schon verändert (Rollback)");
        dbms_rollback ();
    }
    end_try;
        
    /* Liste und Kunde neu aufbauen */
    Loesche_Kontenliste(hwnd);
    kunde_rid = knde_get_rid(dlg->der_Kunde);
        
    knde_unregister(dlg->der_Kunde);
    knde_delete(dlg->der_Kunde);
        
    dlg->der_Kunde = knde_find_by_key(kunde_rid, &rc);
       
    Fuelle_Kontenliste(hwnd, dlg->der_Kunde);
    
    Setze_Status(hwnd, "Konto wurde ausgehaengt!");
    
    return 0;
}


/*---------------------------------------------------------------------------
 * Konto-Selektion geaendert
 *-------------------------------------------------------------------------*/
static void Konto_Selchange(HWND* hwnd)
{
    DLG_Pfku* dlg;
    
    dlg = (DLG_Pfku*)GetWindowLong(hwnd, 0);
    
    dlg->der_Konten_Index = atoi(Tcl_GetVar(hwnd->interp, "knto_sel_index", 0));
}


/*---------------------------------------------------------------------------
 * Callback fuer Aenderung des Kunden
 *-------------------------------------------------------------------------*/
static int Kunde_veraendert(HWND* hwnd)
{
    DLG_Pfku* dlg;
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
   DLG_Pfku* dlg;
   dlg = (DLG_Pfku*)malloc(sizeof(DLG_Pfku));
   
   dlg->der_Kunde        = knde_new();
   dlg->die_Konten_Liste = NULL;
   dlg->der_Konten_Index = -1;
   dlg->der_Zustand      = neuanlage;
   
   SetWindowLong(hwnd, 0, (void*)dlg);
}


/*---------------------------------------------------------------------------
 * Vor dem Anzeigen...
 *-------------------------------------------------------------------------*/
static int Show(HWND* hwnd)
{
    LOG("suchen..\n");
    Setze_Status(hwnd, "");
    Loesche_Maske(hwnd);
}


/*---------------------------------------------------------------------------
 * Freigabe des Dialoges (nach dem Anzeigen)
 *-------------------------------------------------------------------------*/
static int Destroy_Dlg(HWND* hwnd)
{
    DLG_Pfku* dlg;
    
    dlg = (DLG_Pfku*)GetWindowLong(hwnd, 0);

    Loesche_Kontenliste(hwnd);    
    knde_unregister (dlg->der_Kunde); /* HW */
    knde_delete(dlg->der_Kunde);
    
    SetWindowLong(hwnd, 0, NULL);
    free(dlg);
}


/*---------------------------------------------------------------------------
 * Dialogprocedure des Dialoges (Event dispatcher)
 *-------------------------------------------------------------------------*/
int DLGProc_PflegeKunde(HWND* hwnd, char* msg, void* param)
{
    if (strcmp(msg, "ev_knde_suchen")==0)            Suche_Kunde(hwnd);
    if (strcmp(msg, "ev_knde_anlegen")==0)           Anlegen_Kunde(hwnd);
    if (strcmp(msg, "ev_knde_konto_einhaengen")==0)  Konto_einhaengen(hwnd);
    if (strcmp(msg, "ev_knde_konto_aushaengen")==0)  Konto_aushaengen(hwnd);
    if (strcmp(msg, "ev_knde_change")==0)            Kunde_veraendert(hwnd);
    if (strcmp(msg, "ev_knto_selchange")==0)		 Konto_Selchange(hwnd);
    if (strcmp(msg, "ev_show")==0)					 Show(hwnd);
    if (strcmp(msg, DLG_INIT)==0)                    Init_Dlg(hwnd);
    if (strcmp(msg, DLG_DESTROY)==0)                 Destroy_Dlg(hwnd);

    return 0;
}

