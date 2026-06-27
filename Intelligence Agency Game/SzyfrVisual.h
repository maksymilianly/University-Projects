#pragma once
#include "Visual.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <utility>
#include "ProcesDeszyfrowania.h"

import AssetsMod;
import ConfigMod;

/// <summary>
/// Klasa odpowiedzialna za wizualną reprezentację procesów deszyfrowania
/// Zarządza renderowaniem listy aktywnych procesów, zegarów oraz wskaźników postępu
/// </summary>
class SzyfrVisual : public Visual {
private:
    /// <summary>Referencja do czcionki używanej do wyświetlania czasu pozostałego do końca deszyfrowania</summary>
    sf::Font& timeFont;

    /// <summary>
    /// Pomocnicza metoda formatująca czas
    /// </summary>
    /// <param name="czas">Czas w sekundach</param>
    /// <returns>Wektor (x: minuty, y: sekundy)</returns>
    sf::Vector2i formatujCzas(int czas) { return { czas / 60, czas % 60 }; }

    /// <summary>
    /// Sprawdza, czy proces deszyfrowania osiągnął stan krytyczny
    /// </summary>
    /// <param name="czas">Pozostały czas procesu</param>
    /// <returns>True, jeśli czas wynosi 0</returns>
    bool closeToFail(int czas) { return czas == 0; }

    /// <summary>
    /// Sprawdza, czy poziom trudności procesu jest poniżej progu 
    /// </summary>
    /// <param name="poziom">Poziom trudności</param>
    /// <returns>True, jeśli poziom jest niski</returns>
    bool checkPoziom(int poziom) { return poziom < 5; }

public:
    /// <summary>
    /// Inicjalizuje wizualizację systemu deszyfrowania
    /// </summary>
    /// <param name="assets">Referencja do menedżera zasobów</param>
    /// <param name="config">Referencja do konfiguracji gry</param>
    SzyfrVisual(Assets& assets, Config& config);

    /// <summary>
    /// Rysuje dynamiczne elementy listy procesów deszyfrowania na ekranie
    /// </summary>
    /// <param name="window">Referencja do okna renderującego SFML</param>
    /// <param name="szyfry">Kontener wszystkich aktywnych procesów deszyfrowania</param>
    /// <param name="daneSzyfru">Para przechowująca pozycję myszy i indeks ostatnio zaznaczonego szyfru</param>
    void drawDynamic(sf::RenderWindow& window, const std::vector<ProcesDeszyfrowania>& szyfry, std::pair<sf::Vector2f, int>& daneSzyfru);

    /// <summary>
    /// Pomocnicza metoda pobierająca wymiary layoutu dla listy szyfrów
    /// </summary>
    /// <param name="startX">Zwracana pozycja początkowa X</param>
    /// <param name="startY">Zwracana pozycja początkowa Y</param>
    /// <param name="szerokosc">Zwracana szerokość pojedynczego elementu</param>
    /// <param name="wysokosc">Zwracana wysokość pojedynczego elementu</param>
    /// <param name="odstepX">Zwracany odstęp między elementami</param>
    /// <returns>True, jeśli udało się pobrać wymiary z konfiguracji</returns>
    bool pobierzWymiary(float& startX, float& startY, float& szerokosc, float& wysokosc, float& odstepX);
};