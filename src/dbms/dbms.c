/* ------------------------------------------------------------------------
|   Dateiname:      $RCSfile: dbms.c,v $
|   Version:        $Revision: 1 $
|   Erstellt am:    00.00.96
|   Geaendert am:   $Date: 19.11.97 9:36 $
|   Komponente:     DB
|   Erstellt von:   Johannes Weigend
|   Geandert von:   $Author: Johannes $
|   Copyright:      Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
|   Bermerkung:     Tabstop = 4
---------------------------------------------------------------------------*/

#include "dbms.h"
#include "btab.h"
#include "sadm.h"
#include "knde.h"
#include "knto.h"
#include "ctab.h"
#include "cmgr.h"

static btab * knde_database = NULL;
static btab * knto_database = NULL;


void dbms_open () {
    /* Dummy */
}


/* Schliessen und vernichten der Proxys */

void dbms_close () {

    /* Gefaehrlich wenn Server abstuerzt... */
    try {

        if (knde_database) {
            btab_close  (knde_database);
            btab_delete (knde_database);
        }
        if (knto_database) {
            btab_close  (knto_database);
            btab_delete (knto_database);
        }
    }
    catch (FAT_EXCEPT) {

        LOG ("[DBMS]: cant close DB. (sorry) (continueing)\n");
        }
    end_try;

    knde_database = NULL;
    knto_database = NULL;
}


void dbms_commit () {

    ctab_commit (cmgr_get_cid());
}


void dbms_rollback () {

    ctab_rollback (cmgr_get_cid());
}


/* Loeschen der sadm - Serverhandles */

void dbms_data_server_changed () {

   if (knde_database) {
      /*sadm_remove (KNDE_BTAB_SVC);*/
      dbms_close ();
      knde_database = dbms_get_btab (KNDE_BTAB_SVC);
   }

   if (knto_database) {
      /*sadm_remove (KNTO_BTAB_SVC);*/
      dbms_close ();
      knde_database = dbms_get_btab (KNTO_BTAB_SVC);
   }
}


btab * dbms_get_btab (char * svcn) {

    Assert (svcn);

    if (strcmp (KNDE_BTAB_SVC, svcn) == 0) {
        if (! knde_database) {
            knde_database = btab_new ();
            Assert (knde_database);
            btab_open (knde_database, "KNDE.DAT", KNDE_DB_RECORDLENGTH, KNDE_DB_RID_BASE);
        }
        return knde_database;
    }
    else
    if (strcmp (KNTO_BTAB_SVC, svcn) == 0) {
        if (! knto_database) {
            knto_database = btab_new ();
            Assert (knto_database);
            btab_open (knto_database, "KNTO.DAT", KNTO_DB_RECORDLENGTH, KNTO_DB_RID_BASE);
        }
        return knto_database;
    }
    else
    return NULL;
}
