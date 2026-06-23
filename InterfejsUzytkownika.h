#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "interfaces/ISerializable.h"
#include "interfaces/IEksportowalny.h"
#include "models/Student.h"
#include "models/Pracownik.h"
#include "models/ListaObecnosci.h"
#include "exporters/ExporterTxt.h"
#include "exporters/ExporterCsv.h"
using namespace std;

// -------------------------------------------------------

void drukuj(ISerializable *obj)
{
    cout << obj->serialize() << endl;
}

void zapiszDoPliku(ISerializable *obj, string nazwaPliku)
{
    ofstream plik;
    plik.open(nazwaPliku.c_str());
    if (!plik.is_open())
    {
        cout << "Blad: Nie mozna otworzyc pliku!" << endl;
        return;
    }
    plik << obj->serialize();
    plik.close();
    cout << "Zapisano do pliku: " << nazwaPliku << endl;
}

// -------------------------------------------------------

class InterfejsUzytkownika : public ISerializable
{
private:
    Student *tabStudentow;
    Pracownik *tabPracownikow;
    int iloscStudentow, iloscPracownikow;
    int licznikStudentow, licznikPracownikow;
    ListaObecnosci *tabList;
    int iloscList;

    void dodajOsobe()
    {
        int typ;
        cout << "Dodaj: 1-Student, 2-Pracownik: ";
        cin >> typ;
        int w;
        string d, im, naz;
        cout << "Wzrost (cm): ";
        cin >> w;
        cout << "Data urodzenia (dd-mm-rrrr): ";
        cin >> d;
        cout << "Imie: ";
        cin >> im;
        cout << "Nazwisko: ";
        cin >> naz;
        if (typ == 1)
        {
            if (licznikStudentow >= iloscStudentow)
            {
                cout << "Baza studentow pelna!" << endl;
                return;
            }
            int ind;
            cout << "Nr indeksu: ";
            cin >> ind;
            tabStudentow[licznikStudentow].setWzrost(w);
            tabStudentow[licznikStudentow].setDataUrodzenia(d);
            tabStudentow[licznikStudentow].setImie(im);
            tabStudentow[licznikStudentow].setNazwisko(naz);
            tabStudentow[licznikStudentow].setNrIndeksu(ind);
            licznikStudentow++;
            cout << "Student dodany (nr " << licznikStudentow << ")" << endl;
        }
        else if (typ == 2)
        {
            if (licznikPracownikow >= iloscPracownikow)
            {
                cout << "Baza pracownikow pelna!" << endl;
                return;
            }
            int id;
            cout << "ID pracownika: ";
            cin >> id;
            tabPracownikow[licznikPracownikow].setWzrost(w);
            tabPracownikow[licznikPracownikow].setDataUrodzenia(d);
            tabPracownikow[licznikPracownikow].setImie(im);
            tabPracownikow[licznikPracownikow].setNazwisko(naz);
            tabPracownikow[licznikPracownikow].setIdPracownika(id);
            licznikPracownikow++;
            cout << "Pracownik dodany (nr " << licznikPracownikow << ")" << endl;
        }
        else
            cout << "Nieznany typ osoby." << endl;
    }

    void przypiszDoListy()
    {
        int typ, idx, idxL;
        cout << "Typ: 1-Student, 2-Pracownik: ";
        cin >> typ;
        cout << "Nr osoby: ";
        cin >> idx;
        cout << "Nr listy (1-" << iloscList << "): ";
        cin >> idxL;
        idx--;
        idxL--;
        if (idxL < 0 || idxL >= iloscList)
        {
            cout << "Blad: Nie ma takiej listy." << endl;
            return;
        }
        if (typ == 1 && idx >= 0 && idx < licznikStudentow)
            tabList[idxL].dodajWskaznik(&tabStudentow[idx]);
        else if (typ == 2 && idx >= 0 && idx < licznikPracownikow)
            tabList[idxL].dodajWskaznik(&tabPracownikow[idx]);
        else
            cout << "Blad: Niepoprawny nr osoby." << endl;
    }

    void ustawObecnosc()
    {
        int idxL, st;
        string naz;
        cout << "Nr listy (1-" << iloscList << "): ";
        cin >> idxL;
        idxL--;
        cout << "Nazwisko: ";
        cin >> naz;
        cout << "Obecnosc (1-obecny, 0-nieobecny): ";
        cin >> st;
        if (idxL >= 0 && idxL < iloscList)
            tabList[idxL].ustawObecnosc(naz, st == 1);
        else
            cout << "Blad: Nie ma takiej listy." << endl;
    }

    void usunZListy()
    {
        int idxL;
        string naz;
        cout << "Nr listy (1-" << iloscList << "): ";
        cin >> idxL;
        idxL--;
        cout << "Nazwisko: ";
        cin >> naz;
        if (idxL >= 0 && idxL < iloscList)
            tabList[idxL].usunZListy(naz);
        else
            cout << "Blad: Nie ma takiej listy." << endl;
    }

    void edytujOsobe()
    {
        int typ;
        string naz;
        cout << "Edytuj: 1-Student, 2-Pracownik: ";
        cin >> typ;
        cout << "Nazwisko osoby do edycji: ";
        cin >> naz;
        if (typ == 1)
        {
            for (int i = 0; i < licznikStudentow; i++)
            {
                if (tabStudentow[i].getNazwisko() == naz)
                {
                    int w, ind;
                    string d, im, n;
                    cout << "Nowy wzrost: ";
                    cin >> w;
                    cout << "Nowa data ur.: ";
                    cin >> d;
                    cout << "Nowe imie: ";
                    cin >> im;
                    cout << "Nowe nazwisko: ";
                    cin >> n;
                    cout << "Nowy nr indeksu: ";
                    cin >> ind;
                    tabStudentow[i].setWzrost(w);
                    tabStudentow[i].setDataUrodzenia(d);
                    tabStudentow[i].setImie(im);
                    tabStudentow[i].setNazwisko(n);
                    tabStudentow[i].setNrIndeksu(ind);
                    cout << "Dane zaktualizowane." << endl;
                    return;
                }
            }
            cout << "Nie znaleziono studenta." << endl;
        }
        else if (typ == 2)
        {
            for (int i = 0; i < licznikPracownikow; i++)
            {
                if (tabPracownikow[i].getNazwisko() == naz)
                {
                    int w, id;
                    string d, im, n;
                    cout << "Nowy wzrost: ";
                    cin >> w;
                    cout << "Nowa data ur.: ";
                    cin >> d;
                    cout << "Nowe imie: ";
                    cin >> im;
                    cout << "Nowe nazwisko: ";
                    cin >> n;
                    cout << "Nowe ID pracownika: ";
                    cin >> id;
                    tabPracownikow[i].setWzrost(w);
                    tabPracownikow[i].setDataUrodzenia(d);
                    tabPracownikow[i].setImie(im);
                    tabPracownikow[i].setNazwisko(n);
                    tabPracownikow[i].setIdPracownika(id);
                    cout << "Dane zaktualizowane." << endl;
                    return;
                }
            }
            cout << "Nie znaleziono pracownika." << endl;
        }
    }

    void drukujWszystko()
    {
        for (int i = 0; i < iloscList; i++)
        {
            string nazwaListy = "LISTA OBECNOSCI " + to_string(i + 1);
            tabList[i].drukujListe(nazwaListy);
        }
    }

    void zapiszWybor()
    {
        int wybor;
        cout << "Co zapisac? 1-cala lista, 2-wybrana osoba: ";
        cin >> wybor;
        if (wybor == 1)
        {
            int idxL;
            cout << "Nr listy (1-" << iloscList << "): ";
            cin >> idxL;
            idxL--;
            if (idxL >= 0 && idxL < iloscList)
                zapiszDoPliku(&tabList[idxL], "lista.txt");
            else
                cout << "Blad: Nie ma takiej listy." << endl;
        }
        else if (wybor == 2)
        {
            string naz;
            cout << "Nazwisko osoby: ";
            cin >> naz;
            for (int i = 0; i < licznikStudentow; i++)
            {
                if (tabStudentow[i].getNazwisko() == naz)
                {
                    zapiszDoPliku(&tabStudentow[i], "osoba.txt");
                    return;
                }
            }
            for (int i = 0; i < licznikPracownikow; i++)
            {
                if (tabPracownikow[i].getNazwisko() == naz)
                {
                    zapiszDoPliku(&tabPracownikow[i], "osoba.txt");
                    return;
                }
            }
            cout << "Nie znaleziono osoby." << endl;
        }
        else
            cout << "Nieznana opcja." << endl;
    }

    void eksportujOsobe()
    {
        if (licznikStudentow == 0 && licznikPracownikow == 0)
        {
            cout << "Brak osob w bazie." << endl;
            return;
        }

        int typ;
        cout << "Eksportuj: 1-Student, 2-Pracownik, 3-Lista: ";
        cin >> typ;

        IEksportowalny *obj = nullptr;
        string domyslnaNazwa = "";

        if (typ == 1)
        {
            string naz;
            cout << "Nazwisko: ";
            cin >> naz;
            for (int i = 0; i < licznikStudentow; i++)
            {
                if (tabStudentow[i].getNazwisko() == naz)
                {
                    obj = &tabStudentow[i];
                    domyslnaNazwa = "student_" + naz;
                    break;
                }
            }
        }
        else if (typ == 2)
        {
            string naz;
            cout << "Nazwisko: ";
            cin >> naz;
            for (int i = 0; i < licznikPracownikow; i++)
            {
                if (tabPracownikow[i].getNazwisko() == naz)
                {
                    obj = &tabPracownikow[i];
                    domyslnaNazwa = "pracownik_" + naz;
                    break;
                }
            }
        }
        else if (typ == 3)
        {
            int idxL;
            cout << "Nr listy (1-" << iloscList << "): ";
            cin >> idxL;
            idxL--;
            if (idxL >= 0 && idxL < iloscList)
            {
                obj = &tabList[idxL];
                domyslnaNazwa = "lista_" + to_string(idxL + 1);
            }
            else
            {
                cout << "Blad: Nie ma takiej listy." << endl;
                return;
            }
        }

        if (obj == nullptr)
        {
            cout << "Nie znaleziono obiektu." << endl;
            return;
        }

        int format;
        cout << "Format: 1-TXT, 2-CSV: ";
        cin >> format;

        if (format == 1)
        {
            ExporterTxt eksporter;
            eksporter.wykonajEksport(obj, domyslnaNazwa + ".txt");
        }
        else if (format == 2)
        {
            ExporterCsv eksporter;
            eksporter.wykonajEksport(obj, domyslnaNazwa + ".csv");
        }
        else
            cout << "Nieznany format." << endl;
    }

public:
    InterfejsUzytkownika(Student *ts, int ms,
                         Pracownik *tp, int mp,
                         ListaObecnosci *tl, int ml)
        : tabStudentow(ts), tabPracownikow(tp),
          iloscStudentow(ms), iloscPracownikow(mp),
          licznikStudentow(0), licznikPracownikow(0),
          tabList(tl), iloscList(ml)
    {
        for (int i = 0; i < iloscList; i++)
            tabList[i].inicjalizuj(ms + mp);
    }

    string serialize()
    {
        string wynik = "";
        for (int i = 0; i < iloscList; i++)
            wynik += tabList[i].serialize();
        return wynik;
    }

    void petla()
    {
        int wybor = -1;
        while (wybor != 0)
        {
            cout << "\n*** MENU ***"
                 << "\n1. Dodaj osobe do bazy"
                 << "\n2. Przypisz osobe do listy"
                 << "\n3. Ustaw obecnosc"
                 << "\n4. Usun osobe z listy"
                 << "\n5. Edytuj dane osoby"
                 << "\n6. Drukuj wszystkie listy"
                 << "\n7. Zapisz do pliku"
                 << "\n8. Eksportuj"
                 << "\n0. Wyjscie"
                 << "\nWybor: ";
            cin >> wybor;

            switch (wybor)
            {
            case 1:
                dodajOsobe();
                break;
            case 2:
                przypiszDoListy();
                break;
            case 3:
                ustawObecnosc();
                break;
            case 4:
                usunZListy();
                break;
            case 5:
                edytujOsobe();
                break;
            case 6:
                drukujWszystko();
                break;
            case 7:
                zapiszWybor();
                break;
            case 8:
                eksportujOsobe();
                break;
            case 0:
                break;
            default:
                cout << "Nieznana opcja." << endl;
            }
        }
    }
};