/* -------------------------------------------------------------------------
|   Dateiname:      $RCSfile: pkrn.c,v $
|   Version:        $Revision: 1 $
|   Erstellt am:    00.00.96
|   Geaendert am:   $Date: 19.11.97 9:36 $
|   Komponente:     PERSISTENT
|   Erstellt von:   Johannes Weigend, Ludwig Grill, Andreas Huber
|                   Marco Hoffman, Prof. Johannes Siedersleben.
|   Geandert von:   $Author: Johannes $
|   Copyright:      Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
|   Bermerkung:     Tabstop = 4
---------------------------------------------------------------------------*/
#include "rosa.h"
#include "pkrn.h"
#include "otab.h"
#include "misc.h"


void pkrn_init (pkrn * pk) {

    Assert (pk);

    memset (pk, '\0', sizeof (pkrn));
}


void pkrn_clear(pkrn * pk) {

    Assert (pk);
    return;
}


object_state pkrn_state (pkrn * pk) {

    Assert (pk);
    return pk->state;
}


void pkrn_insert (pkrn * pk) {

    Assert (pk && (pk->state == os_new));

        /* Hier wird die rowid vergeben */
    pk->insert_fct(pk->owner, &(pk->rid));

    pk->state = os_clean;
}


void pkrn_update (pkrn * pk) {

    Assert (pk && (pk->state == os_dirty ));

    pk->update_fct(pk->owner, pk->rid);

    pk->state = os_clean;
}


void pkrn_reread (pkrn * pk) {

    Assert (pk && (pk->state == os_dirty));

    pk->reread_fct (pk->owner, pk->rid);

    pk->state = os_clean;
}


void pkrn_register (pkrn * pk, void * owner, OID oid, UPD_FCT upd, INS_FCT ins, REA_FCT rea) {

    Assert (pk && owner && upd && ins);

    pk->update_fct  = upd;
    pk->insert_fct  = ins;
    pk->reread_fct  = rea;
    pk->owner       = owner;
    pk->oid         = oid;
}


void pkrn_unregister (pkrn * pk) {

    Assert (pk);
    pkrn_init (pk);
}


void pkrn_modify ( pkrn * pk ) {

    Assert (pk);

    if ((pk->state == os_new || pk->state == os_dirty)) {

        return;

    }
    pk->state = os_dirty;
}


void pkrn_db_in( pkrn * pk, strg * s ) {


    Assert (pk && s);

    long_db_in(&pk->rid, s);
    long_db_in(&pk->change_cnt, s);
}


void pkrn_db_out( pkrn * pk, strg * s ) {


    Assert (pk && s);

    long_db_out(&pk->rid, s);
    long_db_out(&pk->change_cnt, s);
}


void pkrn_print ( pkrn * pk ) {


    Assert (pk);

    LOG ("PKRN : %x\n", pk);

    LOG (" rid: %ld", pk->rid);

    LOG (" oid: %ld", pk->oid);

    LOG (" state: ");

    switch (pk->state) {

        case os_new:    LOG ("new");        break;
        case os_clean:  LOG ("clean");      break;
        case os_dirty:  LOG ("dirty");      break;

        default :Assert (FALSE); /* Dies darf nie passieren */
    }

    LOG (" change cnt: %ld\n", pk->change_cnt);
}


long pkrn_get_oid (pkrn * pk) {

    Assert (pk);
    return pk->oid;
}

long pkrn_get_rid (pkrn * pk) {

    Assert (pk);
    return pk->rid;
}

