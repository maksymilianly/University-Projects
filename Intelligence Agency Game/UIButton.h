#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "UIElement.h"
#include <functional>

class UIButton : public UIElement
{
private:
    sf::Sprite element;
    std::function<void()> action;

public:
    UIButton(const sf::Sprite& sprite, const sf::Vector2f& pos, std::function<void()> _action);

    void draw(sf::RenderWindow& window);

    void setPos(sf::Vector2f newPos) { element.setPosition(newPos); }

    bool obsluzKlikniecie(const sf::Event& event, const sf::Vector2f& mousePos) override;
};

