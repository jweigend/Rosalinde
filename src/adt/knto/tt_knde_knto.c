/* ------------------------------------------------------------------------
|   Dateiname:      $RCSfile: tt_knde_knto.c,v $
|   Version:        $Revision: 1 $
|   Erstellt am:    00.00.96
|   Geaendert am:   $Date: 19.11.97 9:36 $
|   Komponente:     GLOB
|   Erstellt von:   Johannes Weigend / Christian Stoellinger
|   Geandert von:   $Author: Johannes $
|   Copyright:      Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
|   Bermerkung:     Tabstop = 4
--------------------------------------------------------------------------*/

#include "knde.h"
#include "knto.h"
#include "dbms.h"
#include "ctab.h"
#include "sadm.h"

ENABLE_ERROR_HANDLING;


char xdr_required_nullstring = '\0';


int main (int argc, char * argv[]) {

    knde * k;
    knto * ko1, * ko2;
    list * l;
    long oid;
    RC rc;

    /* Kunde */
    strg  * name;
    strg  * vorname;
    adrs  * adresse;
    anrd  * anrede;

    /* Konto */
    strg  * bankname;
   
    char * brokerhost;


    if (argc != 2) {
        LOG ("Host muss mit angegeben werden.\n\tt_knto (brokerhost) \n");
        exit (-1);
    }
    brokerhost = argv[1];

    sadm_init (brokerhost);

    ctab_init ();
 
    k = knde_new ();
    Assert (k);

    ko1 = knto_new ();
    Assert (ko1);

    ko2 = knto_new ();
    Assert (ko2);

    /* MAKE PERSISTENT */
    knde_register (k, &oid);
    knto_register (ko1, &oid);
    knto_register (ko2, &oid);

    name = strg_new (0);
    Assert (name);
    vorname = strg_new (0);
    Assert (vorname);
    anrede = anrd_new ();
    Assert (anrede);
    adresse = adrs_new ();
    Assert (adresse);
    bankname = strg_new (0);
    Assert (bankname);

    anrd_in (anrede, &rc, LANG, "Herr");
    Assert (rc == OK);
    strg_in (name,              "Bugs");
    strg_in (vorname,           "Bunny");
    adrs_in (adresse,           "Fussenerweg", "61", "83071", "Stephankirchen", "D - Germany");


    /*************************************/
    /* Hier wird der Kunde veraendert    */
    /*************************************/
    knde_set_anrede (k,     anrede);
    knde_set_name (k,       name);
    knde_set_vorname (k,    vorname);
    knde_set_adresse (k,    adresse);


    /* KONTO */
    strg_in (bankname, "HYPO-Muenchen");
    knto_set_bankname (ko1, bankname);
    strg_in (bankname, "SPARDA-Rosenheim");
    knto_set_bankname (ko2, bankname);

    dbms_commit ();

    LOG ("Ordne Konten den Kunden zu.\n");
    knto_set_kunde (ko1, k);
    knto_set_kunde (ko2, k);
    LOG ("---\n");

    dbms_commit ();

    ctab_clear (); /* Alles wegwerfen */
    ctab_init ();

    k = knde_find_by_key (KNDE_DB_RID_BASE, &rc);
    Assert (k);

    LOG ("Suche Konten des Kunden.");
    l = knde_get_konten (k);
    Assert (l);

    list_print (l, (LIST_FCT) knto_print);
    /* Beide Konten muessen in der Liste sein */
    LOG ("---\n");

    ctab_clear ();
    ctab_init ();

    LOG ("Suche Konto ueber ROWID\n");
    ko1 = knto_find_by_key (KNTO_DB_RID_BASE, &rc);
    Assert (ko1);

    knto_print (ko1);
    LOG ("---\n");

    LOG ("Suche dazugehoerigen Kunden.");
    k = knto_get_kunde (ko1);
    if (!k) LOG ("Nicht gefunden.\n");
    else 
    knde_print (k);

    LOG ("Suche unzugeordnete Konten ...\n");
    l = knto_find_unassigned ();
    list_print (l, (LIST_FCT) knto_print);
    LOG ("--- n");
    return 0;

}
