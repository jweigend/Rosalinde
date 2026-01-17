/* ------------------------------------------------------------------------
   |    Dateiname:        $RCSfile: knto.c,v $
   |    Version:          $Revision: 1 $
   |    Erstellt am:      00.00.96
   |    Geaendert am:     $Date: 19.11.97 9:36 $
   |    Komponente:       Konto
   |    Erstellt von:     Christian Stoellinger
   |    Geandert von:     J. Siedersleben, 9.7.96
   |                      kunde als Zeiger, nicht ueber Nummer
   |                      Weigend / Stoellinger (Rattenschwanzladen entfernt)
   |    Copyright:        Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
   |   --------------------------------------------------------------------------- */

#include "knto.h"
#include "ctab.h"
#include "cmgr.h"
#include "btab.h"
#include "dbms.h"


/* Alloc/Init/Free */
knto *
knto_new ()
{
    knto *konto;

    konto = (knto *) malloc (sizeof (knto));
    Assert (konto);

    knto_init (konto);
    return konto;
}


knto *
knto_delete (knto * konto)
{
    Assert (konto);

    knto_clear (konto);
    free (konto);
    return NULL;
}


void
knto_init (knto * konto)
{
    Assert (konto);

    pkrn_init (&(konto->persistent));
    strg_init (&(konto->bankname), MAX_BANKNAME);

    konto->kunde = NULL;
    konto->kunde_rid = 0L;
    konto->konto_id = 0L;
    konto->konto_nummer = 0L;
    konto->blz = 0L;
    konto->betrag = (double) 0.0;
}


void
knto_clear (knto * konto)
{
    Assert (konto);

    pkrn_clear (&(konto->persistent));
    strg_clear (&(konto->bankname));
    konto->kunde = NULL; /* CHECK knde_clear ? */
    konto->kunde_rid = 0L;
    konto->konto_id = 0L;
    konto->konto_nummer = 0L;
    konto->blz = 0L;
    konto->betrag = (double) 0.0;
}

/* Get/Set */
void
knto_set_kunde (knto * konto, knde * kd)
{
    Assert (konto && kd);

    konto->kunde = kd;
    konto->kunde_rid = knde_get_rid (kd);

    pkrn_modify (&(konto->persistent));
}


void
knto_set_unassigned(knto* konto)
{
    Assert(konto);
    
    konto->kunde = NULL;   /* Dieser muss vom Aufrufer geloescht werden! */
    konto->kunde_rid = 0L;
    
    pkrn_modify(&(konto->persistent));
}


knde *
knto_get_kunde (knto * k)
{
    RC rc;

    Assert (k);

    if (k->kunde) return k->kunde;

    if (k->kunde_rid == 0) return NULL;

    k->kunde = knde_find_by_key(k->kunde_rid, &rc);
    /* rc ignored */

    return k->kunde;
}


void
knto_set_konto_nummer( knto* konto, long konto_nr)
{
    Assert(konto);
    
    konto->konto_nummer = konto_nr;
    pkrn_modify(&(konto->persistent));
}

long
knto_get_konto_nummer (knto * konto)
{
    Assert (konto);
    return (konto->konto_nummer);
}


void
knto_set_blz (knto * konto, long blz)
{
    Assert (konto);

    konto->blz = blz;
    pkrn_modify (&(konto->persistent));
}


long
knto_get_blz (knto * konto)
{
    Assert (konto);
    return konto->blz;
}


void
knto_set_bankname (knto * konto, strg * bankname)
{
    Assert (konto);

    strg_copy (&(konto->bankname), bankname);
    pkrn_modify (&(konto->persistent));
}


strg *
knto_get_bankname (knto * konto)
{
    Assert (konto);
    return &(konto->bankname);
}


void
knto_set_betrag (knto * konto, double betrag)
{
    Assert (konto);

    konto->betrag = betrag;
    pkrn_modify (&(konto->persistent));
}


double
knto_get_betrag (knto * konto)
{
    Assert (konto);
    return konto->betrag;
}


/* DB */
void
knto_insert (void *konto, long *sk)
{
    strg db_string;

    Assert (konto && sk);

    strg_init (&db_string, 0);
    knto_db_out (konto, &db_string);

    btab_append (dbms_get_btab (KNTO_BTAB_SVC), strg_out (&db_string), sk);

    strg_clear (&db_string);
}

void
knto_reread (void *knto, long sk)
{

    char buffer[KNTO_DB_RECORDLENGTH + 1] =
    {0};
    strg db_string;
    RC rc;

    Assert (knto && sk);

    strg_init (&db_string, 0);

    rc = btab_get_at (dbms_get_btab (KNTO_BTAB_SVC), sk, buffer);
    Assert (rc == OK);

    strg_in (&db_string, buffer);

    knto_db_in (knto, &db_string);

    strg_clear (&db_string);
}

void
knto_update (void *konto, long sk)
{
    strg db_string;
    knto dbk;

    Assert (konto && (sk >= 0));

    strg_init (&db_string, 0);
    knto_init (&dbk);

/*  TODO: Lock btab  ... */
    knto_reread (&dbk, sk);
		
    if (dbk.persistent.change_cnt > ((knto *) konto)->persistent.change_cnt) { 
	/* ein anderer Client hat den Eintrag schon veraendert */
		
	strg_clear (&db_string);
	knto_clear (&dbk);	
	throw (DB_CHANGED);
    }

    ((knto *) konto)->persistent.change_cnt ++;

    knto_db_out (konto, &db_string);

    btab_put_at (dbms_get_btab (KNTO_BTAB_SVC), strg_out (&db_string));

/* UNLOCK btab ... */
    strg_clear (&db_string);
    knto_clear (&dbk);
}


static long
knto_knde_rid (strg * dbs)
     /* liefert den Fremdschluessel des Kontos im record */
{
    knto k;
    long rid;
    strg tmp;

    knto_init (&k);
    strg_init (&tmp, 0);

    strg_copy (&tmp, dbs); /* String wird durch db_in zerstoert ... */
    knto_db_in (&k, &tmp);
    rid = k.kunde_rid;

    knto_clear (&k);
    strg_clear (&tmp);
    return rid;
}

long   knto_get_rid (knto * k) {

   Assert (k);
   return pkrn_get_rid (&k->persistent);
}


knto *
knto_find_by_key (long key, RC * rc)
{
    knto *k = NULL;
    oent *o = NULL;
    strg *dbs = NULL;
    pkrn *pk = NULL;
    otab *ot = NULL;
    cent *ce;
    long oid;
    char record[KNTO_DB_RECORDLENGTH + 1] =
    {0};


    Assert ((key >= 0) && rc);

    /* Zuerst richtige OTAB holen */
    ce = ctab_get (cmgr_get_cid ());

    /* OK hier gibt es eine OTAB */
    if (ce)
      {
      ot = cent_get_otab (ce);
      Assert (ot);

      /* Dann in der OTAB suchen */
      *rc = otab_find_by_rid (ot, key, &o);
      if (*rc == OK)
        {
        pk = oent_get_pkrn (o);
        Assert (pk);

        return (pk->owner);
        }
      }

    /* Jetzt aus der DB lesen */


    *rc = btab_get_at (dbms_get_btab (KNTO_BTAB_SVC), key, record);
    if (*rc != OK)
    return NULL;


    /* Aufbau des Kontos */

    dbs = strg_new (0);
    strg_in (dbs, record);

    k = knto_new ();
    knto_db_in (k, dbs);

    k->persistent.state = os_clean;

    knto_register (k, &oid);

    strg_delete (dbs);

    *rc = OK;
    return k;
}




list *
knto_find_unassigned ()     /* findet alle nicht zugeordneten Konten */
{
    list *l = NULL;
    btab *b = NULL;
    knto *k = NULL;
    strg *dbs = NULL;
    long oid;
    RC rc;
    char record[KNTO_DB_RECORDLENGTH + 1] =
    {0};

    l = list_new ();        /* Liste fuers Ergebnis */
    Assert(l);

    dbs = strg_new (0);     /* Hilfsstring */
    Assert(dbs);

    b = dbms_get_btab (KNTO_BTAB_SVC);  /* Kontotabelle */
    Assert(b);

    btab_rewind (b);

    while (TRUE) {

       rc = btab_get_next (b, record);
       if (rc != OK)
           break;
       strg_in (dbs, record);

       if (knto_knde_rid (dbs) == 0) {

           k = knto_new ();
           Assert(k);

           knto_db_in (k, dbs);
           k->persistent.state = os_clean;
           knto_register (k, &oid);
           list_append (l, k);

       }
    }
    strg_delete (dbs);
    return (l);
}


list *
knto_find_by_kunde (knde * kunde, long kunde_rid, RC * rc)
{
    list *l = NULL;
    btab *b = NULL;
    knto *k = NULL;
    strg *dbs = NULL;
    long oid;
    RC lrc;
    char record[KNTO_DB_RECORDLENGTH + 1] = {0};

    Assert(kunde && rc);
    *rc = OK;

    l = list_new ();        /* Liste fuers Ergebnis */
    Assert(l);

    dbs = strg_new (0);     /* Hilfsstring */
    Assert(dbs);

    b = dbms_get_btab (KNTO_BTAB_SVC);  /* Kontotabelle */
    Assert(b);

    btab_rewind (b);

/*
  kunde_rid = knde_get_rid(kunde); :: Verursacht Remote einen DEADLOCK 
  Daher muss die ROW_ID in die SS
*/
  
    while (TRUE) {
       lrc = btab_get_next (b, record);
       if (lrc != OK)
           break;

       strg_in (dbs, record);
       if (knto_knde_rid (dbs) == kunde_rid) {

           k = knto_new ();
           Assert(k);

           knto_db_in (k, dbs);
           k->persistent.state = os_clean;
           knto_register (k, &oid);
           list_append (l, k);

       }
    }
    strg_delete (dbs);
    return (l);
}

void
knto_db_out (knto * konto, strg * db_string)
{

    Assert (konto && db_string);

    pkrn_db_out (&konto->persistent, db_string);
    long_db_out (&konto->konto_id, db_string);
    long_db_out (&konto->kunde_rid, db_string);
    long_db_out (&konto->konto_nummer, db_string);
    long_db_out (&konto->blz, db_string);
    strg_db_out (&konto->bankname, db_string);
    double_db_out (&konto->betrag, db_string);
}


void
knto_db_in (knto * konto, strg * db_string)
{
    Assert (konto && db_string);

    pkrn_db_in (&konto->persistent, db_string);

/*  Die ROW-ID des Kunden darf NICHT verschluckt werden,
    da sonst das bearbeiten eines Kontos nur ueber Ratten-
    schwanzladen des Kunden moeglich ist  */

    long_db_in (&konto->konto_id, db_string);
    long_db_in (&konto->kunde_rid, db_string);
    long_db_in (&konto->konto_nummer, db_string);
    long_db_in (&konto->blz, db_string);
    strg_db_in (&konto->bankname, db_string);
    double_db_in (&konto->betrag, db_string);
}


void
knto_register (knto * konto, OID * oid)
{
    Assert (konto);

    LOG ("cid = %s", cmgr_get_cid ());
    ctab_register (cmgr_get_cid (), oid, &(konto->persistent), konto, 
                                       knto_update, knto_insert, knto_reread);
    ctab_print ();
}


void
knto_unregister (knto * konto)
{
    Assert (konto);
 
    if (pkrn_get_oid (&konto->persistent) == 0) return;

    ctab_unregister (cmgr_get_cid (), pkrn_get_oid (&(konto->persistent)));
    ctab_print ();
}


/* Sonstiges */
void
knto_print (knto * konto)
{      
    Assert (konto);
  
    LOG ("Konto:\n");
    strg_print (&(konto->bankname));
    LOG ("KTO: %ld\n", konto->konto_nummer);
    LOG ("BLZ: %ld\n", konto->blz);
    LOG ("Betrag: %lf", konto->betrag);
    pkrn_print (&(konto->persistent));
    LOG ("--------\n");
}


void
knto_einzahlen (knto * konto, double betrag)
{
    double betrag_buffer;

    Assert (konto && (betrag >= (double) 0.0));

    betrag_buffer = knto_get_betrag (konto);

    betrag_buffer += betrag;

    knto_set_betrag (konto, betrag_buffer);
}


void
knto_auszahlen (knto * konto, double betrag)
{
    double betrag_buffer;

    Assert (konto && (betrag >= (double) 0.0));

    betrag_buffer = knto_get_betrag (konto);

    betrag_buffer -= betrag;

    knto_set_betrag (konto, betrag_buffer);
}


BOOL
knto_is_persistent (knto * k) 
{
    Assert (k);
    return pkrn_get_oid (&k->persistent) == 0 ? FALSE : TRUE;
}
