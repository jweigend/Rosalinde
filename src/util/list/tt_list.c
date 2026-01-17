/* ------------------------------------------------------------------------
|   Dateiname:      $RCSfile: tt_list.c,v $
|   Version:        $Revision: 1 $
|   Erstellt am:    00.00.96
|   Geaendert am:   $Date: 19.11.97 9:37 $
|   Komponente:     LIST
|   Erstellt von:   Johannes Weigend
|   Geandert von:   $Author: Johannes $
|   Copyright:      Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
|   Bermerkung:     Tabstop = 4
---------------------------------------------------------------------------*/

#include "rosa.h"
#include "list.h"
#include "except.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

ENABLE_ERROR_HANDLING;

#define HEAD(fnkname) printf("\n\nFUNKTION:\t%s\n",#fnkname);
#define BESCHR(b) printf("BESCHREIBUNG:\t%s\n",b);

int main(void)
{
    printf("TESTTREIBER LIST\n\n");

    /* Test 1: Liste erstellen und Elemente hinzufügen */
    {
        list *l = list_new();
        
        HEAD(list_new und list_append);
        BESCHR("Liste erstellen und Elemente einfuegen");

        if (l == NULL) {
            printf("NOK: list_new fehlgeschlagen\n");
        } else {
            printf("OK: Liste erstellt\n");
            list_append(l, "Element1");
            list_append(l, "Element2");
            printf("OK: 2 Elemente eingefuegt\n");
        }

        list_delete(l);
    }

    /* Test 2: List größe prüfen */
    {
        list *l = list_new();
        
        HEAD(list_nbr_of_el);
        BESCHR("Groesse der Liste pruefen");

        list_append(l, "Test1");
        list_append(l, "Test2");

        int size = list_nbr_of_el(l);
        if (size == 2) {
            printf("OK: Liste hat 2 Elemente\n");
        } else {
            printf("NOK: Liste hat falsche Groesse: %d\n", size);
        }

        list_delete(l);
    }

    /* Test 3: List leeren */
    {
        list *l = list_new();
        
        HEAD(list_clear);
        BESCHR("Liste leeren");

        list_append(l, "A");
        list_append(l, "B");
        list_clear(l);

        if (list_nbr_of_el(l) == 0) {
            printf("OK: Liste ist leer\n");
        } else {
            printf("NOK: Liste sollte leer sein\n");
        }

        list_delete(l);
    }

    return 0;
}
