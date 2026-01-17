/* ------------------------------------------------------------------------
|   Dateiname:      $RCSfile: bent.c,v $
|   Version:        $Revision: 1 $
|   Erstellt am:    00.00.96
|   Geaendert am:   $Date: 19.11.97 9:36 $
|   Komponente:     BROKER
|   Erstellt von:   Johannes Weigend
|   Geandert von:   $Author: Johannes $
|   Copyright:      Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
|   Bermerkung:     Tabstop = 4
---------------------------------------------------------------------------*/

#include <string.h>
#include <malloc.h>

#include "bent.h"


    /* Allokation und Initialisierung */
bent * bent_new () {

    bent * b;

    b = (bent *) malloc (sizeof (bent));
    Assert (b);

    bent_init (b);

    return b;
}

    /* Loeschen eines dynamisch allokierten Objekts*/
bent * bent_delete (bent * b) {

    Assert (b);

    free (b);

    return NULL;
}

    /* Sicherheitshalber alles auf 0 setzten */
void   bent_init (bent * b) {

    Assert (b);
    memset (b, '\0', sizeof (bent));
}


    /* set... und get... Methoden */
void   bent_set_host  (bent * b, char * hostname) {

    Assert (b && hostname);
    if (strlen (hostname) >= MAX_HOSTNAME) throw (INVALID_ARGUMENT);

    strcpy (b->host, hostname);
}


void   bent_set_svcn  (bent * b, char * servicename) {

    Assert (b && servicename);
    if (strlen(servicename) >= MAX_SVCNNAME) throw (INVALID_ARGUMENT);

    strcpy (b->svcn, servicename);
}

void   bent_set_prgnr (bent * b, long programmnr) {

    Assert (b);
    if (programmnr < MIN_RPC_PRG_ID) throw (INVALID_ARGUMENT);

    b->prgnr = programmnr;
}

void   bent_set_versnr (bent * b, long versionsnr) {

    Assert (b);
    if (versionsnr < 1) throw (INVALID_ARGUMENT);

    b->versnr = versionsnr;
}

void   bent_set_proto (bent * b, char * proto) {

    Assert (b && proto);
    if (strlen (proto) >= MAX_PROTONAME) throw (INVALID_ARGUMENT);

    strcpy (b->proto, proto);
}

char * bent_get_host  (bent * b) {

    Assert (b);

    return b->host;
}

char * bent_get_svcn  (bent * b) {

    Assert (b);

    return b->svcn;
}

long   bent_get_prgnr (bent * b) {

    Assert (b);

    return b->prgnr;
}

long  bent_get_versnr (bent * b) {

    Assert (b);

    return b->versnr;
}

char * bent_get_proto (bent * b) {

    Assert (b);

    return b->proto;
}

    /* Kopieren */
void   bent_copy (bent * b, bent * target) {

    Assert (b && target);

    memcpy (target, b, sizeof (bent));
}

    /* Vergleichsfunktion  */
int bent_cmp (const void * a, const void * b) {

    Assert (a && b);

    return strcmp (((bent *) a)->svcn, ((bent *) b)->svcn);
}

    /* Vergleiche auf Identitaet */
int bent_cmp_all (const void * a, const void * b) {

    bent * ba, * bb;

    Assert (a && b);

    ba = (bent *) a;
    bb = (bent *) b;

    return (strcmp (ba->svcn, bb->svcn)   ||
            strcmp (ba->proto, bb->proto) ||
            strcmp (ba->host, bb->host)   ||
            ba->prgnr != bb->prgnr        ||
            ba->versnr != bb->versnr);
}


    /* Druckt den broker entry */
void bent_print (const void * be) {

    bent * b = (bent *) be;

    Assert (b);

    LOG ("Host: %s  Svcn: %s  PrgId: %ld  Versnr: %ld  Proto: %s\n",
                                b->host, b->svcn, b->prgnr, b->versnr, b->proto);
}

    /* Errechnet den Index in der Hashtabelle */
size_t bent_hash_fnk (const void * b) {

    char * s, * p;
    unsigned h = 0, g;

    Assert (b);
    Assert (((bent *) b) ->svcn);

    s = ((bent *) b) ->svcn;

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

