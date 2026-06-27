#pragma once
#include "ProcesDeszyfrowania.h"
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <vector>

import ConfigMod;

class GameState;

/// <summary>
/// Klasa zarządzająca logiką szyfrow 
/// Odpowiada za wykrywanie interakcji (kliknięć) w interfejsie szyfrów, dodawanie nowych procesów oraz aktualizację ich postępu w czasie
/// </summary>
class SzyfrLogic {
public:
    /// <summary>Inicjalizuje logikę szyfrów z dostępem do globalnej konfiguracji i stanu gry</summary>
    /// <param name="config">Referencja do menedżera konfiguracji</param>
    /// <param name="state">Referencja do globalnego stanu gry</param>
    SzyfrLogic(Config& config, GameState& state);

    /// <summary>
    /// Sprawdza, czy kliknięcie myszy nastąpiło w obrębie jednego z wyświetlanych procesów deszyfrowania
    /// Metoda oblicza pozycję kliknięcia względem układu (grid/lista) szyfrów
    /// </summary>
    /// <param name="mousePos">Pozycja kursora myszy</param>
    /// <param name="szyfry">Kontener aktualnie aktywnych procesów deszyfrowania</param>
    /// <param name="startX">Początkowa współrzędna X układu</param>
    /// <param name="startY">Początkowa współrzędna Y układu</param>
    /// <param name="szerokosc">Szerokość pojedynczego elementu szyfru</param>
    /// <param name="wysokosc">Wysokość pojedynczego elementu szyfru</param>
    /// <param name="odstepX">Odstęp w poziomie pomiędzy kolejnymi szyframi</param>
    /// <returns>Para zawierająca pozycję wizualną trafionego elementu oraz jego indeks na liście (lub -1, jeśli nie trafiono)</returns>
    std::pair<sf::Vector2f, int> sprawdzKlikniecie(sf::Vector2f mousePos, const std::vector<ProcesDeszyfrowania>& szyfry, float startX, float startY, float szerokosc, float wysokosc, float odstepX);

    /// <summary>Inicjuje dodanie nowego procesu deszyfrowania do systemu</summary>
    /// <param name="state">Referencja do stanu gry, w którym przechowywane są aktywne zadania</param>
    void dodajSzyfr(GameState& state);

    /// <summary>
    /// Przetwarza logikę aktualizacji wszystkich procesów deszyfrowania w czasie
    /// </summary>
    /// <param name="state">Referencja do stanu gry</param>
    /// <param name="dt">Czas trwania ostatniej klatki w sekundach (delta time)</param>
    void aktualizujProcesy(GameState& state, float dt);
};