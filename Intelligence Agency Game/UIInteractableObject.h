#pragma once
#include "UIWidget.h"
#include <functional>

/// <summary>
/// Reprezentuje obiekt interaktywny w interfejsie użytkownika
/// Wykonuje przypisaną akcję (callback) po kliknięciu lewym przyciskiem myszy
/// jeśli kursor znajduje się wewnątrz granic obiektu
/// </summary>
class UIInteractableObject : public UIWidget {
private:
    /// <summary>Akcja (callback) wykonywana po kliknięciu</summary>
    std::function<void()> actionClick;

public:
    /// <summary>
    /// Inicjalizuje obiekt interaktywny
    /// </summary>
    /// <param name="bg">Sprite tła obiektu</param>
    /// <param name="bgPos">Pozycja tła</param>
    /// <param name="font">Czcionka używana przez widget</param>
    /// <param name="action">Funkcja/lambda do wykonania po kliknięciu</param>
    UIInteractableObject(sf::Sprite bg, sf::Vector2f bgPos, sf::Font& font, std::function<void()> action)
        : UIWidget(bg, font, bgPos), actionClick(action) {
    }

    /// <summary>
    /// Obsługuje zdarzenie kliknięcia. Sprawdza, czy kliknięto lewym przyciskiem myszy w obszarze obiektu
    /// </summary>
    /// <param name="event">Zdarzenie SFML</param>
    /// <param name="mousePos">Pozycja kursora</param>
    /// <returns>True, jeśli obiekt został kliknięty i akcja została wykonana</returns>
    bool obsluzKlikniecie(const sf::Event& event, const sf::Vector2f& mousePos) override
    {
        if (const auto* mouseEvent = event.getIf<sf::Event::MouseButtonPressed>())
        {
            if (mouseEvent->button == sf::Mouse::Button::Left)
            {
                if (hovered(mousePos))
                {
                    if (actionClick) actionClick();
                    return true;
                }
            }
        }
        return false;
    }
};