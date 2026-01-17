/* ------------------------------------------------------------------------
|   Dateiname:      $RCSfile: r_btab_svc_main.c,v $
|   Version:        $Revision: 1 $
|   Erstellt am:    00.00.96
|   Geaendert am:   $Date: 19.11.97 9:36 $
|   Komponente:     BTAB Server-Initialisierung
|   Erstellt von:   Johannes Weigend
|   Geandert von:   $Author: Johannes $
|   Copyright:      Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
|   Bermerkung:     Tabstop = 4
---------------------------------------------------------------------------*/
#include "r_btab.h"
#include "r_brok.h"
#include "btab.h"

ENABLE_ERROR_HANDLING;

int main (int argc, char * argv[]) {

    bent bentry = { "", KNDE_BTAB_SVC, "tcp", R_BTAB, R_BTAB_VERSION };

    char * brokerhost;
    char host [MAX_HOSTNAME] = {0};

    if (argc == 1) {

        LOG ("Broker muss angegeben werden !\n");
        exit (-1);
    }

    brokerhost = argv[1];

    try {
        ctab_init ();
        sadm_init (brokerhost);

        gethostname (host, MAX_HOSTNAME);
        bent_set_host (&bentry, host);
        brok_register (&bentry);

        LOG ("\n[BTAB_SVC]: running.\n");

        rpcgen_main (); /* Endlos Dispatcher */

    }
    catch(FAT_EXCEPT) {

        /* Hier ist eine EXCEPTION aufgetreten */

        LOG ("\n[BTAB_SVC]: shutting down.\n");

        brok_unregister (bent_get_svcn (&bentry));

        ctab_clear ();

    }
    end_try;

    return -1;
}
