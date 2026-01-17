/* ------------------------------------------------------------------------
|   Dateiname:      $RCSfile: dbms.h,v $
|   Version:        $Revision: 1 $
|   Erstellt am:    00.00.96
|   Geaendert am:   $Date: 19.11.97 9:36 $
|   Komponente:     DB
|   Erstellt von:   Johannes Weigend
|   Geandert von:   $Author: Johannes $
|   Copyright:      Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
|   Bermerkung:     Tabstop = 4
---------------------------------------------------------------------------*/

#ifndef _DB_H_
#define _DB_H_

#include "btab.h"

/* Server only */
void dbms_open ();

void dbms_close ();

/* Server und Clients */
void dbms_commit ();

void dbms_rollback ();

    /* Erzwingt am Server ein Neuerzeugen aller BTAB - Handles.
           mit zusaetzlicher Anfrage am Broker */
void dbms_data_server_changed ();

    /* Gibt einen gueltigen BTAB * zurueck. */
btab * dbms_get_btab (char * svcn);

#endif /* _DB_H_ */
