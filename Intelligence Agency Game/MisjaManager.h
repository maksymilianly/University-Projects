#pragma once
#include "SFML/Graphics.hpp"
#include "MisjaLogic.h"
#include "MisjaVisual.h"

import AssetsMod;
import ConfigMod;

class GameState;

/// <summary>
/// Menedżer wysokiego poziomu dla systemu misji
/// Klasa ta koordynuje współpracę między logiką misji (MisjaLogic) a jej reprezentacją wizualną (MisjaVisual),
/// zarządzając cyklem życia zadań, obsługą zdarzeń interfejsu oraz synchronizacją danych gry
/// </summary>
class MisjaManager {
private:
    /// <summary>Moduł logiki obliczeniowej dla misji</summary>
    MisjaLogic logika;
    /// <summary>Moduł odpowiedzialny za renderowanie elementów misji</summary>
    MisjaVisual visual;

    /// <summary>Referencja do zasobów gry</summary>
    Assets& assets;
    /// <summary>Referencja do konfiguracji gry</summary>
    Config& config;
    /// <summary>Referencja do globalnego stanu gry</summary>
    GameState& state;

public:
    /// <summary>
    /// Inicjalizuje menedżera misji
    /// </summary>
    /// <param name="_assets">Referencja do menedżera zasobów</param>
    /// <param name="_config">Referencja do konfiguracji gry</param>
    /// <param name="_state">Referencja do globalnego stanu gry</param>
    MisjaManager(Assets& _assets, Config& _config, GameState& _state);

    /// <summary>
    /// Aktualizuje logikę misji w czasie rzeczywistym
    /// </summary>
    /// <param name="dt">Delta time</param>
    void update(float dt);

    /// <summary>
    /// Rysuje elementy wizualne związane z misjami
    /// </summary>
    /// <param name="window">Referencja do okna renderującego</param>
    void draw(sf::RenderWindow& window);

    /// <summary>
    /// Pobiera listę miast dostępnych dla danego państwa
    /// </summary>
    /// <param name="panstwo">Nazwa lub identyfikator państwa</param>
    /// <returns>Wektor nazw miast</returns>
    std::vector<std::string> checkCities(std::string panstwo);

    /// <summary>
    /// Obsługuje zdarzenia wejściowe (np. kliknięcia) dla interfejsu misji.
    /// </summary>
    /// <param name="event">Zdarzenie SFML</param>
    /// <param name="window">Okno gry</param>
    void obslugaZdarzen(const sf::Event& event, const sf::RenderWindow& window);

    /// <summary>
    /// Synchronizuje dane między menedżerem a stanem gry
    /// </summary>
    void obslugaDanych();
};