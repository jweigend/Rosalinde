/* ------------------------------------------------------------------------
|   Dateiname:      $RCSfile: bent.h,v $
|   Version:        $Revision: 1 $
|   Erstellt am:    00.00.96
|   Geaendert am:   $Date: 19.11.97 9:36 $
|   Komponente:     BROKER
|   Erstellt von:   Johannes Weigend
|   Geandert von:   $Author: Johannes $
|   Copyright:      Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
|   Bermerkung:     Tabstop = 4
---------------------------------------------------------------------------*/

#ifndef _BENT_H_
#define _BENT_H_

#include "rosa.h"

#define MAX_HOSTNAME    128
#define MAX_SVCNNAME    128
#define MAX_PROTONAME   4
#define MIN_RPC_PRG_ID  0x3000000

    /* Ein Eintrag in der Brokerliste */
typedef struct _broker_entry {
    char host [MAX_HOSTNAME];               /* Hostname */
    char svcn [MAX_SVCNNAME];               /* Servicename */
    char proto [MAX_PROTONAME];             /* Protokoll   */
    long prgnr;                             /* Programm ID */
    long versnr;                            /* Versions ID */

} bent;


    /* Allokation und Initialisierung */
bent * bent_new ();
    /* Loeschen */
bent * bent_delete (bent * b);
    /* Init */
void   bent_init (bent * b);


    /* set... und get... Methoden */
void   bent_set_host  (bent * b, char * hostname);

void   bent_set_svcn  (bent * b, char * servicename);

void   bent_set_prgnr (bent * b, long programmnr);

void   bent_set_versnr(bent * b, long versionsnr);

void   bent_set_proto (bent * b, char * proto);

char * bent_get_host  (bent * b);

char * bent_get_svcn  (bent * b);

long   bent_get_prgnr (bent * b);

long   bent_get_versnr(bent * b);

char * bent_get_proto (bent * b);

    /* Kopieren */
void   bent_copy (bent * b, bent * target);

    /* Vergleicht nur die svcn-Namen da dieser eindeutig ist */
int bent_cmp (const void * a, const void * b);

    /* Vergleiche auf Identitaet */
int bent_cmp_all (const void * a, const void * b);

    /* Drucken */
void bent_print (const void * b);

    /* Zum Einfuegen in die Hashtabelle */
size_t bent_hash_fnk (const void * b);

#endif /* _BENT_H_ */

