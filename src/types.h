/* 
 * File:   types.h
 * Autoren: Andreas Köhler, Justus Röderer, Manuel Truckses
 *
 * Erstellt am 23. Dezember 2019, 16:13
 */
 
#ifndef TYPES_H
#define TYPES_H


/**
 * Struktur, die eine quadratische Matirx abbildet. 
 * Beinhaltet die Länge sowie die Daten der Matrix.
 */
typedef struct {
    int n;
    double **data;
} Matrix;


/**
 * Struktur, die einen Vektor abbildet.
 * Beinhaltet die Länge woie die Daten des Vektors.
 */
typedef struct {
    int n;
    double *data;
} Vector;


/**
 * Enumeration, die die verschiedenen unterstützten 
 * Berechnungsverfahren enthält.
 */
typedef enum {
    JACOBI = 0, GAUSS_SEIDEL = 1
} Method;

#endif // TYPES_H