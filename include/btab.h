/* ------------------------------------------------------------------------
|   Dateiname:      $RCSfile: btab.h,v $
|   Version:        $Revision: 1 $
|   Erstellt am:    00.00.96
|   Geaendert am:   $Date: 19.11.97 9:36 $
|   Komponente:     BTAB
|   Erstellt von:   Johannes Weigend
|   Geandert von:   $Author: Johannes $
|   Copyright:      Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
|   Bermerkung:     Tabstop = 4
---------------------------------------------------------------------------*/

#ifndef _BTAB_H_
 #define _BTAB_H_

#include "rosa.h"
#include "misc.h"

#define KEY_LENGTH long_ascii

#define PATH_LENGTH 255

extern const RC btab_eof;

#ifndef BTAB_PROXY

typedef struct {
    int  fd;        /* der Filedeskriptor */
    int  rec_length;    /* Satzlaenge inklusive rid */
    long base;      /* rid des ersten Satzes */
    long cur_rid;        /* Aktueller rid */
    short empty;            /* TRUE wenn Datei leer */
    short open;     /* TRUE wenn Datei geoeffnet */
} btab;

#else

    /* Der Proxy */
typedef long btab;

#endif

    /* Der Servicename */
#define BTAB_SVC "BTAB_SVC"

void btab_init (btab * b);
                /* Trivial-Initialisierung */

void btab_clear (btab * b);
                /* Es passiert nichts */

btab * btab_new();
                /* Speicherplatz allokieren */

btab * btab_delete (btab * b);
                /* Speicherplatz freigeben;
                   zurueckgegeben wird NULL */

void btab_open (btab * b, char * path, int rec_lenght, long base);
                /* oeffnet die Datei mit dem angegeben
                   Namen */

void btab_close (btab * b);
                /* schliesst die Datei */

void btab_rewind (btab * b);
                /* setzt current_rid zurueck */

RC   btab_get_next (btab * b, char * record);
                /* liefert den naechsten Satz zurueck
                   inklusive rid;
                   nach rewind() bekommt man den ersten;
                   Returncodes: ok, eof;
                   der Aufrufer ist verantwortlich fuer
                   die Allokation von record */
RC   btab_get_previous (btab * b, char * record);
                /* liefert den naechsten Satz zurueck
                   inklusive rid;
                   nach rewind() bekommt man den letzten;
                   Returncodes: ok, eof;
                   der Aufrufer ist verantwortlich fuer
                   die Allokation von record */

RC   btab_get_at (btab * b, long rid, char * record);
                /* liefert den Satz inklusive rid an der
                   angegebenen Position zurueck;
                   Allokation von record durch den Aufrufer */
void btab_put_at (btab * b, char * record);
                /* Erwartet den rid an den ersten
                   KEY_LENGTH Stellen von record;
                   schreibt den Satz an dieser Stelle in die
                   Datei */

void btab_append (btab * b, char * record, long * rid);
                /* Berechnet den naechsten zu vergebenden
                   rid;
                   ueberschreibt die ersten KEY_LENGTH
                   Stellen von record mit dem neuen rid
                   haengt diesen Satz an die Datei an */

BOOL btab_is_empty (btab * b);

BOOL btab_is_not_empty (btab * b);


#endif /* _BTAB_H_ */
