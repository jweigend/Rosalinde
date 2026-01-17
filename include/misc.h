/* ------------------------------------------------------------------------
|   Dateiname:      $RCSfile: misc.h,v $
|   Version:        $Revision: 1 $
|   Erstellt am:    00.00.96
|   Geaendert am:   $Date: 19.11.97 9:36 $
|   Komponente:     MISC STRG
|   Erstellt von:   Johannes Siedersleben
|   Geandert von:   $Author: Johannes $
|   Copyright:      Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
|   Bermerkung:     Tabstop = 4
---------------------------------------------------------------------------*/

#ifndef MISC_H
#define MISC_H

#include <stdlib.h>

#include "rosa.h"
#include "strg.h"

#define intg_ascii 5
#define long_ascii 12
#define double_ascii 32 /* CHECK */

void long_db_in(long *l, strg *t);
void long_db_out(long *l, strg *t);

void long_print(long l);

void intg_db_in(int *i, strg *t);
void intg_db_out(int *i, strg *t);

void double_db_in (double * d, strg * t);
void double_db_out(double * d, strg * t);


#define GEN_SWAP(T)                     \
    void T ## _swap(T *x, T *y) {       \
        any_swap(x, y, sizeof(T));      \
}

void any_swap(void *x, void *y, size_t msize);


#endif
