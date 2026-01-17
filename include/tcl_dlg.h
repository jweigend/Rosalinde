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


#ifndef _TCL_DIALOG_H_
#define _TCL_DIALOG_H_

#include "tk.h"

#define DLG_INIT    "INIT"
#define DLG_DESTROY "DESTROY"

typedef struct tagHWND
{
    Tcl_Interp*     interp;
    void*           data;
    char*           window_name;
} HWND;

typedef int (TCL_DLG_PROC)(HWND* dlg, char* msg, void* param);

/* Diese Struktur wird fuer jeden Dialog zur Laufzeit angelegt. */
typedef struct tagTCLDialog
{
    char*           dlg_name;    /* Dieser Name wird fuer die Dialogfunktion gebraucht */
    TCL_DLG_PROC*   dlg_proc;    /* Pointer auf die Dialogfunktion */
    Tcl_Interp*     dlg_interp;  /* Interpreter */
    char*           dlg_wndname; /* Window-Name von TK */
    void*           dlg_data;    /* Anwendungsspezifische Daten */
} TCL_Dialog;

/* Funktionen fuer TCL */
int  TCL_Dialog_cmd(ClientData clientData, Tcl_Interp* interp, int agrc, char* argv[]);
void TCL_Dialog_delete(ClientData clientData);
int  TCL_Dialog_object_cmd(ClientData clientData, Tcl_Interp* interp, int argc, char* argv[]);

/* Interne Dialogfunktionen fuer TCL/TK */
void Dialog_create(TCL_Dialog** dlg);
void Dialog_delete(TCL_Dialog*  dlg);
void Dialog_setproc(TCL_Dialog* dlg, char* dlgname, Tcl_Interp* interp);

/* Funktionen fuer den C-Programmierer */
void* GetWindowLong(HWND* hwnd, int index);
void  SetWindowLong(HWND* hwnd, int index, void* data);

/* Dialogproceduren - Verwaltung */
int  RegisterDLGProc(char* dlg_name, TCL_DLG_PROC* dlg_proc);
TCL_DLG_PROC* FindDLGProc(char* dlg_name);


/* Allgemeine Dialogfunktionen, die in der Dialogfunktion benutzt werden duerfen: */


#endif /* _TCL_DIALOG_H_ */

