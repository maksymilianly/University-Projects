#pragma once
#include <SFML/Graphics.hpp>


import AssetsMod;
import ConfigMod;

class GameState;

/// <summary>
/// Klasa bazowa dla wszystkich złożonych scen w grze (np. Mapa, Sztab, Radar)
/// Definiuje cykl życia sceny i wymagane metody obsługi logiki oraz renderowania
/// </summary>
class GameScenes {
protected:
    /// <summary>Referencja do globalnego menedżera zasobów</summary>
    Assets& assets;
    /// <summary>Referencja do globalnego menedżera konfiguracji</summary>
    Config& config;
    /// <summary>Referencja do globalnego stanu gry</summary>
    GameState& state;

public:
    /// <summary>
    /// Konstruktor klasy bazowej sceny, przypisujący wymagane menedżery do pól chronionych
    /// </summary>
    GameScenes(Assets& _assets, Config& _config, GameState& _state)
        : assets(_assets), config(_config), state(_state) {
    }

    /// <summary>
    /// Wirtualny destruktor
    /// </summary>
    virtual ~GameScenes() = default;

    /// <summary>
    /// Aktualizuje logikę sceny w każdej klatce
    /// </summary>
    /// <param name="dt">Czas trwania ostatniej klatki w sekundach (delta time).</param>
    virtual void update(float dt) = 0;

    /// <summary>
    /// Renderuje elementy graficzne sceny w podanym oknie
    /// </summary>
    /// <param name="window">Referencja do okna SFML</param>
    virtual void draw(sf::RenderWindow& window) = 0;

    /// <summary>
    /// Obsługuje zdarzenia wejściowe (mysz, klawiatura) specyficzne dla danej sceny
    /// </summary>
    /// <param name="event">Referencja do zdarzenia SFML</param>
    /// <param name="window">Referencja do okna (np. do przeliczania pozycji myszy)</param>
    virtual void obslugaZdarzen(const sf::Event& event, const sf::RenderWindow& window) = 0;

    /// <summary>
    /// Metoda synchronizująca dane pomiędzy logiką a warstwą wizualną sceny
    /// Wywoływana np. przy przełączaniu scen lub aktualizacji stanu gry
    /// </summary>
    virtual void obslugaDanych() = 0;
};