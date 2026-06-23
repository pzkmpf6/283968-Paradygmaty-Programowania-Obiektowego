#include "InterfejsUzytkownika.h"

const int MAX_LIST = 2;

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