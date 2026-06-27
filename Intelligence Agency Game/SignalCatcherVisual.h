#pragma once
#include "Visual.h"
#include <SFML/Graphics.hpp>

import AssetsMod;
import ConfigMod;

/// <summary>
/// Klasa odpowiedzialna za wizualną reprezentację obiektu przechwytującego (catcher) na radarze
/// Zarządza renderowaniem spritea celownika oraz aktualizacją jego pozycji na ekranie
/// </summary>
class SignalCatcherVisual : public Visual {
private:
    /// <summary>Sprite reprezentujący catcher na radarze</summary>
    sf::Sprite catcher;

public:
    /// <summary>
    /// Inicjalizuje wizualizację celownika, ładując odpowiednią teksturę z zasobów
    /// </summary>
    /// <param name="assets">Referencja do menedżera zasobów</param>
    /// <param name="config">Referencja do konfiguracji gry</param>
    SignalCatcherVisual(Assets& assets, Config& config);

    /// <summary>
    /// Aktualizuje pozycję wizualną celownika na podstawie otrzymanego wektora
    /// </summary>
    /// <param name="vector">Wektor pozycji celownika.</param>
    void update(sf::Vector2f vector);

    /// <summary>
    /// Renderuje celownik w oknie gry
    /// </summary>
    /// <param name="window">Referencja do okna renderującego</param>
    void drawDynamic(sf::RenderWindow& window);
};