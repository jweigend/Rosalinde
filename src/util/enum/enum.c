/* ------------------------------------------------------------------------
|   Dateiname:      $RCSfile: enum.c,v $
|   Version:        $Revision: 1 $
|   Erstellt am:    10.09.94
|   Geaendert am:   $Date: 19.11.97 9:36 $
|   Komponente:     GLOB
|   Erstellt von:   J. Siedersleben
|   Geandert von:   $Author: Johannes $
|   Copyright:      Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
|   Bermerkung:     Tabstop = 4
--------------------------------------------------------------------------*/

#include "enum.h"
#include "misc.h"

#define GEN_ENUM_IMP(T)                                     \
                                                            \
    char * T##_tab[ENUM_MAX][T##_MAX] = T##_TAB;            \
                                                            \
    void T ## _in (T * a, RC * rc, RPRS r, char * s) {      \
        int i;                                              \
        for (i = 0;                                         \
        i < T##_MAX && strcmp (T##_tab[r][i], s); i++);     \
            (i < T##_MAX) ? (*a = i, *rc = OK) : (*rc = NOK); \
    }                                                       \
                                                            \
                                                            \
    char * T##_out (T * a, RPRS r) {                        \
        return T##_tab[r][*a];                              \
    }                                                       \
                                                            \
    void T ## _db_in (T * a, strg * flatstring) {           \
        Assert (a && flatstring);                           \
        intg_db_in (a, flatstring);                         \
    }                                                       \
                                                            \
    void T ## _db_out ( T * a, strg * flatstring) {         \
        Assert (a && flatstring);                           \
        intg_db_out (a, flatstring);                        \
    }                                                       \
                                                            \
    void T ## _print ( T * a) {                             \
        Assert (a);                                         \
        LOG ("%s\n", T ## _out (a, LANG));                  \
    }                                                       \
                                                            \
    T * T ## _new () {                                   \
        T * a;                                              \
        a = ( T * ) malloc (sizeof(T));                     \
        Assert (a);                                         \
        T ## _init (a);                                     \
        return a;                                           \
    }                                                       \
                                                            \
    void T ## _delete ( T * a) {                            \
        Assert (a);                                         \
        T ## _clear (a);                                    \
        free (a);                                           \
    }                                                       \
                                                            \
    void T ## _clear ( T * a) {                             \
        Assert (a);                                         \
    }                                                       \
                                                            \
    void T ## _init ( T * a ) {                             \
        Assert (a);                                         \
        *a = 0;                                             \
    }


/*******************************************************************/
/****** hier werden alle Enums definiert ***************************/
/*******************************************************************/




/********************* ENUM Anrede *********************************/

#define anrd_MAX  4
#define anrd_TAB  {{ "?",     "Hr",   "Fr",   "Fa" },       \
           { "undef", "Herr", "Frau", "Firma" }}

GEN_ENUM_IMP(anrd)





/********************* ENUM Waehrung *********************************/

#define whrg_MAX  4
#define whrg_TAB  {{ "?",     "DM",     "FF",    "$" },       \
           { "undef", "D-Mark", "Franc", "Dollar" }}

GEN_ENUM_IMP(whrg)






