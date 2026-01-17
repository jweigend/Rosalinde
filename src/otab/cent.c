/* ------------------------------------------------------------------------
|   Dateiname:      $RCSfile: cent.c,v $
|   Version:        $Revision: 1 $
|   Erstellt am:    00.00.96
|   Geaendert am:   $Date: 19.11.97 9:36 $
|   Komponente:     OTAB
|   Erstellt von:   Johannes Weigend
|   Geandert von:   $Author: Johannes $
|   Copyright:      Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
|   Bermerkung:     Tabstop = 4
---------------------------------------------------------------------------*/

#include "cent.h"



    /* Allokation und Initialisierung */
cent * cent_new () {

    cent * o;

    o = (cent *) malloc (sizeof (cent));
    Assert (o);

    cent_init (o);

    return o;
}


    /* Einzelne Eintraege duerfen NICHT geloescht werden */
cent * cent_delete (cent * c) {

    Assert (c);

    otab_clear (&c->o);

    free (c);

    return NULL;
}


void   cent_init (cent * c) {

    Assert (c);

        memset (c, '\0', sizeof (cent));

    otab_init (&c->o);
}


void cent_clear (cent * c) {

    Assert (c);

    otab_clear (&c->o);

    memset (c, '\0', sizeof (cent));
}


    /* set... und get... Methoden */
void   cent_set_cid  (cent * c, char * client_id) {

    Assert (c && client_id && (strlen (client_id) < MAX_CIDLENGTH));

    strcpy (c->cid, client_id);
}


char * cent_get_cid  (cent * c) {

    Assert (c);
    return c->cid;
}


otab * cent_get_otab (cent * c) {

    Assert (c);
    return &c->o;
}



    /*  Vergleicht Client ID */
int cent_cmp (const void * a, const void * b) {

    Assert (a && b);

    return (strcmp (((cent *) a)->cid, ((cent *) a)->cid));
}

    /* Drucken */
void cent_print (const void * o) {

    cent * oe = (cent *) o;

    Assert (o);

    LOG ("client_id: %s\totab: %x\n", oe->cid, &oe->o);
    otab_print (&oe->o);
}


void cent_copy (cent * o, cent * target) {

    Assert (o && target);

    memcpy (target, o, sizeof (cent));
}


    /* Errechnet den Index in der Hashtabelle */
size_t cent_hash_fnk (const void * c) {

    char * s, * p;
    unsigned h = 0, g;

    Assert (c);
    Assert (((cent *) c) ->cid);

    s = ((cent *) c) ->cid;

        /* hashhpw (c) P.J. Weinberger */
    for (p = s; *p != '\0'; p++) {

        h = (h << 4) + (*p);
        if ( g = h & 0xf0000000 ) {

            h = h ^ (g >> 24);
            h = h ^ g;
        }
    }
    return h;
}

