
#include "../../include/except.h"
#include "../../include/rc.h"

#define LOG printf

int f();
int g();
int v();
int h();

#define TEST 100

int f() {
    throw (TEST);
}

int g() {

    try {
        v();
    }
    catch (TEST) {
        LOG ("NOK TEST");
    }
    end_try;

    LOG ("\nNOK: Hier darf Fehler nicht aufgefangen werden.\n");
}

int v() {
    throw (FAT_EXCEPT);
}

int h () {
    try {
        v();
    }
    catch (FAT_EXCEPT) {
        throw (TEST);
    }
    LOG ("\nNOK: Fehler\n");
    end_try;
}

ENABLE_ERROR_HANDLING;


int main () {

    try {
        f ();
    }
    catch (TEST) {
        LOG ("Test 1 : OK\n");
    }
    catch (FAT_EXCEPT) {
        LOG ("NOK: Hier darf nicht reingesprungen werden.\n");
    }
    end_try;

    LOG ("Test 2 : OK\n");

    /* Geschachtelt .. */

    try {
        g();
    }
    catch (FAT_EXCEPT) {
        LOG ("Test 3 : OK\n");
    }
    end_try;


    /* Innerhalb einer Einheit geschachtelt ... */

    try {

        try {

            g ();

        }
        catch (FAT_EXCEPT) {

            LOG ("Test 4 : OK\n");
        }
        catch (TEST) {

            LOG ("Test 4 : NOK\n");
        }
        end_try;
    }
    catch (FAT_EXCEPT) {

        LOG ("Test 5 : NOK\n");
    }
    end_try;


    LOG ("Test 5 : OK\n");

    try {
        h();
    }
    catch (TEST) {

        printf ("Alles OK.\n Hier wird beendet ...\n");

        throw (FAT_EXCEPT);
    }
    end_try;

    LOG ("NOK: Ende");
    return 0;
}
