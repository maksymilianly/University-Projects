#pragma once
#include <SFML/Graphics.hpp>


import AssetsMod;
import ConfigMod;


class GameState;

/// <summary>
/// Klasa abstrakcyjna definiująca wspólny interfejs dla wszystkich ekranów (scen) w grze
/// Każdy nowy ekran gry musi dziedziczyć po tej klasie i zaimplementować jej metody wirtualne
/// </summary>
class Ekran {
protected:
    /// <summary>Referencja do globalnego menedżera zasobów</summary>
    Assets& assets;
    /// <summary>Referencja do globalnego menedżera konfiguracji</summary>
    Config& config;
    /// <summary>Referencja do globalnego stanu gry</summary>
    GameState& state;

public:
    /// <summary>
    /// Konstruktor klasy bazowej inicjalizujący referencje do głównych menedżerów gry
    /// </summary>
    Ekran(Assets& _assets, Config& _config, GameState& _state)
        : assets(_assets), config(_config), state(_state) {
    }

    /// <summary>Inicjalizuje zasoby specyficzne dla danego ekranu</summary>
    virtual void init(Assets& assets, Config& config, GameState& state) = 0;

    /// <summary>Rysuje zawartość ekranu w oknie aplikacji</summary>
    /// <param name="window">Referencja do okna renderującego SFML</param>
    virtual void draw(sf::RenderWindow& window) = 0;

    /// <summary>Aktualizuje logikę ekranu w każdej klatce</summary>
    /// <param name="dt">Delta time - czas od ostatniej klatki w sekundach</param>
    virtual void update(float dt) = 0;

    /// <summary>Obsługuje zdarzenia wejściowe (mysz, klawiatura) przypisane do danego ekranu</summary>
    /// <param name="event">Obiekt zdarzenia SFML</param>
    /// <param name="window">Referencja do okna (potrzebna np. do mapowania współrzędnych myszy)</param>
    virtual void obslugaZdarzen(const sf::Event& event, const sf::RenderWindow& window) = 0;

    /// <summary>Obsługuje synchronizację danych (np. odświeżanie UI po zmianie stanu gry)</summary>
    virtual void obslugaDanych() = 0;

    /// <summary>Wirtualny destruktor zapewniający poprawne usuwanie obiektów klas pochodnych</summary>
    virtual ~Ekran() = default;
};