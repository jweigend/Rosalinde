/* ------------------------------------------------------------------------
|   Dateiname:      $RCSfile: dbms.c,v $
|   Version:        $Revision: 1 $
|   Erstellt am:    00.00.96
|   Geaendert am:   $Date: 19.11.97 9:36 $
|   Komponente:     DB
|   Erstellt von:   Jo hannes Weigend
|   Geandert von:   $Author: Johannes $
|   Copyright:      Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
|   Bermerkung:     Tabstop = 4
---------------------------------------------------------------------------*/

#include "dbms.h"
#include "sadm.h"
#include "r_knde.h"
#include "r_knto.h"
#include "cmgr.h"


static void db_commit (char * svcn) {

  CLIENT * cl;
  short * rc;
  char * cid;

  Assert (svcn);

  cl = sadm_get_serverhandle (svcn);
  if (!cl) return;                      /* Nothing to do... */

  cid = cmgr_get_cid();
  Assert (cid);

  rc = dbms_commit_1 (&cid, cl);
  Assert (rc);

  if (*rc != OK) throw (*rc);
}

static void db_rollback (char * svcn) {

  CLIENT * cl;
  short * rc;
  char * cid;

  Assert (svcn);

  cl = sadm_get_serverhandle (svcn);
  if (!cl) return;

  cid = cmgr_get_cid();
  Assert (cid);

  rc = dbms_rollback_1 (&cid, cl);
  if (*rc != OK) throw (*rc);
}

static void db_data_server_changed (char * svcn) {

  CLIENT * cl;
  short * rc;
  char c = '\0';

  Assert (svcn);

  cl = sadm_get_serverhandle (svcn);
  if (!cl) return;

  rc = dbms_data_server_changed_1 (&c, cl);
  if (*rc != OK) throw (*rc);

  sadm_remove (svcn);
}


/* Spaeter kann hier ueber alle Eintrage des sadms itteriert werden */

void dbms_commit () {

  db_commit (KNDE_SVC);
  db_commit (KNTO_SVC);
}

void dbms_rollback () {

  db_rollback (KNDE_SVC);
  db_rollback (KNTO_SVC);
}

void dbms_data_server_changed () {

  db_data_server_changed (KNDE_SVC);
  db_data_server_changed (KNTO_SVC);
}
