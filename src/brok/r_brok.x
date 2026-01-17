/* ------------------------------------------------------------------------
|   Dateiname:      $RCSfile: r_brok.x,v $
|   Version:        $Revision: 1 $
|   Erstellt am:    00.00.96
|   Geaendert am:   $Date: 4/13/97 1:19p $
|   Komponente:     BROKER
|   Erstellt von:   Johannes Weigend
|   Geandert von:   $Author: Hannes $
|   Copyright:      Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
|   Bermerkung:     Tabstop = 4
---------------------------------------------------------------------------*/

const MAX_PROTO = 4;

    /* Der Broker-entry  */
struct r_bent {
    string host<MAX_HOSTNAME>;
    string svcn<MAX_SVCNNAME>;
    string proto<MAX_PROTO>;
    long prgnr;
    long versnr;
};

    /* Die CID */
struct r_cid {
    string cid<MAX_CIDLENGTH>;
};

program R_BROK {

    version R_BROK_VERSION {

        int BROK_REGISTER (r_bent) = 1;

        int BROK_UNREGISTER (string svcn<MAX_SVCNNAME>) = 2;

        r_bent BROK_BIND (string svcn<MAX_SVCNNAME>) = 3;

        r_cid BROK_GET_CID (void) = 4;

    } = 1;
} = 0x32132435;


#ifdef RPC_HDR
%
%#include "brok.h"
%
%#define R_BROK_PROTO "tcp"
%
% /* fuer CID */
%#include "cent.h"
%
%int rpcgen_main();
%
%   /* Enthaelt nur '\0' */
%extern char xdr_required_nullstring;
%
#endif /* RPC_HDR */
