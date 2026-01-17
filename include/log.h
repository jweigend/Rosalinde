/* ------------------------------------------------------------------------
|   Dateiname:      $RCSfile: log.h,v $
|   Version:        $Revision: 1 $
|   Erstellt am:    00.00.96
|   Geaendert am:   $Date: 19.11.97 9:36 $
|   Komponente:     GLOB
|   Erstellt von:   Johannes Weigend
|   Geandert von:   $Author: Johannes $
|   Copyright:      Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
|   Bermerkung:     Tabstop = 4
--------------------------------------------------------------------------*/
#ifndef _LOG_H_
 #define _LOG_H_

#include "rosa.h"

    /* Schreibt in eine Logdatei oder auf STDERR */
void LOG (char * txt, ...);

    /* offnet die Logdatei siehe fopen () */
void LOG_OPEN (char * file, char * flags);

    /* schliesst die Logdatei */
void LOG_CLOSE ();


#endif /* _LOG_H_ */
