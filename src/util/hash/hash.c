/* ------------------------------------------------------------------------
   |    Dateiname:  $RCSfile: hash.c,v $
|   Version:        $Revision: 1 $
|   Erstellt am:    00.00.96
|   Geaendert am:   $Date: 19.11.97 9:36 $
|   Komponente:     HASH
|   Erstellt von:   Johannes Weigend
|   Geandert von:   $Author: Johannes $
|   Copyright:      Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
|   Bermerkung:     Tabstop = 4
---------------------------------------------------------------------------*/


#include "rosa.h"
#include "list.h"
#include "hash.h"

/* Allokiert Speicher fuer ein HASH-Objekt und initialisiert es*/
hash * hash_new (size_t hs) {

    hash * hp;

    Assert (hs > 0);

    hp = (hash *) malloc (sizeof (hash));
    Assert (hp != NULL);

    hash_init(hp, hs);
    return hp;
}


/* Zu beachten: Die Hashtabelle wird mit Pointern auf verkettete Listen
 initialisiert. -> Funktion darf nur einmal pro hash-Objekt aufgerufen
 werden, oder der Destuktor (hash_delete() muss vorher aufgerufen werden */
void hash_init(hash * hp, size_t hs) {

    Assert (hp);

    hp->size = hs;  /* Groesse der Hashtabelle */

        /* Allokiere Speicher fuer ein Array[hs] aus list-Pointern */
    hp->plpArray = (list **) malloc (sizeof(list*) * hs);
    Assert (hp->plpArray != NULL);

    memset (hp->plpArray, '\0', sizeof(list*) * hs);

    hp->count = 0;
}


/* Deallokierte Hashtabelle (mit Listen) */
hash * hash_delete(hash * hp) {

    Assert (hp);

    hash_clear (hp, TRUE); /* CHECK */
    free (hp);

    return NULL;
}

    /* Deallokierte Objekte der Hashtabelle */
void hash_clear (hash * hp, BOOL deep) {

    size_t i;
    list * l;
    void * d;

    Assert (hp);

    /* Automatic destruction of inserted objects */
    for (i = 0; i < hp->size; i++) {

        l = hp->plpArray[i];
        if (l) {
            list_rewind (l);
            while ((d = list_getnext (l)) && deep) free (d);
            list_delete (l);
        }
    }
    hp->count = 0;
    free (hp->plpArray);
}


/* Insert in Hashtabelle */
void hash_insert(hash * hp, void * obj, HFNK hfnk) {

    size_t pos;

    Assert (hp && obj && hfnk);

        /* Sicherheitshalber nocheimal modulo size da Hashfunktion moeglicherweise
           inkorrekt arbeiten kann. */
    pos = hfnk (obj) % hp->size;
    if (! hp->plpArray [pos]) hp->plpArray[pos] = list_new ();
    Assert (hp->plpArray [pos]);

    list_append (hp->plpArray [pos], obj);

    hp->count ++;
}


/* Print Hashtabelle Printfunktion fuer Listenelemente */
void hash_print(hash * hp, PRINT_FCT pl) {

    size_t i;

    for (i = 0; i < hp->size; i++) {

        if (hp->plpArray[i]) list_print (hp->plpArray[i], pl);
    }
}


/* Return Element mit Schluessel "key" */
void * hash_get (hash * hp, void * key, HFNK hfnk, COMP_FCT cf) {

    list * l;
    size_t d;
    void * retElem;

    Assert (hp && key && hfnk && cf);

    d = hfnk (key);

    l = hp->plpArray[d % hp->size];
    if (!l) return NULL;

    list_rewind (l);

    while (retElem = list_getnext (l)) {

        if (cf (retElem, key) == 0) {

            return retElem;
        }

    }
    return NULL;
}


    /* Entfernt Element mit Schuessel key aus der Hashtab */
void * hash_remove (hash * hp, void * key, HFNK hfnk, COMP_FCT cf) {

    list * l;
    size_t d;
    int pos = 0;
    void * removedElem;

    Assert (hp && key && hfnk && cf);

    d = hfnk (key);
    l = hp->plpArray[d % hp->size];
    if (!l) return NULL;

    list_rewind (l);

    while (removedElem = list_getnext (l)) {

        if (cf (removedElem, key) == 0) {

            list_remove_at (l, pos);

            hp->count --;

            return removedElem;
        }
        pos ++;
    }
    return NULL;
}


void hash_itterate (hash * hp, HASH_CALLBACK_FNK callbackfnk, void * params) {

    size_t i;
    void * retElem = NULL;

    Assert (hp && callbackfnk);

    for (i = 0; i < hp->size; i++) {

        if (hp->plpArray[i]) {

            list_rewind (hp->plpArray[i]);

            while (retElem = list_getnext (hp->plpArray[i]))

                (*callbackfnk) (retElem, params);
        }
    }
}

size_t hash_count (hash * h) {

  Assert (h);
  return h->count;
}
