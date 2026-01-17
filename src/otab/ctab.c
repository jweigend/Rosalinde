/* ------------------------------------------------------------------------
|   Dateiname:      $RCSfile: ctab.c,v $
|   Version:        $Revision: 1 $
|   Erstellt am:    00.00.96
|   Geaendert am:   $Date: 19.11.97 9:36 $
|   Komponente:     ctab
|   Erstellt von:   Johannes Weigend
|   Geandert von:   $Author: Johannes $
|   Copyright:      Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
|   Bermerkung:     Tabstop = 4
---------------------------------------------------------------------------*/

#include "ctab.h"
#include "otab.h"

    /* Die C/S Tabelle */
static ctab _ctab;


    /* Initialisierung der Hashtabelle ...*/
void ctab_init () {

    hash_init (&(_ctab.ctab), CSTB_HASHTABSIZE);
}

    /* Loeschen der Hashtab !! (deep) */
void ctab_clear () {

    hash_clear (&(_ctab.ctab), TRUE);
}


    /* for trace only */
void ctab_print () {

    LOG ("\n\nC/S TAB:\n");
    hash_print (&(_ctab.ctab), cent_print);
    LOG ("\n");
}


void ctab_register (char * cid, OID * oid, pkrn * p, void * obj, UPD_FCT update_fct, INS_FCT insert_fct, REA_FCT reread_fct) {

    cent c;
    cent * pc;

    Assert (cid && obj);

    cent_init (&c);

    cent_set_cid (&c, cid);

    pc = hash_get (&(_ctab.ctab), (void *) &c, cent_hash_fnk, cent_cmp);

    if (! pc) {

        pc = cent_new ();
        Assert (pc);

        cent_set_cid (pc, cid);

        hash_insert (&(_ctab.ctab), pc, cent_hash_fnk);

    }
    cent_clear (&c);

    otab_register (cent_get_otab (pc), oid, p, obj, update_fct, insert_fct, reread_fct);
}


void ctab_unregister (char * cid, OID oid) {

    cent c;
    cent * pc;
    otab * ot;

    Assert (cid && ( oid >= 0));

    cent_init (&c);

    cent_set_cid (&c, cid);

    pc = hash_get (&(_ctab.ctab), (void *) &c, cent_hash_fnk, cent_cmp);
    Assert (pc);

    ot = cent_get_otab (pc);
    Assert (ot);

    otab_unregister (ot, oid);

    if (hash_count (&ot->otab)  == 0) {

        hash_remove (&(_ctab.ctab), pc, cent_hash_fnk, cent_cmp);
        cent_delete (pc);
    }
    cent_clear (&c);
}


    /* Ruft fuer alle Objekte eines Clients die UPDATE Funktion auf */
void  ctab_commit (char * cid) {

    cent c;
    cent * pc;

    Assert (cid);

    cent_init (&c);

    cent_set_cid (&c, cid);

    pc = hash_get (&(_ctab.ctab), (void *) &c, cent_hash_fnk, cent_cmp);
    /*  Darf schiefgenhen wenn vorher kein
        ctab_register aufgerufen wurde */

    cent_clear (&c);

    if (! pc) return;

    otab_commit (&pc->o);
}



    /* Rollback fuer alle Objekte eines Clients */
void  ctab_rollback (char * cid) {

    cent c;
    cent * pc;

    Assert (cid);

    cent_init (&c);

    cent_set_cid (&c, cid);

    pc = hash_get (&(_ctab.ctab), (void *) &c, cent_hash_fnk, cent_cmp);

    cent_clear (&c);

    if (! pc) return;

    otab_rollback (cent_get_otab (pc));

}


cent * ctab_get (char * cid) {

    cent c;
    cent * pc;

    Assert (cid);

        cent_init (&c);

    cent_set_cid (&c, cid);

    pc = hash_get (&(_ctab.ctab), (void *) &c, cent_hash_fnk, cent_cmp);

    cent_clear (&c);

    return pc;
}


void * ctab_get_obj (char * cid, long oid) {

    cent * c;
    oent * o;

    Assert (cid && (oid > 0));

    c = ctab_get (cid);
    if (!c) return NULL;

    otab_get (cent_get_otab (c), oid, &o);
    if (!o) return NULL;

    return oent_get_obj (o);
}
