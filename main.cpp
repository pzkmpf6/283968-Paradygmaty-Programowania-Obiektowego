#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

const int MAX_OSOB = 10;
const int MAX_LIST = 2;
class Osoba
{
private:
    int wzrost;
    string dataUrodzenia;
    int nr_indeksu;
    string imie;
    string nazwisko;

public:
    Osoba() : wzrost(0), dataUrodzenia("-"), nr_indeksu(0), imie(""), nazwisko("") {}

    string getNazwisko() { return nazwisko; }
    string getImie() { return imie; }
    int getNrIndeksu() { return nr_indeksu; }
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
    void setNrIndeksu(int ind)
    {
        if (ind > 0)
            nr_indeksu = ind;
        else
            cout << "Blad: Indeks musi byc wiekszy od 0!" << endl;
    }

    void drukuj()
    {
        cout << left
             << setw(8) << wzrost << " | "
             << setw(12) << dataUrodzenia << " | "
             << setw(8) << nr_indeksu << " | "
             << setw(12) << imie << " | "
             << setw(15) << nazwisko;
    }
};

// -------------------------------------------------------

class ListaObecnosci
{
private:
    Osoba **tablicaOsobWskazniki;
    bool *tablicaObecnosciBool;
    int licznik;
    int maxRozmiar;

public:
    ListaObecnosci()
        : tablicaOsobWskazniki(nullptr), tablicaObecnosciBool(nullptr),
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
        {
            cout << "Brak miejsca na liscie!" << endl;
        }
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
             << setw(8) << "INDEKS" << " | "
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
};

// -------------------------------------------------------

class InterfejsUzytkownika
{
private:
    Osoba *tabOsob;
    int iloscOsob, iloscList;
    ListaObecnosci *tabList;
    int licznikOsob;

    void dodajOsobe()
    {
        if (licznikOsob >= iloscOsob)
        {
            cout << "Baza pelna!" << endl;
            return;
        }
        int w, id;
        string d, i, n;
        cout << "Wzrost (cm): ";
        cin >> w;
        cout << "Data urodzenia (dd-mm-rrrr): ";
        cin >> d;
        cout << "Imie: ";
        cin >> i;
        cout << "Nazwisko: ";
        cin >> n;
        cout << "Nr indeksu: ";
        cin >> id;

        tabOsob[licznikOsob].setWzrost(w);
        tabOsob[licznikOsob].setDataUrodzenia(d);
        tabOsob[licznikOsob].setImie(i);
        tabOsob[licznikOsob].setNazwisko(n);
        tabOsob[licznikOsob].setNrIndeksu(id);
        licznikOsob++;
        cout << "Osoba dodana do bazy. (nr " << licznikOsob - 1 << ")" << endl;
    }

    void przypiszDoListy()
    {
        int idxO, idxL;
        cout << "Nr osoby w bazie (0-" << licznikOsob - 1 << "): ";
        cin >> idxO;
        cout << "Nr listy (0-" << iloscList - 1 << "): ";
        cin >> idxL;
        if (idxO >= 0 && idxO < licznikOsob && idxL >= 0 && idxL < iloscList)
        {
            tabList[idxL].dodajWskaznik(&tabOsob[idxO]);
            cout << "Przypisano." << endl;
        }
        else
        {
            cout << "Blad: Niepoprawny nr osoby lub listy." << endl;
        }
    }

    void ustawObecnosc()
    {
        int idxL;
        string naz;
        int st;
        cout << "Nr listy (0-" << iloscList - 1 << "): ";
        cin >> idxL;
        cout << "Nazwisko: ";
        cin >> naz;
        cout << "Obecnosc (1 - obecny, 0 - nieobecny): ";
        cin >> st;
        if (idxL >= 0 && idxL < iloscList)
        {
            tabList[idxL].ustawObecnosc(naz, st == 1);
        }
        else
        {
            cout << "Blad: Nie ma takiej listy." << endl;
        }
    }

    void usunZListy()
    {
        int idxL;
        string naz;
        cout << "Nr listy (0-" << iloscList - 1 << "): ";
        cin >> idxL;
        cout << "Nazwisko: ";
        cin >> naz;
        if (idxL >= 0 && idxL < iloscList)
        {
            tabList[idxL].usunZListy(naz);
        }
        else
        {
            cout << "Blad: Nie ma takiej listy." << endl;
        }
    }

    void edytujOsobe()
    {
        string naz;
        cout << "Nazwisko osoby do edycji: ";
        cin >> naz;
        for (int i = 0; i < licznikOsob; i++)
        {
            if (tabOsob[i].getNazwisko() == naz)
            {
                int nowyW, nowyInd;
                string nowaD, noweI, noweN;
                cout << "Nowy wzrost (cm): ";
                cin >> nowyW;
                cout << "Nowa data urodzenia: ";
                cin >> nowaD;
                cout << "Nowe imie: ";
                cin >> noweI;
                cout << "Nowe nazwisko: ";
                cin >> noweN;
                cout << "Nowy nr indeksu: ";
                cin >> nowyInd;
                tabOsob[i].setWzrost(nowyW);
                tabOsob[i].setDataUrodzenia(nowaD);
                tabOsob[i].setImie(noweI);
                tabOsob[i].setNazwisko(noweN);
                tabOsob[i].setNrIndeksu(nowyInd);
                cout << "Dane zaktualizowane (zmiana widoczna we wszystkich listach)." << endl;
                return;
            }
        }
        cout << "Nie znaleziono osoby w bazie." << endl;
    }

    void drukujWszystko()
    {
        for (int i = 0; i < iloscList; i++)
        {
            string nazwaListy = "LISTA OBECNOSCI " + to_string(i + 1);
            tabList[i].drukujListe(nazwaListy);
        }
    }

public:
    InterfejsUzytkownika(Osoba *to, int mo, ListaObecnosci *tl, int ml)
        : tabOsob(to), iloscOsob(mo), iloscList(ml), tabList(tl), licznikOsob(0)
    {
        for (int i = 0; i < iloscList; i++)
            tabList[i].inicjalizuj(iloscOsob);
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
    Osoba tablicaOsob[MAX_OSOB];
    ListaObecnosci tablicaList[MAX_LIST];

    InterfejsUzytkownika ui(tablicaOsob, MAX_OSOB, tablicaList, MAX_LIST);
    ui.petla();

    return 0;
}