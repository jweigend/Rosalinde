/* ------------------------------------------------------------------------
|   Dateiname:      $RCSfile: list.c,v $
|   Version:        $Revision: 1 $
|   Erstellt am:    10.09.94
|   Geaendert am:   $Date: 19.11.97 9:37 $
|   Komponente:     GLOB
|   Erstellt von:   J. Siedersleben
|   Geandert von:   $Author: Johannes $
|   Copyright:      Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
|   Bermerkung:     Tabstop = 4
--------------------------------------------------------------------------*/

#include "list.h"

const int default_size = 16;
             /* Standardgroesse einer Liste; immer >= 1 */


void list_init (list * l) {
    int i;

    l->tab = malloc (default_size * sizeof(void*));
    Assert (l->tab);

        l->lsize  = default_size;
        l->cursor = 0;
        l->last   = 0;
        for (i = 0; i < l->lsize; i++) l->tab[i] = NULL;
}   /* end list_init */



void list_resize (list * l) {
    int i;
    Assert (l->last <= l->lsize);

    if (l->last == l->lsize) l->lsize += default_size;
    else if (l->last < l->lsize - default_size)
                     l->lsize -= default_size;
    else return;        /* nichts zu tun */

    l->tab = realloc (l->tab, l->lsize * sizeof(void*));
    Assert ( l->tab);
    for (i = l->last; i < l->lsize; i++) l->tab[i] = NULL;
}       /* end list_resize */



void list_clear (list * l) {

    free(l->tab);
    l->tab = NULL;
    l->cursor = 0;
    l->last   = 0;
    l->lsize  = 0;
}   /* end list_clear */


list * list_new() {
    list *l;

    l = (list *) malloc (sizeof(list));
    Assert (l);
        list_init (l);
        return l;
}   /* end list_new */


void list_delete (list * l) {
    list_clear (l);
    free (l);
}   /* end list_delete  */


void list_check (list * l) {
    int i;

    Assert (0 <= l->cursor);
    Assert (l->cursor <= l->last);
    Assert (l->last <= l->lsize);

    for (i = 0; i < l->last; i++)
        Assert (l->tab[i] != NULL);
    for (i = l->last; i < l->lsize; i++)
        Assert (l->tab[i] == NULL);
}   /* end check */


void list_cat (list * l, list * k) {
    void * x;

    if (list_empty (k)) return;    /* nichts zu tun */

        list_rewind (k);
    while ((x = list_getnext (k))) list_append (l, x);
}   /* end list_cat */


void list_copy (list * l, list * k) {
    if (l == k) return;

    list_clear (l);
    list_init (l);
    list_cat (l, k);
}   /* end list_copy */



void list_rewind (list * l) {
        l->cursor = 0;
}


void list_append (list * l, void * x) {
    list_resize (l);
    l->tab[l->last++] = x;

    list_check (l);
}   /* end list_append */


void * list_remove (list * l) {
        void * x;

    if (list_empty (l)) return NULL;

        x = l->tab[l->last - 1];    /* letztes Element ausgeben */
        l->tab[--(l->last)] = NULL; /* und loeschen */
        if (l->cursor > l->last) l->cursor--;
                        /* Cursor mitziehen */
        list_resize (l);        /* ggfs. verkleinern */
        return x;
}   /* end list_remove */


void * list_getnext (list * l) {
    if (list_eol (l)) return NULL;

    return (l->tab[l->cursor++]);
}   /* end list_getnext  */


void * list_get_at (list * l, int position) {
    Interval (0, position, l->last - 1);

    return (l->tab[position]);
}   /* end list_get_at */


void list_put_at (list * l, int position, void * x) {
    Interval (0, position, l->last - 1);

    l->tab[position] = x;
}   /* end list_put_at */


void * list_remove_at (list * l, int position) {
    void * x;
    int i;
    Interval (0, position, l->last - 1);
        /* Element an position ans Ende */
    x = l->tab[position];
    for (i = position; i < l->last; i++)
        l->tab[i] = l->tab[i+1];
    l->tab[l->last - 1] = x;

    return list_remove(l);
}   /* end list_remove_at */


void * list_find (list * l, char * match,
              int * position, KEY_FCT key) {
    void * x;
    Assert (strlen (match) > 0);
        /* sonst macht strcmp() keinen Sinn */

    list_rewind (l);
    while ((x = list_getnext (l)))
        if (!strcmp (key (x), match)) {
            *position = l->cursor - 1;
            return (l->tab[*position]);
        }
    Assert (list_eol (l));
    return NULL;

}   /* end list_find */


BOOL list_eol (list * l) {
    return (l->cursor == l->last);
}


int list_nbr_of_el (list * l) {
    return l->last;
}


BOOL list_empty (list * l) {
    list_check (l);
    return (l->last == 0);
}


BOOL list_not_empty (list * l) {
    return (l->last > 0);
}


void list_sort (list * l, COMP_FCT comp) {
    if (list_empty (l)) return;
    qsort(l->tab, l->last - 1, sizeof(void *), comp);
}


void list_print (list * l, LIST_FCT p) {
    void * x;
    list_rewind (l);
    while ((x = list_getnext (l))) p(x);
}
