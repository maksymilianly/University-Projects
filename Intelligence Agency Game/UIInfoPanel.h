#pragma once
#include <SFML/Graphics.hpp>
#include "UIWidget.h"
#include "UIButton.h"
#include <memory>
#include <functional>

/// <summary>
/// Panel informacyjny (info box) rozszerzający UIWidget 
/// Służy do wyświetlania tekstu, może opcjonalnie zawierać przycisk funkcyjny
/// </summary>
class UIInfoPanel : public UIWidget {
private:
    /// <summary>Opcjonalny przycisk umieszczony wewnątrz panelu</summary>
    std::unique_ptr<UIButton> UIPbutton;

public:
    /// <summary>Inicjalizuje panel informacyjny bez przycisku</summary>
    /// <param name="bg">Sprite tła</param>
    /// <param name="mainFont">Referencja do czcionki</param>
    UIInfoPanel(sf::Sprite bg, sf::Font& mainFont);

    /// <summary>Inicjalizuje panel informacyjny z przyciskiem funkcyjnym</summary>
    /// <param name="bg">Sprite tła</param>
    /// <param name="mainFont">Referencja do czcionki</param>
    /// <param name="button_sprite">Sprite przycisku</param>
    /// <param name="onClick">Funkcja wywoływana po kliknięciu przycisku</param>
    UIInfoPanel(sf::Sprite bg, sf::Font& mainFont, sf::Sprite button_sprite, std::function<void()> onClick);

    /// <summary>
    /// Aktualizuje zawartość tekstową panelu oraz jego pozycję na ekranie
    /// </summary>
    /// <param name="noweDane">Tekst do wyświetlenia</param>
    /// <param name="nowaPozycja">Nowa pozycja panelu</param>
    void refreshData(const std::string& noweDane, sf::Vector2f nowaPozycja);

    /// <summary>
    /// Rysuje dodatkowe elementy panelu (np. przycisk), które nie są częścią standardowego rysowania widgetu
    /// </summary>
    /// <param name="window">Referencja do okna SFML</param>
    void draw_additions(sf::RenderWindow& window);

    /// <summary>
    /// Obsługuje kliknięcie w panelu. Przekazuje również zdarzenie do wewnętrznego przycisku, jeśli istnieje
    /// </summary>
    /// <param name="event">Zdarzenie SFML</param>
    /// <param name="mousePos">Pozycja kursora</param>
    /// <returns>True, jeśli kliknięcie trafiło w przycisk lub panel</returns>
    bool obsluzKlikniecie(const sf::Event& event, const sf::Vector2f& mousePos) override;

    /// <summary>
    /// Nadpisana metoda, która wymusza, aby ten panel nie reagował na najechanie kursorem
    /// </summary>
    bool hovered(const sf::Vector2f& mousePos) override { return false; }
};