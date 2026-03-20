#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

const int MAX = 10;

void dodajOsobe(string *tabN, string *tabI, int *tabInd, int &licznik, string n, string i, int ind) {
    if (licznik < MAX) {
        tabN[licznik] = n;
        tabI[licznik] = i;
        tabInd[licznik] = ind;
        licznik++;
    }
}
void ustawObecnosc(string *tabN, bool *tabO, int licznik, string nazwisko, bool obecnosc) {
    for (int i = 0; i < licznik; i++) {
        if (tabN[i] == nazwisko) {
            tabO[i] = obecnosc;
        }
    }
}
void usunOsobe(string *tabN, string *tabI, int *tabInd, bool *tabO, int &licznik, string nazwisko) {
    int doUsuniecia = -1;
    for (int i = 0; i < licznik; i++) {
        if (tabN[i] == nazwisko) {
            doUsuniecia = i;
            break;
        }
    }

    if (doUsuniecia != -1) {
        for (int i = doUsuniecia; i < licznik - 1; i++) {
            tabN[i] = tabN[i + 1];
            tabI[i] = tabI[i + 1];
            tabInd[i] = tabInd[i + 1];
            tabO[i] = tabO[i + 1];
        }
        licznik--;
    }
}
void drukujListe(string *tabN, string *tabI, int *tabInd, bool *tabO, int licznik) {
        if (licznik == 0) {
            cout << "\nLista jest pusta." << endl;
            return;
        }
        cout << "\n";
        cout << left << setw(8)  << "INDEKS"   << " | "
             << left << setw(15) << "IMIE"     << " | "
             << left << setw(15) << "NAZWISKO" << " | "
             << "OBECNOSC" << endl;
        cout << "------------------------------------------------------" << endl;
        for (int i = 0; i < licznik; i++) {
            cout << left << setw(8)  << tabInd[i] << " | "
                 << left << setw(15) << tabI[i]   << " | "
                 << left << setw(15) << tabN[i]   << " | "
                 << (tabO[i] ? "1" : "0") << endl;
        }
}
int main() {
    string *tabNazwisk = new string[MAX];
    string *tabImion = new string[MAX];
    int *tabIndeksow = new int[MAX];
    bool *tabObecnosci = new bool[MAX];

    int licznik = 0;
    int wybor = -1;

    while (wybor != 0) {
        cout << "\n1. Dodaj\n2. Ustaw obecnosc\n3. Usun\n4. Drukuj\n0. Wyjscie\nWybor: ";
        cin >> wybor;

        if (wybor == 1) {
            string n, i; int ind;
            cout << "Nazwisko: "; cin >> n;
            cout << "Imie: "; cin >> i;
            cout << "Indeks: "; cin >> ind;
            dodajOsobe(tabNazwisk, tabImion, tabIndeksow, licznik, n, i, ind);
        }
        else if (wybor == 2) {
            string n; int st;
            cout << "Podaj nazwisko: "; cin >> n;
            cout << "Obecnosc (1/0): "; cin >> st;
            ustawObecnosc(tabNazwisk, tabObecnosci, licznik, n, (st == 1));
        }
        else if (wybor == 3) {
            string n;
            cout << "Podaj nazwisko do usuniecia: "; cin >> n;
            usunOsobe(tabNazwisk, tabImion, tabIndeksow, tabObecnosci, licznik, n);
        }
        else if (wybor == 4) {
            drukujListe(tabNazwisk, tabImion, tabIndeksow, tabObecnosci, licznik);
        }
    }

    delete[] tabNazwisk; delete[] tabImion; delete[] tabIndeksow; delete[] tabObecnosci;
    return 0;
}