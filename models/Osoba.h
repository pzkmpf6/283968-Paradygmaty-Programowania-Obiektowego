#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include "../interfaces/ISerializable.h"
using namespace std;

// -------------------------------------------------------

class Osoba : public ISerializable
{
protected:
    int wzrost;
    string dataUrodzenia;
    string imie;
    string nazwisko;

public:
    Osoba() : wzrost(0), dataUrodzenia("-"), imie(""), nazwisko("") {}
    virtual ~Osoba() {}

    string getNazwisko() { return nazwisko; }
    string getImie() { return imie; }
    int getWzrost() { return wzrost; }
    string getDataUrodzenia() { return dataUrodzenia; }

    void setWzrost(int w)
    {
        if (w > 50 && w < 250)
            wzrost = w;
        else
        {
            cout << "Blad: Niepoprawny wzrost!" << endl;
            wzrost = 0;
        }
    }

    void setDataUrodzenia(string d)
    {
        if (d.length() >= 4)
            dataUrodzenia = d;
        else
        {
            cout << "Blad: Za krotka data!" << endl;
            dataUrodzenia = "-";
        }
    }

    void setImie(string i)
    {
        if (i.length() >= 1)
            imie = i;
        else
            cout << "Blad: Imie musi miec co najmniej 1 znak!" << endl;
    }

    void setNazwisko(string n)
    {
        if (n.length() >= 1)
            nazwisko = n;
        else
            cout << "Blad: Nazwisko musi miec co najmniej 1 znak!" << endl;
    }

    virtual void drukuj()
    {
        cout << left
             << setw(8) << wzrost << " | "
             << setw(12) << dataUrodzenia << " | "
             << setw(12) << imie << " | "
             << setw(15) << nazwisko;
    }

    virtual string serialize()
    {
        return getImie() + " " + getNazwisko();
    }
};