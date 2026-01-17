/* ------------------------------------------------------------------------
|   Dateiname:      $RCSfile: tcl_dlg.c,v $
|   Version:        $Revision: 1 $
|   Erstellt am:    00.00.96
|   Geaendert am:   $Date: 19.11.97 9:36 $
|   Komponente:     TCL
|   Erstellt von:   Christian Stoellinger
|   Geandert von:   $Author: Johannes $
|   Copyright:      Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
|   Bermerkung:     Tabstop = 4
---------------------------------------------------------------------------*/


#include "tcl_dlg.h"
#include <string.h>


/* Statische Variablen fuer die Verwaltung der Dialog-Prozeduren */
/* Dieses dynamische array nimmt alle Dialog-Funktionen auf, die */
/* mit RegisterDLGProc registriert wurden. Bei einem Aufruf eines */
/* Dialoges wird die entsprechende Dialog-Funktion aus diesem */
/* array gesucht, und fuer die Ausf’hrung verwendet. */
typedef struct
{
   TCL_DLG_PROC* dlg_proc;  /* Pointer auf die Dialog-Funktion */
   char*         dlg_name;  /* Name der Dialog-Funktion */
} TCL_DLG_Registration;

static TCL_DLG_Registration** tcl_dlg_proc_ptr = NULL;
static int tcl_dlg_proc_size = 0;
static int tcl_dlg_proc_len  = 0;


/* Funktion zum erzeugen eines Dialoges. Diese Funktion wird als */
/* Commando bei TCL Registriert. (Commando sollte DIALOG_create */
/* heižen!). Das Commando braucht einen Parameter, den Namen der */
/* Dialogfunktion, welche zuvor mit RegisterDLGProc registriert wurde! */
/* Der R’ckgabewert im TCL-Skript ist eine Art Handle auf den Dialog. */
int TCL_Dialog_cmd(ClientData clientData, Tcl_Interp* interp, int argc, char* argv[])
{
    TCL_Dialog* dialog;

    if (argc!=1)
    {
	Tcl_SetObjResult(interp, Tcl_NewStringObj("Parameter sind nicht erlaubt!", -1));
	return TCL_ERROR;  // falls das eine Fehlerbedingung ist
    }

    /* Erzeugen der C-Struktur */
    Dialog_create(&dialog);
    if (!dialog)
    {
        /* Speicher ist aus! */
        Tcl_SetObjResult(interp, Tcl_NewStringObj("Speicher aus", -1));
        return TCL_ERROR;  // falls das eine Fehlerbedingung ist
    }

    dialog->dlg_interp = interp;

    /* Der erzeugte Dialog wird als neues Kommando registriert. Der Name */
    /* des Kommandos ist die Adresse der Struktur. Der Name des Kommandos */
    /* interessiert nicht, da das Kommando in einer Variablen (im TCL-Skript) */
    /* gespeichert wird. */
    // JWE 2025 TODO
    //sprintf(interp->result, "%x", dialog);
    //Tcl_CreateCommand(interp,                  /* Neues Cmd im Interpreter */
    //                  interp->result,          /* Cmd erfolgreich */
    //                  TCL_Dialog_object_cmd,   /* Pointer auf Cmd-Funktion */
    //                  (ClientData)dialog,      /* Mit welchen Daten? */
    //                  TCL_Dialog_delete);      /* Freigeben der Daten */
    return TCL_OK;
}


/* Diese Funktion l÷scht eine Dialog-Struktur, und wird von TCL automatisch */
/* zum richtigen Zeitpunkt aufgerufen! */
void TCL_Dialog_delete(ClientData clientData)
{
    TCL_Dialog* dialog = (TCL_Dialog*)clientData;
    Dialog_delete(dialog);
}


/* Diese Funktion ist der Event-Dispatcher f’r Dialoge/Fenster */
/* In der Dialog-Struktur ist der Pointer auf die Dialogfunktion */
/* abgelegt. Der Dispatcher setzt die Motif-Events in eigene Events */
/* um und ’bergibt sie der Dialog-Funktion. Damit der C-Teil zugriff */
/* auf den TCL-Interpreter hat, wird fuer jeden aufruf der Dialog- */
/* Funktion der Interpreter mitgegeben. */
int TCL_Dialog_object_cmd(ClientData clientData, Tcl_Interp* interp, int argc, char* argv[])
{
    TCL_Dialog* dialog = (TCL_Dialog*)clientData;
    HWND* hwnd;

    if (argc==3)
    {
        /* Setzen der Dialog-Funktion */
        if (strcmp(argv[1], "setproc")==0)
        {
            Dialog_setproc(dialog, argv[2], interp);

            /* Hier die 1. Message an die Dialog-Funktion */
            hwnd = (HWND*)malloc(sizeof(HWND));
            hwnd->interp      = interp;
            hwnd->data        = dialog->dlg_data;
            hwnd->window_name = dialog->dlg_wndname;
            if (dialog->dlg_proc) dialog->dlg_proc(hwnd, DLG_INIT, NULL);
            dialog->dlg_data = hwnd->data;
            free(hwnd);
            return TCL_OK;
        }

        /* Setzen des TK-(Window)Namens */
        if (strcmp(argv[1], "setwindowname")==0)
        {
            if (dialog->dlg_wndname) free(dialog->dlg_wndname);
            dialog->dlg_wndname = (char*)malloc(strlen(argv[2])+1);
            strcpy(dialog->dlg_wndname, argv[2]);
            return TCL_OK;
        }
    }

    if (argc==2)
    {
        hwnd = (HWND*)malloc(sizeof(HWND));
        hwnd->interp      = interp;
        hwnd->data        = dialog->dlg_data;
        hwnd->window_name = dialog->dlg_wndname;
        dialog->dlg_proc(hwnd, argv[1], NULL);
        dialog->dlg_data = hwnd->data;
        free(hwnd);
        return TCL_OK;
    }

    Tcl_SetObjResult(interp, Tcl_NewStringObj("Parameter sind nicht erlaubt!", -1));
    return TCL_ERROR;  // falls das eine Fehlerbedingung ist
}

/* Erzeugen und initialisieren einer Dialog-Struktur */
void Dialog_create(TCL_Dialog** dlg)
{
    TCL_Dialog* dialog;
    *dlg = (TCL_Dialog*)malloc(sizeof(TCL_Dialog));
    dialog               = *dlg;
    dialog->dlg_name     = NULL;
    dialog->dlg_proc     = NULL;
    dialog->dlg_wndname  = NULL;
    dialog->dlg_data     = NULL;
}


/* L÷schen einer Dialog-Struktur */
void Dialog_delete(TCL_Dialog* dlg)
{
    HWND hwnd;
    if (dlg)
    {
        /* Message fuer Zerstoeren: */
        hwnd.interp      = dlg->dlg_interp;
        hwnd.data        = dlg->dlg_data;
        hwnd.window_name = dlg->dlg_wndname;
        dlg->dlg_proc(&hwnd, DLG_DESTROY, NULL);
        free(dlg->dlg_name);
        free(dlg);
    }
}

/* Setzen der Dialog-Procedure */
void Dialog_setproc(TCL_Dialog* dlg, char* dlgname, Tcl_Interp* interp)
{
    if (dlg)
    {
        dlg->dlg_name = (char*)malloc(sizeof(char) * (strlen(dlgname)+1) );
        strcpy(dlg->dlg_name, dlgname);
        dlg->dlg_proc = FindDLGProc(dlgname);
    }
}


void* GetWindowLong(HWND* hwnd, int index)
{
    return hwnd->data;
}


void SetWindowLong(HWND* hwnd, int index, void* data)
{
    hwnd->data = data;
}

/* Registrieren einer Dialog-Funktion. Der Name dient als Schl’ssel
   f’r sp„tere Aufrufe von Dialogen */
int RegisterDLGProc(char* dlg_name, TCL_DLG_PROC* dlg_proc)
{
    TCL_DLG_Registration** tmp;
    TCL_DLG_Registration*  reg;

    if (tcl_dlg_proc_len==tcl_dlg_proc_size)
    {
        if (tcl_dlg_proc_ptr)
        {
            tcl_dlg_proc_size += 10;
            tmp = (TCL_DLG_Registration**)realloc(tcl_dlg_proc_ptr,
                                                  sizeof(TCL_DLG_Registration*) * tcl_dlg_proc_size);
            if (tmp) tcl_dlg_proc_ptr = tmp;
            else return 0;
        }
        else
        {
        	tcl_dlg_proc_size += 10;
            tmp = (TCL_DLG_Registration**)malloc(sizeof(TCL_DLG_Registration*) * tcl_dlg_proc_size);
            if (tmp) tcl_dlg_proc_ptr = tmp;
            else return 0;
        }
    }

    /* Ab hier steht der Speicher auf jeden Fall zur Verf’gung! */
    reg = (TCL_DLG_Registration*)malloc(sizeof(TCL_DLG_Registration));
    if (reg)
    {
        reg->dlg_proc = dlg_proc;
        reg->dlg_name = (char*)malloc(sizeof(char) * (strlen(dlg_name)+1) );

        if (reg->dlg_name)
        {
            strcpy(reg->dlg_name, dlg_name);
            tcl_dlg_proc_ptr[tcl_dlg_proc_len] = reg;
            tcl_dlg_proc_len++;
            return 1;
        }
        else
        {
            free(reg);
            return 0;
        }
    }
    else return 0;
}


TCL_DLG_PROC* FindDLGProc(char* dlgname)
{
    int i;

    for (i=0; i<tcl_dlg_proc_len; i++)
    {
        if (strcmp(dlgname, tcl_dlg_proc_ptr[i]->dlg_name)==0)
        {
            return (tcl_dlg_proc_ptr[i]->dlg_proc);
        }
    }

    /* Nicht gefunden! */
    return NULL;
}

