/* ------------------------------------------------------------------------
|   Dateiname:      $RCSfile: tt_knde.c,v $
|   Version:        $Revision: 1 $
|   Erstellt am:    00.00.96
|   Geaendert am:   $Date: 19.11.97 9:36 $
|   Komponente:     GLOB
|   Erstellt von:   Johannes Weigend
|   Geandert von:   $Author: Johannes $
|   Copyright:      Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
|   Bermerkung:     Tabstop = 4
--------------------------------------------------------------------------*/


#include "knde.h"
#include "otab.h"
#include "btab.h"
#include "sadm.h"
#include "ctab.h"
#include "cmgr.h"
#include "dbms.h"

ENABLE_ERROR_HANDLING;

char xdr_required_nullstring = '\0';

int main (int argc, char * argv[]) {

    knde * k;
    knde * k1;
    knde * k3;
    strg * name, * vorname;
    adrs * adresse;
    anrd * anrede;
    long oid;
    RC rc;
    int loops;

    char * brokerhost;

    if (argc != 3) {
        LOG ("Host muss mit angegeben werden.\n\tt_knde (brokerhost) (loops)\n");
        Assert (FALSE);
    }
    brokerhost = argv[1];

    sadm_init (brokerhost);

    LOG ("\n...done\n");


    /************ WICHTIG ***********/
    ctab_init ();
    /********************************/

    for (loops = 0; loops < atoi(argv[2]); loops ++) {

    LOG (" - Lege neue Kunden an ...\n");

    k = knde_new ();
    Assert (k);

    k1 = knde_new ();
    Assert (k1);

    LOG (" - Registriere Kunden in der zugehoerigen OTAB ...\n");

    /*************************************/
    /* Hier werden die Kunden persistent */
    /*************************************/

    knde_register (k, &oid);
    LOG ("Die OID des Kunden k1: %ld\n", oid);

        knde_register (k1, &oid);
        LOG ("Die OID des Kunden k2: %ld\n", oid);

        /* Debug only

    knde_register (k1, &oid);
        LOG ("Die OID des Kunden k2: %ld\n", oid);
    */

    knde_print (k);
    knde_print (k1);

    /****************************************/
    /* Persistente Kunden werden veraendert */
    /****************************************/
    name = strg_new (0);
    Assert (name);
    vorname = strg_new (0);
    Assert (vorname);
    anrede = anrd_new ();
    Assert (anrede);
    adresse = adrs_new ();
    Assert (adresse);


    anrd_in (anrede, &rc, LANG, "Herr");
    Assert (rc == OK);
    strg_in (name,              "Weigend");
    strg_in (vorname,           "Johannes");
    adrs_in (adresse,           "Fussenerweg", "61", "83071", "Stephankirchen", "D - Germany");


    /*************************************/
    /* Hier wird der Kunde veraendert    */
    /*************************************/
    knde_set_anrede (k,     anrede);
    knde_set_name (k,       name);
    knde_set_vorname (k,    vorname);
    knde_set_adresse (k,    adresse);

    anrd_in (anrede, &rc, LANG, "Frau");
    Assert (rc == OK);
    strg_in (name,              "Stoewe");
    strg_in (vorname,           "Katja");
    adrs_in (adresse,           "Fussenerweg", "61", "83071",   "Stephanskirchen", "D - Germany");


    /*************************************/
    /* Hier wird der Kunde veraendert    */
    /*************************************/
    knde_set_name (k1,      name);
    knde_set_vorname (k1,   vorname);
    knde_set_anrede (k1,    anrede);
    knde_set_adresse (k1,   adresse);


    knde_print (k);
    knde_print (k1);

    LOG ("\n - Client/Servertabelle:\n");

    ctab_print ();

    LOG ("\n - Suche Objekt ueber rid vor commit...\n");

    /*************************************/
    /* Suche ueber RowID rid             */
    /*************************************/
    k3 = knde_find_by_key (101, &rc);

    if (k3) {

        LOG("\n...gefunden: \n");

        knde_print (k3);
    }
    else {

        LOG("\n...nicht gefunden (OK)");
    }

    LOG ("\n - Client/Servertabelle:\n");

    ctab_print ();


    /*************************************/
    /* Commit            */
    /*************************************/
    dbms_commit ();

    LOG ("\n\nCOMMIT ausgefuehrt.\n");


    knde_print (k);

    knde_print (k1);

    /* Erzwinge neue Dateiproxys -> neuer bind */

    dbms_data_server_changed ();


    LOG ("\nSuche Objekt ueber rid ...\n");

    k3 = knde_find_by_key (101, &rc);
    Assert (k3 && rc == OK);

    LOG("\n...gefunden: \n");

    knde_print (k3);

    /* Aendern (update ()) */

    strg_in (name, "Schmidt");
    knde_set_name (k3, name);

    try {

        dbms_commit ();
    }
    catch (DB_CHANGED) {

        LOG ("\aKunde(n) wurde(n) von anderem Client veraendert !\n");
        dbms_rollback ();
        LOG ("Rolled back !\n");
    }
    end_try;

    knde_print (k3);

    /*************************************/
    /* Deregistrierung der Kunden        */
    /*************************************/

    LOG (" - Deregistriere Kunden ...\n");

    knde_unregister (k);
    knde_unregister (k1);
    knde_unregister (k3);

    LOG ("\n - Client/Servertabelle:\n");
    ctab_print ();


    /* Aufraeumen .. */

    strg_delete (name);
    strg_delete (vorname);
    adrs_delete (adresse);
    anrd_delete (anrede);


    knde_delete (k);
    knde_delete (k1);

    try {
      knde_delete (k3);
    }
    catch (NOK_PROXY_NOT_FOUND) {
        /* Moeglicherweise sind k1 und k3 dasselbe Objekt */
    }
    end_try;

    }

    ctab_clear ();

    LOG (" - OK\n");

    return 0;
}

