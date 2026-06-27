#pragma once
#include "Ekran.h"
#include "RadarManager.h"
#include "SztabManager.h"
#include "MapaManager.h"
#include "GameScenes.h"
#include <memory>
#include <vector>

import AssetsMod;
import ConfigMod;

class GameState;

/// <summary>
/// Definiuje dostępne sceny wewnątrz głównego ekranu gry
/// </summary>
enum class GameScene {
    Radar, ///< Widok radaru
    Sztab, ///< Widok sztabu 
    Mapa   ///< Widok mapy świata
};

/// <summary>
/// Główny ekran rozgrywki (GameScreen). Klasa ta zarządza kolekcją scen (Radar, Sztab, Mapa)
/// i odpowiada za delegowanie logiki (update, draw, zdarzenia) do aktywnego menedżera sceny
/// </summary>
class GameScreen : public Ekran {
private:
    /// <summary>Kontener posiadający wszystkie sceny gry</summary>
    std::vector<std::unique_ptr<GameScenes>> gameScenes;

    /// <summary>Aktualnie wyświetlana scena</summary>
    GameScene currentView;

public:
    /// <summary>
    /// Inicjalizuje ekran gry, tworząc menedżerów poszczególnych scen
    /// </summary>
    /// <param name="_assets">Referencja do zasobów</param>
    /// <param name="_config">Referencja do konfiguracji</param>
    /// <param name="_state">Referencja do stanu gry</param>
    GameScreen(Assets& _assets, Config& _config, GameState& _state);

    /// <summary>Inicjalizacja ekranu (zgodnie z interfejsem Ekran)</summary>
    void init(Assets& assets, Config& config, GameState& state) override {};

    /// <summary>
    /// Aktualizuje logikę aktualnie wybranej sceny
    /// </summary>
    /// <param name="dt">Delta time</param>
    void update(float dt) override;

    /// <summary>
    /// Renderuje widok aktualnie wybranej sceny
    /// </summary>
    /// <param name="window">Referencja do okna renderującego</param>
    void draw(sf::RenderWindow& window) override;

    /// <summary>
    /// Obsługuje zdarzenia wejściowe i deleguje je do menedżera aktualnej sceny
    /// </summary>
    /// <param name="event">Zdarzenie SFML</param>
    /// <param name="window">Okno gry</param>
    void obslugaZdarzen(const sf::Event& event, const sf::RenderWindow& window) override;

    /// <summary>Zwraca identyfikator aktualnie wyświetlanej sceny</summary>
    GameScene getCurrentView();

    /// <summary>
    /// Synchronizuje dane dla aktualnej sceny
    /// </summary>
    void obslugaDanych() override;
};