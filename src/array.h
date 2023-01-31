/* 
 * File:   array.h
 * Autoren: Andreas Köhler, Justus Röderer, Manuel Truckses
 *
 * Erstellt am 23. Dezember 2019, 19:45
 */

#ifndef ARRAY_H
#define ARRAY_H

#include <stdlib.h>


/**
 * Eine Struktur, die als dynamisches Array genutzt werden kann.
 * Beinhaltet die tatsächliche Größe des Arrays und die zur Speicherung
 * reservierte Grösße, die unter Umständen grösser sein kann.
 */
typedef struct {
    double *array;
    size_t used;
    size_t size;
} Array;


/**
 * Initialisiert ein neues dynamisches Array.
 * @param a Pointer auf das zu initalisierende Array.
 * @param initialSize Anfangsgröße des Arrays.
 */
void initArray(Array *a, size_t initialSize);


/**
 * Fügt einem Array ein Element hinzu.
 * @param a Pointer auf das Array, dem ein Element angefügt wird.
 * @param element Doublewert, der angefügt wird.
 */
void insertArray(Array *a, double element);


/**
 * Löscht das Array.
 * @param a Pointer auf das zu löschende Array.
 */
void freeArray(Array *a);

#endif // ARRAY_H