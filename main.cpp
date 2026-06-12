#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <map>

using namespace std;

const int MAX_LIST = 2;

// -------------------------------------------------------

class ISerializable
{
public:
    virtual string serialize() = 0;
    virtual ~ISerializable() {}
};

// -------------------------------------------------------

class IEksportowalny
{
public:
    virtual map<string, string> eksportuj() = 0;
    virtual ~IEksportowalny() {}
};

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
        dane["nr_indeksu"] = to_string(getNrIndeksu());
        return dane;
    }
};

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
        dane["id_pracownika"] = to_string(getIdPracownika());
        return dane;
    }
};

// -------------------------------------------------------

class ListaObecnosci : public ISerializable
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
};

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

class IExporter
{
public:
    virtual void wykonajEksport(IEksportowalny *obj, string nazwaPliku) = 0;
    virtual ~IExporter() {}
};

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
        cout << "Eksportuj: 1-Student, 2-Pracownik: ";
        cin >> typ;

        string naz;
        cout << "Nazwisko: ";
        cin >> naz;

        IEksportowalny *obj = nullptr;
        string domyslnaNazwa = "";

        if (typ == 1)
        {
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

        if (obj == nullptr)
        {
            cout << "Nie znaleziono osoby." << endl;
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
                 << "\n8. Eksportuj osobe"
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

// -------------------------------------------------------

int main()
{
    const int MAX_ST = 10;
    const int MAX_PR = 10;

    Student tablicaStudentow[MAX_ST];
    Pracownik tablicaPracownikow[MAX_PR];
    ListaObecnosci tablicaList[MAX_LIST];

    InterfejsUzytkownika ui(
        tablicaStudentow, MAX_ST,
        tablicaPracownikow, MAX_PR,
        tablicaList, MAX_LIST);
    ui.petla();

    return 0;
}