/* ------------------------------------------------------------------------
|   Dateiname:      $RCSfile:$
|   Version:        $Revision: 1 $
|   Erstellt am:    00.00.96
|   Geaendert am:   $Date: 4/13/97 1:19p $
|   Komponente:     KNDE_RPC_PROXY
|   Erstellt von:   Johannes Weigend
|   Geandert von:   $Author: Hannes $
|   Copyright:      Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
|   Bermerkung:     Tabstop = 4
 --------------------------------------------------------------------------*/


    /* Die Remote Adresse */

const MAX_ANREDE = 10;
/* Compatibility constants for rpcgen: pulled from include headers */
const MAX_STRASSE = 64;
const MAX_HAUSNR  = 12;
const MAX_PLZ     = 5;
const MAX_ORT     = 32;
const MAX_LAND    = 32;
const MAX_CIDLENGTH = 255;
const MAX_KUNDENNAME = 128;

struct radrs {

    string strasse <MAX_STRASSE>;
    string hausnr  <MAX_HAUSNR>;
    string plz     <MAX_PLZ>;
    string ort     <MAX_ORT>;
    string land    <MAX_LAND>;
};


    /* Generische Uebergabestruktur fuer alle Funktionen */

struct rknd  {

    long oid;                           /* Die OID des Proxys */
    string cid      <MAX_CIDLENGTH>;    /* Die ClientID CID   */

        /* Vereinigungsmenge aller Aufrufparameter */
    string name     <MAX_KUNDENNAME>;
    string vorname  <MAX_KUNDENNAME>;
    string anrede   <MAX_ANREDE>;
    long list_of_konten <>;
    radrs adresse;

    long rid;

    short rc;
};




program R_KNDE {
    version R_KNDE_VERSION {

        rknd KNDE_NEW (rknd)            = 1;

        rknd KNDE_INIT (rknd)           = 2;

        rknd KNDE_CLEAR (rknd)          = 3;

        rknd KNDE_DELETE (rknd)         = 4;

        rknd KNDE_SET_NAME (rknd)       = 5;

        rknd KNDE_SET_VORNAME (rknd)    = 6;

        rknd KNDE_SET_ANREDE (rknd)     = 7;

        rknd KNDE_SET_ADRESSE   (rknd)  = 8;

        rknd KNDE_GET_NAME (rknd)       = 9;

        rknd KNDE_GET_VORNAME (rknd)    = 10;

        rknd KNDE_GET_RID (rknd)        = 11;

        rknd KNDE_GET_KONTEN (rknd)     = 12;

        rknd KNDE_GET_ANREDE (rknd)     = 13;

        rknd KNDE_GET_ADRESSE (rknd)    = 14;

        rknd KNDE_FIND_BY_KEY (rknd)    = 15;

        rknd KNDE_REGISTER (rknd)       = 16;

        rknd KNDE_UNREGISTER (rknd)     = 17;

        /* Datenbank Schnittstelle */

        short DBMS_COMMIT (string cid<MAX_CIDLENGTH>)   = 100;

        short DBMS_ROLLBACK (string cid<MAX_CIDLENGTH>) = 101;

        short DBMS_DATA_SERVER_CHANGED (void) = 102;

    } = 1;
} = 0x32132484;


#ifdef RPC_HDR

#include "knde.h"
#include "adrs.h"
#include "enum.h"
#include "cent.h"

#define R_KNDE_PROTO "tcp"

int rpcgen_main ();

   /* Enthaelt nur '\0' */
extern char xdr_required_nullstring;

   /* Fuelle rknd mit \0 */
   /* XDR_STRING() benoetigt gueltige Zeiger (nicht NULL) */
#define rknd_init(r) memset ((r), '\0', sizeof (rknd));                \
         (r)->name                 = &xdr_required_nullstring;         \
         (r)->vorname              = &xdr_required_nullstring;         \
         (r)->cid                  = &xdr_required_nullstring;         \
         (r)->anrede               = &xdr_required_nullstring;         \
         (r)->adresse.strasse      = &xdr_required_nullstring;         \
         (r)->adresse.hausnr       = &xdr_required_nullstring;         \
         (r)->adresse.plz          = &xdr_required_nullstring;         \
         (r)->adresse.ort          = &xdr_required_nullstring;         \
         (r)->adresse.land         = &xdr_required_nullstring;

#endif /* RPC_HDR */

