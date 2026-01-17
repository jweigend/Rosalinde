/* ------------------------------------------------------------------------
|   Dateiname:      $RCSfile: tt_knto.c,v $
|   Version:        $Revision: 1 $
|   Erstellt am:    00.00.96
|   Geaendert am:   $Date: 19.11.97 9:36 $
|   Komponente:     GLOB
|   Erstellt von:   Johannes Weigend
|   Geandert von:   $Author: Johannes $
|   Copyright:      Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
|   Bermerkung:     Tabstop = 4
--------------------------------------------------------------------------*/


#include "knto.h"
#include "otab.h"
#include "btab.h"
#include "sadm.h"
#include "ctab.h"
#include "cmgr.h"
#include "dbms.h"

ENABLE_ERROR_HANDLING;


char xdr_required_nullstring = '\0';


int main (int argc, char * argv[]) {

    knto * k;
    knto * k1;
    knto * k3;
    strg * bankname;
    long oid;
    RC rc;
    int loops;

    char * brokerhost;

    if (argc != 2) {
        LOG ("Host muss mit angegeben werden.\n\tt_knto (brokerhost) \n");
        Assert (FALSE);
    }
    brokerhost = argv[1];

    sadm_init (brokerhost);

    LOG ("\n...done\n");


    /************ WICHTIG ***********/
    ctab_init ();
    /********************************/

    LOG (" - Lege neue Konton an ...\n");

    k = knto_new ();
    Assert (k);

    k1 = knto_new ();
    Assert (k1);

    LOG (" - Registriere Konten in der zugehoerigen OTAB ...\n");

    /*************************************/
    /* Hier werden die Konton persistent */
    /*************************************/

    knto_register (k, &oid);
    LOG ("Die OID des Kontos k1: %ld\n", oid);

        knto_register (k1, &oid);
        LOG ("Die OID des Kontos k2: %ld\n", oid);

        /* Debug only

    knto_register (k1, &oid);
        LOG ("Die OID des Kontos k2: %ld\n", oid);
    */

    knto_print (k);
    knto_print (k1);

    /****************************************/
    /* Persistente Konten werden veraendert */
    /****************************************/
    bankname = strg_new (0);
    Assert (bankname);
    strg_in (bankname, "HYPO-Bank München");


    /*************************************/
    /* Hier wird das Konto veraendert    */
    /*************************************/
    knto_set_bankname (k, bankname);
    knto_set_betrag (k, 1000);
    knto_set_blz (k, 70090500);


    /*************************************/
    /* Hier wird der Kunde veraendert    */
    /*************************************/
    strg_in (bankname, "Sparda-Bank München");

    knto_set_bankname (k1, bankname);
    knto_set_betrag (k1, 2000);
    knto_set_blz (k1, 70090501);


    knto_print (k);
    knto_print (k1);

    LOG ("\n - Client/Servertabelle:\n");

    ctab_print ();

    LOG ("\n - Suche Objekt ueber rid vor commit...\n");

    /*************************************/
    /* Suche ueber RowID rid             */
    /*************************************/
    k3 = knto_find_by_key (KNTO_DB_RID_BASE + 1, &rc);

    if (k3) {

        LOG("\n...gefunden: \n");

        knto_print (k3);
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


    knto_print (k);

    knto_print (k1);

    /* Erzwinge neue Dateiproxys -> neuer bind */

    dbms_data_server_changed ();


    LOG ("\nSuche Objekt ueber rid ...\n");

    k3 = knto_find_by_key (KNTO_DB_RID_BASE + 1, &rc);
    Assert (k3 && rc == OK);

    LOG("\n...gefunden: \n");

    knto_print (k3);

    /*************************************/
    /* Deregistrierung der Konten        */
    /*************************************/

    LOG (" - Deregistriere Kunden ...\n");

    knto_unregister (k);
    knto_unregister (k1);
    knto_unregister (k3);

    LOG ("\n - Client/Servertabelle:\n");
    ctab_print ();


    /* Aufraeumen .. */

    strg_delete (bankname);

    knto_delete (k);
    knto_delete (k1);

    try {
      knto_delete (k3);
    }
    catch (NOK_PROXY_NOT_FOUND) {
        /* Moeglicherweise sind k1 und k3 dasselbe Objekt */
    }
    end_try;

    ctab_clear ();

    LOG (" - OK\n");

    return 0;
}

