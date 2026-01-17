/* ------------------------------------------------------------------------
|   Dateiname:      $RCSfile: cent.h,v $
|   Version:        $Revision: 1 $
|   Erstellt am:    00.00.96
|   Geaendert am:   $Date: 19.11.97 9:36 $
|   Komponente:     OTAB
|   Erstellt von:   Johannes Weigend
|   Geandert von:   $Author: Johannes $
|   Copyright:      Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
|   Bermerkung:     Tabstop = 4
---------------------------------------------------------------------------*/

#ifndef _cent_H_
#define _cent_H_

#include "otab.h"

#define MAX_CIDLENGTH 255

    /* Ein Eintrag in der Client-Server Tab*/
typedef struct _cs_tab_entry {

    char cid [MAX_CIDLENGTH];

    otab o;                                 /* Die OTAB eines Clients */

} cent;


    /* Allokation und Initialisierung */
cent * cent_new ();
    /* Loeschen */
cent * cent_delete (cent * c);
    /* Initialisieren  */
void   cent_init (cent * c);

void cent_clear (cent * c);


    /* set... und get... Methoden */
void   cent_set_cid (cent * c, char * client_id);

char * cent_get_cid  (cent * c);

otab * cent_get_otab ();


    /* Vergleicht client_host und pid  */
int cent_cmp (const void * a, const void * b);

    /* Drucken */
void cent_print (const void * c);

    /* Kopieren */
void cent_copy (cent * c, cent * target);

    /* Schluessel ist der Name des Clients */
size_t cent_hash_fnk (const void * c);


#endif /* _cent_H_ */

