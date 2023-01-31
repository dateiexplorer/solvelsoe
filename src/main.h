/* 
 * File:   main.h
 * Autoren: Andreas Köhler, Justus Röderer, Manuel Truckses
 *
 * Erstellt am 18. März 2020, 17:13
 */

#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "types.h"
#include "array.h"
#include "utils.h"
#include "linlist.h"


/**
 * Implementierung der Teilaufgabe c).
 * 
 * Programmstart.
 */
int main(int argc, char* argv[]);


/**
 * Implementierung der Teilaufgabe a).
 *
 * Lädt eine Datei in die übergebene Matrix und die übergebenen Vektoren.
 * @param filename Die zu ladende Datei.
 * @param A Die A-Matrix.
 * @param b Der B-Vektor.
 * @param x Der X-Vektor.
 * @return Gibt true zurück, wenn die Datei erfolgreich geladen wurde.
 */
bool load(const char *filename, Matrix *A, Vector *b, Vector *x);


/**
 * Implementierung der Teilaufgabe b).
 * 
 * Löst ein Gleichungssystem nach dem ausgewählten Verfahren.
 * @param method Auswahl des Iterationsverfahrens.
 * @param A Pointer auf eine Matrix-Struktur.
 * @param b Pointer auf eine Vektor-Struktur.
 * @param x Pointer auf eine Vektor-Struktur, die die Startwerte healt.
 * @param e Fehlerschranke, die die Genauigkeit der Werte bestimmt.
 * @return Gibt die erkettete Liste zurück, in der alle Iterationsvektoren gespeichert sind.
 */
List solve(Method method, Matrix* A, Vector* b, Vector* x, double e);


/**
 * Funktion zum Lösen eines Gleichungssystems.
 * Fragt den Benutzer nach Werten ab, die zur Berechnung benötigt werden.
 * @param A Die A-Matrix.
 * @param b Der B-Vektor.
 * @param x Der X-Vektor.
 * @return Gibt true zurück, wenn das Gleichungssystem erfolgreich gelöst werden konnte.
 */
bool tryToSolve(Matrix *A, Vector *b, Vector *x);


/**
 * Erstellt aus den übergebenen Parametern einen Vektor und hängt
 * ihn der Liste an.
 * @param list Liste, der der Vektor angehängt werden soll.
 * @param data Array an Daten für den Vektor.
 * @param size Größe des Arrays an Daten.
 */
void addVectorToList(List list, double data[], int size);


/**
 * Wird für Benutzerabfragen benötigt.
 * @return Gibt true zurück, wenn die Benutzerabfrage mit Nein beantwortet wird.
 */
bool ask();


/**
 * Fragt den Benutzer, ob eine neue Datei eingelesen werden soll.
 * @return Gibt true zurück, wenn eine neue Datei eingelesen werden soll.
 */
bool restart();



#endif // MAIN_H