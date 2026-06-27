#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "UIElement.h"
#include <functional>
#include <optional>

/// <summary>
/// Implementacja przycisku w interfejsie użytkownika
/// Wykorzystuje sprite jako wygląd graficzny oraz std::function jako akcję wywoływaną po kliknięciu
/// </summary>
class UIButton : public UIElement {
private:
    /// <summary>Wizualna reprezentacja przycisku</summary>
    sf::Sprite element;

    std::optional<sf::Text> buttonText;

    /// <summary>Funkcja wywoływana w momencie poprawnego kliknięcia przycisku</summary>
    std::function<void()> action;

public:
    /// <summary>
    /// Inicjalizuje przycisk z podanym wyglądem, pozycją i akcją
    /// </summary>
    /// <param name="sprite">Sprite reprezentujący przycisk</param>
    /// <param name="pos">Początkowa pozycja przycisku na ekranie</param>
    /// <param name="_action">Funkcja (np. lambda), która zostanie wywołana po kliknięciu</param>
    UIButton(const sf::Sprite& sprite,sf::Font& font,  const sf::Vector2f& pos, std::function<void()> _action);

    UIButton(const sf::Sprite& sprite, const sf::Vector2f& pos, std::function<void()> _action);

    void setText(std::string text);

    /// <summary>
    /// Rysuje przycisk w oknie gry
    /// </summary>
    /// <param name="window">Referencja do okna SFML</param>
    void draw(sf::RenderWindow& window);

    /// <summary>
    /// Aktualizuje pozycję przycisku na ekranie
    /// </summary>
    /// <param name="newPos">Nowa pozycja przycisku</param>
    void setPos(sf::Vector2f newPos) { element.setPosition(newPos); }

    /// <summary>
    /// Sprawdza, czy kliknięcie myszy nastąpiło wewnątrz obszaru przycisku
    /// Jeśli tak, wyzwala przypisaną akcję
    /// </summary>
    /// <param name="event">Zdarzenie SFML</param>
    /// <param name="mousePos">Pozycja kursora myszy</param>
    /// <returns>True, jeśli kliknięcie trafiło w przycisk.</returns>
    bool obsluzKlikniecie(const sf::Event& event, const sf::Vector2f& mousePos) override;
};