#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "UIWidget.h"
#include "Staff.h"
#include <functional>

/// <summary>
/// Widget reprezentujący pracownika w interfejsie zatrudnienia
/// Odpowiada za wyświetlanie informacji o pracowniku, jego ikony oraz przycisków interakcji
/// </summary>
class UIEmployerWidget : public UIWidget {
private:
    /// <summary>Ikona/portret pracownika</summary>
    sf::Sprite icon;
    /// <summary>Przycisk potwierdzenia</summary>
    sf::Sprite button_yes;
    /// <summary>Przycisk odrzucenia</summary>
    sf::Sprite button_no;

    /// <summary>Referencja do obiektu pracownika, którego dotyczy widget</summary>
    Staff& person;

    /// <summary>Tekstowe etykiety dla przycisków i statusu pracy</summary>
    sf::Text text_yes;
    sf::Text text_no;
    sf::Text text_working;

    /// <summary>Akcja wywoływana przy kliknięciu przycisku "Tak"</summary>
    std::function<void()> actionYes;
    /// <summary>Akcja wywoływana przy kliknięciu przycisku "Nie"</summary>
    std::function<void()> actionNo;

public:
    /// <summary>
    /// Inicjalizuje widget pracownika
    /// </summary>
    /// <param name="_tlo">Sprite tła widgetu</param>
    /// <param name="_pracownik">Sprite ikony/portretu pracownika</param>
    /// <param name="_buttonYes">Sprite przycisku akceptacji</param>
    /// <param name="buttonNo">Sprite przycisku odrzucenia</param>
    /// <param name="font">Referencja do czcionki</param>
    /// <param name="_person">Referencja do obiektu pracownika</param>
    /// <param name="pozycjaStartowa">Pozycja początkowa widgetu</param>
    /// <param name="_actionYes">Akcja (callback) dla przycisku Yes</param>
    /// <param name="_actionNo">Akcja (callback) dla przycisku No</param>
    UIEmployerWidget(sf::Sprite _tlo, sf::Sprite _pracownik, sf::Sprite _buttonYes,
        sf::Sprite buttonNo, sf::Font& font, Staff& _person, sf::Vector2f pozycjaStartowa,
        std::function<void()> _actionYes, std::function<void()> _actionNo);

    /// <summary>
    /// Rozmieszcza elementy graficzne i tekstowe widgetu (ikony, przyciski, opisy) względem tła
    /// </summary>
    void placeWidgetElements();

    /// <summary>
    /// Zwraca treść podpowiedzi (tooltipa) na podstawie danych pracownika 
    /// </summary>
    virtual std::string getTooltipText() const override { return person.zwrocDane(); }

    /// <summary>
    /// Obsługuje kliknięcia w obrębie widgetu, sprawdzając, czy trafiono w przyciski akcji
    /// </summary>
    /// <param name="event">Zdarzenie SFML</param>
    /// <param name="mousePos">Pozycja kursora myszy</param>
    /// <returns>True, jeśli kliknięto w jeden z przycisków</returns>
    bool obsluzKlikniecie(const sf::Event& event, const sf::Vector2f& mousePos) override;

    /// <summary>
    /// Aktualizuje pozycję widgetu oraz przelicza pozycje wszystkich jego elementów składowych
    /// </summary>
    /// <param name="bounds">Nowa pozycja (lewy górny róg)</param>
    virtual void setWidgetPos(const sf::Vector2f& bounds) override
    {
        UIWidget::setWidgetPos(bounds);
        placeWidgetElements();
    }

    /// <summary>
    /// Rysuje wszystkie składowe widgetu w oknie gry
    /// </summary>
    /// <param name="window">Referencja do okna SFML</param>
    void draw(sf::RenderWindow& window) override;

    /// <summary>
    /// Zwraca referencję do obiektu pracownika powiązanego z tym widgetem
    /// </summary>
    Staff& getPerson() { return person; }
};