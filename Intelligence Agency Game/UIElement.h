#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

/// <summary>
/// Klasa bazowa (interfejs) dla wszystkich elementów interfejsu użytkownika (UI)
/// Każdy konkretny element UI (np. przycisk, overlay) musi dziedziczyć po tej klasie
/// i zaimplementować metody rysowania oraz obsługi interakcji
/// </summary>
class UIElement {
public:
    /// <summary>
    /// Wirtualny destruktor
    /// </summary>
    virtual ~UIElement() = default;

    /// <summary>
    /// Renderuje element interfejsu w oknie gry
    /// </summary>
    /// <param name="window">Referencja do okna renderującego SFML.</param>
    virtual void draw(sf::RenderWindow& window) = 0;

    /// <summary>
    /// Obsługuje zdarzenie kliknięcia dla danego elementu
    /// </summary>
    /// <param name="event">Zdarzenie SFML</param>
    /// <param name="mousePos">Pozycja kursora myszy przekazana w przestrzeni ekranu</param>
    /// <returns>True, jeśli kliknięcie zostało poprawnie obsłużone przez element (np. przycisk został wciśnięty)</returns>
    virtual bool obsluzKlikniecie(const sf::Event& event, const sf::Vector2f& mousePos) = 0;

    /// <summary>
    /// Sprawdza, czy kursor myszy znajduje się nad elementem
    /// Domyślna implementacja zwraca false; klasy pochodne powinny nadpisać tę metodę,
    /// jeśli element ma reagować na najechanie kursorem (np. podświetlenie).
    /// </summary>
    /// <param name="mousePos">Pozycja kursora myszy</param>
    /// <returns>True, jeśli kursor wskazuje na element, w przeciwnym razie false</returns>
    virtual bool hovered(const sf::Vector2f& mousePos) { return false; }
};