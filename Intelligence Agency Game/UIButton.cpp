#include "UIButton.h"

#include <SFML/Graphics.hpp>

#include "UIElement.h"
#include <functional>

UIButton::UIButton(const sf::Sprite& sprite, const sf::Vector2f& pos, std::function<void()> _action)
	: element(sprite), action(std::move(_action))
{
	element.setPosition(pos);
}

void UIButton::draw(sf::RenderWindow& window) 
{
	window.draw(element);
}

bool UIButton::obsluzKlikniecie(const sf::Event& event, const sf::Vector2f& mousePos)
{
    if (const auto* mouseEvent = event.getIf<sf::Event::MouseButtonPressed>())
    {
        if (mouseEvent->button == sf::Mouse::Button::Left)
        {
            if (element.getGlobalBounds().contains(mousePos))
            {
                if (action) {
                    action();
                }
                return true;
            }
        }
    }
    return false;
}