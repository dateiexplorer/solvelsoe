/* 
 * File:   array.h
 * Autoren: Andreas Köhler, Justus Röderer, Manuel Truckses
 *
 * Erstellt am 23. Dezember 2019, 19:46
 */

#include "array.h"


void initArray(Array *a, size_t initialSize) {
    a->array = (double *) malloc(initialSize * sizeof (double));
    a->used = 0;
    a->size = initialSize;
}


void insertArray(Array *a, double element) {
    if (a->used == a->size) { // Wenn das Array zu klein wird, dann vergrößern.
        a->size *= 2;
        a->array = (double *) realloc(a->array, a->size * sizeof (double));
    }
    
    a->array[a->used++] = element;
}


void freeArray(Array *a) {
    free(a->array);
    a->array = NULL;
    a->used = a->size = 0;
}