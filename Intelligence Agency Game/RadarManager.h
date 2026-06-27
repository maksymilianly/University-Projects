#pragma once
#include "SFML/Graphics.hpp"
#include "GameScenes.h"
#include "RadarLogic.h"
#include "RadarVisual.h"
#include "SignalCatcherVisual.h"
#include "SignalCatcherLogic.h"

import AssetsMod;
import ConfigMod;

class GameState;

/// <summary>
/// Menedżer sceny radaru. Odpowiada za koordynację logiki radaru oraz celownika (catcher),
/// zarządzanie widokiem (zoom/unzoom) oraz renderowanie elementów sceny
/// Jest nadrzędnym punktem dostępu dla wszystkiego, co dzieje się w module radarowym
/// </summary>
class RadarManager : public GameScenes {
private:
    /// <summary>Warstwa wizualna radaru</summary>
    RadarVisual visual;
    /// <summary>Warstwa logiczna radaru</summary>
    RadarLogic logika;

    /// <summary>Warstwa wizualna celownika (catcher)</summary>
    SignalCatcherVisual catcher_visual;
    /// <summary>Warstwa logiczna celownika (ruch, kolizje)</summary>
    SignalCatcherLogic catcher_logic;

    /// <summary>Stan drzwi (np. czy konsola radaru jest dostępna)</summary>
    bool doorOpen;
    /// <summary>Czy widok jest obecnie w trybie przybliżenia</summary>
    bool zoomed;

    /// <summary>Parametry pozycji i skali dla trybu normalnego oraz przybliżonego</summary>
    sf::Vector2f normalPos;
    float normalRadius;
    sf::Vector2f zoomPos;
    float zoomRadius;
    float zoomScale;
    float unzoomScale;

public:
    /// <summary>
    /// Inicjalizuje menedżera radaru
    /// </summary>
    /// <param name="_assets">Zasoby gry</param>
    /// <param name="_config">Konfiguracja modułu</param>
    /// <param name="_state">Globalny stan gry</param>
    RadarManager(Assets& _assets, Config& _config, GameState& _state);

    /// <summary>
    /// Główna pętla aktualizacji sceny radaru. Obsługuje rotację, ruch celownika i logikę detekcji
    /// </summary>
    /// <param name="dt">Delta time</param>
    void update(float dt) override;

    /// <summary>
    /// Renderuje wszystkie elementy radaru w oknie gry
    /// </summary>
    /// <param name="window">Referencja do okna renderującego</param>
    void draw(sf::RenderWindow& window) override;

    /// <summary>
    /// Obsługuje zdarzenia wejściowe (kliknięcia, ruch myszy) w obrębie radaru
    /// </summary>
    /// <param name="event">Zdarzenie SFML</param>
    /// <param name="window">Okno gry</param>
    void obslugaZdarzen(const sf::Event& event, const sf::RenderWindow& window) override;

    /// <summary>
    /// Synchronizuje dane między radarem a stanem gry (np. zdobyte punkty za wykryte cele)
    /// </summary>
    void obslugaDanych() override;
};