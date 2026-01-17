/* ------------------------------------------------------------------------
|   Dateiname:      $RCSfile: tt_brok.c,v $
|   Version:        $Revision: 1 $
|   Erstellt am:    00.00.96
|   Geaendert am:   $Date: 19.11.97 9:36 $
|   Komponente:     BROKER
|   Erstellt von:   Johannes Weigend
|   Geandert von:   $Author: Johannes $
|   Copyright:      Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
|   Bermerkung:     Tabstop = 4
---------------------------------------------------------------------------*/

/* TESTTREIBER  */


#include "brok.h"

#ifdef RPC

    #include "r_brok.h"

    CLIENT * BrokerSvcHandle;

#endif /* RPC */


#define TT_MAX 10

ENABLE_ERROR_HANDLING;

int main (int argc, char * argv[])
{

    char svcn [MAX_SVCNNAME];
    char host [MAX_HOSTNAME];
    RC rc;
    int i;
    bent b;

    #ifdef RPC
    char * brokerhost;


        if (argc == 1) {
            LOG ("Host mu… mit angegeben werden.\n\tt_brok (brokerhost)\n");
            Assert (FALSE);
        }
        brokerhost = argv[1];
    #endif /* RPC */

    #ifndef RPC
    brok_init ();
    #else
    LOG ("Trying to connect to host: %s\n", brokerhost);
    BrokerSvcHandle = clnt_create (brokerhost, R_BROK, R_BROK_VERSION, "udp");
    Assert (BrokerSvcHandle);
    #endif

    for (i = 0; i < TT_MAX; i++ ) {

        sprintf (svcn, "SVC%d", i);
        sprintf (host, "HOST%d", i);

        bent_set_host (&b, host);
        bent_set_svcn (&b, svcn);
        bent_set_prgnr (&b, MIN_RPC_PRG_ID + i);
        bent_set_versnr (&b, 1);
        bent_set_proto (&b, "tcp");

        rc = brok_register (&b);
        Assert (rc == OK);
        LOG (".");
    }
    LOG ("succssesfully registered \n");

    #ifndef RPC
    brok_print ();
    #endif

    for (i = 0; i < TT_MAX; i++ ) {

        sprintf (svcn, "SVC%d", i);

        rc = brok_bind (svcn, &b);

        Assert (strcmp (b.svcn, svcn) == 0);

        Assert (rc == OK);

    }
    LOG ("successfully binded\n");

    for (i = 0; i < TT_MAX; i++ ) {

        sprintf (svcn, "SVC%d", i);

        rc = brok_unregister (svcn);

        rc = brok_bind (svcn, &b);

        Assert (rc == SVC_NOT_REGISTERED);

    }
    LOG ("successfully unregistered\n");

    return 0;
}
