/* ------------------------------------------------------------------------
|   Dateiname:      $RCSfile: otab.h,v $
|   Version:        $Revision: 1 $
|   Erstellt am:    00.00.96
|   Geaendert am:   $Date: 19.11.97 9:36 $
|   Komponente:     OTAB
|   Erstellt von:   Johannes Weigend
|   Geandert von:   $Author: Johannes $
|   Copyright:      Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
|   Bermerkung:     Tabstop = 4
---------------------------------------------------------------------------*/

#ifndef _OTAB_H_
#define _OTAB_H_

#include "hash.h"
#include "oent.h"

#define OTAB_HASHTABSIZE 97

#define LOCALHOST "localhost"

typedef long OID;

typedef struct _objekt_tabelle {

    hash otab;

} otab;


    /* NEW */
otab * otab_new ();
    /* Initialisierung der Liste ...*/
void otab_init (otab * o);
    /* Loeschen der Liste !! (nicht der Listenelemente) */
void otab_clear (otab * o);
    /* for trace only */
void otab_print (otab * o);


    /* Uebergibt eine Zeiger auf den Entry mit der passenden oid
        RC = OTAB_NOT_FOUND wenn kein Eintrag gefunden wurde */
RC   otab_get    (otab * o, long oid, oent ** oe);

    /* Uebergibt eine Zeiger auf den Entry mit der passenden oid
        RC = RC = OTAB_NOT_FOUND wenn kein Eintrag gefunden wurde */
RC otab_find_by_rid (otab * o,long rid, oent ** oe);


    /* Ruft fuer alle Objekte die UPDATE oder INSERT Funktion auf */
void  otab_commit (otab * o);

    /* Rollback fuer diese OTAB */
void  otab_rollback (otab * o);


    /* PERSISTENTE OBJEKTE */


    /* Haengt eine Kopie des OTAB-Entrys in die OTAB ein und gibt OID zurueck */
void otab_register (otab * o, long * oid, pkrn * p, void * obj, UPD_FCT update_fct, INS_FCT insert_fct, REA_FCT read_fct);

    /* Loescht den Eintrag mit der OID oid aus der OTAB */
void otab_unregister (otab * o, long oid);


    /* NICHT-PERSISTENTE OBJEKTE */

    /* Entfernt einen Eintrag aus der Otab und loescht diesen */
RC  otab_remove (otab * o, long oid);

/* Vergibt naeschste OID -> o->oid wird ueberschrieben, und
       haengt o in die Liste ein. */
void otab_append (otab * o, oent * oe);


#endif /* _OTAB_H_ */

