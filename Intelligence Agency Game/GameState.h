#pragma once
#include <vector>
#include <queue>
#include <memory>
#include "ProcesDeszyfrowania.h"
#include "Staff.h"
#include "Stol.h"
#include "Misja.h"
#include "CountriesEnums.h"
#include <atomic>

/// <summary>
/// Struktura grupująca dane o pracownikach gracza oraz ofertach dostępnych na rynku pracy
/// </summary>
struct SektorKadr {

    /// <summary>Kontener pracowników aktualnie zatrudnionych (będących w posiadaniu gracza)</summary>
    std::vector<std::unique_ptr<Staff>> pracownicy;

    /// <summary>Kontener pracowników dostępnych do kupienia w sklepie</summary>
    std::vector<std::unique_ptr<Staff>> rynekPracy;
};

/// <summary>
/// Struktura przechowująca informacje o bieżących zadaniach: sygnałach, procesach deszyfrowania i misjach
/// </summary>
struct SektorZadan {

    /// <summary>Złapane transakcje sygnałowe przekazywane do sceny sztabu</summary>
    std::vector<int> transakcjeSygnalowe;

    /// <summary>Aktualnie trwające procesy łamania szyfrów. W przyszłości podstawa do generacji misji.</summary>
    std::vector<ProcesDeszyfrowania> aktywnaDeszyfracja;

    /// <summary>Kolejka przechowująca identyfikatory misji oczekujących na wygenerowanie na mapie</summary>
    std::queue<int> missjeDoWygenerowania;

    /// <summary>Kontener aktualnie aktywnych misji</summary>
    std::vector<Misja> aktywneMisje;
};

/// <summary>
/// Struktura przechowująca obiekty z warstwy wizualnej/logicznej, z którymi można wchodzić w interakcję
/// </summary>
struct SektorSprite {

    /// <summary>Lista stołów w sztabie dostępnych do przypisywania pracowników</summary>
    std::vector<Stol> stoly;
};

/// <summary>
/// Główna klasa przechowująca globalny stan gry 
/// Zarządza budżetem, kadrami, postępem zadań oraz komunikacją z UI
/// </summary>
class GameState {
private:
    SektorKadr staff;
    SektorZadan zadania;
    SektorSprite sprites;

    bool UIrefreshStaff = false;
    bool UIrefreshMission = false;

    std::queue<SztabReport> sztab_reports_queue;

    int bank = 10000000;

    int wybranyPracownik = -1;

public:

    /// <summary>Zmienna atomowa określająca, czy aktualnie trwa jakaś misja (dla środowiska wielowątkowego)</summary>
    std::atomic<bool> missionInProgress{ false };

    void requestRefreshStaff() { UIrefreshStaff = true; }
    bool shouldRefreshStaff() const { return UIrefreshStaff; }
    void clearRefreshStaff() { UIrefreshStaff = false; }

    void requestRefreshMission() { UIrefreshMission = true; }
    bool shouldRefreshMission() const { return UIrefreshMission; }
    void clearRefreshMission() { UIrefreshMission = false; }

    /// <summary>Dodaje nowy raport ze sztabu do kolejki powiadomień</summary>
    void addReport(const SztabReport& report)
    {
        sztab_reports_queue.push(report);
    }

    bool sztab_queue_has_reports() const
    {
        return !sztab_reports_queue.empty();
    }

    /// <summary>Pobiera i usuwa z kolejki najstarszy raport wygenerowany przez sztab (zasada FIFO)</summary>
    const SztabReport take_out_sztab_report()
    {
        SztabReport fifo_report = sztab_reports_queue.front();
        sztab_reports_queue.pop();
        return fifo_report;
    }

    void dodajDane(int t);

    const std::vector<int>& podgladSygnalow() const { return zadania.transakcjeSygnalowe; }

    void setWybranyPracownik(int index) { wybranyPracownik = index; }
    int getWybranyPracownik() const { return wybranyPracownik; }
    void resetWybranyPracownik() { wybranyPracownik = -1; }

    /// <summary>Przenosi zatrudnionego pracownika do zasobów gracza</summary>
    void dodajPracownika(std::unique_ptr<Staff> nowyPracownik);

    /// <summary>Sortuje listę aktualnych pracowników gracza</summary>
    void sortWorkers();

    Staff* pobierzOferte(int ktory) const;

    const std::vector<std::unique_ptr<Staff>>& getPracownicy() const {
        return staff.pracownicy;
    }

    Staff* getPracownik(int index) const {
        if (index >= 0 && index < staff.pracownicy.size()) {
            return staff.pracownicy[index].get();
        }
        return nullptr;
    }

    std::vector<Stol>& getStoly() {
        return sprites.stoly;
    }

    void dodajStol(Stol&& nowy);
    void setStolXY(const sf::Vector2f& pos, int idx);

    /// <summary>Dodaje nowo wygenerowaną ofertę pracownika na rynek (do sklepu)</summary>
    void dodajOferte(std::unique_ptr<Staff> nowaOferta);

    /// <summary>Wycofuje ofertę pracownika z rynku (np. po jego zakupieniu lub odrzuceniu)</summary>
    std::unique_ptr<Staff> wyjmijOferte(int index);

    const std::vector<std::unique_ptr<Staff>>& getRynekPracy() const {
        return staff.rynekPracy;
    }

    /// <summary>Rejestruje nowy proces deszyfrowania w logice sztabu</summary>
    void dodajAktywnySzyfr(const ProcesDeszyfrowania& nowySzyfr);

    void usunSzyfr(int index) {
        if (index >= 0 && index < zadania.aktywnaDeszyfracja.size()) {
            zadania.aktywnaDeszyfracja.erase(zadania.aktywnaDeszyfracja.begin() + index);
        }
    }

    std::vector<ProcesDeszyfrowania>& getAktywneSzyfry() {
        return zadania.aktywnaDeszyfracja;
    }

    const std::vector<ProcesDeszyfrowania>& getAktywnySzyfry(int i) const {
        return zadania.aktywnaDeszyfracja;
    }

    /// <summary>Zwalnia i zwraca pracownika o danym indeksie z zespołu gracza</summary>
    std::unique_ptr<Staff> wyjmijPracownika(int index);

    /// <summary>Zwraca aktualny stan finansowy gracza</summary>
    int getBank()const& { return bank; }
    void setBank(int _bank) { bank = _bank; }
    void addBank(int amount) { bank += amount; }

    /// <summary>Sprawdza, czy gracz posiada wystarczającą ilość gotówki</summary>
    /// <param name="amount">Kwota do sprawdzenia.</param>
    bool checkMoney(int amount) { return (bank >= amount); }

    void wpiszMisjeDoWygenerowania(int dane)
    {
        zadania.missjeDoWygenerowania.push(dane);
    }

    std::queue<int>& getMisjeDoWygenerowania() { return zadania.missjeDoWygenerowania; }

    /// <summary>Tworzy nową misję i dodaje ją do puli aktywnych misji na mapie</summary>
    void addMisja(std::string miasto, Country kraj, sf::Vector2f pozycja);

    std::vector<Misja>& getAktywneMisje() { return zadania.aktywneMisje; }

    /// <summary>Czyści stare/przetworzone sygnały w Sektorze Zadań</summary>
    void cleanS();
};