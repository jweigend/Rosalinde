/* ------------------------------------------------------------------------
|   Dateiname:      $RCSfile: strg.h,v $
|   Version:        $Revision: 1 $
|   Erstellt am:    00.00.96
|   Geaendert am:   $Date: 19.11.97 9:36 $
|   Komponente:     STRG
|   Erstellt von:   Johannes Weigend
|   Geandert von:   $Author: Johannes $
|   Copyright:      Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
|   Bermerkung:     Tabstop = 4
---------------------------------------------------------------------------*/

#ifndef _STRING_H_
 #define _STRING_H_

#define strg_h_rcs_revision " $Revision: 1 $ "
#define strg_h_rcs_date     " $Date: 19.11.97 9:36 $ "
#define strg_h_rcs_author   " $Author: Johannes $ "
#define strg_h_rcs_state    " $State: Exp $ "
#define strg_h_rcs_source   " $Source: /home/hannes/rosa/RCS/include/RCS/strg.h,v $ "
#define strg_h_rcs_log      " $Log "

#include <limits.h>
#include "rosa.h"

#ifndef MAX_STRING_LENGTH
 #define MAX_STRING_LENGTH INT_MAX - 1
#endif

/*  Standardgroesse fuer einen dynamischen String festlegen; dies entspricht
    der Anzahl an tatsaechlich speicherbaren Zeichen (also ohne '\0' */
#ifndef STD_DYN_STRG_LENGTH
 #define STD_DYN_STRG_LENGTH  255
#endif


typedef struct {
    char * s;
    int length;     /* Anz. der Zeichen in (*s) ohne '\0'*/
    int alloc_length;   /* Anz. der verfuegb. Zchn. ohne.'\0'*/
    BOOL dyn;       /* dyn == TRUE variable Länge        */
                /* dyn == FALSE feste Länge          */
} strg;



strg * strg_new (int m_length);
    /* Allokation des Rumpfes, wenn m_length==0 -> dynamischer String */

void strg_init (strg * s, int m_length);
    /* Alloktion des Char-arrays und Initialisierung ("") */

strg * strg_delete (strg * s);
    /* Destruktion von Puffer und Rumpf gibt wenn erfolgreich NULL zuruck */

void strg_free_buffer (strg * s);
#define strg_clear(s) strg_free_buffer(s)
    /* Gibt den allokierten Speicher des Pufferbereiches frei. */

void strg_in (strg  * s,  char * c);
    /* Kopiert nullterminiertes Array c in den String s.
       Wenn s zu kurz ist, wird Rest von c abgeschnitten */

char * strg_out (strg * s);
    /* Liefert Zeiger auf die Stringdaten zurueck. */

void strg_cat (strg * s,  strg * t);
    /* Haengt den String t an den String s an.
       Dabei wird der Rest abgeschnitten (Statischer String s), sofern der
       String s den String t nicht ganz aufnehmen kann. Ist s dynamisch, so
       wird dieser String ggf. um die entspr. Laenge aufgeweitet. */

void strg_cat_str (strg * s,  char * c);
    /*  Kopiert Charakter-Array "c" an das Ende von s (siehe strg_cat())  */

void strg_copy (strg * s,  strg * t);
    /* Kopiert Stringdaten von t nach s.
       Dabei wird s->s verlaengert, wenn s dynamisch ist.
       Ist hingegen s statisch , so werden die Restdaten abgeschnitten. */

char * strg_chr (strg * s, char c);
    /* siehe strchr() C-Library */

int strg_cmp (strg * s,  strg * t);
    /* siehe strcmp() C-Library */

int strg_len (strg * s);
    /* siehe strlen() C-Library */

void strg_print (strg * s);
    /* Druckt alle Attribute von s auf den Bildschirm (Trace)  */

void strg_sprintf (strg * dest,  strg * s,...);

void strg_sprintf_str (strg * s,  char * c,...);
    /* Wie sprinf() Puffer und Formatstring sind strg* statt char*
       Bsp: strg_sprintf_str(s,"X:=%d, Y:=%d",x,y);
       druckt formatiert nach s    */

void strg_rcs_info (strg * s);
    /* Druckt RCS-Informationen in s */

void strg_cut (strg * s, int s_offset);
    /* Schneidet s um s_offset Zeichen VORNE ab !!!.
       Dynamische Strings werden physikalisch um s_offset Zeichen
       verkl. Statische  Strings werden nur entsprechend umkopiert. */

void strg_db_in (strg * s, strg * t);
    /* Schneidet die Daten fuer s aus t heraus  */

void strg_db_out (strg * s, strg * t);
    /* Erzeugt die Datenbankdarstellung von "s" und haengt an t an  */

void strg_record (strg * s, strg * praefix, int * offset, strg * t);
    /* Haengt die Satzbeschreibung des Strings s mit praefix an t an */








/******************************************************************************
 ******************************************************************************
  BEMERKUNGEN:

    Der ADT - strg kann dynamische wie statische Strings verwalten. D.h.
    jede Opereration auf einem dynamischen String impliziert eine moegliche
    Vergroesserung bzw. Verkleinerung des allokierten Speichers.
    Sinnvolle Vorgehensweisen:

    A, Dynamisches Anlegen ueber Stringpointer:
    *******************************************
     1. Allokation strg * p = NULL;       / x == 0 --> dynamische Laenge
        ---------- p = strg_new (x);     |
                                         \  sonst  --> statisch Laenge (x)
     2. Dealokation strg_delete (p);
        -----------

    B, Automatisches Anlegen (z.B. Variable einer Struktur)
    *******************************************************
     zB. typedef struct {
            strg sVorname;
            strg sNachname;
        } Name;

      1. Allokation (automatisch);
         ----------  strg s;
      Initialisierung noetig:   / x == 0 --> dynamische Laenge
             strg_init (s, x);  |
                                \ sonst  --> statische Laenge (x)
      2. Dealokation ( KEIN strg_delete() !!!! )
         ----------- strg_clear (s);

Dieser Aufwand ist leider notwendig, da der Rumpf des Strings vom Compiler
automatisch allokiert wird, die Nutzdaten jedoch dynamisch von strg_init()
allokiert werden.
Ebenso werden alle automatisch allokierten Variablen beim verlassen eines
Blocks vom Compiler deallokiert; daher wuerde der Rumpf noch Aufruf von strg-
delete() nocheinmal freigegeben werden -> RUNTIMEERROR.
Eine elegante Loesung ist demnach nur in C++ moeglich da dort fur die auto-
matische wie auch dynamische Allokation dieselbe Funktion verwendet wird. */

#endif /* _STRING_H_ */
