/* -------------------------------------------------------------------------
|   Dateiname:      $RCSfile: pkrn.h,v $
|   Version:        $Revision: 1 $
|   Erstellt am:    00.00.96
|   Geaendert am:   $Date: 19.11.97 9:36 $
|   Komponente:     PERSISTENT
|   Erstellt von:   Johannes Weigend, Ludwig Grill, Andreas Huber
|                   Marco Hoffman, Prof. Johannes Siedersleben.
|   Geandert von:   $Author: Johannes $
|   Copyright:      Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
|   Bermerkung:     Tabstop = 4
---------------------------------------------------------------------------*/

#ifndef _PKRN_H_
#define _PKRN_H_


#include "rosa.h"
#include "strg.h"

    /* Objectstates OS */

typedef enum { os_new, os_clean, os_dirty } object_state;

    /* Zeiger auf update-Funktion
         Parameter: 1. Zeiger auf ADT
         Parameter: 2. rid
    */
typedef void ( *UPD_FCT )(void *, long );


    /* Zeiger auf insert-Funktion
         Parameter: 1. Zeiger auf ADT
         Parameter: 2. Vergebener rid wird zurueckgegeben
    */
typedef void ( *INS_FCT )(void *, long *);

    /* Lesefunktion wie Updatefct */
typedef UPD_FCT REA_FCT;


typedef struct {
    long    rid;            /* eindeutiger rid, entspricht Offset in btab */
    object_state state;     /* Zustand des Objektes */
    UPD_FCT update_fct;     /* Zeiger auf update-Funktion */
    INS_FCT insert_fct;     /* Zeiger auf insert-Funktion */
    REA_FCT reread_fct;     /* Zeiger auf reread-Funktion   */
    void *  owner;          /* Zeiger auf den Besitzer des pkrn */
    long    oid;            /* Die OID als Referenz zum Eintrag in der otab */
    long    change_cnt;     /* Sichert Konsistenz in der DB */
} pkrn;



void pkrn_init ( pkrn * pk);
    /* initialisieren der Daten von pkrn */

void pkrn_clear ( pkrn * pk );

void pkrn_insert ( pkrn * pk);
    /* Zustandsuebergang von new nach clean, erstes Schreiben auf Datenbank */

void pkrn_modify ( pkrn * pk );
    /* setzt den Zustand von clean auf dirty */

void pkrn_update ( pkrn * pk );
    /* schreibt veraenderten Datensatz auf Datei zurueck */

void pkrn_reread ( pkrn * pk);
    /* List Datensatz nochmal aus der Datei (Rollback) */

void pkrn_db_in ( pkrn * pk, strg * s );
    /* formt pkrn in einen strg um zum Schreiben auf Datenbank */

void pkrn_db_out ( pkrn * pk, strg * s );
    /* liest aus s die fuer den pkrn wichtigen Daten aus */

void pkrn_print ( pkrn * pk );
    /* druckt den pkrn auf stdout */

object_state pkrn_state ( pkrn * pk );
    /* Gibt den aktuellen status zurueck */

void pkrn_register ( pkrn * pk, void * owner, long oid, UPD_FCT upd, INS_FCT ins, REA_FCT rea);
    /* Registrierung des PKRN : Zustand wird auf clean gesetzt */

void pkrn_unregister (pkrn * pk);
    /* Deregistrierung des PKRN */

long pkrn_get_oid (pkrn * pk);
    /* Gibt die OID zurueck */

long pkrn_get_rid (pkrn * pk);
    /* Gibt die RowID zurueck */
#endif /* _PKRN_H_ */
