#pragma once
#include <SFML/Graphics.hpp>


import AssetsMod;


class GameState;

/// <summary>
/// Klasa zarządzająca logiką Sztabu. Odpowiada za rozmieszczanie elementów
/// (np. stołów), sprawdzanie kolizji oraz walidację pozycji
/// </summary>
class SztabLogic {
public:
    /// <summary>
    /// Generuje losowe współrzędne (X, Y) w obrębie obszaru roboczego sztabu.
    /// </summary>
    /// <returns>Punkt (sf::Vector2f) o losowych współrzędnych</returns>
    sf::Vector2f genRandomXY();

    /// <summary>
    /// Tworzy i umieszcza nowy stół w sztabie.
    /// Metoda może weryfikować pozycję, aby uniknąć kolizji z innymi obiektami
    /// </summary>
    /// <param name="assets">Referencja do menedżera zasobów (potrzebna do załadowania grafiki stołu)</param>
    /// <param name="state">Referencja do stanu gry (tu zostaje zapisany nowy stół)</param>
    /// <param name="pojemnoscNowegoStolu">Liczba miejsc dla grup przy nowym stole</param>
    void placeNowyStol(Assets& assets, GameState& state, int pojemnoscNowegoStolu);

    /// <summary>
    /// Sprawdza, czy prostokąt (np. hitbox stołu) wykracza poza granice widocznego ekranu
    /// </summary>
    /// <param name="posStol">Granice obiektu do sprawdzenia</param>
    /// <returns>True, jeśli obiekt znajduje się poza ekranem, w przeciwnym razie false</returns>
    bool outOfScreenBounds(const sf::FloatRect& posStol);

    /// <summary>
    /// Sprawdza, czy występuje kolizja między dwoma prostokątami AABB
    /// </summary>
    /// <param name="obj1">Granice pierwszego obiektu</param>
    /// <param name="obj2">Granice drugiego obiektu</param>
    /// <returns>True, jeśli obiekty na siebie nachodzą</returns>
    bool checkColision(const sf::FloatRect& obj1, const sf::FloatRect& obj2);
};