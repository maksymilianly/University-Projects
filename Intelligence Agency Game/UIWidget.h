#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "UIElement.h"

/// <summary>
/// Klasa rozszerzająca UIElement o obsługę tła (sprite) oraz wyświetlanie informacji tekstowych
/// Służy jako klasa bazowa dla wszystkich widgetów, które posiadają podkład graficzny i wyświetlają dane (np. panele informacyjne, etykiety)
/// </summary>
class UIWidget : public UIElement {
protected:
    /// <summary>Tło widgetu</summary>
    sf::Sprite widget_bg;
    /// <summary>Obszar prostokątny wyznaczający granice widgetu (używany do kolizji)</summary>
    sf::FloatRect widget_bounds;
    /// <summary>Obiekt tekstowy wyświetlający informacje</summary>
    sf::Text info;

public:
    /// <summary>
    /// Inicjalizuje widget z podanym tłem, czcionką i pozycją
    /// </summary>
    /// <param name="bg">Sprite służący jako tło</param>
    /// <param name="mainFont">Referencja do załadowanej czcionki</param>
    /// <param name="bgPos">Początkowa pozycja widgetu</param>
    UIWidget(sf::Sprite bg, sf::Font& mainFont, sf::Vector2f bgPos);

    /// <summary>Ustawia treść informacyjną widgetu</summary>
    /// <param name="informacja">Tekst do wyświetlenia</param>
    void setInfo(std::string informacja);

    /// <summary>Rysuje tło oraz tekst widgetu w oknie</summary>
    virtual void draw(sf::RenderWindow& window) override;

    /// <summary>Zwraca granice widgetu</summary>
    sf::FloatRect getWidgetBounds() const;

    /// <summary>Aktualizuje pozycję tła i granic widgetu</summary>
    /// <param name="bounds">Nowa pozycja (lewy górny róg)</param>
    virtual void setWidgetPos(const sf::Vector2f& bounds)
    {
        widget_bounds.position.x = bounds.x;
        widget_bounds.position.y = bounds.y;

        widget_bg.setPosition(bounds);
    }

    /// <summary>Sprawdza, czy widget posiada zdefiniowaną treść podpowiedzi (tooltipa)</summary>
    /// <returns>True, jeśli tekst nie jest pusty</returns>
    bool hasTooltip() const { return !info.getString().isEmpty(); }

    /// <summary>Zwraca treść podpowiedzi</summary>
    virtual std::string getTooltipText() const { return info.getString(); }

    /// <summary>Czysto wirtualna metoda obsługi kliknięcia. Klasy pochodne muszą ją zaimplementować</summary>
    virtual bool obsluzKlikniecie(const sf::Event& event, const sf::Vector2f& mousePos) = 0;

    /// <summary>Sprawdza, czy kursor znajduje się w granicach widgetu</summary>
    /// <param name="mousePos">Aktualna pozycja kursora</param>
    /// <returns>True, jeśli kursor najeżdża na widget</returns>
    virtual bool hovered(const sf::Vector2f& mousePos) override;

    /// <summary>Zwraca obiekt tekstowy widgetu</summary>
    virtual sf::Text getInfo() { return info; }
};