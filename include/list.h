/* ------------------------------------------------------------------------
|   Dateiname:      $RCSfile: list.h,v $
|   Version:        $Revision: 1 $
|   Erstellt am:    10.09.94
|   Geaendert am:   $Date: 19.11.97 9:36 $
|   Komponente:     GLOB
|   Erstellt von:   J. Siedersleben
|   Geandert von:   $Author: Johannes $
|   Copyright:      Fachhochschule Rosenheim, Anwendungsentwicklung, 1996
|   Bermerkung:     Tabstop = 4
--------------------------------------------------------------------------*/

#ifndef LIST_H
#define LIST_H


#include "rosa.h"


   typedef struct {
    int cursor; /* cursor = last bedeutet eol    */
    int last;   /* erste nicht belegte Position  */
                    /* last = 0 bei leerer Liste     */
    int lsize;      /* allokierter Platz             */
    void ** tab;    /* Array von Zeigern auf void    */
   } list;


   typedef int (*COMP_FCT) (const void *, const void *);
    /* benoetigt zum Sortieren einer Liste   */

   typedef void (*LIST_FCT) (const void *);
    /* benoetigt zum iterieren einer Liste, z.B. beim Drucken  */

   typedef char * (*KEY_FCT) (const void *);
    /* liefert den Schluessel eines Listenelements  */


   void list_init (list * l);

   void list_clear (list * l);

   list * list_new ();

   void list_delete (list * l);
        /* deallokiert eine Liste; die von tab
           referenzierten Elemente bleiben erhalten */

   void list_check (list * l);
        /* ueberprueft die Konsistenz der Liste */

   void list_cat (list * l, list * k);
        /* haengt Liste k an Liste l an;
           Liste k unveraendert */

   void list_copy (list * l, list * k);
        /* kopiert k auf l; verlaengert l bei Bedarf */

   void list_append (list * l, void * x);
    /* haengt x hinten an l an, verlaengert l bei Bedarf    */

   void * list_remove (list * l);
    /* entfernt das letzte Element der Liste und gibt es zurueck;
       bei leerer Liste wird NULL zurueckgegeben     */

   void list_rewind (list * l);
        /* setzt den Cursor auf 0   */

   void * list_getnext (list * l);
    /* liefert Element und verschiebt den Cursor;
       liefert NULL, wenn Liste leer oder EOL */

   void list_put_at (list * l, int position, void * x);
                /* setzt x an die Position position */
                /* 0 <= position < last        */

   void * list_get_at (list * l, int position);
        /* liefert das Element an Position position */
        /* Liste bleibt unveraendert      */

   void * list_remove_at (list * l, int position);
        /* holt das Element an Position position */
        /* und entfernt es aus der Liste         */


   void * list_find (list * l, char * match,
                     int * position, KEY_FCT key);
                /* sucht in der Liste  den Key "match" */
                /* in position wird die Position des gefundenen */
                /* Elements zurueckgegeben */
                /* gibt NULL zurueck, wenn nichts gefunden */

   int list_nbr_of_el (list * l);

   BOOL list_eol (list * l);

   BOOL list_empty (list * l);

   BOOL list_not_empty (list * l);

   void list_sort(list *l, COMP_FCT comp);

   void list_print(list *l, LIST_FCT p);



#define GEN_LIST(T)                 \
                                                        \
   T * T##_list_getnext (list * l);         \
                                                        \
   void T##_list_append (list * l, T * k);          \
                                                        \
   T * T##_list_remove (list * l);          \
                                                        \
   void T##_list_put_at (list * l, int position, T * k);     \
                                                        \
   T * T##_list_get_at (list * l, int position);      \
                                                        \
   T * T##_list_remove_at (list * l, int position);   \
                                                        \
   void T##_list_sort (list * l);                     \
                                                        \
   void T##_list_print (list * l);                    \
                            \
   T * T##_list_find (list * l, char * match,          \
               int * position);



#define GEN_LIST_IMP(T)                     \
                                                                \
                                                                \
   T *  T ## _list_getnext (list *l) {                  \
    return (T *) list_getnext (l);                          \
   }                                                        \
                                                                \
   void T ## _list_append (list *l, T * k) {            \
    list_append(l, k);                                  \
   }                                                        \
                                                                \
   T * T ## _list_remove (list * l) {                   \
    return (T *) list_remove (l);                           \
   }                                                        \
                                                                \
   void T ## _list_put_at (list *l, int position, T *k) {       \
    list_put_at (l, position, k);                       \
   }                                                        \
                                                                \
   T * T ## _list_get_at (list *l, int position) {              \
    return (T *) list_get_at (l, position);                 \
   }                                                        \
                                                                \
   T *  T ## _list_remove_at (list * l, int position) {     \
    return (T *) list_remove_at (l, position);              \
   }                                                        \
                                                                \
                                                                \
   void T ## _list_sort (list * l) {                            \
        list_sort (l, (COMP_FCT) T ## _cmp);                    \
   }                                                            \
                                    \
   T * T ## _list_find (list * l, char * match,                 \
                          int * position) {                     \
        return (T *) list_find (l, match, position,             \
                                (KEY_FCT) T ## _key );          \
   }                                                            \
                                                                \
   void T ## _list_print (list * l) {                           \
        list_print(l, (LIST_FCT) T ## _print);                  \
   }

#endif
