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
#include "knde.h"
#include "sadm.h"
#include "ctab.h"

#include <netdb.h>

ENABLE_ERROR_HANDLING;

char xdr_required_nullstring = '\0';

int main (int argc, char * argv[]) {

    bent bentry = { "", KNDE_BTAB_SVC, R_BTAB_PROTO, R_BTAB_KNDE, R_BTAB_VERSION };

    char * brokerhost;
    struct hostent * hent;
    char host [MAX_HOSTNAME] = {0};

    if (argc != 2) {

        LOG ("[BTAB_KNDE_SVC]: Missing Argument !\n");
        LOG ("Syntax: r_btab_knde_svc BROKERHOST\n");
        exit (-1);
    }

    brokerhost = argv[1];

    try {
        ctab_init ();
        sadm_init (brokerhost);

        /* Gethostname liefert nur den Hostnamen */
        gethostname (host, MAX_HOSTNAME);
        hent = gethostbyname (host);
        /* Gethostbyname liefert den Hostnamen incl. Domain. */
        Assert (hent);

        bent_set_host (&bentry, (char *) hent->h_name);

        try {
            brok_register (&bentry);
        }
        catch (FAT_EXCEPT) {
            LOG ("\n[BTAB_KNDE_SVC]: Cant connect to broker !\n"\
                 "\tcheck Hostname or IP-Adress (ping host)\n"\
                 "\tcheck r_brok_svc running on this host\n");
            exit (-1);
        }
        end_try;

        LOG ("\n[BTAB_KNDE_SVC]: running.\n");

        rpcgen_main (); /* Endlos Dispatcher */

    }
    catch(FAT_EXCEPT) {

        /* Hier ist eine EXCEPTION aufgetreten */
        LOG ("\n[BTAB_SVC]: FATAL EXCEPTION");
        LOG ("\n[BTAB_SVC]: shutting down.\n");

        try {
            brok_unregister (bent_get_svcn (&bentry));
        }
        catch (FAT_EXCEPT) {
            LOG ("\n[BTAB_KNDE_SVC]: Cant unregister broker"\
                 "\n\tplease restart broker (possibly crashed).\n");
        }
        end_try;

        ctab_clear ();
    }
    end_try;

    return -1;
}







