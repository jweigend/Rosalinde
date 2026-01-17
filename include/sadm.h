/* ------------------------------------------------------------------------
|   Dateiname:      $RCSfile: sadm.h,v $
|   Version:        $Revision: 1 $
|   Erstellt am:    00.00.96
|   Geaendert am:   $Date: 19.11.97 9:36 $
|   Komponente:     SERVER-ADMINISTRATOR
|   Erstellt von:   Johannes Weigend
|   Geandert von:   $Author: Johannes $
|   Copyright:      Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
|   Bermerkung:     Tabstop = 4
---------------------------------------------------------------------------*/

#ifndef _SADM_H_
#define _SADM_H_

#include "sent.h"
#include "hash.h"



typedef struct _server_administrator {

    hash cltab;

    char brokerhost [MAX_HOSTNAME];

    CLIENT * brokerhandle;

} sadm;


#define SADM_HASH_TAB_SIZE 97   /* PRIM */


    /* Initialisierung der Hashtabelle ...*/
void sadm_init (char * brokerhost);

    /* Loeschen der Hashtabelle */
void sadm_clear ();

    /* Loescht einen Eintrag im SADM */
void sadm_remove (char * svcn);

    /* for trace only */
void sadm_print ();

   /* Bad Design ... */
char * sadm_get_broker ();

    /* Ping Server OK / NOK */
RC sadm_ping_server (CLIENT * cl);

    /* Gibt einen initalisierten Serverhandle zurueck */
CLIENT * sadm_get_serverhandle  (char * svcn);

    /* Gibt einen gueltigen Handle auf den Broker zurueck */
CLIENT * sadm_get_brokerhandle ();

    /* Utility um Server zu testen */
RC sadm_ping (char * host, long prognr, long versnr, char * proto);

#endif /* _BROKER_H_ */
