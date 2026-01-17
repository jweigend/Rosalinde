/* ------------------------------------------------------------------------
|   Dateiname:      $RCSfile: cmgr.h,v $
|   Version:        $Revision: 1 $
|   Erstellt am:    00.00.96
|   Geaendert am:   $Date: 19.11.97 9:36 $
|   Komponente:     CLIENT  und SERVER
|   Erstellt von:   Johannes Weigend
|   Geandert von:   $Author: Johannes $
|   Copyright:      Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
|   Bermerkung:     Tabstop = 4
---------------------------------------------------------------------------*/

#ifndef _cmgr_H_
#define _cmgr_H_

/* Der CMGR (ClientManager) kuemmert sich um die Verwaltung
   der ClientIDs und ServerIDs.
   Jeder Server hat waehrend seiner gesamten Lebensdauer genau
   eine eindeutige ServerID (sid).
   Die ClientID ist entweder identisch mit der ServerID, oder
   ist die ID der aktuellen Clientanfrage */

void cmgr_init ();

/*  Bei einem "nur" Client sind ServerID (sid) und
    ClientID (cid) identisch.
    Bei dem Server identifiziert die sid den eigenen
    Server und die cid die Anfrage eines Clients */


    /* Setzt ClientID */
void   cmgr_set_cid  (char * cid);

    /* Gibt ClientID zurueck */
char * cmgr_get_cid  ();

    /* Gibt ServerID zurueck */
char * cmgr_get_sid ();


#endif /* _cmgr_H_ */
