# solvelsoe

A program that solves linear systems of equations.

## Disclaimer

This program is part of the C programming course of the DHBW Mosbach.
Therefore the documentation of the source code is in German.

The tool is not under active development. Use it on your own risk.

## Hinweis zur Kompilierung unter Linux

Zum Kompilieren des Programms Makefile mit `make` ausführen. Um kompilierte
Dateien wieder zu löschen, `make clean` ausführen. Das Programm wird dann
mit dem Befehl `./bin/solvelsoe` ausgeführt.


## Problemstellung

In dem Programmentwurf sollen zwei Verfahren zur Berechnung der L¨osung eines
linearen Gleichungssystems, das Jacobi- und das Gauß-Seidel-Verfahren
implementiert werden (siehe de.wikipedia.org/wiki/Jacobi-Verfahren und
de.wikipedia.org/wiki/Gauß-Seidel-Verfahren).

a₁₁x₁ + a₁₂x₂ + . . . a₁ₙxₙ = b₁
a₂₁x₁ + a₂₂x₂ + . . . a2ₙxₙ = b₂
.
.
aₙ₁x₁ + aₙ₂x₂ + . . . aₙₙxₙ = bₙ

Die beiden Verfahren berechnen aus einem Startvektor x° = (x₁⁰,x₂⁰ ... , xₙ⁰)
eine Folge von Vektoren xⁿ = ( x₁ⁿ , x₂ⁿ , ... , xₙⁿ ), die unter bestimmten
Voraussetzungen gegen die Lösung des Gleichungssystems konvergiert.

## Bedingungen

* Eine Bearbeitung in Gruppen von 3 Studierenden ist zulässig. Alle
  Studierenden in einer Gruppe erhalten die gleiche Bewertung.
* Das Programm muss unter Linux mit dem GCC-Compiler unter Verwendung der
  Optionen `-Wall` und `-pedantic-errors` fehlerfrei und ohne Warnungen
  kompilierbar sein.
* Die vorgegebenen Datentypen und Funktionen müssen wie oben beschrieben zur
  Lösung der Aufgabe eingesetzt werden. Es dürfen nach Bedarf weitere
  Datentypen und Funktionen ergänzt werden. Globale Variablen sind nicht
  erlaubt.
* Abgabe: Source Code als c-File oder zip-File auf Moodle hochladen. Die Datei
  mit den Namen der Gruppenmitglieder benennen. Abgabetermin ist 22.03.2020.

## Authors

* Manuel Truckses
* Justus Röderer
* Andreas Köhler
