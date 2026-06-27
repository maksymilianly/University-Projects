#pragma once
#include <SFML/Graphics.hpp>
#include "UIWidget.h"
#include "Misja.h" 
#include <functional>

/// <summary>
/// Widget reprezentujący pojedynczą misję w interfejsie użytkownika
/// Odpowiada za wyświetlanie informacji o misji oraz obsługę przycisków akcji
/// </summary>
class UIMissionWidget : public UIWidget {
private:
    /// <summary>Ikona miasta powiązanego z misją</summary>
    sf::Sprite icon_city;
    /// <summary>Przycisk akceptacji misji</summary>
    sf::Sprite button_accept;
    /// <summary>Przycisk odrzucenia misji</summary>
    sf::Sprite button_reject;

    /// <summary>Referencja do obiektu misji, którą widget reprezentuje</summary>
    Misja& misja;

    /// <summary>Tekstowe informacje o mieście, kraju oraz przyciskach</summary>
    sf::Text text_city;
    sf::Text text_country;
    sf::Text text_accept;
    sf::Text text_reject;

    /// <summary>Akcja wywoływana po kliknięciu przycisku akceptacji</summary>
    std::function<void()> actionAccept;
    /// <summary>Akcja wywoływana po kliknięciu przycisku odrzucenia</summary>
    std::function<void()> actionReject;

public:
    /// <summary>
    /// Inicjalizuje widget misji z kompletem grafik, fontów i logiką obsługi przycisków
    /// </summary>
    /// <param name="_tlo">Sprite tła widgetu</param>
    /// <param name="_iconCity">Sprite ikony miasta</param>
    /// <param name="_btnAccept">Sprite przycisku akceptacji</param>
    /// <param name="_btnReject">Sprite przycisku odrzucenia</param>
    /// <param name="font">Referencja do czcionki używanej w tekstach</param>
    /// <param name="_misja">Obiekt misji do wyświetlenia</param>
    /// <param name="pozycjaStartowa">Początkowa pozycja widgetu na ekranie</param>
    /// <param name="_actionAccept">Lambda/funkcja dla akcji akceptacji</param>
    /// <param name="_actionReject">Lambda/funkcja dla akcji odrzucenia</param>
    UIMissionWidget(sf::Sprite _tlo, sf::Sprite _iconCity, sf::Sprite _btnAccept, sf::Sprite _btnReject,
        sf::Font& font, Misja& _misja, sf::Vector2f pozycjaStartowa,
        std::function<void()> _actionAccept, std::function<void()> _actionReject);

    /// <summary>
    /// Rozmieszcza elementy graficzne i tekstowe (ikony, przyciski, napisy) względem tła widgetu
    /// </summary>
    void placeWidgetElements();

    /// <summary>
    /// Obsługuje kliknięcia w obrębie widgetu, sprawdzając, czy trafiono w przyciski akceptacji lub odrzucenia
    /// </summary>
    /// <param name="event">Zdarzenie SFML</param>
    /// <param name="mousePos">Pozycja kursora</param>
    /// <returns>True, jeśli kliknięto w jeden z przycisków</returns>
    bool obsluzKlikniecie(const sf::Event& event, const sf::Vector2f& mousePos) override;

    /// <summary>
    /// Rysuje wszystkie składowe widgetu (tło, teksty, ikony, przyciski)
    /// </summary>
    /// <param name="window">Referencja do okna SFML</param>
    void draw(sf::RenderWindow& window) override;

    /// <summary>
    /// Aktualizuje pozycję widgetu oraz przelicza pozycje wszystkich jego elementów składowych
    /// </summary>
    /// <param name="bounds">Nowa pozycja (lewy górny róg)</param>
    virtual void setWidgetPos(const sf::Vector2f& bounds) override
    {
        UIWidget::setWidgetPos(bounds);
        placeWidgetElements();
    }
};