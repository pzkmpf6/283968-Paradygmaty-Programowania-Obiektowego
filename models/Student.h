#pragma once
#include <string>
#include <map>
#include "Osoba.h"
#include "../interfaces/IEksportowalny.h"
using namespace std;

// -------------------------------------------------------

class Student : public Osoba, public IEksportowalny
{
private:
    int nr_indeksu;

public:
    Student() : Osoba(), nr_indeksu(0) {}

    int getNrIndeksu() { return nr_indeksu; }

    void setNrIndeksu(int ind)
    {
        if (ind > 0)
            nr_indeksu = ind;
        else
            cout << "Blad: Indeks musi byc wiekszy od 0!" << endl;
    }

    void drukuj()
    {
        Osoba::drukuj();
        cout << " | ind: " << nr_indeksu;
    }

    string serialize()
    {
        string pelneNazwisko = getImie() + " " + getNazwisko();
        int dlugosc = (int)pelneNazwisko.length();
        int odstep = (dlugosc < 22) ? (22 - dlugosc) : 1;
        return "[ Student   ]  " + pelneNazwisko +
               string(odstep, ' ') +
               "ind: " + to_string(getNrIndeksu());
    }

    map<string, string> eksportuj()
    {
        map<string, string> dane;
        dane["typ"] = "Student";
        dane["imie"] = getImie();
        dane["nazwisko"] = getNazwisko();
        dane["nr_indeksu"] = to_string(getNrIndeksu());
        return dane;
    }
};