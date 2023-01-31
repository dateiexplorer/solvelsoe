/* 
 * File:   linlist.h
 * Autoren: Andreas Köhler, Justus Röderer, Manuel Truckses
 *
 * Erstellt am 26. Dezember 2019, 18:24
 */
 
#ifndef LIN_LIST_H
#define LIN_LIST_H

#include <stdlib.h>
#include "types.h"


/**
 * Einzelnes Element einer Liste, das den Inhalt dieses Elements enthält, 
 * sowie Referenzen auf das vorhergehende und nachfolgende Element.
 */
typedef struct Element
{
    Vector *vector;
    struct Element *next;
    struct Element *prev;
} Element;


/**
 * Eine Liste, die ein Head- unt Tail-Element hält.
 */
typedef struct List 
{
    struct Element *head;
    struct Element *tail;
} List;


/**
 * Erstellt eine neue leere Liste von Vektoren.
 * @return Gibt die erstellte Liste zurück.
 */
List createList();


/**
 * Löscht eine komplette Liste und gibt den Speicher wieder frei.
 * @param list Die zu löschende Liste.
 */
void deleteList(List list);


/**
 * Fügt ein Element an die Liste hinten an.
 * @param list Die Liste, der das Element angehängt werden soll.
 * @param vector Der Vektor, der hinzugefügt werden soll.
 */
void push(List list, Vector *vector);

#endif // LIN_LIST_H