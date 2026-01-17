/* ------------------------------------------------------------------------
|   Dateiname:      $RCSfile: tt_otab.c,v $
|   Version:        $Revision: 1 $
|   Erstellt am:    00.00.96
|   Geaendert am:   $Date: 19.11.97 9:36 $
|   Komponente:     OTAB
|   Erstellt von:   Johannes Weigend
|   Geandert von:   $Author: Johannes $
|   Copyright:      Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
|   Bermerkung:     Tabstop = 4
---------------------------------------------------------------------------*/


#include "otab.h"

#define TT_MAX 10


ENABLE_ERROR_HANDLING;


int main (int argc, char * argv[])
{

    RC rc;
    int i, e;
    oent o;
    oent * ret;

    otab ot;

    for (e = 0; e < 1; e++) {

        otab_init (&ot);

        for (i = 0; i < TT_MAX; i++) {

            oent_init (&o);

            otab_append (&ot, &o);

            Assert (o.oid == ( i + 1));

        }

        LOG ("successfully appended %d objects\n", TT_MAX);
        otab_print (&ot);
        LOG ("\n");

        for (i = TT_MAX ; i > 0; i--) {

            rc = otab_get (&ot, i, &ret);

            Assert (rc == OK);

            oent_print (ret);
        }

        LOG ("successfully got %d objects by oid\n", TT_MAX);

        rc = otab_get (&ot, TT_MAX + 1, &ret);
        Assert (rc == OTAB_NOT_FOUND);

        LOG ("successfully error by requesting a nonvalid object\n", TT_MAX);

        otab_clear (&ot);

    }
    return 0;
}

