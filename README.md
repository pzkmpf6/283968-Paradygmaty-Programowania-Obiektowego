# Paradygmaty Programowania Obiektowego

Laborki z PPO, gr. 2, piątek 7:30. Projekt zaliczeniowy.

## Co to jest

Program do prowadzenia listy obecności. Można dodawać studentów i pracowników, zaznaczać obecność i eksportować dane do TXT albo CSV. Nic więcej.

## Jak uruchomić

```bash
g++ -Wall main.cpp -o lista
./lista
```

## Struktura projektu

- `Osoba` — klasa bazowa z imieniem, nazwiskiem itd.
- `Student`, `Pracownik` — dziedziczą po `Osoba`
- `ListaObecnosci` — trzyma wskaźniki na osoby i zarządza obecnością
- `InterfejsUzytkownika` — pętla menu, cała interakcja z użytkownikiem
- `ExporterTxt`, `ExporterCsv` — eksport danych, wzorzec Strategy

## Użyte koncepty

Dziedziczenie, polimorfizm, wzorzec Strategy, interfejsy (`ISerializable`, `IEksportowalny`), surowe wskaźniki (`new`/`delete`).
