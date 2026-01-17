/* ------------------------------------------------------------------------
|   Dateiname:      $RCSfile: tt_strg.c,v $
|   Version:        $Revision: 1 $
|   Erstellt am:    00.00.96
|   Geaendert am:   $Date: 19.11.97 9:37 $
|   Komponente:     STRG
|   Erstellt von:   Johannes Weigend
|   Geandert von:   $Author: Johannes $
|   Copyright:      Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
|   Bermerkung:     Tabstop = 4
---------------------------------------------------------------------------*/

#include "strg.h"
#include "except.h"
#include "stdio.h"
#include "stdlib.h"

ENABLE_ERROR_HANDLING;

#define HEAD(fnkname) printf("\n\nFUNKTION:\t%s\n",#fnkname);
#define BESCHR(b) printf("BESCHREIBUNG:\t%s\n",b);

void test_strg_db_in();

int main(void)
{
  printf("TESTTREIBER STRG\n\n");

  test_strg_db_in();

  return 0;
}


void test_strg_db_in()
{
  int cnt=1;
  strg *s1=NULL,*s2=NULL,*s3=NULL, *s4=NULL, *s5=NULL, *s6=NULL, *s7=NULL;


  HEAD(strg_db_in() und strg_db_out());
  BESCHR("DB-Darstellung eines statischen Strings und zuruecklesen.");

  s1 = strg_new (0);
  s2 = strg_new (25);
  s3 = strg_new (20);
  strg_in (s2,"DB-Darstellung");
  strg_db_out (s2, s1);
  strg_db_out (s2, s1);
  strg_print (s2);
  strg_print (s1);
  strg_db_in (s3, s1);
  strg_db_in (s3, s1);
  strg_print (s3);
  if(strg_cmp (s3, s2) == 0) printf("OK\n");
   else printf("NOT OK\n");
  strg_delete (s1);
  strg_delete (s2);
  strg_delete (s3);


  BESCHR("DB-Darstellung 2 statischer Strings und zuruecklesen.");
  s1 = strg_new(20);
  s2 = strg_new (40);
  s3 = strg_new (0);
  s4 = strg_new (20);
  s5 = strg_new(40);
  strg_in (s1,"DB-STRING A (20 Chars)");
  strg_in (s2,"DB-STRING B (40 Chars ist laenger)");
  strg_db_out (s1, s3);
  strg_db_out (s2, s3);
  strg_print (s1);
  strg_print (s2);
  strg_print (s3);
  strg_db_in (s4, s3);
  strg_db_in (s5,s3);
  if(strg_cmp (s1, s4) || strg_cmp (s2, s5)) printf("NOK\n");
   else printf("OK\n");
  strg_delete (s1);
  strg_delete (s2);
  strg_delete (s3);
  strg_delete (s4);
  strg_delete (s5);


  BESCHR("DB-Darstellung 3 statischer Strings und zuruecklesen.");
  s1 = strg_new (10);
  s2 = strg_new (20);
  s3 = strg_new (30);
  s4 = strg_new (10);
  s5 = strg_new (20);
  s6 = strg_new (30);
  s7 = strg_new (0);
  strg_in (s1,"StringA");
  strg_in (s2,"StringB");
  strg_in (s3,"StringC");
  strg_db_out (s1,s7);
  strg_db_out (s2,s7);
  strg_db_out (s3,s7);
  strg_print (s1);
  strg_print (s2);
  strg_print (s3);
  strg_print (s7);
  strg_db_in (s4,s7);
  strg_db_in (s5,s7);
  strg_db_in (s6,s7);
  if (strg_cmp (s1, s4) || strg_cmp (s2, s5) || strg_cmp(s3, s6)) printf("NOK\n");
   else printf("OK\n");

  strg_delete (s1);
  strg_delete (s2);
  strg_delete (s3);
  strg_delete (s4);
  strg_delete (s5);
  strg_delete (s6);
  strg_delete (s7);
}
