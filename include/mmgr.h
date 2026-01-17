/* ------------------------------------------------------------------------
|   Dateiname:      $RCSfile: mmgr.h,v $
|   Version:        $Revision: 1 $
|   Erstellt am:    00.00.96
|   Geaendert am:   $Date: 19.11.97 9:36 $
|   Komponente:     GLOB
|   Erstellt von:   Johannes Weigend
|   Geandert von:   $Author: Johannes $
|   Copyright:      Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
|   Bermerkung:     Tabstop = 4
--------------------------------------------------------------------------*/

#ifndef _MMGR_H_
#define _MMGR_H_

    /* size_t */
#include <stdlib.h>

#ifdef _DEBUG
#define MEM_DEBUG
#endif

#ifdef MEM_DEBUG
#define malloc(size)                                \
    mmgr_malloc (size, __FILE__, __LINE__)

#define free(ptr)                                   \
    mmgr_free (ptr, __FILE__, __LINE__)

#define realloc(ptr, size)                          \
    mmgr_realloc (ptr, size, __FILE__, __LINE__)

#endif /* MEM_DEBUG */


void * mmgr_malloc (size_t size, char * file, long line);

void * mmgr_realloc (void * ptr, size_t size, char * file, long line);

void mmgr_free (void * ptr, char * file, long line);

void mmgr_dump ();

#endif /* _MMGR_H_ */
