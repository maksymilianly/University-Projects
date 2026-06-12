#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class UIElement
{
public:
	virtual ~UIElement() = default;
	virtual void draw(sf::RenderWindow& window) = 0;
	//virtual void update(const sf::Event& event) = 0;
	virtual bool obsluzKlikniecie(const sf::Event& event, const sf::Vector2f& mousePos) = 0;
	virtual bool hovered(const sf::Vector2f& mousePos) { return false; }
};	