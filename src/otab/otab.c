/* ------------------------------------------------------------------------
|   Dateiname:      $RCSfile: otab.c,v $
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

static long __otab_oid_counter = 0;

static void * _globalFoundObject;


    /* Hilfsfunktion fuer commit */
void otab_make_obj_persistent (void * oentry, void * args );

    /* Hilfsfunktion fuer rollback */
void otab_reread_objects (void * oentry, void * args );

    /* Hilfsfunktion fuer otab_find_by_rid */
void otab_get_with_rid (void * oentry, void * rid );

    /* Hilfsfunktion fuer otab_find_object */
void otab_find_by_object (void * oentry, void * obj);

    /* Suchen ob sich Objektzeiger schon in der Otab befindet*/
RC otab_find_obj (otab * o, oent ** poe, void * obj);


otab * otab_new () {

    otab * o;

    o = (otab *) malloc (sizeof (otab));
    Assert (o);

    otab_init (o);

    return o;
}



otab * otab_delete (otab * o) {

    Assert (o);

    otab_clear (o);

    free (o);

    return NULL;
}


    /* Initialisierung der Liste ...*/
void otab_init (otab * o) {

    hash_init (&o->otab, OTAB_HASHTABSIZE);
}

    /* Loeschen der Liste !! (deep) */
void otab_clear (otab * o) {

    Assert (o);

    hash_clear (&o->otab, TRUE);
}


    /* for trace only */
void otab_print (otab * o) {

    Assert (o);

    LOG ("OTAB: %x\n", o);
    hash_print (&o->otab, oent_print);
    LOG ("\n");
}

    /* Vergibt naeschste OID -> o->oid wird ueberschrieben, und
       fuegt o in die Hashtabelle ein. */
void otab_append (otab * o, oent * oe) {

    oent * po;

    Assert (oe && o);

    po = oent_new ();
    Assert (po);

    oe->oid = ++ __otab_oid_counter;

    oent_copy (oe, po);

    hash_insert (&o->otab, po, oent_hash_fnk);

    return;
}

    /* Uebergibt eine Zeiger auf den Entry mit der passenden oid
        RC = OTAB_NOT_FOUND wenn kein Eintrag gefunden wurde */
RC   otab_get    (otab * o, long oid, oent ** po) {

    oent oe;

    Assert (o);

    oent_init (&oe);
    oent_set_oid (&oe, oid);

    *po = hash_get (&o->otab, (void *) &oe, oent_hash_fnk, oent_cmp);

    oent_clear (&oe);

    if (*po) return OK;
    else return OTAB_NOT_FOUND;
}



RC  otab_remove (otab * o, long oid) {

    oent oe;
    oent * removedEntry;

    Assert (oid);

    oent_init (&oe);
    oent_set_oid (&oe, oid);    /* Die OID ist der Schluessel */

    removedEntry = hash_remove (&o->otab, (void *) &oe, oent_hash_fnk, oent_cmp);

    if (! removedEntry) return OTAB_NOT_FOUND;

        /* Eintrag loeschen */
    oent_delete (removedEntry);
    oent_clear (&oe);

    return OK;
}


    /* Ruft fuer alle Objekte der OTAB otab_make_persistent() auf*/
void  otab_commit (otab * o) {

    Assert (o);

    hash_itterate (&o->otab, otab_make_obj_persistent, NULL);
}


    /* Rollback fuer diese OTAB */
void  otab_rollback (otab * o) {

    Assert (o);

    hash_itterate (&o->otab, otab_reread_objects, NULL);
}



    /* Haengt eine Kopie des OTAB-Entrys in die OTAB ein  */
void otab_register (otab * o, long * oid, pkrn * p, void * obj, UPD_FCT update_fct, INS_FCT insert_fct, REA_FCT read_fct) {

    oent oe;
    oent * poe;

    Assert (o && obj);

    oent_init (&oe);

    oent_set_obj (&oe, obj);

    if (p) {
        oent_set_pkrn (&oe, p);
    }

    if (otab_find_obj (o, &poe, obj) == OTAB_NOT_FOUND) {

            otab_append (o, &oe);          /* Hier wird die OID vergeben */
            *oid = oent_get_oid (&oe);
    }
    else {

        *oid = oent_get_oid (poe);
        oent_set_pkrn (poe, p);
    }

    /* Wenn Objekt nicht persistent ist wars das */

    if (p) {
        Assert (update_fct && insert_fct);
        pkrn_register (p, obj, *oid, update_fct, insert_fct, read_fct);
    }
    /* Aufraeumen ... */
    oent_clear (&oe);
}



    /* Loescht den Eintrag mit der OID oid aus der OTAB */
void otab_unregister (otab * o, long oid) {

    oent * oe;
    pkrn * pk;
	RC rc;

    Assert (o && (oid > 0));

    rc = otab_get (o, oid, &oe);

    pk = oent_get_pkrn (oe);

     /* nur persistente Objekte besitzen einen pkrn */
    if (pk) pkrn_unregister (pk);

    otab_remove (o, oid);
}



void otab_make_obj_persistent (void * oentry, void * parms) {

    oent o;

    Assert (oentry);

    oent_copy ((oent *) oentry, &o);

    if (! o.p) return; /* raus bei nichtpersistenten Objekten */

    if (pkrn_state (o.p) == os_new) {

            pkrn_insert (o.p);
    }

    if (pkrn_state (o.p) == os_dirty) {

            pkrn_update (o.p);
    }

    return;
}


    /* Uebergibt einen Zeiger auf den Entry mit der passenden oid  */
    /* Darf nur fuer persistente Objekte aufgerufen werden !       */
RC otab_find_by_rid (otab * ot, long rid, oent ** o) {

    Assert (o);

    _globalFoundObject = NULL;

    hash_itterate (&ot->otab, otab_get_with_rid, (void *) &rid);

    if (_globalFoundObject != 0) {

        *o = _globalFoundObject;
        return OK;
    }

    return OTAB_NOT_FOUND;
}

RC otab_find_obj (otab * ot, oent ** poe, void * obj) {

    Assert (ot && obj);

    _globalFoundObject = NULL;

    hash_itterate (&ot->otab, otab_find_by_object, obj);

    if (_globalFoundObject != 0) {

        *poe = _globalFoundObject;
        return OK;
    }

    return OTAB_NOT_FOUND;
}

    /* Hilfsfunktion (callback) fuer otab_find_by_rid */
void otab_get_with_rid ( void * oentry, void * rid ) {

    pkrn * pk;

    Assert (oentry && rid);

    if (_globalFoundObject) return;

    pk = oent_get_pkrn ((oent *) oentry);
    if (!pk) return;

    if (pk->rid == *((long *) rid)) {

        _globalFoundObject = oentry;

    }
}


void otab_find_by_object (void * oentry, void * obj) {

    Assert (oentry && obj);

    if (_globalFoundObject) return;

    if (oent_get_obj ((oent*) oentry) == obj) {

        _globalFoundObject = oentry;

    }

}


void otab_reread_objects (void * oentry, void * rowid ) {

    pkrn * pk;

    Assert (oentry);

    pk = oent_get_pkrn ((oent *) oentry);
    if (! pk) return;

    if (pkrn_state (pk) == os_dirty) pkrn_reread (pk);

}





