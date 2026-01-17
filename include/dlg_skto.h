/* ------------------------------------------------------------------------
|	Dateiname:		$RCSfile: dlg_skto.h,v $											
|	Version:		$Revision: 1 $										
|	Erstellt am:	00.00.96												
|	Geaendert am:	$Date: 19.11.97 9:36 $											
|	Komponente:		DLG												
|	Erstellt von:	Christian Stoellinger												
|	Geandert von:	$Author: Johannes $												
|	Copyright:		Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
|	Bermerkung:		Tabstop = 4												
---------------------------------------------------------------------------*/


#ifndef _DLG_SKTO_H_
#define _DLG_SKTO_H_

#include "tcl_dlg.h"
#include "knto.h"

int DLGProc_SucheKonto(HWND* hwnd, char* msg, void* param);
knto* SKTO_get_Konto();

#endif /* _DLG_SKTO_H_ */
