/* ------------------------------------------------------------------------
|   Dateiname:      $RCSfile: tt_hash.c,v $
|   Version:        $Revision: 1 $
|   Erstellt am:    00.00.96
|   Geaendert am:   $Date: 19.11.97 9:37 $
|   Komponente:     HASH
|   Erstellt von:   Johannes Weigend
|   Geandert von:   $Author: Johannes $
|   Copyright:      Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
|   Bermerkung:     Tabstop = 4
---------------------------------------------------------------------------*/

#include "rosa.h"
#include "hash.h"
#include "except.h"
#include "stdio.h"
#include "stdlib.h"

ENABLE_ERROR_HANDLING;

#define HEAD(fnkname) printf("\n\nFUNKTION:\t%s\n",#fnkname);
#define BESCHR(b) printf("BESCHREIBUNG:\t%s\n",b);

int main(void)
{
    printf("TESTTREIBER HASH\n\n");

    /* Test 1: Hash erstellen */
    {
        hash *h = hash_new(10);
        
        HEAD(hash_new);
        BESCHR("Hashtabelle mit Groesse 10 erstellen");

        if (h == NULL) {
            printf("NOK: hash_new fehlgeschlagen\n");
        } else {
            printf("OK: Hash erstellt\n");
        }

        hash_delete(h);
        printf("OK: Hash geloescht\n");
    }

    /* Test 2: Hash mit verschiedenen Größen */
    {
        hash *h1 = hash_new(5);
        hash *h2 = hash_new(20);
        hash *h3 = hash_new(100);
        
        HEAD(hash_new);
        BESCHR("Hashtabellen mit verschiedenen Groessen erstellen");

        if (h1 != NULL && h2 != NULL && h3 != NULL) {
            printf("OK: 3 Hashtabellen mit Groessen 5, 20, 100 erstellt\n");
            
            size_t c1 = hash_count(h1);
            size_t c2 = hash_count(h2);
            size_t c3 = hash_count(h3);
            
            printf("OK: Elemente: h1=%zu, h2=%zu, h3=%zu\n", c1, c2, c3);
        } else {
            printf("NOK: hash_new fehlgeschlagen\n");
        }

        hash_delete(h1);
        hash_delete(h2);
        hash_delete(h3);
    }

    return 0;
}
