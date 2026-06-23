# 283968 — Paradygmaty Programowania Obiektowego

**Student:** Andrii Parashchuk | **Nr indeksu:** 283968  
Zajęcia laboratoryjne, gr. 2, PT TNP 7:30–9:00

---

## Co to jest

Program do prowadzenia listy obecności. Można dodawać studentów i pracowników, zaznaczać obecność i eksportować dane do TXT albo CSV.

## Jak uruchomić

```bash
g++ -Wall main.cpp -o lista
./lista
```

## Struktura projektu

```
models/
  Osoba.h          — klasa bazowa z imieniem, nazwiskiem itd.
  Student.h        — dziedziczy po Osoba
  Pracownik.h      — dziedziczy po Osoba
  ListaObecnosci.h — trzyma wskaźniki na osoby, zarządza obecnością
interfaces/
  ISerializable.h  — interfejs serializacji
  IEksportowalny.h — interfejs eksportu
  IExporter.h      — interfejs eksporterów
exporters/
  ExporterTxt.h    — eksport do TXT
  ExporterCsv.h    — eksport do CSV
InterfejsUzytkownika.h — pętla menu, cała interakcja z użytkownikiem
main.cpp
```

## Użyte koncepty

Dziedziczenie, polimorfizm, wzorzec Strategy, interfejsy (`ISerializable`, `IEksportowalny`), surowe wskaźniki (`new`/`delete`).
