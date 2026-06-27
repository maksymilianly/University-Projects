#pragma once
#include "Staff.h"
#include <concepts>
#include <random>
#include <vector>
#include <memory>
#include <cmath>
#include "GameState.h"

import AssetsMod;
import ConfigMod;

/// <summary>
/// Klasa logiczna odpowiedzialna za zarządzanie kadrami: generowanie nowych ofert pracy, 
/// obsługę transakcji zakupu oraz zarządzanie pulą dostępnych pracowników
/// </summary>
class StaffLogic {
private:
    Assets& assets;
    Config& config;
    GameState& state;

public:
    /// <summary>
    /// Inicjalizuje logikę kadr
    /// </summary>
    /// <param name="assets">Referencja do menedżera zasobów</param>
    /// <param name="config">Referencja do konfiguracji (np. listy imion)</param>
    /// <param name="state">Referencja do globalnego stanu gry (przechowuje rynek pracy)</param>
    StaffLogic(Assets& assets, Config& config, GameState& state);

    /// <summary>
    /// Obsługuje proces zakupu pracownika z rynku pracy
    /// </summary>
    /// <param name="index">Indeks pracownika na liście ofert</param>
    /// <returns>Unikalny wskaźnik do zakupionego pracownika</returns>
    std::unique_ptr<Staff> buyPracownik(int index);

    /// <summary>
    /// Usuwa ofertę z rynku pracy
    /// </summary>
    /// <param name="ktory">Indeks oferty</param>
    /// <param name="czyUsun">Jeśli true, usuwa obiekt; jeśli false, może tylko wycofać</param>
    void usunOferte(int ktory, bool czyUsun);

    /// <summary>
    /// Dodaje nowo wygenerowany obiekt typu Staff do puli ofert w GameState
    /// Wymusza, aby obiekt dziedziczył po klasie Staff
    /// </summary>
    /// <typeparam name="T">Typ pracownika (Agent lub Grupa)</typeparam>
    template <std::derived_from<Staff> T>
    void dodajDoPuli(T obiekt)
    {
        auto nowy = std::make_unique<T>(std::move(obiekt));
        state.dodajOferte(std::move(nowy));
    }

    /// <summary>
    /// Szablon metody generującej nowego pracownika 
    /// </summary>
    template <std::derived_from<Staff> T>
    void gen();

    /// <summary>
    /// Przeprowadza pełną regenerację puli pracowników na rynku pracy
    /// </summary>
    void regen(GameState& state);
};

/// <summary>
/// Specjalizacja szablonu generująca losowego Agenta
/// Losuje imię, przydziela statystyki oraz oblicza koszt (payment) na podstawie umiejętności i doświadczenia
/// </summary>
template <> inline void StaffLogic::gen<Agent>()
{
    static std::random_device rd;
    static std::mt19937 engine(rd());
    int rozmiar{};
    std::string nowyNickname;

    // Losowanie imienia z konfiguracji lub nadanie domyślnego
    if (!config.agentNames.empty())
    {
        rozmiar = config.agentNames.size() - 1;
        std::uniform_int_distribution<int> id(0, rozmiar);
        int nicknameID = id(engine);
        nowyNickname = config.agentNames[nicknameID];
        config.agentNames.erase(config.agentNames.begin() + nicknameID);
    }
    else
    {
        std::uniform_int_distribution<int> id(1, 100);
        nowyNickname = "Agent Specjalny " + std::to_string(id(engine));
    }

    // Losowanie statystyk
    std::uniform_int_distribution<int> skills(0, 50);
    int newcharisma = skills(engine);
    int newaim = skills(engine);
    int newagility = skills(engine);
    int newexp = (skills(engine) / 5);

    // Obliczanie kosztu
    float newPayment = (std::pow((0.33f * newcharisma + 0.33f * newaim + 0.33f * newagility), 1.66f) + std::pow(newexp, 1.33f) + 100.0f);

    // Losowanie specjalizacji
    std::uniform_int_distribution<int> typAgenta(0, 2);
    int newAgent = typAgenta(engine);
    Specjalizacja wybranaSpec;
    if (newAgent == 0) wybranaSpec = Specjalizacja::Zabojstwo;
    else if (newAgent == 1) wybranaSpec = Specjalizacja::Wywiad;
    else wybranaSpec = Specjalizacja::Kradziez;

    Agent nowyAgent(nowyNickname, wybranaSpec, 5);

    // Ustawienie danych obiektu
    nowyAgent.setZajety(false);
    nowyAgent.dodajCeche("english");
    nowyAgent.setExp(newexp);
    nowyAgent.ustawStatystyke("Charisma", newcharisma);
    nowyAgent.ustawStatystyke("Aim", newaim);
    nowyAgent.ustawStatystyke("Agility", newagility);
    nowyAgent.setPayment(newPayment);

    dodajDoPuli(std::move(nowyAgent));
}

/// <summary>
/// Specjalizacja szablonu generująca losową Grupę deszyfrującą
/// Przydziela statystyki inżynieryjne oraz przypisuje do losowego obszaru działań
/// </summary>
template <> inline void StaffLogic::gen<Grupa>()
{
    static std::random_device rd;
    static std::mt19937 engine(rd());
    int rozmiar{};
    std::string nowyNickname;

    // Losowanie nazwy grupy
    if (!config.groupNames.empty())
    {
        rozmiar = config.groupNames.size() - 1;
        std::uniform_int_distribution<int> id(0, rozmiar);
        int nicknameID = id(engine);
        nowyNickname = config.groupNames[nicknameID];
        config.groupNames.erase(config.groupNames.begin() + nicknameID);
    }
    else
    {
        std::uniform_int_distribution<int> id(1, 100);
        nowyNickname = "Grupa Deszyfrujaca " + std::to_string(id(engine));
    }

    // Losowanie statystyk
    std::uniform_int_distribution<int> skills(1, 50);
    int newA = skills(engine);
    int newB = skills(engine);
    int newC = skills(engine);
    int newexp = (skills(engine) / 5);

    // Obliczanie kosztu
    float newPayment = (std::pow((0.33f * newA + 0.33f * newB + 0.33f * newC), 2.0f) + std::pow(newexp, 1.33f) + 100.0f);

    // Losowanie obszaru
    std::uniform_int_distribution<int> typGrupy(0, 2);
    int newGroup = typGrupy(engine);

    Obszar wybranyObszar;
    if (newGroup == 0) wybranyObszar = Obszar::Telegraficzny;
    else if (newGroup == 1) wybranyObszar = Obszar::Glosowy;
    else wybranyObszar = Obszar::Tekstowy;

    Grupa nowaGrupa(nowyNickname, wybranyObszar, 5);

    // Ustawienie danych obiektu
    nowaGrupa.setZajety(false);
    nowaGrupa.setExp(newexp);
    nowaGrupa.ustawStatystyke("Inzyneria", newA);
    nowaGrupa.ustawStatystyke("Kryptoanaliza", newB);
    nowaGrupa.ustawStatystyke("Nasluch", newC);
    nowaGrupa.setPayment(newPayment);

    dodajDoPuli(std::move(nowaGrupa));
}