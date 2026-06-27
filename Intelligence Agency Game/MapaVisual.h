#pragma once
#include "Visual.h"
#include <SFML/Graphics.hpp>
#include <unordered_map>

import AssetsMod;
import ConfigMod;

class GameState;

/// <summary>
/// Klasa odpowiedzialna za wizualną reprezentację mapy gry
/// Zarządza renderowaniem elementów mapy, obsługuje maski kolizji dla regionów
/// oraz dynamiczne wyświetlanie informacji o miastach i granicach państw
/// </summary>
class MapaVisual : public Visual {
private:
    /// <summary>Mapa masek kolizji, używana do precyzyjnego sprawdzania najechania myszką na regiony</summary>
    std::unordered_map<std::string, sf::Image> maskiKolizji;

public:
    /// <summary>
    /// Inicjalizuje warstwę wizualną mapy, ładując niezbędne tekstury i konfigurację
    /// </summary>
    /// <param name="assets">Referencja do zasobów</param>
    /// <param name="config">Referencja do konfiguracji mapy</param>
    MapaVisual(Assets& assets, Config& config);

    /// <summary>
    /// Renderuje bazową warstwę mapy
    /// </summary>
    /// <param name="window">Referencja do okna renderującego</param>
    void draw(sf::RenderWindow& window) override;

    /// <summary>
    /// Rysuje dynamiczne elementy mapy, które zmieniają się w zależności od stanu gry
    /// </summary>
    /// <param name="window">Referencja do okna renderującego</param>
    /// <param name="config">Konfiguracja wizualna</param>
    /// <param name="state">Aktualny stan gry</param>
    void drawDynamic(sf::RenderWindow& window, Config& config, GameState& state);

    /// <summary>
    /// Sprawdza, czy pozycja myszy znajduje się wewnątrz zdefiniowanego prostokąta
    /// </summary>
    /// <param name="obj1">Obszar obiektu.</param>
    /// <param name="posMyszy">Aktualna pozycja kursora</param>
    /// <returns>True, jeśli kursor jest wewnątrz prostokąta</returns>
    bool checkMyszke(const sf::FloatRect& obj1, const sf::Vector2f& posMyszy)
    {
        return obj1.contains(posMyszy);
    }

    /// <summary>
    /// Sprawdza, nad którym państwem znajduje się kursor myszy, analizując maski kolizji
    /// </summary>
    /// <param name="window">Okno gry</param>
    /// <param name="assets">Zasoby potrzebne do dostępu do masek</param>
    /// <param name="posMyszy">Pozycja kursora</param>
    /// <returns>Para: czy znaleziono region oraz nazwa państwa</returns>
    std::pair<bool, std::string> checkGranice(const sf::RenderWindow& window, const Assets& assets, const sf::Vector2f& posMyszy);

    /// <summary>
    /// Rysuje granice wskazanego państwa 
    /// </summary>
    /// <param name="window">Referencja do okna renderującego</param>
    /// <param name="panstwo">Nazwa lub identyfikator państwa</param>
    void drawGranice(sf::RenderWindow& window, std::string panstwo);

    /// <summary>
    /// Rysuje marker/ikonę miasta w podanej lokalizacji
    /// </summary>
    /// <param name="window">Referencja do okna renderującego</param>
    /// <param name="config">Konfiguracja wizualna</param>
    /// <param name="pozycja">Współrzędne na mapie</param>
    void drawMiasto(sf::RenderWindow& window, Config& config, sf::Vector2f pozycja);
};