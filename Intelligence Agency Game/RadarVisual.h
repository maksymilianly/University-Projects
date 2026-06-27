#pragma once
#include "SFML/Graphics.hpp"
#include "RadarTypes.h"
#include "Visual.h"

import AssetsMod;
import ConfigMod;

/// <summary>
/// Klasa odpowiedzialna za wizualną reprezentację systemu radaru
/// Zarządza renderowaniem animacji (rotacja głowic, światła), wyświetlaniem sygnałów oraz 
/// obsługą wizualną elementów interfejsu radaru (przyciski, drzwi)
/// </summary>
class RadarVisual : public Visual {
private:
    /// <summary>Zegar używany do animacji świateł sygnalizacyjnych</summary>
    sf::Clock swiatlaClock;

public:
    /// <summary>
    /// Inicjalizuje wizualizację radaru
    /// </summary>
    /// <param name="assets">Referencja do zasobów</param>
    /// <param name="config">Referencja do konfiguracji</param>
    RadarVisual(Assets& assets, Config& config);

    /// <summary>
    /// Rysuje statyczne elementy radaru 
    /// </summary>
    /// <param name="window">Referencja do okna renderującego</param>
    void draw(sf::RenderWindow& window) override;

    /// <summary>
    /// Ustawia kąt wizualny projektora radaru
    /// </summary>
    /// <param name="angle">Kąt w stopniach</param>
    void setProjectorAngle(float angle);

    /// <summary>
    /// Ustawia kąt wizualny odbiornika radaru
    /// </summary>
    /// <param name="angle">Kąt w stopniach</param>
    void setOdbiornikAngle(float angle);

    /// <summary>
    /// Rysuje dynamiczne elementy radaru, zależne od aktualnego stanu gry i wykrytych obiektów.
    /// </summary>
    /// <param name="window">Referencja do okna renderującego</param>
    /// <param name="sygnaly">Lista wykrytych sygnałów do narysowania</param>
    /// <param name="sukcesy">Lista udanych przechwyceń do narysowania</param>
    /// <param name="isRadarOn">Czy radar jest włączony</param>
    /// <param name="isPoleOn">Czy pole skanowania jest aktywne</param>
    /// <param name="doorOpen">Czy drzwi do radaru są otwarte</param>
    /// <param name="zoomed">Czy włączono tryb przybliżenia</param>
    void drawDynamic(sf::RenderWindow& window, const std::vector<Signal>& sygnaly,
        const std::vector<SukcesWylapania>& sukcesy,
        bool isRadarOn, bool isPoleOn, bool doorOpen,
        bool zoomed);

    /// <summary>
    /// Rysuje animowane światła na panelu radaru
    /// </summary>
    /// <param name="window">Referencja do okna renderującego</param>
    void drawSwiatla(sf::RenderWindow& window);

    /// <summary>Zwraca obszar kolizji dla przycisku włączania radaru</summary>
    sf::FloatRect przyciskPos() {
        return sprites.at("radar_button_onoff").getGlobalBounds();
    }

    /// <summary>Zwraca obszar kolizji dla zamkniętych drzwi radaru</summary>
    sf::FloatRect doorClosedPos() {
        return sprites.at("radar_doors_closed").getGlobalBounds();
    }

    /// <summary>Zwraca obszar kolizji dla otwartych drzwi radaru</summary>
    sf::FloatRect doorOpenPos() {
        return sprites.at("radar_doors_open").getGlobalBounds();
    }

    /// <summary>Zwraca obszar kolizji dla przycisku Zoom</summary>
    sf::FloatRect zoomPos() {
        return sprites.at("radar_button_zoom").getGlobalBounds();
    }
};