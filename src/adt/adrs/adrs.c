/* ------------------------------------------------------------------------
|   Dateiname:      $RCSfile: adrs.c,v $
|   Version:        $Revision: 1 $
|   Erstellt am:    00.00.96
|   Geaendert am:   $Date: 19.11.97 9:36 $
|   Komponente:     Anrede
|   Erstellt von:   Johannes Weigend
|   Geandert von:   $Author: Johannes $
|   Copyright:      Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
|   Bermerkung:     Tabstop = 4
---------------------------------------------------------------------------*/

#include "adrs.h"


    /* Konstruktion und Destruktion */
adrs * adrs_new () {

    adrs * a;

    a = (adrs *) malloc (sizeof (adrs));
    Assert (a);

    adrs_init (a);

    return a;
}

void adrs_init (adrs * a) {

    Assert (a);

    strg_init (&a->strasse, MAX_STRASSE);
    strg_init (&a->hausnr,  MAX_HAUSNR);
    strg_init (&a->plz,     MAX_PLZ);
    strg_init (&a->ort,     MAX_ORT);
    strg_init (&a->land,    MAX_LAND);
}

void adrs_clear (adrs * a) {

    Assert (a);

    strg_clear (&a->strasse);
    strg_clear (&a->hausnr);
    strg_clear (&a->plz);
    strg_clear (&a->ort);
    strg_clear (&a->land);
}

adrs * adrs_delete (adrs * a) {

    Assert (a);

    adrs_clear (a);
    free (a);

    return NULL;
}


    /* Set Methoden */
void adrs_set_strasse (adrs * a, char * strasse) {

    Assert (a && strasse);

    strg_in (&a->strasse, strasse);
}

void adrs_set_hausnr (adrs * a, char * hausnr) {

    Assert (a && hausnr);

    strg_in (&a->hausnr, hausnr);
}

void adrs_set_plz (adrs * a, char * plz) {

    Assert (a && plz);

    strg_in (&a->plz, plz);
}

void adrs_set_ort (adrs * a, char * ort) {

    Assert (a && ort);

    strg_in (&a->ort, ort);
}

void adrs_set_land (adrs * a, char * land) {

    Assert (a && land);

    strg_in (&a->land, land);
}


    /* Get Methoden */
char * adrs_get_strasse (adrs * a) {

    Assert (a);

    return strg_out(&a->strasse);
}

char * adrs_get_hausnr (adrs * a) {

    Assert (a);

    return strg_out(&a->hausnr);
}

char * adrs_get_plz (adrs * a) {

    Assert (a);

    return strg_out(&a->plz);
}

char * adrs_get_ort (adrs * a) {

    Assert (a);

    return strg_out(&a->ort);
}

char * adrs_get_land (adrs * a) {

    Assert (a);

    return strg_out(&a->land);
}


void adrs_in (adrs * a, char * strasse, char * hausnr, char * plz, char * ort, char * land) {

    Assert (a && strasse && plz && ort && land);

    adrs_set_strasse(a, strasse);
    adrs_set_hausnr (a, hausnr);
    adrs_set_plz    (a, plz);
    adrs_set_ort    (a, ort);
    adrs_set_land   (a, land);
}


    /* Kopieren */
void adrs_copy (adrs * a_to, adrs * a_from) {

    Assert (a_to && a_from);

    strg_copy (&a_to->strasse, &a_from->strasse);
    strg_copy (&a_to->hausnr, &a_from->hausnr);
    strg_copy (&a_to->plz, &a_from->plz);
    strg_copy (&a_to->ort, &a_from->ort);
    strg_copy (&a_to->land, &a_from->land);
}


    /* Datenbankdarstellung */
void adrs_db_in (adrs * a, strg * flatstring) {

    Assert (a && flatstring);

    strg_db_in (&a->strasse, flatstring);
    strg_db_in (&a->hausnr, flatstring);
    strg_db_in (&a->plz, flatstring);
    strg_db_in (&a->ort, flatstring);
    strg_db_in (&a->land, flatstring);
}


void adrs_db_out (adrs * a, strg * flatstring) {

    Assert (a && flatstring);

    strg_db_out (&a->strasse, flatstring);
    strg_db_out (&a->hausnr, flatstring);
    strg_db_out (&a->plz, flatstring);
    strg_db_out (&a->ort, flatstring);
    strg_db_out (&a->land, flatstring);
}


void adrs_print (adrs * a) {

    strg_print (&a->strasse);
    strg_print (&a->hausnr);
    strg_print (&a->plz);
    strg_print (&a->ort);
    strg_print (&a->land);
}

