/* ------------------------------------------------------------------------
|   Dateiname:      $RCSfile: r_knde_svc_main.c,v $
|   Version:        $Revision: 1 $
|   Erstellt am:    00.00.96
|   Geaendert am:   $Date: 19.11.97 9:36 $
|   Komponente:     KNDE Server-Initialisierung
|   Erstellt von:   Johannes Weigend
|   Geandert von:   $Author: Johannes $
|   Copyright:      Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
|   Bermerkung:     Tabstop = 4
---------------------------------------------------------------------------*/

#include "r_knde.h"
#include "r_brok.h"
#include "r_btab.h"
#include "btab.h"
#include "ctab.h"
#include "knde.h"
#include "sadm.h"
#include "ctab.h"
#include "dbms.h"

#include <netdb.h>

ENABLE_ERROR_HANDLING;


char xdr_required_nullstring = '\0';


int main (int argc, char * argv[]) {

    bent bentry = { "", KNDE_SVC, "tcp", R_KNDE, R_KNDE_VERSION };

    char * brokerhost;
    struct hostent * hent;
    char host [MAX_HOSTNAME] = {0};

    if (argc != 2) {

        LOG ("[KNDE_SVC]: missing argument !\n");
        LOG ("syntax: r_knde_svc BROKERHOST");
        exit (-1);
    }

    brokerhost = argv[1];

    try {

        sadm_init (brokerhost);
        ctab_init ();

            /* Den Broker informieren ... */
        gethostname (host, MAX_HOSTNAME);
        Assert (host[0]);
        hent = gethostbyname (host);
        Assert (hent);

        bent_set_host (&bentry, (char *) hent->h_name);

        try {

            brok_register (&bentry);
        }
        catch (FAT_EXCEPT) {
            LOG ("\n[KNDE_SVC]: cant connect to broker.\n"\
                             "\tcheck Hostname or IP-Address\n"\
                             "\tcheck r_brok_svc running on this system.\n");
            exit (-1);
        }
        end_try;

        btab_clnt_stub_chge_svcn (KNDE_BTAB_SVC);

        LOG ("\n[KNDE_SVC]: running.\n");

        rpcgen_main ();
    }
    catch (FAT_EXCEPT) {

            dbms_close ();

            brok_unregister (bent_get_svcn(&bentry));

            ctab_clear ();

            try {

                dbms_close ();
            }
            catch (FAT_EXCEPT) {
                LOG ("\n[KNDE_SVC]: cant shut down DB. (Sorry).");
            }
    }
    end_try;

    return -1;
}
