# Arkusz kalkulacyjny

## 1. main.cpp
- start działania programu - wywołanie funkcji menu

## 2. menu.cpp:
- funkcja powitalna i wybór akcji
  - utworzenie arkusza kalkulacyjnego o danych wymiarach
  - wprowadzenie/aktualizacja danych do arkusza
  - wyświetlanie zawartości arkusza
  - zmiana wymiarów arkusza
  - zapis arkusza do pliku
  - odczyt arkusza z pliku
  - usunięcie wybranego pliku z arkuszem
  - wybór operacji matematycznej na arkuszu
  - zakończenie pracy z programem
## 3. tablica.cpp:
- funkcja tworząca dwuwymiarową tablicę dynamiczną
- funkcja wprowadzająca/aktualizująca dane w tablicy
- funkcja aktualizująca rozmiar tablicy
  - funkcja zerująca arkusz
	- funkcja kopiująca zawartość arkusza o starych wymiarach do arkusza o nowych wymiarach
- funkcja wysyłająca dane do wykonania zapisu arkusza do pliku
- funkcja odbierająca dane z wykonanego odczytu arkusza z pliku
- funkcja wysyłająca nazwę pliku do usunięcia oraz informację o błędzie
- funkcje realizujące operacje matematyczne na arkuszu
  - funkcja sumująca po wierszach/kolumnach
  - funkcja znajdująca wartość największą w wierszu/kolumnie
  - funkcja znajdująca wartość najmniejszą w wierszu/kolumnie
  - funkcja obliczająca wartość średnią wiersza/kolumny
## 4. tablica_wysw.cpp:
- funkcja wyświetlająca zawartość arkusza na ekranie
## 5. operacje_na_plikach.cpp:
- funkcja zapisująca zawartość arkusza do pliku
- funkcja odczytująca zawartość arkusza z pliku
- funkcja usuwająca wybrany plik z arkuszem
