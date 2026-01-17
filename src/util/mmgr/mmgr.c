/* ------------------------------------------------------------------------
|   Dateiname:      $RCSfile: mmgr.c,v $
|   Version:        $Revision: 1 $
|   Erstellt am:    00.00.96
|   Geaendert am:   $Date: 19.11.97 9:37 $
|   Komponente:     MMGR
|   Erstellt von:   Johannes Weigend
|   Geandert von:   $Author: Johannes $
|   Copyright:      Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
|   Bermerkung:     Tabstop = 4
---------------------------------------------------------------------------*/
/*********************/
/* NOT READY YET ... */
/*********************/

#include "rosa.h"

/* Hier wird malloc nicht ersetzt */

#ifdef MEM_DEBUG
#undef malloc
#undef free
#undef realloc

#define VALID_MEMORYFILLER      0xEF
#define UNVALID_MEMORYFILLER    0xCD

#define MAX_FILE_LENGTH         128

#define MAX_MALLOCS 5000

#define VALID   1
#define UNVALID 0


typedef struct _Memory_Checkpoint {

    char new_file_name [MAX_FILE_LENGTH];   /* delete () */
    long new_line;                          /* Die Zeilennummer */
    char del_file_name [MAX_FILE_LENGTH];   /* new() */
    long del_line;                          /* Die Zeilennummer */
    size_t size;                            /* Groesse des allokierten Speichers */
    void * ptr;                             /* Der Zeiger auf den Speicherbereich */
    int valid;                              /* Valid flag: gueltig, ungueltig */

} mckp;


static mckp mem_array [MAX_MALLOCS] = {0};

static size_t global_mem_cnt = 0;

    /* init () */
static void mckp_init (mckp * mp) {

    Assert (mp);
    memset (mp, '\0', sizeof (mckp));
}

    /* print () */
static void mckp_print (mckp * mp) {

    Assert (mp);
    /* TO DO LOG (...) */
    fprintf (stderr, "new() in file: %s, line: %ld, size: %ld\ndelete() in file: %s, line: %ld\n, valid: %s, ptr: %x\n",
        mp->new_file_name,
        mp->new_line,
        mp->size,
        mp->del_file_name,
        mp->del_line,
        (mp->valid) ? "TRUE" : "FALSE",
        mp->ptr
    );
}


void mckp_append (char * file, long line, size_t size, void * ptr) {

    Assert (file && ptr && (line > 0) && (size > 0));
    Assert (strlen (file) < MAX_FILE_LENGTH);

    mckp_init (&mem_array [global_mem_cnt]);

    strcpy (mem_array [global_mem_cnt].new_file_name, file);

    mem_array [global_mem_cnt].new_line = line;
    mem_array [global_mem_cnt].size     = size;
    mem_array [global_mem_cnt].valid    = VALID;
    mem_array [global_mem_cnt].ptr      = ptr;

    global_mem_cnt ++;
}

static int check_valid (void * p, char * file, long line) {

    size_t i, pos;
    int equal = 0;
    int already_deleted = 0, del_pos = 0;
    unsigned char * c;

    Assert (p);
    Assert (global_mem_cnt > 0);
    Assert (strlen (file) < MAX_FILE_LENGTH);

    c = p;

    for (i = 0; i < global_mem_cnt; i++) {

        if (mem_array [i].ptr == p) {

            if (mem_array [i].valid) {

                /* auf valid muss geprueft werden, da Speicher schon verwendet und
                wieder freigegeben sein kann. */
                equal ++;
                pos = i;
            }
            else {
                already_deleted ++;
                del_pos = i;
            }

            if (equal > 1) {

                LOG ("[MMGR]: Internal Error: duplicate pointers.");
                mckp_print (& mem_array [i]);
                Assert (FALSE);
            }
        }
    }
    if (! equal) {

        if (already_deleted) {

            LOG ("[MMGR]: already deleted pointer.\n");
            LOG ("free() at file: %s, line: %ld\n", file, line);
            mckp_print (&mem_array[del_pos]);
            Assert (FALSE);
        }

        LOG ("[MMGR]: No valid pointer found.");
        mmgr_dump ();
        Assert (FALSE);
    }



    /* Hier wird geprueft ob Speicher freigegeben wurde */
    for (i = 0; i < mem_array[pos].size; i ++) {

        if (*c ++ == UNVALID_MEMORYFILLER) {

            LOG ("[MMGR]: possible freed memory area.");
            mckp_print (&mem_array[i]);
            Assert (FALSE);
        }
    }
    Assert (pos >= 0);
    Assert (mem_array [pos].size > 0);

    return pos;
}


static int check_unvalid (void *p, size_t length) {

    size_t i, pos = 0;
    int equal = 0;
    unsigned char * c;

    Assert (p && (length > 0));
    Assert (global_mem_cnt >= 0);

    c = p;

    for (i = 0; i < global_mem_cnt; i++) {

        if (mem_array [i].ptr == p) {
            equal ++;
            pos = i;
        }
    }
    if (equal)  Assert (0 == "Speicherplatz schon vergeben");

        /* Hier wird geprueft ob Speicher freigegeben wurde */
    for (c; c + mem_array[pos].size; c ++) Assert (*c != UNVALID_MEMORYFILLER);

    Assert (pos >= 0);
    Assert (mem_array [pos].size > 0);
    Assert (mem_array [pos].valid);

    return pos;
}


void * mmgr_malloc (size_t size, char * file, long line) {

    void * p;
    unsigned char * c;
    size_t i;

    Assert ((size > 0) && (line > 0) && file);

    p = malloc (size);
    Assert (p);

    /* check_unvalid (p, size); */

    mckp_append (file, line, size, p);

    c = (unsigned char *) p;

    for (i = 0; i < size; i ++) {
        if (*c ++ == VALID_MEMORYFILLER)
            LOG ("[MMGR]: Warning valid filler found at malloc !\nfile:%s, line: %ld\n",
                    file, line);
    }

    memset (p, VALID_MEMORYFILLER, size);

    return p;
}

void * mmgr_realloc (void * ptr, size_t size, char * file, long line) {

    int i;
    void * p;
    size_t pos;

    Assert (ptr && file);
    Assert (strlen (file) < MAX_FILE_LENGTH);

    pos = check_valid (ptr, file, line);
    Assert (pos >= 0);

    p = realloc (ptr, size);
    Assert (p);

    if (p == ptr) {
        mem_array[pos].size = size;
    }
    else {
        strcpy (mem_array [pos].del_file_name, file);
        mem_array[pos].del_line = line;
        mem_array[pos].valid = UNVALID;
        memset (mem_array[pos].ptr, UNVALID_MEMORYFILLER, mem_array[pos].size);
        mckp_append (file, line, size, p);
    }
    return p;
}

void mmgr_free (void * ptr, char * file, long line) {

    size_t i = 0;

    int equal = 0;
    int pos = 0;

    Assert (ptr && file && (line > 0));
    Assert (strlen (file) < MAX_FILE_LENGTH);

    pos = check_valid (ptr, file, line);
    Assert (pos >= 0);

    memset (ptr, UNVALID_MEMORYFILLER, mem_array[pos].size);

    strcpy (mem_array [pos].del_file_name, file);

    mem_array [pos].del_line = line;

    free (ptr);

    mem_array[pos].valid = UNVALID;
}


int mmgr_check_ptr (void * ptr) {

    return 0;
}


void mmgr_dump () {

    size_t i;

    for (i = 0; i < global_mem_cnt; i++) {

        mckp_print (&mem_array[i]);
    }
}

#endif

