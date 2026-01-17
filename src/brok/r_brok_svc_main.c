/* ------------------------------------------------------------------------
|   Dateiname:      $RCSfile: r_brok_svc_main.c,v $
|   Version:        $Revision: 1 $
|   Erstellt am:    00.00.96
|   Geaendert am:   $Date: 19.11.97 9:36 $
|   Komponente:     brok Server-Initialisierung
|   Erstellt von:   Johannes Weigend
|   Geandert von:   $Author: Johannes $
|   Copyright:      Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
|   Bermerkung:     Tabstop = 4
---------------------------------------------------------------------------*/
#include "except.h"
#include "r_brok.h"
#include "brok.h"

ENABLE_ERROR_HANDLING;

int main (int argc, char * argv[]) {

    try {

        brok_init ();

        LOG ("\n[BROK_SVC]: running.\n");

        rpcgen_main ();
    }
    catch(FAT_EXCEPT) {

        LOG ("[BROK_SVC]: shutting down\n");
    }
    end_try;

    return -1;
}

