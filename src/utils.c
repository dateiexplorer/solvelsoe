/* 
 * File:   utils.c
 * Autoren: Andreas Köhler, Justus Röderer, Manuel Truckses
 *
 * Erstellt am 03. Januar 2019, 16:15
 */

#include "utils.h"

#define BUFFER_SIZE 256


void printVector(int listNo, Vector *vector) {
    if (vector->data != NULL) {
        printf("\n   %3d)   %.10lf", listNo, vector->data[0]);
        for (int i = 1; i < vector->n; i++) {
            printf(", %.10lf", vector->data[i]);
        }
    }
}


void printMatrix(Matrix *matrix) {
    if (matrix->data != NULL) {
        for (int i = 0; i < matrix->n; i++) {
            printf("\n   %.10lf", matrix->data[i][0]);
            for (int j = 1; j < matrix->n; j++) {
                printf(", %.10lf", matrix->data[i][j]);
            }
        }
    }
}


int getRowNum(FILE *file) {
    int rowNum = 0;
    fseek(file, 0, SEEK_SET);

    while (!feof(file)) {
        if (ferror(file)) {
            printf("=> Fehler beim Lesen der Datei!\n");
            return -1;
        }

        char temp = fgetc(file);
        if (temp == '\n') { // Zeilenumbruch gibt an, dass Zeile zünde ist.
            rowNum++; 
        }
    }

    fseek(file, 0, SEEK_SET);
    return rowNum;
}


void copyFileWithoutBlankLines(FILE *source, FILE *dest) {
    char buffer[BUFFER_SIZE];

    fseek(source, 0, SEEK_SET);
    while ((fgets(buffer, BUFFER_SIZE, source)) != NULL) {
        if (!isBlank(buffer)) {
            fputs(buffer, dest);
        }
    }

    fseek(source, 0, SEEK_SET);
}


bool isBlank(const char *str) {
    char temp;

    do {
        temp = *(str++);
        if (!isspace(temp)) {
            return false;
        }
    } while (temp != '\n');

    return true;
}  


bool isValid(const char *str) {
    int count = 0;
    char ch = *(str++);

    while (ch != '\0') {
        if (isdigit(ch)) { // Nummern
            count++;
        } else if (ch == '-') { // Minuszeichen
            if (count > 0) {
                return false;
            }
        } else if (ch == '.') { // Fliesskommazahlen
            if (count == 0) return false;
            count = 0;
        } else {
            return false;
        }

        ch = *(str++);
    }

    return true;
}


void copyArray(double *source, double *target, size_t size) {
    for (size_t i = 0; i < size; i++) {
        target[i] = source[i];
    }
}


double max(double a, double b) {
    return a > b ? a : b;
}
