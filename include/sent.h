/* ------------------------------------------------------------------------
|   Dateiname:      $RCSfile: sent.h,v $
|   Version:        $Revision: 1 $
|   Erstellt am:    00.00.96
|   Geaendert am:   $Date: 19.11.97 9:36 $
|   Komponente:     SERVER-ADMINISTAOR
|   Erstellt von:   Johannes Weigend
|   Geandert von:   $Author: Johannes $
|   Copyright:      Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
|   Bermerkung:     Tabstop = 4
---------------------------------------------------------------------------*/

#ifndef _SENT_H_
#define _SENT_H_

#ifdef LOCAL
#include "local.h"
#else
#include <rpc/rpc.h>
#endif

#include "brok.h"



    /* Ein Eintrag des Server-Administrators */
typedef struct _server_admin_entry {

    CLIENT * cl;                            /* Serverhandle */

    char svcn [MAX_SVCNNAME];               /* Servicename  */

} sent;


    /* Allokation und Initialisierung */
sent * sent_new ();
    /* Loeschen */
sent * sent_delete (sent * s);
    /* Init */
void   sent_init (sent * s);


    /* set... und get... Methoden */
void   sent_set_client  (sent * s, CLIENT * cl);

void   sent_set_svcn  (sent * s, char * servicename);

void    sent_set_clientId (sent * s, char * cid);


char   * sent_get_svcn  (sent * s);

CLIENT * sent_get_client  (sent * s);

char    * sent_get_clientId (sent * s);

    /* Kopieren */
void   sent_copy (sent * b, sent * target);

    /* Vergleicht nur dev svcn-Namen da dieser eindeutig ist */
int sent_cmp (const void * a, const void * b);

    /* Drucken */
void sent_print (const void * b);

    /* Zum Einfuegen in die Hashtabelle */
size_t sent_hash_fnk (const void * b);

#endif /* _sent_H_ */

