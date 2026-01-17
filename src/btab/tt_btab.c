/* ------------------------------------------------------------------------
|   Dateiname:      $RCSfile: tt_btab.c,v $
|   Version:        $Revision: 1 $
|   Erstellt am:    00.00.96
|   Geaendert am:   $Date: 19.11.97 9:36 $
|   Komponente:     BTAB_RPC
|   Erstellt von:   Johannes Weigend
|   Geandert von:   $Author: Johannes $
|   Copyright:      Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
|   Bermerkung:     Tabstop = 4
---------------------------------------------------------------------------*/

#include <stdio.h>
#include "btab.h"
#include "sadm.h"

#ifdef BTAB_PROXY
 #include "r_btab.h"
#endif /* BTAB_PROXY */

char s1[] = "000000000010 Dies ist ein Testdatensatz ";
char s2[] = "000000000000";

#define BASE 100
#define FILE "test.dat"
#define LOOP 10


ENABLE_ERROR_HANDLING;

char xdr_required_nullstring = '\0';


int main (int argc, char * argv[]) {

    btab * b;
    btab bStatic;

    long rid;
    char puffer[70] = {0};
    int i;
    RC rc;

#ifndef LOCAL

    char * brokerhost;

    if (argc == 1) {
        LOG ("Host muss mit angegeben werden.\n\tt_r_btab (brokerhost)\n");
        Assert (FALSE);
    }
    brokerhost = argv[1];

    sadm_init (brokerhost);

    LOG ("\n...done\n");


#else
    sadm_init ("localhost");

#endif /* LOCAL */

        /* TEST Construction and Destruction */
    for (i = 0; i < LOOP; i++) {

        b = btab_new ();
        Assert (b != 0);
        printf ("btab_new()\n");
        btab_open (b, FILE, strlen (s1) + strlen (s2), BASE);
        printf ("btab_open()\n");
        b = btab_delete (b);     /* implizit close ()   */
        printf ("btab_delete()\n");
    }

    #ifndef BTAB_PROXY
        /* PROXYS duerfen nur mit new() erzeugt werden ! */
        /* TEST Automatic Construction  */
    for (i = 0; i < LOOP; i++) {
        btab_init (&bStatic);
        btab_open (&bStatic, FILE, strlen (s1) + strlen (s2), BASE);
        btab_clear (&bStatic);
    }
    printf ("Automatic construction passed.\n");

    #endif


    b = btab_new();
    Assert (b != 0);
    btab_open (b, FILE, strlen (s1) + strlen (s2), BASE);

    if (1) /*(btab_is_empty (b))*/ {
        /* append */
        printf ("\nAppend %d records to file\n", LOOP);
        for (i = 0; i < LOOP; i++) {
            sprintf (s2, "%*d", KEY_LENGTH, i + BASE);
            strcpy (puffer, s1);
            strcat (puffer, s2);
            btab_append (b, puffer, &rid);
        }
        }
        rc = btab_is_empty (b);
        Assert (rc == FALSE);
    printf ("\nGet %d records with rid\n", LOOP);
        /* get_at (rid) */
    for (i = 0; i < LOOP ; i++) {
        btab_get_at (b, i + BASE, puffer);
        printf ("%s\n", puffer);
    }

    printf ("\nPut X in Pos 12 on %d records\n", LOOP);

        /* put_at (rid) */
    for (i = 0; i < LOOP; i++) {
        btab_get_at (b, i + BASE, puffer);
        puffer [12] = 'X';
        btab_put_at (b, puffer);
        btab_get_at (b, i + BASE, puffer);
        printf ("%s\n", puffer);
    }

    printf ("\nItterate (get_next()) on all records\n");
        /* rewind + get_next + get_prev */
    btab_rewind (b);
    printf ("Rewinded !\n");
    while (btab_get_next (b, puffer) == OK)
        printf("%s\n", puffer);

    printf ("\nItterate (get_previous()) on all records\n");
    while (btab_get_previous (b, puffer) == OK)
        printf("%s\n", puffer);


    printf ("\nGet record with key 102\n");
        btab_get_at (b, 102, puffer);
        printf ("%s\n", puffer);

    printf ("\nGet Next ...\t");
        rc = btab_get_next (b, puffer);
        if (rc == OK) printf ("\n%s\n", puffer);
    else printf ("NO Next !!!!!\n");

    printf ("\nGet Previous ...\t");
    rc = btab_get_previous (b, puffer);
    if (rc == OK) printf ("\n%s\n", puffer);
        else printf ("NO Previous !!!!\n");

    btab_close (b);

    b = btab_delete (b); /* sorgt fuer close */
    Assert (b == NULL);

 return 0;
}
