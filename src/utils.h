/* 
 * File:   utils.h
 * Autoren: Andreas Köhler, Justus Röderer, Manuel Truckses
 *
 * Erstellt am 03. Januar 2019, 16:13
 */

#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>

#include "types.h"


/** 
 * Druckt den Inhalt eines Vektors auf die Konsole aus.
 * @param listNo Kennzahl in einer Liste.
 * @param vector Der auszugebende Vektor.
 */
void printVector(int listNo, Vector *vector);


/** 
 * Druckt den Inhalt einer Matrix auf die Konsole.
 * Gibt eine Matrix auf der Konsole aus.
 * @param matrix Die auszugebende Matrix.
 */
void printMatrix(Matrix *matrix);


/** 
 * Gibt die Anzahl der Zeilen einer Datei zurück.
 * @param file Die Datei, deren Zeilenanzahl ermittelt werden soll.
 * @return Gibt die Anzahl der Zeilenumbrüche zurück.
 */
int getRowNum(FILE *file);


/**
 * Kopiert eine Datei ohne leere Zeichen dazwischen zu berücksichtigen.
 * @param source Die zu kopierende Qülldatei.
 * @param dest Die Zieldatei.
 */
void copyFileWithoutBlankLines(FILE *source, FILE *dest);


/**
 * Überprüft einen String darauf, ob darin nur Whitespace enthalten ist.
 * @param str Der zu überprüfende String.
 * @return Gibt true zurück, wenn der String nur Whitespace enthält.
 */
bool isBlank(const char *str);

/**
 * Überprüft einen String, ob dieser nur zulässige Werte enthält.
 * Dies sind Ziffern jeglicher Art.
 * @param str Der zu überprüfende String.
 * @return Gibt true zurück, wenn der String ein gültiges Format enthält.
 */
bool isValid(const char *str);


/**
 * Kopiert die ersten (bis size) Elemente von einem Array in ein anderes.
 * @param source Pointer auf ein Doublearray, das kopiert werden soll.
 * @param target Pointer auf das Zielarray.
 * @param size Anzahl der zu kopierenden Elemente.
 */
void copyArray(double *source, double *target, size_t size);


/**
 * Berechnet das Maximum zweier Werte.
 * @param a Der erste zu vergleichende Wert.
 * @param b Der zweite zu vergleichende Wert.
 * @return Gibt das Maximum zurück.
 */
double max(double a, double b);

#endif // UTILS_H