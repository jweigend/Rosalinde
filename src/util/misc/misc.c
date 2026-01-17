/* ------------------------------------------------------------------------
|   Dateiname:      $RCSfile: misc.c,v $
|   Version:        $Revision: 1 $
|   Erstellt am:    00.00.96
|   Geaendert am:   $Date: 19.11.97 9:37 $
|   Komponente:     STRG MISC
|   Erstellt von:   Johannes Siedersleben
|   Geandert von:   $Author: Johannes $
|   Copyright:      Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
|   Bermerkung:     Tabstop = 4
---------------------------------------------------------------------------*/

#include "misc.h"


void long_db_in(long *l,  strg *t) {

    strg u;

    Assert (l && t);

    strg_init(&u, long_ascii);
    strg_copy(&u, t);

    *l = atol(strg_out(&u));
    strg_cut(t, long_ascii);
    strg_clear (&u);
}



void long_db_out(long *l, strg *t) {

     char s[long_ascii + 3];  /* long in Ascii-Darstellung plus "d" plus '\0' */
     strg u;

     Assert (l && t);

    sprintf(s, "%-*ld", long_ascii,  *l);
    strg_init(&u, long_ascii);
    strg_in(&u, s);
    strg_cat(t, &u);
    strg_clear (&u);
}

void double_db_in(double *d,  strg *t) {

    strg u;

    strg_init(&u, double_ascii);
    strg_copy(&u, t);

    *d = atof(strg_out(&u));
    strg_cut(t, double_ascii);
    strg_clear (&u);
}


void double_db_out(double *d, strg *t) {

     char s[double_ascii + 3];  /* long in Ascii-Darstellung plus "d" plus '\0' */
     strg u;

     Assert (d && t);

    sprintf(s, "%-*f", double_ascii,  *d);
    Assert (strlen (s) < double_ascii + 2);

    strg_init(&u, double_ascii);
    strg_in(&u, s);
    strg_cat(t, &u);
    strg_clear (&u);
}


void intg_db_in(int *i, strg *t) {

    strg u;

    Assert (i && t);

    strg_init(&u, intg_ascii + 1);
    strg_copy(&u, t );

    *i = atoi(strg_out(&u));
    strg_cut(t, intg_ascii + 1);
    strg_clear (&u);
}



void intg_db_out(int *i, strg *t) {

    char s[intg_ascii + 3];
    strg u;

    Assert (i && t);

    sprintf(s, "%-*id", intg_ascii,  *i);
    Assert (strlen (s) < intg_ascii + 2);

    strg_init(&u, intg_ascii + 1);
    strg_in(&u, s);
    strg_cat(t, &u);
    strg_clear (&u);
}

void long_print(long l) {

    LOG ("%ld", l);
}




    void any_swap(void *x, void *y, size_t msize) {

    /*  any_swap() vertauscht Speicherobjekte beliebiger Groesse.                 */
    /*  der Aufrufer verantwortet, da x und y auf Speicherobjekte                */
    /*  der Groesse msize zeigen, und da es Sinn macht, die Speicherinhalte      */
    /*  miteinander zu vertauschen.  any_swap() hat keine Chance, irgendetwas in  */
    /*  dieser Richtung zu pruefen.                                               */

          void *z;

    z = malloc(msize);
    memcpy(z, x, msize);
    memcpy(x, y, msize);
    memcpy(y, z, msize);
    free(z);                   /* sonst bleiben Loecher! */
        }








