/* ------------------------------------------------------------------------
|   Dateiname:      $RCSfile: brok.h,v $
|   Version:        $Revision: 1 $
|   Erstellt am:    00.00.96
|   Geaendert am:   $Date: 19.11.97 9:36 $
|   Komponente:     BROKER
|   Erstellt von:   Johannes Weigend
|   Geandert von:   $Author: Johannes $
|   Copyright:      Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
|   Bermerkung:     Tabstop = 4
---------------------------------------------------------------------------*/

#ifndef _BROKER_H_
#define _BROKER_H_

#include "rosa.h"
#include "bent.h"
#include "hash.h"

typedef struct _broker {
    hash hashtab;
} brok;

#define BROKER_HASH_TAB_SIZE 97 /* PRIM */

#define DUPLICATE_SVC_ENTRY -1011
#define UNKNOWN_ERROR       -100
#define SVC_NOT_REGISTERED  -101

/**********************************/
/* INTERNE Methoden des Brokers   */
/**********************************/
    /* Initialisierung der Liste ...*/
void brok_init ();
    /* Loeschen der Liste !! (nicht der Listenelemente) */
void brok_clear ();
    /* for trace only */
void brok_print ();


/**********************************/
/* Die RPC Broker Schnittstelle : */
/**********************************/

/*  registriert einen Service:
    RC: OK                   wenn alles klappt
        DUPLICATE_SVC_ENTRY  fuer doppelte Registrierung */
RC brok_register (bent * be);

/*  deregistriert einen Service:
    RC: OK
        SVC_NOT_REGISTERED  fuer nicht gefundene Servicenamen */
RC brok_unregister (char * svcn);

/*  Fuellt be mit dem gefunden Eintrag:
    RC: OK
        SVC_NOT_REGISTERED  fuer nicht gefundene Servicenamen */
RC brok_bind (char * svcn, bent * be);

/* Vergibt eine eindeutig CID (Client ID)
    zur Idenfikation aller Objekte dieses Clients */
char * brok_get_cid ();

#endif /* _BROKER_H_ */
