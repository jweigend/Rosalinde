/* ------------------------------------------------------------------------
|   Dateiname:      $RCSfile: knde.h,v $
|   Version:        $Revision: 1 $
|   Erstellt am:    00.00.96
|   Geaendert am:   $Date: 19.11.97 9:36 $
|   Komponente:     KNDE
|   Erstellt von:   Johannes Weigend
|   Geandert von:   $Author: Johannes $
|   Copyright:      Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
|   Bermerkung:     Tabstop = 4
---------------------------------------------------------------------------*/

#ifndef _KNDE_H_
#define _KNDE_H_

#include "rosa.h"
#include "pkrn.h"
#include "strg.h"
#include "otab.h"
#include "adrs.h"
#include "enum.h"
#include "list.h"

#define MAX_KUNDENNAME          128
#define KNDE_DB_RECORDLENGTH    515
#define KNDE_DB_RID_BASE        100

#ifndef KNDE_PROXY


typedef struct _der_Kunde {

    pkrn persistent;

    anrd anrede;

    strg name;
    strg vorname;

    adrs adresse;

    list konten;
} knde;

#else

typedef long knde;

#endif

#define KNDE_SVC      "KNDE Funktionen"
#define KNDE_BTAB_SVC "KNDE Daten"

    /* Allokation und Initialisierung */
knde * knde_new ();
    /* Loeschen */
knde * knde_delete (knde * k);
    /* Init */
void   knde_init (knde * k);
    /* Clear */
void   knde_clear (knde * k);

    /* set Methoden */
void   knde_set_name  (knde * k, strg * name);

void   knde_set_vorname  (knde * k, strg * vorname);

void   knde_set_anrede (knde * k, anrd * a);

void   knde_set_adresse (knde * k, adrs * a);

void   knde_set_konten (knde * k, list * kl);

    /* get Methoden */
strg * knde_get_name    (knde * k);

strg * knde_get_vorname  (knde * k);

anrd * knde_get_anrede (knde * k);

adrs * knde_get_adresse (knde * k);

list * knde_get_konten (knde * k);

long   knde_get_rid (knde * k);


    /* Einfuegen in die DB -- rid wird vergeben */
void    knde_insert (void * k, long * sk);

    /* Aendern in der DB ueber rid */
void    knde_update (void * k, long sk);

    /* Nochmaliges lesen aus der DB (rollback) */
void    knde_reread (void * k, long sk);

    /* suchen ueber rid */
knde * knde_find_by_key (long key, RC * rc);

    /* Drucken */
void knde_print (knde * k);

    /* Erzeugt die DB-Darstellung */
void knde_db_out (knde * k, strg * db_string);

    /* Generiert den Kunden k aus der DB-Darstellung */
void knde_db_in (knde * k, strg * db_string);

    /* Registriert Kunden in der OTAB und intialisiert den PKRN */
void knde_register (knde * k, OID * oid);

    /* Loescht Kunden aus der OTAB */
void knde_unregister (knde * k);

    /* Ist Kunde Persistent ? */
BOOL knde_is_persistent (knde * k);

#endif /* _KNDE_H_ */
