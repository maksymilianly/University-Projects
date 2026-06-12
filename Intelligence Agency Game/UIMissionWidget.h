#pragma once
#include "UIWidget.h"
#include "Misja.h" 
#include <functional>

class UIMissionWidget : public UIWidget {
private:
    sf::Sprite icon_city;
    sf::Sprite button_accept;
    sf::Sprite button_reject;

    Misja& misja;

    sf::Text text_city;
    sf::Text text_country;
    sf::Text text_accept; 
    sf::Text text_reject; 

    std::function<void()> actionAccept;
    std::function<void()> actionReject;

public:
    UIMissionWidget(sf::Sprite _tlo, sf::Sprite _iconCity, sf::Sprite _btnAccept, sf::Sprite _btnReject,
        sf::Font& font, Misja& _misja, sf::Vector2f pozycjaStartowa,
        std::function<void()> _actionAccept, std::function<void()> _actionReject);

    void placeWidgetElements();
    bool obsluzKlikniecie(const sf::Event& event, const sf::Vector2f& mousePos) override;
    void draw(sf::RenderWindow& window) override;

    virtual void setWidgetPos(const sf::Vector2f& bounds) override
    {
        UIWidget::setWidgetPos(bounds);
        placeWidgetElements();
    }
};