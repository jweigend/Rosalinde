/* ------------------------------------------------------------------------
|   Dateiname:      $RCSfile: oent.h,v $
|   Version:        $Revision: 1 $
|   Erstellt am:    00.00.96
|   Geaendert am:   $Date: 19.11.97 9:36 $
|   Komponente:     OTAB
|   Erstellt von:   Johannes Weigend
|   Geandert von:   $Author: Johannes $
|   Copyright:      Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
|   Bermerkung:     Tabstop = 4
---------------------------------------------------------------------------*/

#ifndef _OENT_H_
#define _OENT_H_

#include "pkrn.h"
#include "brok.h"


    /* Ein Eintrag in der OTAB */
typedef struct _otab_entry {

    long oid;                               /* Die Objekt ID  (eindeutig)*/
                                            /* OID ist unabhaengig vom rid */
    pkrn * p;                               /* PKRN bei persistenten Objekten */

    void * obj;                             /* bei nichtpersistenten Objekten */

} oent;


    /* Allokation und Initialisierung */
oent * oent_new ();
    /* Loeschen */
oent * oent_delete (oent * o);
    /* Initialisieren  */
void   oent_init (oent * o);

void   oent_clear (oent * o);


    /* set... und get... Methoden */
void   oent_set_oid (oent * o, long oid);

    /* Fuer persistente Objekte */
void   oent_set_pkrn (oent * o, pkrn * pk);

    /* Fuer nichtpersistente Objekte */
void   oent_set_obj (oent * o, void * obj);


long oent_get_oid  (oent * o);

pkrn * oent_get_pkrn (oent * o);

void * oent_get_obj (oent * o);


    /* Vergleicht nur OID */
int oent_cmp (const void * a, const void * b);

    /* Drucken */
void oent_print (const void * o);

    /* Kopieren */
void oent_copy (oent * o, oent * target);


    /* Schluessel ist die oid */
size_t oent_hash_fnk (const void * o);

#endif /* _OENT_H_ */

