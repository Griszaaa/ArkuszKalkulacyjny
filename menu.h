/// @file

#ifndef UNTITLED_MENU_H
#define UNTITLED_MENU_H
#include "tablica.h"

/** Funkcja wyświetlająca powitanie oraz dostępne opcje w programie
 */
void welcome(void);

/** Funkcja odpowiedzialna na za działanie menu użytkownika
 */
void menu(Sheet sheet);

/** Funkcja oczekująca potwierdzenia działania przez użytkownika
 */
bool confirm(void);
/** Funkcja pobierająca od użytkownika typ kolumn arkusza
 * @return prawda 0, gdy kolumna liczbowa, 1 gdy kolumna tekstowa
*/
int* columnType(int x);

/** Funkcja pobierająca informacje o wyborze wymiaru oraz rodzaju działania matematycznego
 * @param[in,out] dim_choice wskaźnik do zmiennej służącej do wyboru wymiaru
 * @param[in,out] math_choice wskaźnik do zmiennej służącej do wyboru działania matematycznego
 */
void choice_math(int *dim_choice, int *math_choice);
#endif //UNTITLED_MENU_H
