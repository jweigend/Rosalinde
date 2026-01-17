/* Generierung von Testdaten */
/* J. Siedersleben 3.7.96    */
/* To Do : Wie verteilt man den Kram auf die ADTs ? */


#include "rosa.h"
#include "list.h"
#include "adrs.h"
#include "enum.h"
#include "knde.h"
#include "knto.h"
#include "dbms.h"
#include "ctab.h"

ENABLE_ERROR_HANDLING;

static long cnt = 0;    /* Zaehler zum Durchnumerieren */


char * next_number () {  /* liefert die naechste Nummer als String */
  char * s;

  s = (char *) malloc (12);
  sprintf (s, "%ld", ++cnt);
  return s;
}



adrs * adrs_gen (char * land, char * plz, char * ort, char *strasse ) {
  adrs * a;

  a = adrs_new ();
  Assert (a);

  adrs_set_strasse (a, strasse);
  adrs_set_hausnr  (a, next_number ());
  adrs_set_plz     (a, plz);
  adrs_set_ort     (a, ort);
  adrs_set_land    (a, land);
  return a;
}


knde * knde_gen (char * anrede, char * name, char * vorname,
         char * land, char * plz, char * ort, char *strasse) {
                    /* generiert einen Kunden ohne Konten */
  anrd an;
  adrs * ad;
  knde * kd;
  strg s;
  RC rc;

  anrd_in (&an, &rc, LANG, anrede);
  Assert (rc == OK);

  ad = adrs_gen (land, plz, ort, strasse);
  kd = knde_new ();
  Assert (kd);
  knde_init (kd);
  knde_set_adresse (kd, ad);

  strg_init (&s, 0);   /* dynamischer Hilfsstring */
  strg_in (&s, name);
  knde_set_name (kd, &s);
  strg_in (&s, vorname);
  knde_set_vorname (kd, &s);
  knde_set_anrede (kd, &an);

  return kd;
}





int main (int argc, char * argv[]) {

  knde * kd;
  long oid;
  int i, count;

  if (argc != 2) {
        printf ("\nAnzahl zu generierender Saetze mitangeben !\n");
        exit (-1);
  }
  count = atoi (argv[1]);
  Assert (count >= 0);

  ctab_init ();
  brok_init ();

  dbms_open ();

  for (i = 0; i < count; i++) {

    kd = knde_gen ("Herr", "Maier", "Johann", "D", "83104",
          "Brettschleipfen", "Bahnhofstr");

    knde_register (kd, &oid);
  }

  dbms_commit ();

  dbms_close ();
  return 0;
}
