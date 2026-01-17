/* ------------------------------------------------------------------------
|   Dateiname:      $RCSfile: rc.h,v $
|   Version:        $Revision: 1 $
|   Erstellt am:    00.00.96
|   Geaendert am:   $Date: 19.11.97 9:36 $
|   Komponente:     RC
|   Erstellt von:   Johannes Weigend
|   Geandert von:   $Author: Johannes $
|   Copyright:      Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
|   Bermerkung:     Tabstop = 4
---------------------------------------------------------------------------*/

#ifndef _RC_H_
#define _RC_H_

typedef long RC;

/* Returncodes */

#define OK                               0
#define OK_IDENTITY                      1
#define NOK                             -1
#define EXCEPTION                       -10
#define INCONSISTENT                    -11
#define OUT_OF_MEMORY                   -12
#define NOK_EMPTY                       -100
#define EOL                             -101
#define NOT_FOUND                       -102
#define NOK_POSITION                    -103
#define OTAB_NOT_FOUND                  -104
#define NOK_PKRN_NOT_NEW                -105
#define NOK_PKRN_IS_CLEAN               -106
#define NOK_PKRN_UPDATE_NOT_ALLOWED     -107
#define NOK_NO_PREV                     -108
#define NOK_NO_NEXT                     -109
#define NOK_NOT_FOUND                   -110
#define KNDE_ALREADY_UPDATED            -111
#define NOK_PROXY_NOT_FOUND             -112
#define BROKER_REMOVED_ENTRY            -113

/* Exceptionhandling */

#define FAT_EXCEPT                       1
#define DB_CHANGED                       2
#define INVALID_ARGUMENT                 3
#endif /* _RC_H_ */

