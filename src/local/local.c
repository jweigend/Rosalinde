/* ------------------------------------------------------------------------
|   Dateiname:      $RCSfile: local.c,v $
|   Version:        $Revision: 1 $
|   Erstellt am:    00.00.96
|   Geaendert am:   $Date: 19.11.97 9:36 $
|   Komponente:     Lokale Dummy Methoden
|   Erstellt von:   Johannes Weigend
|   Geandert von:   $Author: Johannes $
|   Copyright:      Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
|   Bermerkung:     Tabstop = 4
---------------------------------------------------------------------------*/

#include "local.h"


CLIENT * clnt_create (char * host, long prgid, long versnr, char * proto) {

    CLIENT * c;

    c = (CLIENT *) malloc (sizeof (CLIENT));
    Assert (c);

    return c;
}


long authunix_create_default () {

    return 1L;
}

char * cmgr_get_cid () {

    static char s[128] = "LOCALHOST:0";
    return s;
}



