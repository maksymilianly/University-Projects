#pragma once

#include "Staff.h"
#include <concepts>
#include <random>
#include <vector>
#include <memory>
#include <cmath>

struct Assets;
#include "Config.h"
#include "GameState.h"

class StaffLogic
{
private:
    Assets& assets;
    Config& config;
    GameState& state;

public:
    StaffLogic(Assets& assets, Config& config, GameState& state);

    std::unique_ptr<Staff> buyPracownik(int index);
    void usunOferte(int ktory, bool czyUsun);

    template <std::derived_from<Staff> T>
    void dodajDoPuli(T obiekt)
    {
        auto nowy = std::make_unique<T>(std::move(obiekt));
        state.dodajOferte(std::move(nowy));
    }


    template <std::derived_from<Staff> T>
    void gen();

    void regen(GameState&state);

};



template <> inline void StaffLogic::gen<Agent>()
{
    static std::random_device rd;
    static std::mt19937 engine(rd());
    int rozmiar{};
    std::string nowyNickname;
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

    std::uniform_int_distribution<int> skills(0, 50);
    int newcharisma = skills(engine);
    int newaim = skills(engine);
    int newagility = skills(engine);
    int newexp = (skills(engine)/5);
    float newPayment = (std::pow((0.33f * newcharisma + 0.33f * newaim + 0.33f * newagility), 1.66f) + std::pow(newexp, 1.33f) + 100.0f);

    std::uniform_int_distribution<int> typAgenta(0, 2);
    int newAgent = typAgenta(engine);
    Specjalizacja wybranaSpec;
    if (newAgent == 0) wybranaSpec = Specjalizacja::Zabojstwo;
    else if (newAgent == 1) wybranaSpec = Specjalizacja::Wywiad;
    else wybranaSpec = Specjalizacja::Kradziez;

    Agent nowyAgent(nowyNickname, wybranaSpec, 5);

    nowyAgent.setZajety(false);
    nowyAgent.dodajCeche("english");
    nowyAgent.setExp(newexp);
    nowyAgent.ustawStatystyke("Charisma", newcharisma);
    nowyAgent.ustawStatystyke("Aim", newaim);
    nowyAgent.ustawStatystyke("Agility", newagility);
    nowyAgent.setPayment(newPayment);

    dodajDoPuli(std::move(nowyAgent));
}

template <> inline void StaffLogic::gen<Grupa>()
{
    static std::random_device rd;
    static std::mt19937 engine(rd());
    int rozmiar{};
    std::string nowyNickname;
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

    std::uniform_int_distribution<int> skills(1, 50);
    int newA = skills(engine);
    int newB = skills(engine);
    int newC = skills(engine);
    int newexp = (skills(engine)/5);

    float newPayment = (std::pow((0.33f * newA + 0.33f * newB + 0.33f * newC), 2.0f) + std::pow(newexp, 1.33f) + 100.0f);

    std::uniform_int_distribution<int> typGrupy(0, 2);
    int newGroup = typGrupy(engine);

    Obszar wybranyObszar;
    if (newGroup == 0) wybranyObszar = Obszar::Telegraficzny;
    else if (newGroup == 1) wybranyObszar = Obszar::Glosowy;
    else wybranyObszar = Obszar::Tekstowy;

    Grupa nowaGrupa(nowyNickname, wybranyObszar, 5);

    nowaGrupa.setZajety(false);
    nowaGrupa.setExp(newexp);
    nowaGrupa.ustawStatystyke("Inzyneria", newA);
    nowaGrupa.ustawStatystyke("Kryptoanaliza", newB);
    nowaGrupa.ustawStatystyke("Nasluch", newC);
    nowaGrupa.setPayment(newPayment);

    dodajDoPuli(std::move(nowaGrupa));
}

