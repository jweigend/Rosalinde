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

#include "r_knde.h"
#include "dbms.h"
#include "cmgr.h"
#include "sadm.h"

short * dbms_commit_1_svc (char ** argp, struct svc_req *rqstp) {

  static short result;

  Assert (argp);

  result = OK;

  cmgr_set_cid (*argp);


  try {

    dbms_commit ();

  }
  catch (FAT_EXCEPT) {

    LOG ("[DBMS]: Fatal Exception bei commit()\n");
    result = FAT_EXCEPT;
  }
  catch (DB_CHANGED) {

    LOG ("[DBMS]: DB wurde schon veraendert. (Rollback)\n");
    result = DB_CHANGED;
  }
  end_try;

  return &result;
}

short * dbms_rollback_1_svc (char ** argp, struct svc_req *rqstp) {

  static short result;

  Assert (argp);

  result = OK;

  cmgr_set_cid (*argp);

  try {

    dbms_rollback ();

  }
  catch (FAT_EXCEPT) {

    LOG ("[DBMS]: Fatal Exception bei rollback()\n");
    result = FAT_EXCEPT;
  }
  end_try;

  return &result;
}


short * dbms_data_server_changed_1_svc (void * argp, struct svc_req *rqstp) {

    static short result;
    char * broker;

    /* Force rebind () */
    broker = sadm_get_broker ();
    Assert (broker);
    sadm_clear ();
    sadm_init (broker);

    dbms_data_server_changed ();

    result = OK;

    return &result;
}
