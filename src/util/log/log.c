/* ------------------------------------------------------------------------
|   Dateiname:      $RCSfile: log.c,v $
|   Version:        $Revision: 1 $
|   Erstellt am:    00.00.96
|   Geaendert am:   $Date: 19.11.97 9:37 $
|   Komponente:     GLOB
|   Erstellt von:   Johannes Weigend
|   Geandert von:   $Author: Johannes $
|   Copyright:      Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
|   Bermerkung:     Tabstop = 4  Simpler Logmechanismus
--------------------------------------------------------------------------*/

#include <stdarg.h>
#include <stdio.h>

#include "log.h"


static FILE * fp = NULL;


void LOG_OPEN (char * file, char * flags) {

    fp = fopen (file, flags);
    Assert (fp != NULL);
}


void LOG_CLOSE () {

    int rc;

    rc = fclose (fp);
    Assert (rc >= 0);
}

    /* Hier darf kein Assert () verwendet werden */

void LOG (char * txt, ...) {

    va_list args;

    if (! txt) return;

    if (fp == NULL) fp = stderr;

    va_start (args, txt);

    vfprintf (fp, txt, args);

    fflush (fp);

    va_end (args);
}





