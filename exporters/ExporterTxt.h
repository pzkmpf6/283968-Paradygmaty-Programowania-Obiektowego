#pragma once
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include "../interfaces/IExporter.h"
using namespace std;

// -------------------------------------------------------

class ExporterTxt : public IExporter
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
        map<string, string>::iterator it;
        for (it = dane.begin(); it != dane.end(); ++it)
            plik << it->first << ": " << it->second << "  ";
        plik << "\n";
        plik.close();
        cout << "Zapisano TXT: " << nazwaPliku << endl;
    }
};