/* ------------------------------------------------------------------------
|   Dateiname:      $RCSfile: hash.h,v $
|   Version:        $Revision: 1 $
|   Erstellt am:    00.00.96
|   Geaendert am:   $Date: 19.11.97 9:36 $
|   Komponente:     HASH
|   Erstellt von:   Johannes Weigend
|   Geandert von:   $Author: Johannes $
|   Copyright:      Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
|   Bermerkung:     Tabstop = 4
---------------------------------------------------------------------------*/

#ifndef _HASH_H_
#define _HASH_H_

#include <stdlib.h>
#include "list.h"

typedef struct {
  list ** plpArray;     /* Ein Array aus Listen-Pointern */
  size_t  size;         /* Groesse der Hashtabelle */
  size_t count;
} hash;


#define HASH_NOT_FOUND -10

        /* Hashfunktion berechnet die Adress aus einem
           Schluessel (void*) */
typedef size_t (*HFNK)(const void *);

        /* Printfunktion zum Ausdruch der ueber die Hashtabelle
           gespeicherten Daten Debug */
typedef void (*PRINT_FCT)(const void *);

        /* Callback zum Itterieren */
typedef void (*HASH_CALLBACK_FNK)(void * obj, void * params);


        /* Allokation */
hash * hash_new (size_t hs);

        /* Initialisierung */
void hash_init (hash * hp, size_t hs);

        /* Deallocation */
hash * hash_delete (hash * hp);
        /* Deallocation aller Listen
           (wenn deep == TRUE auch der Objekt)*/
void hash_clear (hash * hp, BOOL deep);

        /* Einfuegen eines Elements "obj" mithilfe der Hashfunktion
           "hfnk" in Hashtabelle "hp" */
void hash_insert (hash * hp, void * obj, HFNK hfnk);

        /* Ausdruck aller in der Tabelle eingefuegten Daten
           pl muss den jeweiligen Datentyp drucken koennen */
void hash_print (hash * hp, PRINT_FCT pl);

        /* Gibt einen Zeiger auf das ueber "key"
           ansprechbare Element zurueck (oder NULL) */
void * hash_get (hash * hp, void * key, HFNK hfnk, COMP_FCT cf);

        /* Entfernt Element mit Schuessel key aus der Hashtab */
void * hash_remove (hash * hp, void * key, HFNK hfnk, COMP_FCT cf);

        /* Itteriert ueber alle Elemente und ruft callbackfnk auf */
void hash_itterate (hash * h, HASH_CALLBACK_FNK callbackfnk, void * params);

        /* Gibt die Anzahl Elemente in der Hashtabelle zurueck */
size_t hash_count (hash * h);

#endif /* _HASH_H_ */

