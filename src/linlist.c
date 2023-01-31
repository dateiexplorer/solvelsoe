/* 
 * File:   linlist.c
 * Autoren: Andreas Köhler, Justus Röderer, Manuel Truckses
 *
 * Erstellt am 26. Dezember 2019, 18:27
 */

#include "linlist.h"

List createList() {
    List list;
    list.head = malloc(sizeof (Element));
    list.tail = malloc(sizeof (Element));

    // Am Anfang zeigt das Head-Element auf das Tail-Element und umgekehrt.
    list.head->next = list.tail->next = list.tail;
    list.head->prev = list.tail->prev = list.head;

    return list;
}


void deleteList(List list) {
    Element *p = list.head->next; 
    while (p != list.tail) { // Liste komplett bis Tail-Element durchlaufen.
        Element *e = p;
        p = p->next;
        free(e->vector->data);
        free(e->vector);
        free(e); // Aktuell ausgewähltes Element löschen.
    }

    free(list.head); // Head löschen.
    free(list.tail); // Tail löschen.
}


void push(List list, Vector *vector) {
    // neues Element erzeugen.
    Element *elem = malloc(sizeof (Element));
    elem->vector = vector;

    elem->next = list.tail;
    elem->prev = list.tail->prev;
    
    // Referenzen aktualisieren.
    list.tail->prev = list.tail->prev->next = elem;
}