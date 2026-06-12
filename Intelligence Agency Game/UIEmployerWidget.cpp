#include "UIEmployerWidget.h"

#include <functional>
#include "UIWidget.h"
#include "Staff.h"


UIEmployerWidget::UIEmployerWidget(sf::Sprite _tlo, sf::Sprite _pracownik, sf::Sprite _buttonYes
	, sf::Sprite buttonNo, sf::Font& font, Staff& _person, sf::Vector2f pozycjaStartowa, std::function<void()> _actionYes, std::function<void()> _actionNo)
	: UIWidget(_tlo, font, pozycjaStartowa), icon(_pracownik), button_yes(_buttonYes), button_no(buttonNo), person(_person),
	text_yes(font), text_no(font), text_working(font),
	actionYes(_actionYes), actionNo(_actionNo)
{
	info.setString(person.shopInfo());
	placeWidgetElements();

	text_yes.setString("Kup");
	text_yes.setCharacterSize(12);
	text_yes.setFillColor(sf::Color::White);

	text_no.setString("Usun");
	text_no.setCharacterSize(12);
	text_no.setFillColor(sf::Color::White);

	text_working.setString(person.getZajetyString());
	text_working.setCharacterSize(12);
	text_working.setFillColor(sf::Color::White);


}

void UIEmployerWidget::placeWidgetElements()
{
	sf::Vector2f baza = widget_bg.getPosition();
	icon.setPosition({ baza.x + 15.f, baza.y + 20.f });
	button_yes.setPosition({ baza.x + 175.0f, baza.y + 130.0f });
	button_no.setPosition({ baza.x + 275.0f, baza.y + 130.0f });
	info.setPosition({ baza.x + 120.0f, baza.y + 50.f });
	text_working.setPosition({ baza.x + 10.0f,baza.y + widget_bounds.size.y - 20.0f });


	auto centerText = [](sf::Text& text, const sf::Sprite& sprite) {
		sf::FloatRect textRect = text.getLocalBounds();
		text.setOrigin({ textRect.position.x + (textRect.size.x / 2.0f),
						 textRect.position.y + (textRect.size.y / 2.0f) });

		sf::FloatRect spriteRect = sprite.getGlobalBounds();
		text.setPosition({
			spriteRect.position.x + (spriteRect.size.x / 2.0f),
			spriteRect.position.y + (spriteRect.size.y / 2.0f)
			});
		};

	centerText(text_yes, button_yes);
	centerText(text_no, button_no);
}

bool UIEmployerWidget::obsluzKlikniecie(const sf::Event& event, const sf::Vector2f& mousePos)
{

	if (const auto* mouseEvent = event.getIf<sf::Event::MouseButtonPressed>())
	{
		if (mouseEvent->button == sf::Mouse::Button::Left)
		{
			if (button_yes.getGlobalBounds().contains(mousePos))
			{
				if (actionYes) { actionYes(); }
				return true;
			}
			else if (button_no.getGlobalBounds().contains(mousePos))
			{
				if (actionNo) { actionNo(); }
				return true;
			}
		}
	}
	return false;
}

void UIEmployerWidget::draw(sf::RenderWindow& window)
{
	if (person.getZajety())
	{
		text_working.setString("Zajety");
		text_working.setFillColor(sf::Color::Red);
	}
	else
	{
		text_working.setString("Wolny");
		text_working.setFillColor(sf::Color::Green);
	}

	window.draw(widget_bg);
	window.draw(icon);
	window.draw(info);
	window.draw(text_yes);
	window.draw(text_no);
	window.draw(button_yes);
	window.draw(button_no);
	window.draw(text_working);
}
