#include "UIInfoPanel.h"

#include <SFML/Graphics.hpp>


UIInfoPanel::UIInfoPanel(sf::Sprite bg, sf::Font& mainFont)
    : UIWidget(bg, mainFont, { 0.0f, 0.0f })
{
    UIPbutton = nullptr;
    info.setCharacterSize(20);
    info.setFillColor(sf::Color::Black);
}

UIInfoPanel::UIInfoPanel(sf::Sprite bg, sf::Font& mainFont, sf::Sprite buttonSprite, std::function<void()> onClick)
    : UIWidget(bg, mainFont, { 0.0f, 0.0f })
{
    UIPbutton = std::make_unique<UIButton>(buttonSprite, sf::Vector2f{ 0.0f, 0.0f }, onClick);

    info.setCharacterSize(20);
    info.setFillColor(sf::Color::Black);
}

void UIInfoPanel::draw_additions(sf::RenderWindow& window)
{
    if (UIPbutton)
    {
        UIPbutton->draw(window);
    }
}

void UIInfoPanel::refreshData(const std::string& noweDane, sf::Vector2f nowaPozycja)
{
    info.setString(noweDane);

    widget_bg.setPosition({ nowaPozycja.x, nowaPozycja.y + 15.0f });
    sf::Vector2f bgPos = widget_bg.getPosition();
    sf::Vector2f bgSize = widget_bg.getGlobalBounds().size;
    info.setPosition({ bgPos.x + bgSize.x / 4.0f, bgPos.y + bgSize.y / 4.0f });
    if (UIPbutton)
    {
        UIPbutton->setPos({ bgPos.x + bgSize.x / 2.0f,bgPos.y + bgSize.y-50.0f});
    }
    widget_bounds = widget_bg.getGlobalBounds();
}

bool UIInfoPanel::obsluzKlikniecie(const sf::Event& _event, const sf::Vector2f& mousePos)
{
    if (UIPbutton)
    {
        if (UIPbutton->obsluzKlikniecie(_event, mousePos))
        {
            return true;
        }
    }
    return false;
}
