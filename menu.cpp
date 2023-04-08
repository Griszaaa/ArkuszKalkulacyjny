/// @file
#include <iostream>
#include <cstdlib>
#include <string>
#include "menu.h"
#include "tablica.h"
#include "tablica_wysw.h"

using namespace std;

//*******************************************************************************************************************************************************************
void welcome(void)
{
    cout << "ARKUSZ KALKULACYJNY" << endl;
    cout << "Wybierz działanie:" << endl;
    cout << "1. Wybierz rozmiar arkusza i utwórz nowy arkusz" << endl
         << "2. Wprowadź/zaktualizuj dane arkusza"<< endl
         << "3. Wyświetl zawartość arkusza" << endl
         << "4. Zmień rozmiar arkusza" << endl
         << "5. Zapisz zawartość arkusza do pliku" << endl
         << "6. Odczytaj zawartość arkusza z pliku" << endl
         << "7. Usuń wybrany plik z arkuszem" << endl
         << "8. Operacje matematyczne na arkuszu" << endl
         << "9. Zakończ" << endl;
}
//*******************************************************************************************************************************************************************
void menu(Sheet sheet)
{
    while(1)
    {
        welcome();
        string file;
        int choice;
        int *colType;
        int x;
        int y;
        cin >> choice;

        switch(choice)
        {
            case 1:
            {
                cout << "Podaj ilość wierszy: " << endl;
                cin >> x;
                while(x < 0)
                {
                    cout << "BŁĄD - Nieprawidłowa ilość wierszy!" << endl;
                    cout << "Podaj ilość wierszy: " << endl;
                    cin >> x;
                }
                cout << endl;

                cout << "Podaj ilość kolumn: " << endl;
                cin >> y;
                while(y < 0)
                {
                    cout << "Podaj ilość kolumn: " << endl;
                    cout << "BŁĄD - Nieprawidłowa ilość kolumn!" << endl;
                    cin >> y;
                }
                cout << endl; 

                cout << "Podaj typy kolumn: " << endl;
                cout << "0 - liczby" << endl << "1 - tekst" << endl;
                colType = columnType(y);

                cout << "Czy utworzyć nowy arkusz?" << endl;
                if(confirm())
                {
                    sheet.new_tab(x, y, colType);
                }
                break;
            }

            case 2:
            {
                while(1)
                {
                    Cell *value = sheet.edit(&x, &y);
                    sheet.update_tab(x-1, y-1, value);
                    cout << "Czy chcesz dalej edytować zawartość arkusza?" << endl;
                    if(confirm() == 0)
                    {
                        break;
                    }
                }
                break;
            }

            case 3:
            {
                sheet.tab_disp();
                break;
            }

            case 4:
            {
                int newr1;
                int newr2;
                colType = sheet.edit_size(&newr1, &newr2, colType);
                sheet.update_tabsize(newr1, newr2, colType);
                break;
            }

            case 5:
            {
                cout << "Podaj nazwę pliku (bez rozszerzenia): ";
                cin >> file;
                file += ".txt";

                if(sheet.write_sheet(file))
                {
                    cout << "Zapisano" << endl;
                }
                else
                {
                    cout << "Błąd zapisu!" << endl;
                }
                break;
            }

            case 6:
            {
                cout << "Podaj nazwę pliku (bez rozszerzenia): ";
                cin >> file;
                file += ".txt";

                if(sheet.read_sheet(file))
                {
                    cout << "Odczytano" << endl;
                }
                else
                {
                    cout << "Brak pliku " << "\"" << file << "\". " << "Najpierw wykonaj zapis!" << endl;
                }
                break;
            }

            case 7:
            {
                cout << "Podaj nazwę pliku (bez rozszerzenia): ";
                cin >> file;
                file += ".txt";

                if(delete_sheet(file))
                {
                    cout << "Usunięto wybrany plik" << endl;
                }
                else
                {
                    cout << "Brak pliku " << "\"" << file << "\". " << endl;
                }
                break;
            }

            case 8:
            {
                int dim_choice;
                int math_choice;

                choice_math(&dim_choice, &math_choice);
                sheet.math(dim_choice, math_choice);
                break;
            }

            case 9:
            {
                cout << "Zakończyć pracę?" << endl;
                if(confirm())
                {
                    exit(0);
                }
                else
                {
                    break;
                }
            }
        }
    }
}
//*******************************************************************************************************************************************************************
bool confirm(void)
{
    cout << "t/n" << endl;
    char a;
    cin >> a;
    if(a == 't')
    {
        return 1;
    }
    if(a == 'n')
    {
        return 0;
    }
    else
    {
        return 0;
    }
}

//*******************************************************************************************************************************************************************
int* columnType(int x)
{
    int *cType = new int[x];

    for(int i = 1; i<=x; i++)
    {
        cout << i << ". ";
        cin >> cType[i-1];
        cout << endl;
        while((cType[i-1] != 0) && (cType[i-1] != 1))
        {
            cout << "BŁĄD - Nieprawidłowy typ kolumny!" << endl;
            cout << "Podaj typy kolumn: " << endl;
            cout << "0 - liczby" << endl << "1 - tekst" << endl;
            cout << i << ". ";
            cin >> cType[i-1];
        }
        cout << endl;
    }
    return cType;
}
//*******************************************************************************************************************************************************************
Cell* Sheet::edit(int *wskx, int *wsky)
{
    double doubleval;
    string stringval;

    cout << "Wprowadź współrzędne komórki" << endl;
    cout << "Podaj numer wiersza: ";
    cin >> *wskx;
    while((*wskx>r1) || (*wskx == 0))
    {
        cout << "BŁĄD - nie ma takiego wiersza!" << endl;
        cout << "Podaj numer wiersza: ";
        cin >> *wskx;
    }
    cout << endl;

    cout << "Podaj numer kolumny: ";
    cin >> *wsky;
    while((*wsky>r2) || (*wsky == 0))
    {
        cout << "BŁĄD - nie ma takiej kolumny!" << endl;
        cout << "Podaj numer kolumny: ";
        cin >> *wsky;
    }
    cout << endl;

    if(tab[*wskx-1][*wsky-1]->getNum() == true)
    {
        Cell *value = new DoubleCell;
        cout << "Wprowadź wartość liczbową: ";
        cin >> doubleval;
        value->setValue(to_string(doubleval));
        return value;

    }
    if(tab[*wskx-1][*wsky-1]->getNum() == false)
    {
        Cell *value = new StringCell;
        cout << "Wprowadź wartość tekstową: ";
        cin >> stringval;
        value->setValue(stringval);
        return value;
    }
}
//*******************************************************************************************************************************************************************
int* Sheet::edit_size(int *wsknewr1, int *wsknewr2, int *colType)
{
    cout << "Podaj nowy rozmiar tablicy" << endl;
    cout << "Podaj ilość wierszy: ";
    cin >> *wsknewr1;
    while(*wsknewr1<r1)
    {
        cout << "UWAGA - podałeś mniejszy rozmiar, niż obecny!" << endl;
        cout << "Nastąpi utrata danych, czy kontynuować?" << endl;
        if(confirm())
        {
            break;
        }
        else
        {
            cout << "Podaj ilość wierszy: ";
            cin >> *wsknewr1;
        }
    }
    cout << endl;

    cout << "Podaj ilość kolumn: ";
    cin >> *wsknewr2;
    while(*wsknewr2<r2)
    {
        cout << "UWAGA - podałeś mniejszy rozmiar, niż obecny!" << endl;
        cout << "Nastąpi utrata danych, czy kontynuować?" << endl;
        if(confirm())
        {
            break;
        }
        else
        {
            cout << "Podaj ilość kolumn: ";
            cin >> *wsknewr2;
        }
    }
    cout << endl;

    if(*wsknewr2>r2)
    {
        cout << "Podaj typy kolumn: " << endl;
        cout << "0 - liczby" << endl << "1 - tekst" << endl;
        colType = columnType(*wsknewr2);
    }
    return colType;
}
//*******************************************************************************************************************************************************************
void choice_math(int *dim_choice, int *math_choice)
{
    cout << "Wybierz wymiar: " << endl;
    cout << "1. Wiersze" << endl
         << "2. Kolumny" << endl;

    cin >> *dim_choice;
    cout << endl;

    cout << "Wybierz operację: " << endl;
    cout << "1. Sumowanie" << endl
         << "2. Wartość największa" << endl
         << "3. Wartość najmniejsza" << endl
         << "4. Wartość średnia" << endl;

    cin >> *math_choice;
}
//*******************************************************************************************************************************************************************
void Sheet::math(int dim_choice, int math_choice)
{
    int x = 0;

    switch(math_choice)
    {
        case 1:
        {
            Cell **result = this->sum(dim_choice);

            if(dim_choice == 1)
            {
                cout << "Zsumowanie poszczególne wiersze: ";
                for(int i = 0; i<r1; i++)
                {
                    cout << result[i]->getValue() << ", ";
                }
                cout << endl;
            }

            if(dim_choice == 2)
            {
                cout << "Zsumowane poszczególne kolumny: ";
                for(int i = 0; i<r2; i++)
                {
                    cout << result[i]->getValue() << ", ";
                }
                cout << endl;
            }
            break;
        }

        case 2:
        {
            Cell *greatest = new DoubleCell;
            cout << "Podaj numer wiersza/kolumny: " << endl;
            cin >> x;
            greatest = (this->greatest_value(dim_choice, x-1));
            cout << "Wartość największa: " << greatest->getValue() << endl;
            break;
        }

        case 3:
        {
            Cell *smallest = new DoubleCell;
            cout << "Podaj numer wiersza/kolumny: " << endl;
            cin >> x;
            smallest = (this->smallest_value(dim_choice, x-1));
            cout << "Wartość najmniejsza: " << smallest->getValue() << endl;
            break;
        }

        case 4:
        {
            Cell *average = new DoubleCell;
            cout << "Podaj numer wiersza/kolumny: " << endl;
            cin >> x;
            average = (this->average_value(dim_choice, x-1));
            cout << "Wartość średnia: " << average->getValue() << endl;
            break;
        }

    }
}
//*******************************************************************************************************************************************************************

