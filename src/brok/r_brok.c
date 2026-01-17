/* ------------------------------------------------------------------------
|   Dateiname:      $RCSfile: r_brok.c,v $
|   Version:        $Revision: 1 $
|   Erstellt am:    00.00.96
|   Geaendert am:   $Date: 19.11.97 9:36 $
|   Komponente:     BROKER  RPC Serverstubs
|   Erstellt von:   Johannes Weigend
|   Geandert von:   $Author: Johannes $
|   Copyright:      Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
|   Bermerkung:     Tabstop = 4
---------------------------------------------------------------------------*/


#include "r_brok.h"
#include "brok.h"

char xdr_required_nullstring = '\0';

int *
brok_register_1_svc(r_bent *argp, struct svc_req *rqstp)
{

    static int  result;
    static bent b;

    Assert (argp != NULL);

    bent_init (&b);

    try {
      bent_set_svcn (&b, argp->svcn);
      bent_set_host (&b, argp->host);
      bent_set_prgnr(&b, argp->prgnr);
      bent_set_versnr(&b, argp->versnr);
      bent_set_proto (&b, argp->proto);
    }
    catch (INVALID_ARGUMENT) {
      LOG ("[BROK]: Invalid Argument for bent_set...\n");
      result = INVALID_ARGUMENT;
    }
    end_try;

    result = brok_register (&b);

    return(&result);
}

int *
brok_unregister_1_svc(char **argp, struct svc_req *rqstp)
{

    static int  result;

    Assert (argp);
    Assert (*argp);

    result = brok_unregister (*argp);

    return(&result);
}

r_bent *
brok_bind_1_svc(char **argp, struct svc_req *rqstp)
{
    RC rc;
    static r_bent  result;
    static bent b;

    Assert (argp);
    Assert (*argp);

    rc = brok_bind (*argp, &b);
    Assert ((rc == OK) || (rc == SVC_NOT_REGISTERED));

    if (rc == OK) {
        result.svcn =  b.svcn;
        result.host =  b.host;
        result.prgnr = b.prgnr;
        result.versnr = b.versnr;
        result.proto = b.proto;

    } else {
        result.svcn = &xdr_required_nullstring;
        result.host = &xdr_required_nullstring;
        result.prgnr = MIN_RPC_PRG_ID + 1;
        result.versnr = 0;
        result.proto =  &xdr_required_nullstring;
    }

    return(&result);
}


r_cid *
brok_get_cid_1_svc(void * argp, struct svc_req *rqstp) {

    static long counter = 0;
    static r_cid result;
    char * host;
    long uid, gid;
    static char buffer [MAX_CIDLENGTH];

    host = (char *)((struct authunix_parms *) (rqstp->rq_clntcred))->aup_machname;
    uid  = (long) ((struct authunix_parms *) (rqstp->rq_clntcred))->aup_uid;
    gid  = (long) ((struct authunix_parms *) (rqstp->rq_clntcred))->aup_gid;

    sprintf (buffer, "[%s:@%ld:@%ld:%ld]", host, uid, gid, ++counter);

    result.cid = buffer;

    return &result;
}

