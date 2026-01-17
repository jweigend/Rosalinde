/* ------------------------------------------------------------------------
|   Dateiname:      $RCSfile: strg.c,v $
|   Version:        $Revision: 1 $
|   Erstellt am:    00.00.96
|   Geaendert am:   $Date: 19.11.97 9:37 $
|   Komponente:     STRG
|   Erstellt von:   Johannes Weigend
|   Geandert von:   $Author: Johannes $
|   Copyright:      Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
|   Bermerkung:     Tabstop = 4
---------------------------------------------------------------------------*/


#include <string.h>
#include <stdarg.h>
#include "strg.h"
#include "misc.h"
#include "log.h"

    /* RCS  */
#define strg_c_rcs_revision " $Revision: 1 $ "
#define strg_c_rcs_date     " $Date: 19.11.97 9:37 $ "
#define strg_c_rcs_author   " $Author: Johannes $ "
#define strg_c_rcs_state    " $State: Exp $ "
#define strg_c_rcs_source   " $Source: /home/hannes/rosa/RCS/src/util/strg/RCS/strg.c,v $ "
#define strg_c_rcs_log      " $Log "
/*****************************************************************************/

    /* Dont give NULL back */
static char static_empty_string = '\0';

/*  Hilfsfunktion fuer dynamische Arrays (private), daher kein Prototyp
    im Header; Vergroessert bzw. verkleinert den Stringpuffer
    (Inhalt bleibt erhalten)                                                 */
void strg_resize (strg * s, size_t newsize) {
    /* realloc verschiebt wenn noetig den Speicherblock */
  s->s = (char *) realloc (s->s, newsize + 1);
  Assert (s->s != NULL);
  s->alloc_length = newsize;
}

    /* Moegliche Konstistenzueberpuefung */
void strg_check (strg * s) {

 Assert (s->length == (int) strlen (s->s));
 Assert (s->length <= s->alloc_length);
 Assert (s->length <= MAX_STRING_LENGTH);
}

    /* Allokation und Initialisierung */
strg * strg_new (int m_length) {
 strg * s = NULL;
 Assert (m_length <= MAX_STRING_LENGTH);
 s = (strg *) malloc (sizeof (strg));
 Assert (s != NULL);
 s->s = NULL;
 strg_init (s, m_length);
 return s;
}

    /* Allokiert s->s und initialisiert mit "\0" */
void strg_init (strg * s, int m_length) {

 Assert (s != NULL);
 Assert (m_length <= MAX_STRING_LENGTH);

    /* Ist der String dynamisch oder statisch ?*/
 if (m_length == 0) {
    s->dyn = TRUE;
    m_length = STD_DYN_STRG_LENGTH;
 }
 else s->dyn = FALSE;

 s->s = (char *) malloc ((size_t) (m_length + 1));
    /* Allok.fuer Charakterarray */
 Assert (s->s != NULL);
 s->alloc_length = m_length;
 *(s->s) = '\0';
 s->length = 0;
}

/*  Kopiert nullterminiertes Array c in den String s.
    Wenn s zu kurz ist, wird Rest von c abgeschnitten */
void strg_in (strg * s,  char * c) {

 int l = 0;

 Assert (s != NULL);
 Assert (c != NULL);
 if (s->dyn) l = 0;
 else l = s->alloc_length;
 strg_clear (s);
 strg_init (s, l);
 strg_cat_str (s, c);
}

/* Liefert Zeiger auf die Stringdaten zurueck. */
char * strg_out (strg * s) {

 Assert ( s != NULL);
 return ((char*) s->s);
}

/* Loescht das Strg-Objekt.
   Speicher wird freigegeben und (*s) wird auf NULL gesetzt. */
strg * strg_delete (strg * s) {

 Assert (s != NULL);
 Assert (s->s != NULL);
 strg_clear (s);     /* Puffer freigeben */
 free (s);   /* String freigeben */
 return NULL;
}

    /* Gibt den allokierten Speicher des Pufferbereiches frei. */
void strg_free_buffer (strg * s) {

 Assert (s != NULL);
 Assert (s->s != NULL);
 free (s->s);
 s->s = NULL;
 s->alloc_length = 0;
 s->length = 0;
}

    /* Haengt den String t an den String s an. */
void strg_cat(strg * s,  strg * t)
{
 Assert (s != NULL);
 Assert (t != NULL);
 strg_cat_str (s, t->s);
}

/*  Haengt den char* String t an den String s an.
    Dabei wird der Rest abgeschnitten (Statischer String s), sofern der
    String s den String t nicht ganz aufnehmen kann. Ist s dynamisch, so
    wird dieser String ggf. um die entspr. Laenge aufgeweitet. */
void strg_cat_str(strg * s,  char * c) {

 int sl,tl;
 Assert(s != NULL);
 Assert(c != NULL);

 sl = s->length;
 tl = strlen (c);

 if (sl+tl > s->alloc_length) {           /* Passen s u. t in s hinein? */
    if (s->dyn) strg_resize(s, sl + tl);  /* ggf. s verlaengern     */
    else tl = s->alloc_length - sl;   /* bzw. Restdaten abschneiden */
 }
 memcpy (&(s->s[sl]), c, tl);         /* Daten von t an s haengen   */
 s->s[sl + tl] = '\0';
 s->length = sl + tl;
}


/*  Kopiert Stringdaten von t nach s.
    Dabei wird s->s verlaengert, wenn s dynamisch ist.
    Ist hingegen s statischer Natur, so werden die Restdaten abgeschnitten.  */
void strg_copy (strg * s,  strg * t) {

 Assert (s != NULL);
 Assert (t != NULL);
 strg_in (s, t->s);
}


int strg_cmp (strg * s,  strg * t) {

 Assert (s != NULL);
 Assert (t != NULL);
 return (strcmp (s->s, t->s)); /* Siehe C-ANSI Lib */
}


int strg_len (strg * s) {

 Assert (s != NULL);
 return (s->length);
}

    /* Gibt falls Zeichen nicht gefunden '\0' zurueck */
char * strg_chr (strg * s, char c) {

 char * s_ret;

 Assert (s != NULL);
 s_ret = strchr (s->s, c);
 if (s_ret) return (s_ret);
 else return (&static_empty_string);
}


    /* Gibt RCS-INFO fuer strg.h und strg.c aus: Trennzeichen ","                */
void strg_rcs_info(strg * s) {

 Assert (s != NULL);
 strg_in (s, "\nstrg.h:\t");
 strg_cat_str (s, strg_h_rcs_revision);
 strg_cat_str (s, strg_h_rcs_date);
 strg_cat_str (s, strg_h_rcs_author);
 strg_cat_str (s, strg_h_rcs_state);
 strg_cat_str (s, strg_h_rcs_log);
 strg_cat_str (s, "\nstrg.c:\t");
 strg_cat_str (s, strg_c_rcs_revision);
 strg_cat_str (s, strg_c_rcs_date);
 strg_cat_str (s, strg_c_rcs_author);
 strg_cat_str (s, strg_c_rcs_state);
 strg_cat_str (s, strg_c_rcs_log);
}


/* s_offset-Zeichen am Stringanfang abschneiden */
void strg_cut (strg * s, int s_offset) {

  Assert (s != NULL);
  Assert (s->length >= s_offset);
  memmove (s->s, s->s + s_offset, s->length-s_offset+1); /*   ueberlappend !  */
  /* Physikalisches Abschneiden nur bei einem dynamischen String !  */
  if (s->dyn) strg_resize (s, s->alloc_length - s_offset);
  s->length = s->length - s_offset;
}

/*  Attribute zum fuellen von s aus flatstring entnehmen und abschneiden    */
/*  Die Datenbankdarstellung sieht folgendermassen aus:

    0         10    20    30        40
    01234567890123456789012345678901234567890
    XX    dYY    dZZZZZZZZZZZZBBBBBBBBBBBBBBB

    wobei  XX = Allokierte Groesse.
       YY = Laenge des folgenden Strings
       ZZ = Stringdaten mit Blanks B auf (s->alloc_length) Zeichen
            aufgefuellt (nicht nullterminiert) */
void strg_db_in (strg * s, strg * t) {

 int slength, alloc_length;

 Assert (s != NULL);
 Assert (t != NULL);

 intg_db_in (&slength, t);
 intg_db_in (&alloc_length, t);

 strg_in (s, t->s);
 Assert (slength <= s->alloc_length);

 s->s[slength] = '\0';
 s->length = slength;
 strg_cut (t, alloc_length);
}

/*  Datenbankdarstellung von s an flatstring anhaengen..                     */
void strg_db_out(strg * s, strg * t) {

  int i, save;

  Assert (s != NULL);
  Assert (t != NULL);
  Assert (s->dyn != TRUE);  /* Kein Dynamischer String in DB */

  intg_db_out (&s->length, t);
  intg_db_out (&s->alloc_length, t);

  save = s->length;

  for (i = s->length; i < s->alloc_length; i++) s->s[i] = 'x';
  s->s[s->alloc_length] = '\0';
  s->length = s->alloc_length;

  strg_cat (t, s);

  s->s[save] = '\0';
  s->length = save;
}


/* Liefert Satzbeschreibung des Strings s
*/
void strg_record(strg * s, strg * praefix, int * offset, strg * flatstring) {

 strg * sTemp=NULL;

 Assert (s != NULL);
 Assert (flatstring != NULL);
 Assert (praefix != NULL);
 sTemp = strg_new (0);
 strg_copy (sTemp, praefix);
 strg_cat_str (sTemp, ".alloc_length");
 /* intg_record(&((int)s->alloc_length),sTemp,offset,flatstring);*/
 strg_copy(sTemp, praefix);
 strg_cat_str(sTemp, ".length");
 /* intg_record(&((int)s->length), "length",offset,flatstring);*/
 strg_sprintf_str (sTemp, "%s\t%u\t%u\n",praefix->s, *offset,s->alloc_length);
 strg_cat (flatstring, sTemp);
 strg_delete (sTemp);
 *offset += s->alloc_length;
}


/* Druckt alle Attribute von s in einen neu angelegten String
*/
void strg_print (strg * s) {

 Assert (s != NULL);
 LOG ("%s (%d, %d, %d)\n",
            s->s, s->length, s->alloc_length, s->dyn);
}


/* Wie sprinf() Puffer und Formatstring sind strg* statt char*
*/
void strg_sprintf (strg * dest,  strg * s,...) {

 va_list args;
 char* puffer;
 int vs_ret;

 Assert (s != NULL);
 Assert (dest != NULL);

 /* TO DO: Logik zur Berechnung des benoetigten Speicherplatzes */
 /* Derzeit ist Puffergroesse 10 * Stringlaenge */
 puffer = (char *) malloc((size_t) (s->length * 10));
 Assert (puffer != NULL);
 va_start (args,s);
 vs_ret = vsprintf (puffer, s->s,args);
 Assert (vs_ret >= 0);
 va_end (args);
 strg_in (dest, puffer);
 free (puffer);
}


void strg_sprintf_str (strg * s,  char * c,...) {

  va_list args;
  char * puffer;
  int vs_ret;

  Assert (s != NULL);
  Assert (c != NULL);

  /* TO DO: Logik zur Berechnung des benoetigten Speicherplatzes */
  /* Derzeit ist Puffergroesse 10 * Stringlaenge */
  puffer = (char*) malloc ((size_t) (strlen (c) * 10));
  Assert (puffer != NULL);
  va_start (args,c);
  vs_ret = vsprintf(puffer,c,args);
  Assert (vs_ret >= 0);
  va_end (args);
  strg_in (s, puffer);
  free (puffer);
}
