#pragma once
#include <SFML/Graphics.hpp>

#include "UIWidget.h"
#include "UIButton.h"
#include <memory>

#include <functional>

class UIInfoPanel : public UIWidget
{
private:
    std::unique_ptr<UIButton> UIPbutton;
public:
    UIInfoPanel(sf::Sprite bg, sf::Font& mainFont);
    UIInfoPanel(sf::Sprite bg, sf::Font& mainFont, sf::Sprite button_sprite, std::function<void()> onClick);

    void refreshData(const std::string& noweDane, sf::Vector2f nowaPozycja);

    void draw_additions(sf::RenderWindow& window);

    bool obsluzKlikniecie(const sf::Event& event, const sf::Vector2f& mousePos) override;

    bool hovered(const sf::Vector2f& mousePos) override { return false;}

};