#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "UIElement.h"


class UIWidget : public UIElement
{
protected:
	sf::Sprite widget_bg;
	sf::FloatRect widget_bounds;
	sf::Text info;
public:
	UIWidget(sf::Sprite bg, sf::Font& mainFont, sf::Vector2f bgPos);

	void setInfo(std::string informacja);

	virtual void draw(sf::RenderWindow& window) override;

	sf::FloatRect getWidgetBounds() const;

	virtual void setWidgetPos(const sf::Vector2f& bounds)
	{
		widget_bounds.position.x = bounds.x;
		widget_bounds.position.y = bounds.y;

		widget_bg.setPosition(bounds);
	}

	bool hasTooltip() const { return !info.getString().isEmpty(); }

	virtual std::string getTooltipText() const { return info.getString(); }

	virtual bool obsluzKlikniecie(const sf::Event& event, const sf::Vector2f& mousePos) = 0;

	virtual bool hovered(const sf::Vector2f& mousePos) override;

	virtual sf::Text getInfo() { return info; }

};