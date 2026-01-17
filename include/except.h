/* ------------------------------------------------------------------------
|   Dateiname:      $RCSfile: except.h,v $
|   Version:        $Revision: 1 $
|   Erstellt am:    00.00.96
|   Geaendert am:   $Date: 19.11.97 9:36 $
|   Komponente:     EXCEPTION HANDLING
|   Erstellt von:   Johannes Weigend
|   Geandert von:   $Author: Johannes $
|   Copyright:      Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
|   Bermerkung:     Tabstop = 4
---------------------------------------------------------------------------*/

#ifndef _EXCEPT_H
#define _EXCEPT_H

#include <setjmp.h>

#include "log.h"

#define MAX_ENVIRONMENT 1024

extern jmp_buf _err_environment[MAX_ENVIRONMENT];
extern int _env_counter;
extern int _exception_handling_rc;
extern int catched;

#define ENABLE_ERROR_HANDLING                                               \
    jmp_buf _err_environment[MAX_ENVIRONMENT];                              \
    int _env_counter = 0;                                                   \
    int _exception_handling_rc = 0;                                         \
    int catched = 0

#define try\
    if (_env_counter < MAX_ENVIRONMENT) {                                    \
         _exception_handling_rc = setjmp (_err_environment[_env_counter ++]);\
        catched = 0;                                                         \
    }                                                                        \
    else {                                                                   \
        LOG ("Too many handler (ignored)\n");                                \
        _exception_handling_rc = 0;                                          \
    }                                                                        \
    if (! _exception_handling_rc)


#define catch(error_to_catch) \
    if ((_exception_handling_rc == error_to_catch) && (catched = 1))


/* Throw wirft einen beliebigen Fehler aus */

#define throw(throw_error)                                                  \
                                                                            \
    if (_env_counter > 0) {                                                 \
            catched = 0;                                                    \
            longjmp(_err_environment[--_env_counter], throw_error);         \
    }                                                                       \
    else {                                                                  \
                                                                            \
        LOG ("\nNo valid errorhandler\n");                                  \
        exit (-1);                                                          \
    }

#define end_try                                                             \
    if (! catched && _exception_handling_rc)  {                             \
        throw (_exception_handling_rc)                                      \
    }                                                                       \
    else {                                                                  \
        catched = 0;                                                        \
        if (!_exception_handling_rc) _env_counter --;                       \
        _exception_handling_rc = 0;                                         \
    }

/*  Es wird nur ein Assert-Level unterstuetzt, um
    bestehende Schnittstellen nicht zu veraendern.
    d.h. es wird immer FAT_EXCEPT ausgeworfen */

#define Assert(f) \
    if (!(f)) {                                                             \
        LOG ("\nAssertion failed\n\tline: %d\n", __LINE__);                 \
        LOG ("\tfile: %s\n", __FILE__);                                     \
        perror (#f);                                                        \
        throw (FAT_EXCEPT);                                                 \
    }                                                                       \
    else {                                                                  \
    }

#endif
