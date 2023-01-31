/* 
 * File:   main.c
 * Autoren: Andreas Köhler, Justus Röderer, Manuel Truckses
 *
 * Erstellt am 23. Dezember 2019, 13:13
 */

#include "main.h"

#define INPUT_BUFFER_LENGTH 4096
#define MAX_ROW_LENGTH 16000
#define MAX_STEPS 100


bool load(const char *filename, Matrix *A, Vector *b, Vector *x) {
    bool success = true;

    FILE *source = fopen(filename, "rb");
    if (!source) {
        printf("=> Fehler beim \u00D6ffnen der Datei!\n");
        printf("   Bitte \u00FCberpr\u00FBfen Sie ihre Eingabe und Leserechte!\n");
        return false;
    }

    FILE *file = tmpfile();
    if (!file) {
        printf("=> Fehler beim Erstellen der tempor\u00E4ren Datei!\n");
        printf("   Bitte \u00FCberpr\u00FBfen Sie ihre Schreibreichte!\n");
        fclose(source);
        return false;
    }

    // Quelldatei in temporäre Datei ohne Leerzeilen kopieren,
    // sodass die spätere Ermittlung von Werten korrekt ist.
    copyFileWithoutBlankLines(source, file);
    fclose(source);

    int rowNum = getRowNum(file);
    if (rowNum < 0) { // Fehlerüberprüfung.
        success = false;
    }

    // Array initialisieren.
    Array **rows = malloc(sizeof (Array) * rowNum);
    for (int i = 0; i < rowNum; i++) {
        rows[i] = malloc(sizeof (Array));
        initArray(rows[i], 32);
    }

    // Datei einlesen.
    char *currentRow = malloc(MAX_ROW_LENGTH * sizeof (char));
    for (int i = 0; i < rowNum; i++) { // Zeilen einzeln einlesen
        fgets(currentRow, MAX_ROW_LENGTH, file);

        char *ptr = strtok(currentRow, ", \n\r"); // Erste Zahl extrahieren.
        int valüCount = 0;
        while (ptr) {
            // Prüfen, ob nur gültige Zahlen enthalten sind.
            if (isValid(ptr)) {
                insertArray(rows[i], atof(ptr));
                ptr = strtok(NULL, ", \n\r"); // Weitere Zahlen extrahieren.
                valüCount++;
            } else {
                printf("=> Fehler beim Lesen der Datei:\n");
                printf("   Ung\u00FCltiges Format in Zeile %d!\n", i + 1);
                success = false;
                break;
            }
        }

        // Sind zu viele oder zu wenig Werte vorhanden? => Fehlermeldung.
        if (success && (valüCount < rowNum + 1 || valüCount > rowNum + 2)) {
            printf("=> Fehler: Anzahl der Werte unzul\u00E4ssig!\n");
            success = false;
            break;
        }
    }

    free(currentRow);

    // Strukturen befüllen.

    // Matrix befüllen.
    A->n = rowNum;
    A->data = malloc(sizeof (double*) * A->n);
    for (int i = 0; i < A->n; i++) {
        A->data[i] = malloc(sizeof (double) * A->n);
        for (int j = 0; j < A->n; j++) {
            A->data[i][j] = rows[i]->array[j];
        }
    }

    // Vektoren befüllen.
    b->n = rowNum;
    x->n = rowNum;

    b->data = malloc(sizeof (double) * b->n);
    x->data = malloc(sizeof (double) * x->n);
    for (int i = 0; i < rowNum; i++) {
        b->data[i] = rows[i]->array[rowNum];

        // Wenn x(i0) angegeben ist, wird der Wert in den Vektor geschrieben,
        // ansonsten wird für x(i0) der Wert 0 in den Vektor geschrieben.
        x->data[i] = rows[i]->used > rowNum + 1 ? rows[i]->array[rowNum + 1] : 0;
    }

    // Aufräumen
    fclose(file);

    for (int i = 0; i < rowNum; i++) {
        freeArray(rows[i]);
        free(rows[i]);
    }

    free(rows);
    return success;
}


void addVectorToList(List list, double data[], int size) {
    // Vektor befüllen.
    Vector *vector = malloc(sizeof (Vector));
    vector->n = size;
    vector->data = malloc(sizeof (double) * size);

    // übergebenes Array kopieren.
    copyArray(data, vector->data, size);

    // Vektor zur Liste hinzufügen.
    push(list, vector);
}


List solve(Method method, Matrix *A, Vector *b, Vector *x, double e) {
    List list = createList();

    // Kopie der x-Vektoren
    double* xold = malloc(sizeof (double) * x->n);
    copyArray(x->data, xold, x->n);

    double xnew[x->n];
    copyArray(x->data, xnew, x->n);

    double epsilon = 0;
    double sum = 0;
    for (size_t m = 0; m < MAX_STEPS; m++) { // Anzahl der Schritte
        epsilon = 0; // Fehler zurücksetzen.

        switch (method) {
            case JACOBI:
                // Jacobi-Verfahren
                copyArray(b->data, xnew, b->n);
                for (int k = 0; k < A->n; k++) {
                    for (int i = 0; i < A->n; i++) {
                        if (k != i) {
                            xnew[k] -= A->data[k][i] * xold[i];
                        }
                    }

                    xnew[k] /= A->data[k][k];
                    epsilon = max(epsilon, fabs(xnew[k] - xold[k]));
                }

                break;
            case GAUSS_SEIDEL:
                // Gauss-Seidel-Verfahren
                for (int k = 0; k < A->n; k++) {
                    for (int i = 0; i < A->n; i++) {
                        sum += A->data[k][i] * xnew[i];
                    }

                    xnew[k] = xnew[k] - (1 / A->data[k][k]) * (sum - b->data[k]);

                    // Fehlerberechnung
                    epsilon = max(epsilon, fabs(xnew[k] - xold[k]));
                    sum = 0;
                }

                break;
        }

        // Werte des neuen Vektors in alten Vektor kopieren.
        copyArray(xnew, xold, x->n);

        addVectorToList(list, xold, x->n);

        if (epsilon < e) { // Fehlerschranke überprüfen.
            break;
        }
    }
    free(xold);

    return list;
}


bool tryToSolve(Matrix *A, Vector *b, Vector *x) {
    bool success = false;

    char input[INPUT_BUFFER_LENGTH] = {0};

    // Verfahren wählen.
    int method = 0;

    printf("\n:: Welches Verfahren m\u00F6chten Sie nutzen?");
    printf("\n\t0) Jacobi\n\t1) Gauss-Seidel\n");

    do {
        printf("Geben Sie eine Zahl ein: ");
        fgets(input, INPUT_BUFFER_LENGTH, stdin);
    } while (sscanf(input, "%d", &method) != 1 || !(method == 0 || method == 1));

    // Fehlerschranke wählen.
    double epsilon = -1;

    do {
        printf("Geben Sie eine Fehlerschranke ein: ");
        fgets(input, INPUT_BUFFER_LENGTH, stdin);
    } while (sscanf(input, "%lf", &epsilon) != 1 || epsilon < 0);

    // Berechnung.
    List list = solve(method, A, b, x, epsilon);

    // Ausgabe auswählen.
    if (list.head->next != list.tail) {
        Element *element = list.head->next; // Erstes Element der Liste auswählen.

        int output = 0;

        printf("\n:: Was soll ausgegeben werden?");
        printf("\n\t0) letzter Vektor\n\t1) Verlauf\n");

        do {
            printf("Geben Sie eine Zahl ein: ");
            fgets(input, INPUT_BUFFER_LENGTH, stdin);
        } while (sscanf(input, "%d", &output) != 1 || !(output == 0 || output == 1));

        // Ausgabe.

        // Verlauf ausgeben, wenn gewünscht.
        int i = 0; // Anzahl der in der Liste enthaltenen Vektoren.
        if (output) {
            printf("\n:: Verlauf:");
        }

        for (i = 0; element != list.tail; i++) {
            if (output) {
                printVector(i, element->vector);
            }
            element = element->next;
        }

        if (output) {
            printf(" (Output)\n");
        }

        // Letzten Vektor ausgeben.
        printf("\n:: Ergebnis nach %d Iteration(en):", i);
        printVector(i, list.tail->prev->vector);
        printf("\n");

        success = true;
    } else {
        printf("=> Bei der Berechnung ist ein Fehler aufgetreten!\n");
    }

    deleteList(list);
    return success;
}


bool ask() {
    char answer = getchar();

    // Buffer leeren.
    char temp = 0;
    while (temp != '\n') {
        temp = getchar();
    }

    // Wird nicht j oder J getippt, so wird false zurückgegeben.
    return !(answer == 'j' || answer == 'J');
}


bool restart() {
    printf("\nWollen Sie eine neue Datei einlesen? [J/n] ");
    return ask();
}


int main(int argc, char *argv[]) {
    bool exit = false;

    char filename[INPUT_BUFFER_LENGTH] = {0};

    while (!exit) { // Solange das Programm nicht beendet werden soll...
        // Evtl. Startparameter als Dateipfad setzen.
        if (argc > 1 && strlen(argv[1]) < INPUT_BUFFER_LENGTH) {
            strncpy(filename, argv[1], INPUT_BUFFER_LENGTH);

            argc = 1; // Kommandozeilenparameter beim nächsten Mal ignorieren.
        } else {
            // Dateipfad einlesen.
            char input[INPUT_BUFFER_LENGTH] = {0};

            do {
                printf("Geben Sie einen Dateipfad ein: ");
                fgets(input, INPUT_BUFFER_LENGTH, stdin);
            } while (sscanf(input, "%s", filename) != 1);

        }

        // Matrix allokieren und zurücksetzen.
        Matrix *A = malloc(sizeof (Matrix)); A->n = 0; A->data = NULL;
        Vector *b = malloc(sizeof (Vector)); b->n = 0; b->data = NULL;
        Vector *x = malloc(sizeof (Vector)); x->n = 0; x->data = NULL;

        // Datei laden.
        if (!load(filename, A, b, x)) {
            exit = restart();
        } else {
            // Datei geladen.
            printf("Daten erfolgreich geladen!\n");

            if (!tryToSolve(A, b, x)) {
                printf("\nWollen Sie eine neue Berechnung versuchen? [J/n] ");
                exit = ask();
                
                argc = 1;
            } else {
                exit = restart();
            }
        }

        // Aufräumen
        if (A->data != NULL) {
            for (int i = 0; i < A->n; i++) {
                free(A->data[i]);
            }

            free(A->data);
        }

        if (b->data != NULL) {
            free(b->data);
        }

        if (x->data != NULL) {
            free(x->data); 
        }

        free(A);
        free(b);
        free(x);
    } // Ende der while-Schleife.

    printf("\nProgramm wird beendet...\n");
    return EXIT_SUCCESS;
}
