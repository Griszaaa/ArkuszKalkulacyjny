/// @file

#include <iostream>
#include <fstream>
#include <string>
#include "operacje_na_plikach.h"
#include "tablica.h"

using namespace std;

//*******************************************************************************************************************************************************************
bool Sheet::read(string file_name)
{
    ifstream(sheet_read);
    sheet_read.open(file_name);
    if(sheet_read.good())
    {
        int verses = 0;
        int columns = 0;

        string value;

        sheet_read >> verses;
        sheet_read >> columns;
        int *cType = new int[columns];

        for(int i = 0; i<columns; i++)
        {
            sheet_read >> cType[i];
        }

        Cell ***tab = create_tab(verses, columns, cType);

        for(int i = 0; i<verses; i++)
        {
            for(int j = 0; j<columns; j++)
            {
                sheet_read >> value;
                if(tab[i][j]->getNum())
                {
                    tab[i][j]->setValue(value);
                }
                else
                {
                    tab[i][j]->setValue(value);
                }
            }
        }
        sheet_read.close();

        this->update_tabsize(verses, columns, cType);

        copy_tab(this->tab, tab, r1, r2);

        for(int i = 0; i<verses; i++)
        {
            delete [] tab[i];
        }
        delete [] tab;

        return 1;
    }

    return 0;
}
//*******************************************************************************************************************************************************************
bool Sheet::write(string file_name)
{
    ofstream(sheet_write);
    sheet_write.open(file_name);

    sheet_write << r1 << endl;
    sheet_write << r2 << endl;

    for(int i = 0; i<r2; i++)
    {
        if(tab[0][i]->getNum())
        {
            sheet_write << 0 << endl;
        }
        else
        {
            sheet_write << 1 << endl;
        }
    }

    for(int i = 0; i<r1; i++)
    {
        for(int j = 0; j<r2; j++)
        {
            sheet_write << tab[i][j]->getValue()<< "\t";
        }
        sheet_write << endl;
    }
    sheet_write.close();

    return 1;
}
//*******************************************************************************************************************************************************************
bool del(string file_name)
{
    const char *file_del = file_name.c_str();
    if(remove(file_del) == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
//*******************************************************************************************************************************************************************


