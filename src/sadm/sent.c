/* ------------------------------------------------------------------------
|   Dateiname:      $RCSfile: sent.c,v $
|   Version:        $Revision: 1 $
|   Erstellt am:    00.00.96
|   Geaendert am:   $Date: 19.11.97 9:36 $
|   Komponente:     SERVER-ADMINISTRATOR
|   Erstellt von:   Johannes Weigend
|   Geandert von:   $Author: Johannes $
|   Copyright:      Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
|   Bermerkung:     Tabstop = 4
---------------------------------------------------------------------------*/

#include <string.h>
#include <malloc.h>

#include "sent.h"


    /* Allokation und Initialisierung */
sent * sent_new () {

    sent * s;

    s = (sent *) malloc (sizeof (sent));
    Assert (s);

    sent_init (s);

    return s;
}

    /* Loeschen eines dynamisch allokierten Objekts*/
sent * sent_delete (sent * s) {

    Assert (s);

    free (s);

    return NULL;
}

    /* Sicherheitshalber alles auf 0 setzten */
void   sent_init (sent * s) {

    Assert (s);
    memset (s, '\0', sizeof (sent));
}


    /* set... und get... Methoden */

void   sent_set_svcn  (sent * s, char * servicename) {

    Assert (s);
    Assert (servicename);
    Assert (strlen(servicename) < MAX_SVCNNAME);

    strcpy (s->svcn, servicename);
}


void   sent_set_client (sent * s, CLIENT * cl) {

    Assert (s && cl);

    s->cl = cl;
}


CLIENT * sent_get_client  (sent * s) {

    Assert (s);

    return s->cl;
}

char * sent_get_svcn  (sent * s) {

    Assert (s);

    return s->svcn;
}


    /* Kopieren */
void   sent_copy (sent * s, sent * target) {

    Assert (s);
    Assert (target);

    memcpy (target, s, sizeof (sent));
}

    /* Vergleichsfunktion  */
int sent_cmp (const void * a, const void * s) {

    Assert (a);
    Assert (s);

    return strcmp (((sent *) a)->svcn, ((sent *) s)->svcn);
}

    /* Druckt den entry */
void sent_print (const void * be) {

    sent * s = (sent *) be;

    Assert (s);

    LOG ("Client: %x  Svcn: %s\n", s->cl, s->svcn);
}

    /* Errechnet den Index in der Hashtabelle */
size_t sent_hash_fnk (const void * s) {

    char * c, * p;
    unsigned h = 0, g;

    Assert (s);
    Assert (((sent *) s) ->svcn);

    c = ((sent *) s) ->svcn;

        /* hashhpw (c) P.J. Weinberger */
    for (p = c; *p != '\0'; p++) {

        h = (h << 4) + (*p);
        if ( g = h & 0xf0000000 ) {

            h = h ^ (g >> 24);
            h = h ^ g;
        }
    }

    return h;

}

