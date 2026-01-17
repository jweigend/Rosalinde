/* ------------------------------------------------------------------------
   |    Dateiname:      $RCSfile: knto.h,v $
   |    Version:        $Revision: 1 $
   |    Erstellt am:    00.00.96
   |    Geaendert am:   $Date: 19.11.97 9:36 $
   |    Komponente:     Anrede
   |    Erstellt von:   Johannes Weigend
   |    Geandert von:   $Author: Johannes $   J. Siedersleben, 9.7.96
   |    Copyright:      Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
   |    Bermerkung:     Tabstop = 4
   --------------------------------------------------------------------------- */

#ifndef _KNTO_H_
#define _KNTO_H_

#include "rosa.h"
#include "pkrn.h"
#include "strg.h"
#include "otab.h"
#include "list.h"
#include "knde.h"

#define MAX_BANKNAME            60
#define KNTO_DB_RECORDLENGTH    204
#define KNTO_DB_RID_BASE        10000
#define KNTO_SVC                "KNTO Funktionen"
#define KNTO_BTAB_SVC           "KNTO Daten"
#define MAX_KNTO_LIST           1024

#ifdef KNTO_PROXY
typedef long knto;
#else
typedef struct tagknto
  {
      pkrn persistent;

      knde *kunde;
      long konto_id;	/* ID = Key */
      long kunde_rid;
      long konto_nummer;
      long blz;
      strg bankname;
      double betrag;
  }
knto;
#endif

/* Alloc/Init/Free */
knto *knto_new ();
knto *knto_delete (knto * konto);
void knto_init (knto * konto);
void knto_clear (knto * konto);

/* Get/Set */

void knto_set_kunde (knto * konto, knde * kd);
knde * knto_get_kunde (knto * konto);
void knto_set_unassigned(knto* konto);

long knto_get_rid(knto* konto); /* neu */

/* void knto_set_konto_nummer (knto * konto, long konto_nummer); */
/* Fachlicher Schluessel wird wie RID (Konto_ID) vom System vergeben ! */
long knto_get_konto_nummer (knto * konto);
void knto_set_konto_nummer (knto* konto, long kto_nr); /* neu */

void knto_set_blz (knto * konto, long blz);
long knto_get_blz (knto * konto);

void knto_set_bankname (knto * konto, strg * bankname);
strg *knto_get_bankname (knto * konto);

void knto_set_betrag (knto * konto, double betrag);
double knto_get_betrag (knto * konto);

/* DB */
void knto_insert (void *konto, long *sk);
void knto_update (void *konto, long sk);
void knto_reread (void *konto, long sk);
knto *knto_find_by_key (long key, RC * rc);
list *knto_find_by_kunde (knde *  k, long kunde_rid, RC * rc);
list *knto_find_unassigned ();
void knto_db_out (knto * konto, strg * db_string);
void knto_db_in (knto * konto, strg * db_string);
void knto_register (knto * konto, OID * oid);
void knto_unregister (knto * konto);

/* Sonstiges */
void knto_print (knto * konto);

/* Fachliches */
void knto_einzahlen (knto * konto, double betrag);
void knto_auszahlen (knto * konto, double betrag);

    /* Ist Konto Persistent ? */
BOOL knto_is_persistent (knto * k);

#endif /* _knto_H_ */
