#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "CountriesEnums.h" 

/// <summary>
/// Reprezentuje obiekt misji w grze
/// Przechowuje dane o celu misji: nazwę miasta, państwo oraz współrzędne na mapie
/// </summary>
class Misja {
private:
    /// <summary>Nazwa miasta docelowego misji</summary>
    std::string nazwaMiasta;
    /// <summary>Kraj, w którym odbywa się misja</summary>
    Country kraj;
    /// <summary>Pozycja miasta w przestrzeni mapy gry</summary>
    sf::Vector2f pozycjaMiasta;

public:
    /// <summary>
    /// Inicjalizuje nową misję z podanymi parametrami
    /// </summary>
    /// <param name="n">Nazwa miasta.</param>
    /// <param name="k">Kraj docelowy.</param>
    /// <param name="p">Pozycja na mapie (sf::Vector2f).</param>
    Misja(std::string n, Country k, sf::Vector2f p);

    /// <summary>
    /// Zwraca nazwę miasta, w którym toczy się misja
    /// </summary>
    /// <returns>Referencja do nazwy miasta</returns>
    const std::string& getNazwa() const { return nazwaMiasta; }

    /// <summary>
    /// Zwraca kraj docelowy misji
    /// </summary>
    /// <returns>Wartość wyliczeniową Country</returns>
    Country getKraj() const { return kraj; }

    /// <summary>
    /// Zwraca pozycję miasta na mapie
    /// </summary>
    /// <returns>Pozycja miasta jako sf::Vector2f</returns>
    const sf::Vector2f& getPozycjaMiasta() const { return pozycjaMiasta; }
};