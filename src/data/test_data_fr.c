/* ------------------------------------------------------------------------
|   Dateiname:      $RCSfile: test_data.c,v $
|   Version:        $Revision: 1 $
|   Erstellt am:    00.00.96
|   Geaendert am:   $Date: 19.11.97 9:36 $
|   Komponente:     GLOB
|   Erstellt von:   Johannes Weigend
|   Geandert von:   $Author: Johannes $
|   Copyright:      Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
|   Bermerkung:     Tabstop = 4
--------------------------------------------------------------------------*/


#include "knde.h"
#include "knto.h"
#include "otab.h"
#include "btab.h"
#include "sadm.h"
#include "ctab.h"
#include "cmgr.h"
#include "dbms.h"

ENABLE_ERROR_HANDLING;

char xdr_required_nullstring = '\0';


void make_kunden()
{
    knde* k;
    strg* name,* vorname;
    adrs* adresse;
    anrd* anrede;
    RC    rc;
    int   loops;
    long  oid;

    char  k_name[40];
    char  k_vorname[40];
    char  k_strasse[40];
    char  k_ort[40];
    char  k_hnr[20];
    char  k_plz[10];
    
    name = strg_new (0);
    Assert (name);
    vorname = strg_new (0);
    Assert (vorname);
    anrede = anrd_new ();
    Assert (anrede);
    adresse = adrs_new ();
    Assert (adresse);


    for (loops = (KNDE_DB_RID_BASE+0); loops < (KNDE_DB_RID_BASE+1000); loops ++) 
    {
        k = knde_new ();
        Assert (k);

        knde_register (k, &oid);

        anrd_in (anrede, &rc, LANG, "Herr");
        Assert (rc == OK);
        
        sprintf(k_name,    "Legrand%i", loops);
        sprintf(k_vorname, "Jean");
        sprintf(k_strasse, "avenue de la gare");
        sprintf(k_plz,     "22305");
        sprintf(k_hnr,     "%i", loops);
        sprintf(k_ort,     "Lannion");
        
        LOG(k_name);      
        strg_in (name,      k_name);
        strg_in (vorname,   k_vorname);
        adrs_in (adresse,   k_strasse, k_hnr, k_plz, k_ort, "F France");

        knde_set_anrede  (k, anrede);
        knde_set_name    (k, name);
        knde_set_vorname (k, vorname);
        knde_set_adresse (k, adresse);

        dbms_commit ();
        
        knde_unregister(k);
        knde_delete(k);
    }
    
    strg_delete(name);
    strg_delete(vorname);
    anrd_delete(anrede);
    adrs_delete(adresse);
}


void make_konten()
{
    int    loops;
    RC     rc;
    knto*  k;
    knde*  kunde;
    
    strg*  bankname;
    long   oid;
    
    char   k_bankname[40];
    long   k_blz;
    
    bankname = strg_new(0);
    Assert(bankname);
    
    for (loops=0; loops<2000; loops++)
    {
        k = knto_new();
        Assert(k);
        
        knto_register(k, &oid);
        
        sprintf(k_bankname, "Credit de Lyon%i", (loops+KNTO_DB_RID_BASE) );
        k_blz = (loops + KNTO_DB_RID_BASE) + 700000;
        
        strg_in(bankname, k_bankname);
        
        knto_set_bankname(k, bankname);
        knto_set_blz(k, k_blz);
        
        if ( loops<1000)
        {
            kunde = knde_find_by_key(loops+KNDE_DB_RID_BASE, &rc);
            Assert(kunde);
        }
        else
        {
            kunde = knde_find_by_key(loops-1000+KNDE_DB_RID_BASE, &rc);
            Assert(kunde);
        }
        
        knto_set_kunde(k, kunde);
        
        dbms_commit();        
        
        knde_unregister(kunde);
        knde_delete(kunde);
        
        knto_unregister(k);
        knto_delete(k);
    }
    
    strg_delete(bankname);
}


int main (int argc, char * argv[]) 
{
    char* brokerhost;
    
    if (argc != 2) 
    {
        LOG ("Host muss mit angegeben werden.\ntest_data (brokerhost)\n");
        Assert (FALSE);
    }
    brokerhost = argv[1];

    sadm_init (brokerhost);
    ctab_init ();
    
    make_kunden();
    make_konten();
}

