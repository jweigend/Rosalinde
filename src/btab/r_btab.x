/* ------------------------------------------------------------------------
|   Dateiname:      $RCSfile: r_btab.x,v $
|   Version:        $Revision: 1 $
|   Erstellt am:    00.00.96
|   Geaendert am:   $Date: 4/13/97 1:19p $
|   Komponente:     BTAB_RPC_PROXY
|   Erstellt von:   Johannes Weigend
|   Geandert von:   $Author: Hannes $
|   Copyright:      Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
|   Bermerkung:     Tabstop = 4
 --------------------------------------------------------------------------*/

const MAX_PATH=256;
const MAX_RECORD=8192;


    /* Generische Uebergabestruktur fuer alle Funktionen */
struct rtab {

    long oid; /* Die OID des Proxys */

    string cid<MAX_CIDLENGTH>; /* Die Client ID */

        /* Vereinigungsmenge aller Aufrufparameter */
    string path<MAX_PATH>;
    string record<MAX_RECORD>;

    long base_param;
    long rid;

    short rc;
    int rec_length_param;
};


/* Alle Funktionen die den inneren Zustand der BTAB-Objekte veraendern
   muessen diese auch wieder zum Client zurueckgeben (init, append ...).
   Daher aendert sich das Interface bezueglich btab.h  */

program R_BTAB {
    version R_BTAB_VERSION {

        rtab BTAB_NEW (rtab)        = 1;

        rtab BTAB_INIT (rtab)       = 2;

        rtab BTAB_CLEAR (rtab)      = 3;

        rtab BTAB_DELETE (rtab)     = 4;

        rtab BTAB_OPEN (rtab)       = 5;

        rtab BTAB_CLOSE (rtab)      = 6;

        rtab BTAB_REWIND (rtab)     = 7;

        rtab BTAB_GET_NEXT (rtab)   = 8;

        rtab BTAB_GET_PREVIOUS (rtab)   = 9;

        rtab BTAB_GET_AT (rtab)     = 10;

        rtab BTAB_PUT_AT (rtab)     = 11;

        rtab BTAB_APPEND (rtab)     = 12;

        short BTAB_IS_EMPTY (rtab)  = 13;

        short BTAB_IS_NOT_EMPTY (rtab)  = 14;

    } = 1;
} = 0x32132434;


#ifdef RPC_HDR
% /* Programmnummern fuer Kunden und Konten Btabs ... */
%#define R_BTAB_KNDE 0x33132435
%#define R_BTAB_KNTO 0x33132436
%
%#include "btab.h"
%
%#include "cent.h"
%
%#define R_BTAB_PROTO "tcp"
%
%extern CLIENT * pBtabServerHandle;
%
%
%   /* main wird in rpcgen_main umbenannt */
%int rpcgen_main ();
%
%void btab_clnt_stub_chge_svcn (char * svcn);
%
%   /* Enthaelt nur '\0' */
%extern char xdr_required_nullstring;
%
%   /* Fuelle rtab mit \0 */
%   /* XDR_STRING() benoetigt gueltige Zeiger (nicht NULL) */
%#define rtab_init(r) memset ((r), '\0', sizeof (rtab));    \
          (r)->record = &xdr_required_nullstring;   \
          (r)->path =  &xdr_required_nullstring;    \
          (r)->cid =  &xdr_required_nullstring;
%
#endif /* RPC_HDR */
