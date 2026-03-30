#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

const int MAX = 10;

class Osoba {
private:
    int wzrost;
    string dataUrodzenia;
    int nr_indeksu;
    string imie;
    string nazwisko;

public:
    Osoba();
    Osoba(int w, string d, string i, string n, int ind);

    int getWzrost();
    string getDataUrodzenia();
    string getNazwisko();
    string getImie();
    int getNrIndeksu();

    void setWzrost(int wartosc);
    void setDataUrodzenia(string wartosc);
    void setNazwisko(string wartosc);
    void setImie(string wartosc);
    void setNrIndeksu(int wartosc);
};

Osoba::Osoba() {
    wzrost = 0;
    dataUrodzenia = "-";
    imie = "";
    nazwisko = "";
    nr_indeksu = 0;
}

Osoba::Osoba(int w, string d, string i, string n, int ind) {
    setWzrost(w);
    setDataUrodzenia(d);
    setImie(i);
    setNazwisko(n);
    setNrIndeksu(ind);
}

int Osoba::getWzrost() { return wzrost; }
string Osoba::getDataUrodzenia() { return dataUrodzenia; }
string Osoba::getNazwisko() { return nazwisko; }
string Osoba::getImie() { return imie; }
int Osoba::getNrIndeksu() { return nr_indeksu; }

void Osoba::setWzrost(int wartosc) {
    if (wartosc > 50 && wartosc < 250) { wzrost = wartosc; }
    else { cout << "Blad: Niepoprawny wzrost! Ustawiono 0." << endl; wzrost = 0; }
}

void Osoba::setDataUrodzenia(string wartosc) {
    if (wartosc.length() >= 4) { dataUrodzenia = wartosc; }
    else { cout << "Blad: Za krotka data! Ustawiono domyslna." << endl; dataUrodzenia = "-"; }
}

void Osoba::setImie(string wartosc) {
    if (wartosc.length() >= 1) { imie = wartosc; }
    else { cout << "Blad: Imie musi miec co najmniej 1 znak!" << endl; }
}

void Osoba::setNazwisko(string wartosc) {
    if (wartosc.length() >= 1) { nazwisko = wartosc; }
    else { cout << "Blad: Nazwisko musi miec co najmniej 1 znak!" << endl; }
}

void Osoba::setNrIndeksu(int wartosc) {
    if (wartosc > 0) { nr_indeksu = wartosc; }
    else { cout << "Blad: Indeks musi byc > 0!" << endl; }
}

class ListaObecnosci {
private:
    Osoba** tablicaOsobWskazniki;
    bool* tablicaObecnosciBool;
    int licznik;
    int maxRozmiar;

public:
    ListaObecnosci(int rozmiar) {
        maxRozmiar = rozmiar;
        licznik = 0;
        tablicaOsobWskazniki = new Osoba*[maxRozmiar];
        tablicaObecnosciBool = new bool[maxRozmiar];
        for(int i = 0; i < maxRozmiar; i++) tablicaObecnosciBool[i] = false;
    }

    ~ListaObecnosci() {
        delete[] tablicaOsobWskazniki;
        delete[] tablicaObecnosciBool;
    }

    void dodajWskaznik(Osoba* s) {
        if (licznik < maxRozmiar) {
            tablicaOsobWskazniki[licznik] = s;
            tablicaObecnosciBool[licznik] = false;
            licznik++;
        }
    }

    void ustawObecnosc(string nazwisko, bool presence) {
        for (int i = 0; i < licznik; i++) {
            if (tablicaOsobWskazniki[i]->getNazwisko() == nazwisko) {
                tablicaObecnosciBool[i] = presence;
                return;
            }
        }
        cout << "Nie znaleziono studenta na tej liscie." << endl;
    }

    void usunWskaznikBySurname(string nazwisko) {
        int doUsuniecia = -1;
        for (int i = 0; i < licznik; i++) {
            if (tablicaOsobWskazniki[i]->getNazwisko() == nazwisko) {
                doUsuniecia = i;
                break;
            }
        }
        if (doUsuniecia != -1) {
            for (int i = doUsuniecia; i < licznik - 1; i++) {
                tablicaOsobWskazniki[i] = tablicaOsobWskazniki[i+1];
                tablicaObecnosciBool[i] = tablicaObecnosciBool[i+1];
            }
            licznik--;
        }
    }

    Osoba* getWskaznikBySurname(string nazwisko) {
        for (int i = 0; i < licznik; i++) {
            if (tablicaOsobWskazniki[i]->getNazwisko() == nazwisko) {
                return tablicaOsobWskazniki[i];
            }
        }
        return nullptr;
    }

    void drukujListe(string nazwaListy) {
        if (licznik == 0) {
            cout << "\n--- " << nazwaListy << ": Pusta ---" << endl;
            return;
        }
        cout << "\n--- " << nazwaListy << " ---" << endl;
        cout << left << setw(8)  << "WZROST"   << " | "
             << left << setw(12) << "DATA UR." << " | "
             << left << setw(8)  << "INDEKS"   << " | "
             << left << setw(15) << "IMIE"     << " | "
             << left << setw(15) << "NAZWISKO" << " | "
             << "OBECNOSC" << endl;
        cout << "----------------------------------------------------------------------------" << endl;
        for (int i = 0; i < licznik; i++) {
            Osoba* current = tablicaOsobWskazniki[i];
            cout << left << setw(8)  << current->getWzrost()         << " | "
                 << left << setw(12) << current->getDataUrodzenia()  << " | "
                 << left << setw(8)  << current->getNrIndeksu()      << " | "
                 << left << setw(15) << current->getImie()           << " | "
                 << left << setw(15) << current->getNazwisko()       << " | "
                 << (tablicaObecnosciBool[i] ? "1" : "0") << endl;
        }
    }
};

int main() {
    Osoba* mainRegistry[MAX];
    for(int i = 0; i < MAX; i++) mainRegistry[i] = nullptr;
    int mainLicznik = 0;

    ListaObecnosci lista1(MAX);
    ListaObecnosci lista2(MAX);

    int wybor = -1;

    while (wybor != 0) {
        cout << "\n*** GLOWNE MENU ***\n"
             << "1. Dodaj nowego studenta (do Listy 1)\n"
             << "2. Ustaw obecnosc (wybierz liste)\n"
             << "3. Usun studenta z systemu (z obu list)\n"
             << "4. Edytuj dane studenta (aktualizacja globalna)\n"
             << "5. Drukuj obie listy\n"
             << "6. Kopiuj wkaznik studenta z Listy 1 do Listy 2\n"
             << "0. Wyjscie\n"
             << "Wybor: ";
        cin >> wybor;

        if (wybor == 1) {
            if (mainLicznik < MAX) {
                int w, ind; string d, n, i;
                cout << "Wzrost (cm): "; cin >> w;
                cout << "Data urodzenia (np. 01-01-2000): "; cin >> d;
                cout << "Nazwisko: "; cin >> n;
                cout << "Imie: "; cin >> i;
                cout << "Indeks: "; cin >> ind;

                Osoba* dynamicznaOsoba = new Osoba(w, d, i, n, ind);
                mainRegistry[mainLicznik++] = dynamicznaOsoba;
                lista1.dodajWskaznik(dynamicznaOsoba);
                cout << "Dodano studenta!" << endl;
            } else {
                cout << "Brak miejsca w systemie!" << endl;
            }
        }
        else if (wybor == 2) {
            int nrListy;
            cout << "W ktorej liscie ustawic obecnosc? (1 lub 2): ";
            cin >> nrListy;

            if (nrListy == 1 || nrListy == 2) {
                string n; int st;
                cout << "Podaj nazwisko: "; cin >> n;
                cout << "Obecnosc (1 - obecny, 0 - nieobecny): "; cin >> st;

                if (nrListy == 1) { lista1.ustawObecnosc(n, (st == 1)); }
                if (nrListy == 2) { lista2.ustawObecnosc(n, (st == 1)); }
                cout << "Zaktualizowano obecnosc w Liscie " << nrListy << "!" << endl;
            } else {
                cout << "Blad: Nie ma takiej listy." << endl;
            }
        }
        else if (wybor == 3) {
            string stareN;
            cout << "Podaj nazwisko do usuniecia: "; cin >> stareN;

            lista1.usunWskaznikBySurname(stareN);
            lista2.usunWskaznikBySurname(stareN);

            for(int i = 0; i < mainLicznik; i++) {
                if(mainRegistry[i]->getNazwisko() == stareN) {
                    delete mainRegistry[i];
                    for (int j = i; j < mainLicznik - 1; j++) { mainRegistry[j] = mainRegistry[j+1]; }
                    mainRegistry[--mainLicznik] = nullptr;
                    cout << "Student usuniety z systemu." << endl;
                    break;
                }
            }
        }
        else if (wybor == 4) {
            string stareN;
            cout << "Podaj nazwisko osoby do edycji: "; cin >> stareN;

            Osoba* target = nullptr;
            for(int i = 0; i < mainLicznik; i++) {
                if(mainRegistry[i]->getNazwisko() == stareN) {
                    target = mainRegistry[i];
                    break;
                }
            }
            if (target != nullptr) {
                int noweW, nowyInd; string nowaD, noweN, noweI;
                cout << "Podaj nowy wzrost (cm): "; cin >> noweW;
                cout << "Podaj nowa date urodzenia: "; cin >> nowaD;
                cout << "Podaj nowe nazwisko: "; cin >> noweN;
                cout << "Podaj nowe imie: "; cin >> noweI;
                cout << "Podaj nowy indeks: "; cin >> nowyInd;

                target->setWzrost(noweW);
                target->setDataUrodzenia(nowaD);
                target->setNazwisko(noweN);
                target->setImie(noweI);
                target->setNrIndeksu(nowyInd);
                cout << "Zaktualizowano dane we wszystkich listach!" << endl;
            } else {
                cout << "Nie znaleziono studenta." << endl;
            }
        }
        else if (wybor == 5) {
            lista1.drukujListe("LISTA OBECNOSCI 1");
            lista2.drukujListe("LISTA OBECNOSCI 2");
        }
        else if (wybor == 6) {
            string stareN;
            cout << "Podaj nazwisko studenta z Listy 1 do skopiowania do Listy 2: "; cin >> stareN;
            Osoba* studentInList1 = lista1.getWskaznikBySurname(stareN);

            if (studentInList1 != nullptr) {
                lista2.dodajWskaznik(studentInList1);
                cout << "Student skopiowany do Listy 2!" << endl;
            } else {
                cout << "Nie znaleziono takiego studenta w Liscie 1!" << endl;
            }
        }
    }

    for(int i = 0; i < mainLicznik; i++) delete mainRegistry[i];

    return 0;
}