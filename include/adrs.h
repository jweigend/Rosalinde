/* ------------------------------------------------------------------------
|   Dateiname:      $RCSfile: adrs.h,v $
|   Version:        $Revision: 1 $
|   Erstellt am:    00.00.96
|   Geaendert am:   $Date: 19.11.97 9:36 $
|   Komponente:     Adresse
|   Erstellt von:   Johannes Weigend
|   Geandert von:   $Author: Johannes $
|   Copyright:      Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
|   Bermerkung:     Tabstop = 4
---------------------------------------------------------------------------*/

#ifndef _ADRS_H_
#define _ADRS_H_

#include "strg.h"

#define MAX_STRASSE 64
#define MAX_HAUSNR  12
#define MAX_PLZ     5
#define MAX_ORT     32
#define MAX_LAND    32

typedef struct _die_Adresse {

    strg strasse;
    strg hausnr;
    strg plz;
    strg ort;
    strg land;

} adrs;

    /* Konstruktion und Destruktion */
adrs * adrs_new ();

void adrs_init (adrs * a);

void adrs_clear (adrs * a);

adrs * adrs_delete (adrs * a);


    /* Set Methoden */
void adrs_set_strasse (adrs * a, char * strasse);

void adrs_set_hausnr (adrs * a, char * hausnr);

void adrs_set_plz (adrs * a, char * plz);

void adrs_set_ort (adrs * a, char * ort);

void adrs_set_land (adrs * a, char * land);


    /* Get Methoden */
char * adrs_get_strasse (adrs * a);

char * adrs_get_hausnr (adrs * a);

char * adrs_get_plz (adrs * a);

char * adrs_get_ort (adrs * a);

char * adrs_get_land (adrs * a);


    /* IN */
void adrs_in (adrs * a, char * strasse, char * hausnr, char * plz, char * ort, char * land);



    /* Kopieren */
void adrs_copy (adrs * a_to, adrs * a_from);


    /* Datenbankdarstellung */
void adrs_db_in (adrs * a, strg * flatstring);

void adrs_db_out (adrs * a, strg * flatstring);

void adrs_print (adrs * a);

#endif /* _ADRS_H_ */

