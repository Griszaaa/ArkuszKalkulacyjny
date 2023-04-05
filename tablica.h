#ifndef UNTITLED_TABLICA_H
#define UNTITLED_TABLICA_H
/// @file

#include <string>


/** Klasa przechowująca typy wartości w komórkach arkusza
 */
class Cell
{
public:

    /** Funkcja informująca czy dana komórka jest numeryczna
     * @return prawda albo fałsz
     */
    virtual bool getNum(void) = 0;

    /** Getter
     */
    virtual std::string getValue(void) = 0;

    /** Setter
      */
    virtual void setValue(std::string value) = 0;
};
/** Klasa komórki typu liczbowego
*/
class DoubleCell: public Cell
{
    double doubleValue = 0;
public:
    std::string getValue(void);
    void setValue(std::string value);
    bool getNum(void);
};
/** Klasa komórki typu tekstowego
*/
class StringCell: public Cell
{
    std::string stringValue = "-";

public:
    std::string getValue(void);
    void setValue(std::string value);
    bool getNum(void);
};

/** Klasa przechowująca dane o arkuszu
 */
class Sheet
{
    /** Wskaźnik do dwuwymiarowej tablicy dynamicznej obiektów klasy Cell (arkusz)
     */
    Cell ***tab;
    /** Pierwszy wymiar arkusza (wiersze)
     */
    int r1 = 0;
    /** Drugi wymiar arkusza (kolumny)
     */
    int r2= 0;

    /** Funkcja tworząca arkusz kalkulacyjny o danych wymiarach
      * @param[in] r1 pierwszy wymiar arkusza (wiersze)
      * @param[in] r2 drugi wymiar arkusza (kolumny)
      * @param[in] colType wskaźnik do tablicy przechowującej dane o typie kolumn
      * @return wskaźnik do dwuwymiarowej tablicy dynamicznej obiektów klasy Cell (arkusz)
     */
    Cell*** create_tab(int r1, int r2, int *colType);

    /** Funkcja kopiująca zawartość między dwiema tablicami
     * @param[in,out] t1 wskaźnik do dwuwymiarowej tablicy dynamicznej obiektów klasy Cell (arkusz) docelowej
     * @param[in] t2 wskaźnik do dwuwymiarowej tablicy dynamicznej obiektów klasy Cell (arkusz) kopiowanej
     * @param[in] r1 pierwszy wymiar tablicy docelowej (wiersze)
     * @param[in] r2 drugi wymiar tablicy docelowej (kolumny)
     */
    void copy_tab(Cell ***t1, Cell ***t2, int r1, int r2);

    /** Funkcja zerująca zawartość arkusza
     * @param[in,out] t wskaźnik do dwuwymiarowej tablicy dynamicznej obiektów klasy Cell (arkusz)
     * @param[in] r1 pierwszy wymiar tablicy (wiersze)
     * @param[in] r2 drugi wymiar arkusza (kolumny)
     */
    void reset_sheet(Cell ***t, int r1, int r2);

    /** Funkcja odczytująca zawartość arkusza z pliku
     * @param[in] file_name nazwa pliku do odczytu
     * @return 1 gdy plik istnieje, 0 gdy plik nie istnieje
     */
    bool read(std::string file_name);

    /** Funkcja zapisująca zawartość arkusza do pliku
     * @param[in,out] file_name nazwa pliku docelowego
     * @return 1 gdy zapis został wykonany poprawnie, 0 gdy zapis nie został wykonany
     */
    bool write(std::string file_name);

    /** Funkcja realizująca operację sumowania wierszy/kolumn
     * @param[in] dim_choice zmienna przechowująca dane o wybranym wymiarze
     * @return adres obiektu tablicy z wynikiem
     */
    Cell** sum(int dim_choice);

    /** Funkcja realizująca operację znajdowania wartości największej w wierszach/kolumnach
     * @param[in] dim_choice zmienna przechowująca dane o wybranym wymiarze
     * @param[in] x zmienna przechowująca numer wybranego wiersza/kolumny
     * @return obiekt z wynikiem
     */
    Cell* greatest_value(int dim_choice, int x);

    /** Funkcja realizująca operację znajdowania wartości najmniejszej w wierszach/kolumnach
     * @param[in] dim_choice zmienna przechowująca dane o wybranym wymiarze
     * @param[in] x zmienna przechowująca numer wybranego wiersza/kolumny
     * @return obiekt z wynikiem
     */
    Cell* smallest_value(int dim_choice, int x);

    /** Funkcja realizująca operację obliczania wartości średniej w wierszach/kolumnach
     * @param[in] dim_choice zmienna przechowująca dane o wybranym wymiarze
     * @param[in] x zmienna przechowująca numer wybranego wiersza/kolumny
     * @return obiekt z wynikiem
     */
    Cell* average_value(int dim_choice, int x);

    /** Funkcja zwracająca liczbę niepustych komórek danego wiersza/kolumny
     * @param[in] dim_choice zmienna przechowująca dane o wybranym wymiarze
     * @param[in] x zmienna przechowująca numer wybranego wiersza/kolumny
     * @return liczba niepustych komórek danego wiersza/kolumny
     */
    double not_empty(int dim_choice, int x);

public:
    /** Funkcja tworząca nowy arkusz
     * @param[in] x pierwszy wymiar arkusza (wiersze)
     * @param[in] y drugi wymiar arkusza (kolumny)
     * @param[in] colType
     */
    void new_tab(int x, int y, int *colType);

    /** Funkcja aktualizująca zawartość arkusza
     * @param[in] x numer wiersza w arkuszu
     * @param[in] y numer kolumny w arkuszu
     * @param[in] value wartość wpisywana do wskazanej komórki arkusza
     */
    void update_tab(int x, int y, Cell *value);

    /** Funkcja aktualizująca rozmiar arkusza
     * @param[in,out] sheet wskaźnik do zmiennej strukturalnej przechowującej arkusz i jego wymiary
     * @param[in] nr1 nowy pierwszy wymiar arkusza (wiersze)
     * @param[in] nr2 nowy drugi wymiar arkusza (kolumny)
     */
    void update_tabsize(int nr1, int nr2, int *colType);

    /** Funkcja wyświetlająca zawartość arkusza na ekranie
      */
    void tab_disp(void);

    /** Funkcja zerująca zawartość arkusza
     */
    void reset_sheet(void);

    /** Funkcja odczytująca arkusz z pliku
     * @param[in] file_name nazwa pliku do odczytu
     * @return 1 gdy odczyt został wykonany poprawnie, 0 gdy odczyt nie został wykonany
     */
    bool read_sheet(std::string file_name);

    /** Funkcja zapisująca arkusz do pliku
     * @param[in,out] sheet zmienna strukturalna przechowująca arkusz i jego wymiary
     * @param[in,out] file_name nazwa pliku docelowego
     * @return 1 gdy zapis został wykonany poprawnie, 0 gdy zapis nie został wykonany
     */
    bool write_sheet(std::string file_name);

    /** Funkcja pobierająca współrzędne komórki i wartość od użytkownika
     * @param[in,out] wskx wskaźnik do zmiennej odpowiedzialnej za numer wiersza
     * @param[in,out] wsky wskaźnik do zmiennej odpowiedzialnej za numer kolumny
     */
    Cell* edit(int *wskx, int *wsky);

    /** Funkcja pobierająca nowe rozmiary arkusza od użytkownika
     * @param[in,out] wsknewr1 wskaźnik do zmiennej odpowiedzialnej za nowy rozmiar arkusza (wiersze)
     * @param[in,out] wsknewr2 wskaźnik do zmiennej odpowiedzialnej za nowy rozmiar arkusza (kolumny)
     */
    int* edit_size(int *wsknewr1, int *wsknewr2, int *colType);

    /** Funkcja realizująca poszczególne działania matematyczne
     * @param[in] dim_choice zmienna przechowująca dane o wybranym wymiarze
     * @param[in] math_choice zmienna przechowująca dane o wybranym działaniu matematycznym
     */
    void math(int dim_choice, int math_choice);
};

/** Funkcja usuwająca wybrany plik z arkuszem
 * @param[in] file_name nazwa pliku do usunięcia
 * @return 1 gdy plik został usunięty, 0 gdy plik nie został usunięty
 */
bool delete_sheet(std::string file_name);

#endif //UNTITLED_TABLICA_H
