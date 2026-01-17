/* ------------------------------------------------------------------------
|   Dateiname:      $RCSfile: tt_misc.c,v $
|   Version:        $Revision: 1 $
|   Erstellt am:    00.00.96
|   Geaendert am:   $Date: 19.11.97 9:37 $
|   Komponente:     MISC
|   Erstellt von:   Johannes Weigend
|   Geandert von:   $Author: Johannes $
|   Copyright:      Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
|   Bermerkung:     Tabstop = 4
---------------------------------------------------------------------------*/

#include "rosa.h"
#include "misc.h"
#include "strg.h"
#include "except.h"
#include "stdio.h"
#include "stdlib.h"

ENABLE_ERROR_HANDLING;

#define HEAD(fnkname) printf("\n\nFUNKTION:\t%s\n",#fnkname);
#define BESCHR(b) printf("BESCHREIBUNG:\t%s\n",b);

int main(void)
{
    printf("TESTTREIBER MISC\n\n");

    /* Test 1: Integer <-> String Konvertierung */
    {
        strg *s = strg_new(50);
        int value = 42;
        int result;
        
        HEAD(intg_db_out und intg_db_in);
        BESCHR("Integer in String konvertieren und zuruecklesen");

        intg_db_out(&value, s);
        strg_print(s);
        printf("OK: Integer in String konvertiert\n");

        intg_db_in(&result, s);
        if (result == value) {
            printf("OK: Integer korrekt zurueckgelesen: %d\n", result);
        } else {
            printf("NOK: Integer stimmt nicht ueberein\n");
        }

        strg_delete(s);
    }

    /* Test 2: Long <-> String Konvertierung */
    {
        strg *s = strg_new(50);
        long value = 123456789L;
        long result;
        
        HEAD(long_db_out und long_db_in);
        BESCHR("Long in String konvertieren und zuruecklesen");

        long_db_out(&value, s);
        strg_print(s);
        printf("OK: Long in String konvertiert\n");

        long_db_in(&result, s);
        if (result == value) {
            printf("OK: Long korrekt zurueckgelesen: %ld\n", result);
        } else {
            printf("NOK: Long stimmt nicht ueberein\n");
        }

        strg_delete(s);
    }

    return 0;
}
