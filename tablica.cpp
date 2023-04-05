/// @file

#include <iostream>
#include <string>
#include <cstring>
#include "tablica.h"
#include "menu.h"
#include "operacje_na_plikach.h"

using namespace std;

//*******************************************************************************************************************************************************************
bool DoubleCell::getNum(void)
{
    return true;
}
//*******************************************************************************************************************************************************************
bool StringCell::getNum(void)
{
    return false;
}
//*******************************************************************************************************************************************************************
string DoubleCell::getValue(void)
{
    return to_string(doubleValue);
}
//*******************************************************************************************************************************************************************
void DoubleCell::setValue(string value)
{
    doubleValue = stod(value);
}
//*******************************************************************************************************************************************************************
string StringCell::getValue(void)
{
    return stringValue;
}
//*******************************************************************************************************************************************************************
void StringCell::setValue(string value)
{
    stringValue = value;
}
//*******************************************************************************************************************************************************************
void Sheet::new_tab(int x, int y, int *colType)
{
    r1 = x;
    r2 = y;

    tab = create_tab(r1, r2, colType);
}
//*******************************************************************************************************************************************************************
Cell*** Sheet::create_tab(int r1, int r2, int *colType)
{
    Cell ***tab = new Cell**[r1];

    for(int i = 0; i<r1; i++)
    {
        tab[i] = new Cell*[r2];

        for(int j = 0; j<r2; j++)
        {

            if(colType[j] == 0)
            {
                tab[i][j] = new DoubleCell;
            }
            if(colType[j] == 1)
            {
                tab[i][j] = new StringCell;
            }
        }
    }
    return tab;
}
//*******************************************************************************************************************************************************************
void Sheet::update_tab(int x, int y, Cell *value)
{
    if(tab[x][y]->getNum() == true)
    {
        tab[x][y]->setValue(value->getValue());
    }
    if(tab[x][y]->getNum() == false)
    {
        tab[x][y]->setValue(value->getValue());
    }
}
//*******************************************************************************************************************************************************************
void Sheet::update_tabsize(int nr1, int nr2, int *colType)
{
    Cell*** sheet_copy = create_tab(nr1, nr2, colType);
    reset_sheet(sheet_copy, nr1, nr2);

    if(r1<=nr1)
    {
        if(r2<=nr2)
        {
            copy_tab(sheet_copy, tab, r1, r2);
        }
        else
        {
            copy_tab(sheet_copy, tab, r1, nr2);
        }
    }
    if(r1>nr1)
    {
        if(r2>nr2)
        {
            copy_tab(sheet_copy, tab, nr1, nr2);
        }
        else
        {
            copy_tab(sheet_copy, tab, nr1, r2);
        }
    }

    r1 = nr1;
    r2 = nr2;
    tab = sheet_copy;
}
//*******************************************************************************************************************************************************************
void Sheet::copy_tab(Cell ***t1, Cell ***t2, int r1, int r2)
{
    for(int i = 0; i<r1; i++)
    {
        for(int j = 0; j<r2; j++)
        {
            if(t1[i][j]->getNum() == true)
            {
                t1[i][j]->setValue(t2[i][j]->getValue());
            }
            else
            {
                t1[i][j]->setValue(t2[i][j]->getValue());
            }
        }
    }
}
//*******************************************************************************************************************************************************************
void Sheet::reset_sheet(Cell ***t, int r1, int r2)
{
    for(int i = 0; i<r1; i++)
    {
        for(int j = 0; j<r2; j++)
        {
            if(t[i][j]->getNum())
            {
                t[i][j]->setValue(to_string(0));
            }
            else
            {
                t[i][j]->setValue("-");
            }
        }
    }
}
//*******************************************************************************************************************************************************************
void Sheet::reset_sheet(void)
{
    for(int i = 0; i<r1; i++)
    {
        for(int j = 0; j<r2; j++)
        {
            if(tab[i][j]->getNum())
            {
                tab[i][j]->setValue(0);
            }
            else {
                tab[i][j]->setValue("-");
            }
        }
    }
}
//*******************************************************************************************************************************************************************
bool Sheet::read_sheet(string file_name)
{
    return (this->read(file_name));
}
//*******************************************************************************************************************************************************************
bool Sheet::write_sheet(string file_name)
{
    return (this->write(file_name));
}
//*******************************************************************************************************************************************************************
bool delete_sheet(string file_name)
{
    return (del(file_name));
}
//*******************************************************************************************************************************************************************
Cell** Sheet::sum(int dim_choice)
{
    if(dim_choice == 1)
    {
        Cell **result = new Cell*[r1];

        for(int i = 0; i<r1; i++)
        {
            result[i] = new DoubleCell;
        }

        for(int i = 0; i<r1; i++)
        {
            result[i]->setValue(to_string(0));
        }

        for(int i = 0; i<r1; i++)
        {
            for(int j = 0; j<r2; j++)
            {
                if(tab[i][j]->getNum())
                {
                    result[i]->setValue(to_string(stod(result[i]->getValue()) + stod(tab[i][j]->getValue())));
                }
            }
        }
        return result;
    }

    if(dim_choice == 2)
    {
        Cell **result = new Cell*[r2];

        for(int i = 0; i<r2; i++)
        {
            result[i] = new DoubleCell;
        }

        for(int i = 0; i<r2; i++)
        {
            result[i]->setValue(to_string(0));
        }

        for(int i = 0; i<r2; i++)
        {
            for(int j = 0; j<r1; j++)
            {
                if(tab[j][i]->getNum())
                {
                    result[i]->setValue(to_string(stod(result[i]->getValue()) + stod(tab[j][i]->getValue())));
                }
            }
        }
        return result;
    }
}
//*******************************************************************************************************************************************************************
Cell* Sheet::greatest_value(int dim_choice, int x)
{
    Cell *max = new DoubleCell;

    if(dim_choice == 1)
    {
        max->setValue(tab[x][0]->getValue());

        for(int i = 0; i<r2; i++)
        {
            if(tab[x][i]->getNum())
            {
                if(stod(tab[x][i]->getValue()) > stod(max->getValue()))
                {
                    max->setValue(tab[x][i]->getValue());
                }
            }
        }
        return max;
    }

    if(dim_choice == 2)
    {
        if(tab[0][x]->getNum())
        {
            max->setValue(tab[0][x]->getValue());

            for(int i = 0; i<r1; i++)
            {
                if(tab[i][x]->getNum())
                {
                    if(stod(tab[i][x]->getValue()) > stod(max->getValue()))
                    {
                        max->setValue(tab[i][x]->getValue());
                    }
                }
            }
        }
        return max;
    }
}
//*******************************************************************************************************************************************************************
Cell* Sheet::smallest_value(int dim_choice, int x)
{
    Cell *min = new DoubleCell;

    if(dim_choice == 1)
    {
        min->setValue(tab[x][0]->getValue());

        for(int i = 0; i<r2; i++)
        {
            if(tab[x][i]->getNum())
            {
                if(stod(tab[x][i]->getValue()) < stod(min->getValue()))
                {
                    min->setValue(tab[x][i]->getValue());
                }
            }
        }

        return min;
    }

    if(dim_choice == 2)
    {
        if(tab[0][x]->getNum())
        {
            min->setValue(tab[0][x]->getValue());

            for(int i = 0; i<r1; i++)
            {
                if(tab[i][x]->getNum())
                {
                    if(stod(tab[i][x]->getValue()) < stod(min->getValue()))
                    {
                        min->setValue(tab[i][x]->getValue());
                    }
                }
            }
        }
        return min;
    }
}
//*******************************************************************************************************************************************************************
Cell* Sheet::average_value(int dim_choice, int x)
{
    Cell *avg = new DoubleCell;
    double a = 0;

    if(dim_choice == 1)
    {
        for(int i = 0; i<r2; i++)
        {
            if(tab[x][i]->getNum())
            {
                a += stod(tab[x][i]->getValue());
            }
        }

        avg->setValue(to_string(a/(this->not_empty(dim_choice, x))));
        return avg;
    }

    if(dim_choice == 2)
    {
        if(tab[0][x]->getNum())
        {
            for(int i = 0; i<r1; i++)
            {
                if(tab[i][x]->getNum())
                {
                    a += stod(tab[i][x]->getValue());
                }
            }

            avg->setValue(to_string(a/(this->not_empty(dim_choice, x))));
        }
        return avg;
    }
}
//*******************************************************************************************************************************************************************
double Sheet::not_empty(int dim_choice, int x)
{
    double counter = 0;

    if(dim_choice == 1)
    {
        for(int i = 0; i<r2; i++)
        {
            if(tab[x][i]->getNum())
            {
                if(stod(tab[x][i]->getValue()) != 0)
                {
                    counter++;
                }
            }
        }

        if(counter == 0)
        {
            return 1;
        }

        return counter;
    }

    if(dim_choice == 2)
    {
        for(int i = 0; i<r1; i++)
        {
            if(tab[i][x]->getNum())
            {
                if(stod(tab[i][x]->getValue()) != 0)
                {
                    counter++;
                }
            }
        }

        if(counter == 0)
        {
            return 1;
        }

        return counter;
    }
}
//*******************************************************************************************************************************************************************
