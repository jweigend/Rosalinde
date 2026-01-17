/* ------------------------------------------------------------------------
|   Dateiname:      $RCSfile: template.c,v $
|   Version:        $Revision: 1 $
|   Erstellt am:    00.00.96
|   Geaendert am:   $Date: 19.11.97 9:36 $
|   Komponente:     DLG
|   Erstellt von:   Christian Stoellinger
|   Geandert von:   $Author: Johannes $
|   Copyright:      Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
|   Bermerkung:     Tabstop = 4
---------------------------------------------------------------------------*/


#ifndef _DLG_SBRO_H_
#define _DLG_SBRO_H_

#include "tcl_dlg.h"


int DLGProc_SelectBroker(HWND* hwnd, char* msg, void* param);

extern char der_broker_host[200];

#endif /* _DLG_SBRO_H_ */
