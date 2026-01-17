/* ------------------------------------------------------------------------
|   Dateiname:      $RCSfile: ctab.h,v $
|   Version:        $Revision: 1 $
|   Erstellt am:    00.00.96
|   Geaendert am:   $Date: 19.11.97 9:36 $
|   Komponente:     ctab
|   Erstellt von:   Johannes Weigend
|   Geandert von:   $Author: Johannes $
|   Copyright:      Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
|   Bermerkung:     Tabstop = 4
---------------------------------------------------------------------------*/

#ifndef _CSTB_H_
#define _CSTB_H_

#include "hash.h"
#include "cent.h"
#include "otab.h"

#define CSTB_HASHTABSIZE 97


typedef struct _client_server_tabelle {

    hash ctab;

} ctab;


/* Kein new ! Pro Server 1x ctab */

    /* Initialisierung der Liste ...*/
void ctab_init ();
    /* Loeschen der Liste !! (nicht der Listenelemente) */
void ctab_clear ();
    /* for trace only */
void ctab_print ();

    /* Gibt OID zurueck */
void ctab_register (char * cid, long * oid, pkrn * p, void * obj, UPD_FCT update_fct, INS_FCT insert_fct, REA_FCT read_fct);

void ctab_unregister (char * cid, long oid);


    /* Ruft fuer alle Objekte eines Clients die UPDATE Funktion auf */
void  ctab_commit (char * cid);

    /* Rollback fuer alle Objekte eines Clients */
void  ctab_rollback (char * cid);


    /* Gibt den passenden centry zurueck */
cent * ctab_get (char * cid);

void * ctab_get_obj (char * cid, long oid);

#endif /* _CSTB_H_ */

