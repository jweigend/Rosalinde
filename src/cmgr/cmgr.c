/* ------------------------------------------------------------------------
|   Dateiname:      $RCSfile: cmgr.c,v $
|   Version:        $Revision: 1 $
|   Erstellt am:    00.00.96
|   Geaendert am:   $Date: 19.11.97 9:36 $
|   Komponente:     CLIENT
|   Erstellt von:   Johannes Weigend
|   Geandert von:   $Author: Johannes $
|   Copyright:      Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
|   Bermerkung:     Tabstop = 4
---------------------------------------------------------------------------*/
#include "cmgr.h"
#include "brok.h"
#include "cent.h"

static char client_id_mgr [MAX_CIDLENGTH];
static char server_id_mgr [MAX_CIDLENGTH];

 /* Setzt ServerID */
void    cmgr_set_sid (char * sid);

static int initialized = 0;


void cmgr_init () {

    char * cid;

    if (initialized) return;

    memset (client_id_mgr, '\0', sizeof (client_id_mgr));

    cid = brok_get_cid ();
    Assert (cid);

    initialized = 1;

    cmgr_set_cid (cid);
    cmgr_set_sid (cid);
}


void   cmgr_set_cid  (char * cid) {

    Assert (cid && (strlen (cid) < MAX_CIDLENGTH));

    if (! initialized) cmgr_init ();

    strcpy (client_id_mgr, cid);
}


void    cmgr_set_sid (char * sid) {

    Assert (sid && (strlen (sid) < MAX_CIDLENGTH));

    if (! initialized) cmgr_init ();

    strcpy (server_id_mgr, sid);
}

char * cmgr_get_cid  () {

    if (! initialized) cmgr_init ();

    return client_id_mgr;
}


char * cmgr_get_sid () {

    if (! initialized) cmgr_init ();

    return server_id_mgr;
}
