/* ------------------------------------------------------------------------
|   Dateiname:      $RCSfile: tt_log.c,v $
|   Version:        $Revision: 1 $
|   Erstellt am:    00.00.96
|   Geaendert am:   $Date: 19.11.97 9:37 $
|   Komponente:     LOG
|   Erstellt von:   Johannes Weigend
|   Geandert von:   $Author: Johannes $
|   Copyright:      Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
|   Bermerkung:     Tabstop = 4
---------------------------------------------------------------------------*/

#include "rosa.h"
#include "log.h"
#include "except.h"
#include "stdio.h"
#include "stdlib.h"

ENABLE_ERROR_HANDLING;

#define HEAD(fnkname) printf("\n\nFUNKTION:\t%s\n",#fnkname);
#define BESCHR(b) printf("BESCHREIBUNG:\t%s\n",b);

int main(void)
{
    printf("TESTTREIBER LOG\n\n");

    /* Test 1: LOG auf STDERR (Standard) */
    {
        HEAD(LOG);
        BESCHR("Ausgabe auf STDERR");

        LOG("Test: Einfache Nachricht\n");
        LOG("Test: Zahl = %d, String = %s\n", 42, "Hallo");
        printf("OK: LOG auf STDERR funktioniert\n");
    }

    /* Test 2: LOG in Datei */
    {
        HEAD(LOG_OPEN);
        BESCHR("Ausgabe in Logdatei umleiten");

        LOG_OPEN("/tmp/test.log", "w");
        LOG("Test: Nachricht in Datei\n");
        LOG("Test: Mit Parametern: %d, %s\n", 123, "Text");
        LOG_CLOSE();
        
        FILE *fp = fopen("/tmp/test.log", "r");
        if (fp != NULL) {
            printf("OK: Logdatei erstellt und Eintraege geschrieben\n");
            fclose(fp);
        } else {
            printf("NOK: Logdatei konnte nicht geoeffnet werden\n");
        }
    }

    return 0;
}
