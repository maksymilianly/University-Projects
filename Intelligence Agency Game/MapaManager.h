#pragma once
#include "GameSceneWithUI.h"
#include "MapaVisual.h"
#include "MapaLogic.h"
#include "MisjaManager.h"
#include "CountriesEnums.h"
#include <atomic>
#include <memory>

import AssetsMod;
import ConfigMod;

class GameState;

/// <summary>
/// Główny menedżer sceny mapy. Klasa sterująca, która łączy warstwę wizualną (MapaVisual), 
/// logikę mapy (MapaLogic) oraz system misji (MisjaManager)
/// Odpowiada za aktualizację stanu sceny, obsługę zdarzeń interfejsu oraz synchronizację danych gry
/// </summary>
class MapaManager : public GameSceneWithUI {
private:
    /// <summary>Komponent odpowiedzialny za renderowanie mapy</summary>
    MapaVisual visual;
    /// <summary>Komponent odpowiedzialny za logikę przestrzenną mapy (np. granice, kliknięcia)</summary>
    MapaLogic logika;
    /// <summary>Zarządca logiki misji (aktywne zadania, przydziały agentów)</summary>
    MisjaManager misja_manager;

    bool rysujGranice;
    std::string ktoraGranica;

    /// <summary>Panele UI dla misji (widgety wyboru i misji)</summary>
    std::unique_ptr<UIOverlay> mission_widgets_panel;
    std::unique_ptr<UIOverlay> mission_panel;

    /// <summary>Zmienne atomowe monitorujące status misji (bezpieczne dla operacji wielowątkowych)</summary>
    std::atomic<bool> missionInProgress{ false };
    std::atomic<int> timeForMission{ 0 };
    std::atomic<bool> isTargetClicked{ false };
    std::atomic<bool> missionEnd{ false };

    bool startMinigame = false;
    int missionToRemowe = -1;
    std::unique_ptr<Staff> agentOnMission;

public:
    /// <summary>
    /// Inicjalizuje menedżera mapy z odwołaniami do zasobów, konfiguracji i stanu gry
    /// </summary>
    /// <param name="_assets">Referencja do zasobów (grafiki, czcionki)</param>
    /// <param name="_config">Referencja do konfiguracji gry</param>
    /// <param name="_state">Referencja do globalnego stanu gry</param>
    MapaManager(Assets& _assets, Config& _config, GameState& _state);

    /// <summary>
    /// Główna pętla aktualizacji logiki sceny mapy 
    /// </summary>
    /// <param name="dt">Czas trwania klatki</param>
    void update(float dt) override;

    /// <summary>
    /// Renderuje całą zawartość sceny mapy: mapę, wszystkie elementy UI i nakładki
    /// </summary>
    /// <param name="window">Referencja do okna renderującego</param>
    void draw(sf::RenderWindow& window) override;

    /// <summary>
    /// Obsługuje zdarzenia wejściowe (mysz, klawiatura) specyficzne dla sceny mapy
    /// </summary>
    /// <param name="event">Zdarzenie SFML</param>
    /// <param name="window">Okno gry</param>
    void obslugaZdarzen(const sf::Event& event, const sf::RenderWindow& window) override;

    /// <summary>
    /// Synchronizuje dane między logiką a stanem gry
    /// </summary>
    void obslugaDanych() override;
};