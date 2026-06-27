#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Visual.h"

import AssetsMod;
import ConfigMod;

class GameState;

/// <summary>
/// Klasa odpowiedzialna za wizualną reprezentację sztabu
/// Zarządza renderowaniem statycznych elementów pomieszczenia oraz dynamicznych obiektów,
/// takich jak zegar odliczający czas czy przesuwalne stoły
/// </summary>
class SztabVisual : public Visual {
private:
    /// <summary>Referencja do czcionki używanej do wyświetlania czasu</summary>
    sf::Font& timeFont;

    /// <summary>
    /// Pomocnicza metoda formatująca czas w sekundach na minuty i sekundy
    /// </summary>
    /// <param name="czas">Czas w sekundach</param>
    /// <returns>Wektor (x: minuty, y: sekundy)</returns>
    sf::Vector2i formatujCzas(int czas) { return { czas / 60, czas % 60 }; }

    /// <summary>
    /// Pomocnicza metoda sprawdzająca, czy czas dobiega końca
    /// </summary>
    /// <param name="czas">Pozostały czas</param>
    /// <returns>True, jeśli czas wynosi 0</returns>
    bool closeToFail(int czas) { return czas == 0; }

public:
    /// <summary>
    /// Inicjalizuje wizualizację sztabu
    /// </summary>
    /// <param name="assets">Referencja do zasobów</param>
    /// <param name="config">Referencja do konfiguracji</param>
    SztabVisual(Assets& assets, Config& config);

    /// <summary>
    /// Rysuje statyczne elementy wizualne sztabu
    /// </summary>
    /// <param name="window">Referencja do okna renderującego</param>
    void draw(sf::RenderWindow& window) override;

    /// <summary>
    /// Rysuje dynamiczne elementy sztabu, które zmieniają się w trakcie gry
    /// </summary>
    /// <param name="window">Referencja do okna renderującego</param>
    /// <param name="assets">Zasoby potrzebne do renderowania</param>
    /// <param name="state">Stan gry</param>
    /// <param name="przesuwanie">Flaga informująca, czy użytkownik aktualnie przesuwa</param>
    void drawDynamic(sf::RenderWindow& window, Assets& assets, GameState& state, bool przesuwanie);
};