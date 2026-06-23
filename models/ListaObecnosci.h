#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include "../interfaces/ISerializable.h"
#include "../interfaces/IEksportowalny.h"
#include "Osoba.h"
using namespace std;

// -------------------------------------------------------

class ListaObecnosci : public ISerializable, public IEksportowalny
{
private:
    Osoba **tablicaOsobWskazniki;
    bool *tablicaObecnosciBool;
    int licznik;
    int maxRozmiar;

public:
    ListaObecnosci() : tablicaOsobWskazniki(nullptr), tablicaObecnosciBool(nullptr),
                       licznik(0), maxRozmiar(0) {}

    void inicjalizuj(int rozmiar)
    {
        maxRozmiar = rozmiar;
        tablicaOsobWskazniki = new Osoba *[maxRozmiar];
        tablicaObecnosciBool = new bool[maxRozmiar];
        for (int i = 0; i < maxRozmiar; i++)
            tablicaObecnosciBool[i] = false;
    }

    ~ListaObecnosci()
    {
        delete[] tablicaOsobWskazniki;
        delete[] tablicaObecnosciBool;
    }

    void dodajWskaznik(Osoba *s)
    {
        if (licznik < maxRozmiar)
        {
            tablicaOsobWskazniki[licznik] = s;
            tablicaObecnosciBool[licznik] = false;
            licznik++;
        }
        else
            cout << "Brak miejsca na liscie!" << endl;
    }

    void ustawObecnosc(string nazwisko, bool obecnosc)
    {
        for (int i = 0; i < licznik; i++)
        {
            if (tablicaOsobWskazniki[i]->getNazwisko() == nazwisko)
            {
                tablicaObecnosciBool[i] = obecnosc;
                return;
            }
        }
        cout << "Nie znaleziono osoby na tej liscie." << endl;
    }

    void usunZListy(string nazwisko)
    {
        for (int i = 0; i < licznik; i++)
        {
            if (tablicaOsobWskazniki[i]->getNazwisko() == nazwisko)
            {
                for (int j = i; j < licznik - 1; j++)
                {
                    tablicaOsobWskazniki[j] = tablicaOsobWskazniki[j + 1];
                    tablicaObecnosciBool[j] = tablicaObecnosciBool[j + 1];
                }
                licznik--;
                cout << "Usunieto osobe z listy." << endl;
                return;
            }
        }
        cout << "Nie znaleziono osoby na tej liscie." << endl;
    }

    void drukujListe(string nazwaListy)
    {
        cout << "\n--- " << nazwaListy << " ---" << endl;
        if (licznik == 0)
        {
            cout << "Pusta." << endl;
            return;
        }
        cout << left
             << setw(8) << "WZROST" << " | "
             << setw(12) << "DATA UR." << " | "
             << setw(12) << "IMIE" << " | "
             << setw(15) << "NAZWISKO" << " | "
             << "OBECNOSC" << endl;
        cout << string(75, '-') << endl;
        for (int i = 0; i < licznik; i++)
        {
            tablicaOsobWskazniki[i]->drukuj();
            cout << " | " << (tablicaObecnosciBool[i] ? "OBECNY" : "NIEOBECNY") << endl;
        }
    }

    string serialize()
    {
        string linia = string(48, '=') + "\n";
        string wynik = linia;
        wynik += "        LISTA OBECNOSCI\n";
        wynik += linia;
        int obecnych = 0;
        for (int i = 0; i < licznik; i++)
        {
            string status = tablicaObecnosciBool[i] ? "[ OBECNY    ]" : "[ NIEOBECNY ]";
            wynik += status + "  " + tablicaOsobWskazniki[i]->serialize() + "\n";
            if (tablicaObecnosciBool[i])
                obecnych++;
        }
        wynik += linia;
        wynik += "Obecnych: " + to_string(obecnych) + " / " + to_string(licznik) + "\n";
        wynik += linia;
        return wynik;
    }

    map<string, string> eksportuj()
    {
        map<string, string> dane;
        dane["typ"] = "ListaObecnosci";
        dane["licznik"] = to_string(licznik);
        int obecnych = 0;
        for (int i = 0; i < licznik; i++)
            if (tablicaObecnosciBool[i])
                obecnych++;
        dane["obecnych"] = to_string(obecnych);
        return dane;
    }
};