/* ------------------------------------------------------------------------
|   Dateiname:      $RCSfile:$
|   Version:        $Revision: 1 $
|   Erstellt am:    00.00.96
|   Geaendert am:   $Date: 4/13/97 1:19p $
|   Komponente:     KNTO_RPC_PROXY
|   Erstellt von:   Christian Stoellinger
|   Geandert von:   $Author: Hannes $
|   Copyright:      Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
|   Bermerkung:     Tabstop = 4
 --------------------------------------------------------------------------*/

/* Generische Uebergabestruktur fuer alle Funktionen */

struct rknt  {
    long oid;                   /* Die OID des Proxys */
    string cid<MAX_CIDLENGTH>;  /* Die ClientID CID   */

    /* Vereinigungsmenge aller Aufrufparameter */
    long    kunde_oid;
    long    kunde_rid;
    long    konto_id;
    long    konto_nummer;
    long    blz;
    string  bankname<MAX_BANKNAME>;
    long    list_of_knto<>;
    double  betrag;
    long rid;
    short rc;
};

program R_KNTO {
    version R_KNTO_VERSION {
        rknt KNTO_NEW (rknt)            = 1;
        rknt KNTO_INIT (rknt)           = 2;
        rknt KNTO_CLEAR (rknt)          = 3;
        rknt KNTO_DELETE (rknt)         = 4;

		rknt KNTO_SET_KONTO_NUMMER(rknt)= 5;
        rknt KNTO_SET_BLZ (rknt)        = 6;
        rknt KNTO_SET_BANKNAME (rknt)   = 7;
        rknt KNTO_SET_BETRAG (rknt)     = 8;
        rknt KNTO_SET_KUNDE (rknt)      = 9;
        rknt KNTO_SET_UNASSIGNED (rknt) = 10;
		rknt KNTO_GET_KUNDE (rknt)      = 11;
        rknt KNTO_GET_KONTO_NUMMER(rknt)= 12;
        rknt KNTO_GET_BLZ(rknt)         = 13;
        rknt KNTO_GET_BANKNAME (rknt)   = 14;
        rknt KNTO_GET_BETRAG (rknt)     = 15;

        rknt KNTO_EINZAHLEN (rknt)      = 16;
        rknt KNTO_AUSZAHLEN (rknt)      = 17;

        rknt KNTO_FIND_BY_KEY (rknt)    = 18;
        rknt KNTO_FIND_BY_KUNDE(rknt)   = 19;
        rknt KNTO_FIND_UNASSIGNED (rknt)= 20;
        rknt KNTO_GET_RID(rknt)		    = 21;

        rknt KNTO_REGISTER (rknt)       = 22;
        rknt KNTO_UNREGISTER (rknt)     = 23;

            /* Datenbank Schnittstelle */

        short DBMS_COMMIT (string cid<MAX_CIDLENGTH>)   = 100;
        short DBMS_ROLLBACK (string cid<MAX_CIDLENGTH>) = 101;
        short DBMS_DATA_SERVER_CHANGED (void)           = 102;
    } = 1;
} = 0x32132486;

#ifdef RPC_HDR
%
%#include "knto.h"
%#include "cent.h"
%#include "cmgr.h"
%
%#define R_KNTO_PROTO "tcp"
%
%int rpcgen_main ();
%
%   /* Enthaelt nur '\0' */
%extern char xdr_required_nullstring;
%
%   /* Fuelle rknd mit \0 */
%   /* XDR_STRING() benoetigt gueltige Zeiger (nicht NULL) */
%#define rknt_init(r) memset ((r), '\0', sizeof (rknt));    \
         (r)->bankname = &xdr_required_nullstring;         \
         (r)->cid      = &xdr_required_nullstring;
%
#endif /* RPC_HDR */

