/* ------------------------------------------------------------------------
|   Dateiname:      $RCSfile: oent.c,v $
|   Version:        $Revision: 1 $
|   Erstellt am:    00.00.96
|   Geaendert am:   $Date: 19.11.97 9:36 $
|   Komponente:     OTAB
|   Erstellt von:   Johannes Weigend
|   Geandert von:   $Author: Johannes $
|   Copyright:      Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
|   Bermerkung:     Tabstop = 4
---------------------------------------------------------------------------*/

#include "oent.h"



    /* Allokation und Initialisierung */
oent * oent_new () {

    oent * o;

    o = (oent *) malloc (sizeof (oent));
    Assert (o);

    oent_init (o);

    return o;
}


    /* Einzelne Eintraege duerfen NICHT geloescht werden */
oent * oent_delete (oent * o) {

    Assert (o);

    free (o);

    return NULL;
}

void   oent_init (oent * o) {

    Assert (o);

    memset (o, '\0', sizeof (oent));

}

void   oent_clear (oent *o) {

    Assert (o);

    memset (o, '\0', sizeof(oent));
}

void   oent_set_oid (oent * o, long oid) {

    Assert (o && (oid >= 0));
    o->oid = oid;
}

void   oent_set_pkrn (oent * o, pkrn * pk) {

    Assert (o && pk);
    o->p = pk;
}

void oent_set_obj (oent * o, void * obj) {

    Assert (o && obj);
    o->obj = obj;
}


long oent_get_oid  (oent * o) {

    Assert (o);
    return o->oid;
}

pkrn * oent_get_pkrn (oent * o) {

    Assert (o);
    return o->p;
}

void * oent_get_obj (oent * o) {

    Assert (o);
    return o->obj;
}


    /* Vergleicht nur OID */
int oent_cmp (const void * a, const void * b) {

    Assert (a && b);

    return (((oent *) a)->oid != ((oent *) b)->oid);
}

    /* Drucken */
void oent_print (const void * o) {

    oent * oe = (oent *) o;

    Assert (o);

    LOG ("oid: %ld\tprkn: %x\tobj: %x\n", oe->oid, oe->p, oe->obj );

    if (oe->p) pkrn_print (oe->p);
}


void oent_copy (oent * o, oent * target) {

    Assert (o && target);

    memcpy (target, o, sizeof (oent));
}

    /* Errechnet den Index in der Hashtabelle */
size_t oent_hash_fnk (const void * o) {

    return (((oent *) o)->oid);
}

