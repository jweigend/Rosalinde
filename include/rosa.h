/* ------------------------------------------------------------------------
|   Dateiname:      $RCSfile: rosa.h,v $
|   Version:        $Revision: 1 $
|   Erstellt am:    00.00.96
|   Geaendert am:   $Date: 19.11.97 9:36 $
|   Komponente:     GLOB
|   Erstellt von:   Johannes Weigend
|   Geandert von:   $Author: Johannes $
|   Copyright:      Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
|   Bermerkung:     Tabstop = 4
--------------------------------------------------------------------------*/
#ifndef _AE10_H_
 #define _AE10_H_

#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <string.h>
#include <malloc.h>

#include "mmgr.h"
#include "rc.h"
#include "log.h"
#include "except.h"

    /* Dieser Aufwand ist wegen der RPC - Bibliothek noetig da BOOL auch
       dort deklariert ist */

#ifndef TRUE
    #define TRUE 1
#endif

#ifndef FALSE
    #define FALSE 0
#endif

#ifndef BOOL
    typedef int BOOL;
#endif


#define STDIN  0
#define STDOUT 1
#define STDERR 2

#define READ  0
#define WRITE 1


#define Interval(x,elem,y)  \
    ((x) <= (elem) <= (y)) ? TRUE : FALSE;


#define INTERVAL(lb, x, ub) \
        Assert (((lb) <= (x)) && ((x) <= (ub)))

#endif /* _AE10_H_ */

