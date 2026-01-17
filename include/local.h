/* ------------------------------------------------------------------------
|   Dateiname:      $RCSfile: local.h,v $
|   Version:        $Revision: 1 $
|   Erstellt am:    00.00.96
|   Geaendert am:   $Date: 19.11.97 9:36 $
|   Komponente:     Lokale Dummy Methoden
|   Erstellt von:   Johannes Weigend
|   Geandert von:   $Author: Johannes $
|   Copyright:      Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
|   Bermerkung:     Tabstop = 4
---------------------------------------------------------------------------*/
#ifndef _LOCAL_H_
#define _LOCAL_H_

#include "rosa.h"


#define R_BTAB   0x12345678
#define R_BTAB_VERSION 1


#define RBROK_SVC "R_Brok_Service"
#define R_BROK  0x12345679
#define R_BROK_VERSION 1


typedef struct {

    long cl_auth;

} CLIENT;

CLIENT * clnt_create (char *, long, long, char *);

long authunix_create_default ();

#endif /* _LOCAL_H_ */
