/* ------------------------------------------------------------------------
|   Dateiname:      $RCSfile: btab.c,v $
|   Version:        $Revision: 1 $
|   Erstellt am:    00.00.96
|   Geaendert am:   $Date: 19.11.97 9:36 $
|   Komponente:     BTAB
|   Erstellt von:   Johannes Weigend
|   Geandert von:   $Author: Johannes $
|   Copyright:      Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
|   Bermerkung:     Tabstop = 4
---------------------------------------------------------------------------*/

#include <malloc.h>
#include <stdio.h>
#include <fcntl.h>

#ifndef _WIN32
#include <sys/file.h>
#include <unistd.h>
#else
#include <io.h>
#endif
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "btab.h"
#include "misc.h"

/*********************************************************************/
#define btab_c_rcs_rev      "$Revision: 1 $Date:"
#define btab_c_rcs_author   "$Author: Johannes $State:"
#define btab_c_rcs_source   "$Source:"
/*********************************************************************/

static const int o_mode = O_RDWR | O_CREAT;
static const int a_mode = 0644;          /* Create Mode : rw_ r__ r__ */

static const int fpos_EOF =   -1;        /* fuer cur_rid */
static const int fpos_START = -2;
    /**** Interne Funktionen ****/

    /* Lese rid aus record */
long btab_get_rid (btab * b, char * record);
    /* Ueberschreibe rid in record */
void btab_ovw_rid (btab * b, char * record, long newkey);
    /* Berechnet Dateiposition aus cur_rid */
long btab_calc_fpos (btab * b);


long btab_calc_fpos (btab * b) {
    return ((b->cur_rid - b->base) * b->rec_length);
}

    /* Allokation der Basistabelle */
btab * btab_new() {

    btab * b;

    b = (btab *) malloc (sizeof(btab));

    btab_init (b);
    return b;
}

    /* Initialisierung */
void btab_init (btab * b) {

    Assert (b != NULL);

    b->fd = 0;
    b->rec_length = 0;
    b->base = 0;
    b->cur_rid = fpos_START;
    b->open = FALSE;
    b->empty = TRUE;

}

    /* Deallokation von btab */
btab * btab_delete (btab * b) {

    Assert (b != NULL);

    if (b->open) btab_close (b);

    free (b);
    return NULL;
}

    /* implizit close */
void btab_clear (btab * b) {

    Assert (b != NULL);
    if (b->open) btab_close (b);
}

    /* Oeffnen der Datei */
void btab_open (btab * b, char * path, int rec_length, long base) {

    char * buffer;
    long rc;

    Assert (b != NULL);
    Assert (path != NULL);
    Assert (rec_length > 0);
    Assert (base >= 0);


    buffer = (char *) malloc (sizeof (char) * rec_length);
    Assert (buffer != NULL);

    b->fd = open (path, o_mode, a_mode); /* CHECK Errorhandling */
    Assert (b->fd != -1);

    b->open = TRUE;
    b->base = base;
    b->rec_length = rec_length;

        /* Ist Datei leer ? */
    rc = read (b->fd, buffer, rec_length);
    Assert (rc >= 0);

        /* Wenn Datei nicht leer ist, muss der gelesene rid mit
           base ubereinstimmen. */
    if (rc == 0) b->empty = TRUE;
    else {
        b->empty = FALSE;
        b->cur_rid = btab_get_rid (b, buffer);
        Assert (b->cur_rid == base);
    }

    btab_rewind (b);

    free (buffer);
}


    /* Schliessen der Datei */
void btab_close (btab * b) {

    long rc;

    Assert (b != NULL);
    Assert (b->fd > 0);        /* CHECK: NO multiple close() ? */
    Assert (b->open == TRUE);

    rc = close (b->fd);
    Assert (rc == 0);

    btab_init(b);
}

    /* Positionieren auf den 1. Satz */
void btab_rewind (btab * b) {

    long file_rc;

    Assert (b != NULL);
    Assert (b->open);
        /* Dateianfang suchen */
    file_rc = lseek (b->fd, 0, SEEK_SET);
    Assert (file_rc != -1L);

    b->cur_rid = fpos_START;
}

    /* Gibt die ersten long_ascii Stellen von record als long zurueck */
long btab_get_rid (btab * b, char * record) {

    char * buffer;
    long rid;

    Assert (b != NULL);
    Assert (record != NULL);

    buffer = (char *) malloc (sizeof (char) * b->rec_length);
    Assert (buffer != NULL);
        /* Kein Ueberlappen moeglich */
    /*(void)*/ memcpy (buffer, record, b->rec_length * sizeof (char));
    buffer[long_ascii] = '\0';

    rid = atol (buffer);
    free (buffer);
    return rid;
}

    /* Ueberschreibt die ersten long_ascii Zeichen von record
       mit der ASCII Darstellung von newkey */
void btab_ovw_rid (btab * b, char * record, long newkey) {

    char * buffer;

    Assert (b != NULL);
    Assert (record != NULL);
    Assert (newkey >= b->base);

    buffer = (char *) malloc (sizeof (char) * (long_ascii + 1));
    Assert (buffer != NULL);

    (void) sprintf (buffer, "%*ld", long_ascii, newkey);
    (void) strncpy (record, buffer, long_ascii);

    free (buffer);
    return;
}


    /* Naechster Satz wird in record gespeichert */
RC  btab_get_next (btab * b, char * record) {

    RC rc;

    Assert (b != NULL);
    Assert (b->open);

    if (btab_is_empty (b))      return NOK_EMPTY;
    if (b->cur_rid == fpos_EOF)     return NOK_NO_NEXT;

    if (b->cur_rid != fpos_START)
        rc = btab_get_at (b, b->cur_rid + 1, record);
    else
        rc = btab_get_at (b, b->base, record);

    if (rc != OK) b->cur_rid = fpos_EOF;

    return ( rc == OK ? OK : NOK_NO_NEXT );
}

    /* Vorheriger Satz wird in record gespeichert */
RC   btab_get_previous (btab * b, char * record) {

    long file_rc;

    Assert (b != NULL);
    Assert (b->open);

    if (btab_is_empty (b))  return NOK_EMPTY;

    if ((b->cur_rid == b->base) || (b->cur_rid == fpos_START))
        return NOK_NO_PREV;

        /* Welchen rid hat letzter Satz ? */
    if (b->cur_rid == fpos_EOF) {
        file_rc = lseek (b->fd, 0 - b->rec_length, SEEK_END);
        Assert (file_rc >= 0);
        file_rc = read (b->fd, record, b->rec_length);
        Assert (file_rc == b->rec_length);
        /* aktuellen rid holen */
        b->cur_rid = btab_get_rid (b, record);
        file_rc = btab_get_at (b, b->cur_rid, record);
    }
    else    file_rc = btab_get_at (b, b->cur_rid - 1, record);

    Assert (file_rc == OK) ;

    return ( OK );
}

    /* Satz mit Schluessel rid wird in record gespeichert.
       Funktioniert nur wenn Schluessel der Datei fortlaufend und ohne
       Luecken vergeben wurden. */
RC btab_get_at (btab * b, long rid, char * record) {

    RC rc;
    long fpos;

    Assert (b != NULL);
    Assert (b->open);
    Assert (record && (rid > 0));

    record[0] = '\0';

    b->cur_rid = rid;

    fpos = btab_calc_fpos (b);
    if (fpos < 0) return NOK_NOT_FOUND;


    rc = lseek (b->fd, fpos, SEEK_SET);
    Assert (rc != -1L);

    rc = read (b->fd, record, b->rec_length);
    Assert (rc >= 0);

    if (rc != b->rec_length) return NOK_NOT_FOUND;
    else return OK;
}

    /* Satz wird geschrieben. rid sind die ersten long_ascii Zeichen
       der Datei. */
void btab_put_at (btab * b, char * record) {

    long rc;
    long fpos;

    Assert (b != NULL);
    Assert (b->open);

    b->cur_rid = btab_get_rid (b, record);

    fpos = btab_calc_fpos (b);
    Assert (fpos >= 0);

    rc = lseek (b->fd, fpos, SEEK_SET);
    Assert (rc != -1L);

    rc = write (b->fd, record, b->rec_length);
    Assert (rc == b->rec_length);

    return ; /* To DO: Check if rid valid */
}

    /* Anhaengen und vergeben eines neuen rids */
void btab_append (btab * b, char * record, long * rid) {

    RC rc;
    char * buffer;
    long file_rc;

    Assert (b != NULL);
    Assert (b->open);
    Assert (record != NULL);
    Assert (rid != NULL);

    buffer = (char *) malloc (sizeof (char) * (b->rec_length + 1));
    Assert (buffer != NULL);

    if ( btab_is_not_empty (b)) {
            /* liest den letzten Satz und dessen rid */
        file_rc = lseek (b->fd, - b->rec_length, SEEK_END);
        Assert (file_rc != -1);
        file_rc = read (b->fd, buffer, b->rec_length);
        Assert (file_rc == b->rec_length);
        buffer[b->rec_length] = '\0';
        *rid = btab_get_rid (b, buffer) + 1; /* CHECK Overflow */
    }
    else *rid = b->base;    /* Beginnend bei base wenn Datei leer ! */
            /* pos. fileend */
    rc = lseek (b->fd, 0, SEEK_END);
    Assert (rc != -1L);
        /* Modify record with new rid */
    btab_ovw_rid (b, record, *rid);
        /* write to disk */
    rc = write (b->fd, record, b->rec_length);
    Assert (rc == b->rec_length);

    b->empty = FALSE;
    b->cur_rid = fpos_EOF;

    free (buffer);
}

BOOL btab_is_empty (btab * b) {

    Assert (b != NULL);
    Assert (b->open);

    return (b->empty);
}

BOOL btab_is_not_empty (btab * b) {

    Assert (b != NULL);
    Assert (b->open);

    return (! b->empty);
}

