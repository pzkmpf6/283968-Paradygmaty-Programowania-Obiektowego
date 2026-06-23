#pragma once
#include <string>
#include <map>
#include "Osoba.h"
#include "../interfaces/IEksportowalny.h"
using namespace std;

// -------------------------------------------------------

class Pracownik : public Osoba, public IEksportowalny
{
private:
    int id_pracownika;

public:
    Pracownik() : Osoba(), id_pracownika(0) {}

    int getIdPracownika() { return id_pracownika; }

    void setIdPracownika(int id)
    {
        if (id > 0)
            id_pracownika = id;
        else
            cout << "Blad: ID musi byc wieksze od 0!" << endl;
    }

    void drukuj()
    {
        Osoba::drukuj();
        cout << " | id: " << id_pracownika;
    }

    string serialize()
    {
        string pelneNazwisko = getImie() + " " + getNazwisko();
        int dlugosc = (int)pelneNazwisko.length();
        int odstep = (dlugosc < 22) ? (22 - dlugosc) : 1;
        return "[ Pracownik ]  " + pelneNazwisko +
               string(odstep, ' ') +
               "id:  " + to_string(getIdPracownika());
    }

    map<string, string> eksportuj()
    {
        map<string, string> dane;
        dane["typ"] = "Pracownik";
        dane["imie"] = getImie();
        dane["nazwisko"] = getNazwisko();
        dane["id_pracownika"] = to_string(getIdPracownika());
        return dane;
    }
};