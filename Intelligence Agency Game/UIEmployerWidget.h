#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "UIWidget.h"
#include "Staff.h"

#include <functional>

class UIEmployerWidget : public UIWidget
{
private:

	sf::Sprite icon;
	sf::Sprite button_yes;
	sf::Sprite button_no;

	Staff& person;

	sf::Text text_yes; 
	sf::Text text_no;
	sf::Text text_working;

	std::function<void()> actionYes;
	std::function<void()> actionNo;

public:
	UIEmployerWidget(sf::Sprite _tlo, sf::Sprite _pracownik, sf::Sprite _buttonYes
		, sf::Sprite buttonNo, sf::Font& font, Staff& _person, sf::Vector2f pozycjaStartowa, std::function<void()> _actionYes, std::function<void()> _actionNo);

	void placeWidgetElements();

	virtual std::string getTooltipText() const override { return person.zwrocDane(); }

	bool obsluzKlikniecie(const sf::Event& event, const sf::Vector2f& mousePos) override;

	virtual void setWidgetPos(const sf::Vector2f& bounds) override
	{
		UIWidget::setWidgetPos(bounds);

		placeWidgetElements();

	}

	void draw(sf::RenderWindow& window) override;
	
	Staff& getPerson() { return person; }
	
};