
#include <assert.h>

#define MEM_DEBUG 1

#include "mmgr.h"

int main () {

    long * p;
    long * q;
    int i;

    for (i = 0; i < 2; i++) {

        q = p = (long *) malloc (sizeof (long));
        assert (p);

        free (p);
    }

    /* Testfall 1: doppeltes free ()
    free (p);                       */

    /* Testfall 2: free () eines ungueltigen Zeigers */

    mmgr_dump ();

    free (q);

    return 0;
}