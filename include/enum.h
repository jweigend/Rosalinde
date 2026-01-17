/* ------------------------------------------------------------------------
|   Dateiname:      $RCSfile: enum.h,v $
|   Version:        $Revision: 1 $
|   Erstellt am:    12.04.95
|   Geaendert am:   $Date: 19.11.97 9:36 $
|   Komponente:     misc
|   Erstellt von:   Prof. Johannes Siedersleben
|   Geandert von:   $Author: Johannes $
|   Copyright:      Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
|   Bermerkung:     Tabstop = 4
---------------------------------------------------------------------------*/

#ifndef _ENUM_H_
#define _ENUM_H_

#include "rosa.h"
#include "strg.h"

#define ENUM_MAX 2          /* Anzahl der  Repraesentationen */

typedef enum { KURZ, LANG } RPRS;
        /* die beiden bisher verwendeten */

#define GEN_ENUM(T)                                     \
    typedef int T;                                      \
    void T## _in (T * a, RC * rc, RPRS r, char * s);   \
    char * T## _out (T * a,  RPRS r);                  \
    char ** T## _values (RPRS r);                      \
    void T## _db_in (T * a, strg * flatstring);        \
    void T## _db_out (T * a, strg * flatstring);       \
    void T## _print (T * a);                           \
    T* T## _new ();                                \
    void T## _delete (T * a);                          \
    void T## _clear (T * a);                           \
    void T## _init (T * a);

/************************************************************************************/
/**** hier werden alle Enums benannt*************************************************/
/************************************************************************************/


GEN_ENUM(anrd)
GEN_ENUM(whrg)

#endif
