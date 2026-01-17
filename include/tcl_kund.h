/* Einfacher ADT zum Testen der TCL-Moeglichkeiten */


#include "tk.h"


int TCL_KUND_cmd(ClientData clientData, Tcl_Interp* interp, int agrc, char* argv[]);

void TCL_KUND_delete(ClientData clientData);

int TCL_KUND_object_cmd(ClientData clientData, Tcl_Interp* interp, int argc, char* argv[]);

