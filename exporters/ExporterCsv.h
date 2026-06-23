#pragma once
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include "../interfaces/IExporter.h"
using namespace std;

// -------------------------------------------------------

class ExporterCsv : public IExporter
{
public:
    void wykonajEksport(IEksportowalny *obj, string nazwaPliku)
    {
        map<string, string> dane = obj->eksportuj();
        ofstream plik;
        plik.open(nazwaPliku.c_str());
        if (!plik.is_open())
        {
            cout << "Blad: Nie mozna otworzyc pliku!" << endl;
            return;
        }
        string naglowki = "";
        string wartosci = "";
        for (map<string, string>::iterator it = dane.begin(); it != dane.end(); ++it)
        {
            if (naglowki != "")
            {
                naglowki += ", ";
                wartosci += ", ";
            }
            naglowki += it->first;
            wartosci += it->second;
        }
        plik << naglowki << "\n"
             << wartosci << "\n";
        plik.close();
        cout << "Zapisano CSV: " << nazwaPliku << endl;
    }
};