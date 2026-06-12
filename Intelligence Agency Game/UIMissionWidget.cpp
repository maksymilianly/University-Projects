#include "UIMissionWidget.h"

UIMissionWidget::UIMissionWidget(sf::Sprite _tlo, sf::Sprite _iconCity, sf::Sprite _btnAccept, sf::Sprite _btnReject,
    sf::Font& font, Misja& _misja, sf::Vector2f pozycjaStartowa,
    std::function<void()> _actionAccept, std::function<void()> _actionReject)
    : UIWidget(_tlo, font, pozycjaStartowa),
    icon_city(_iconCity),
    button_accept(_btnAccept),
    button_reject(_btnReject),
    misja(_misja),
    actionAccept(_actionAccept),
    actionReject(_actionReject),
	text_city(font), text_country(font), text_accept(font), text_reject(font)
{
    text_accept.setFont(font);
    text_accept.setString("Przyjmij");
    text_accept.setCharacterSize(12);
    text_accept.setFillColor(sf::Color::White);

    text_reject.setFont(font);
    text_reject.setString("Odrzuc");
    text_reject.setCharacterSize(12);
    text_reject.setFillColor(sf::Color::White);

    text_city.setFont(font);
    text_city.setString(misja.getNazwa()); 
	text_city.setCharacterSize(14);

}

void UIMissionWidget::placeWidgetElements() {
    sf::Vector2f baza = widget_bg.getPosition();

    icon_city.setPosition({ baza.x + 15.f, baza.y + 20.f });

    text_city.setPosition({ baza.x + 100.f, baza.y + 20.f });
    text_country.setPosition({ baza.x + 100.f, baza.y + 50.f });

    button_accept.setPosition({ baza.x + 175.0f, baza.y + 130.0f });
    button_reject.setPosition({ baza.x + 275.0f, baza.y + 130.0f });

    auto centerText = [](sf::Text& text, const sf::Sprite& sprite) {
        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin({ textRect.position.x + (textRect.size.x / 2.0f),
                         textRect.position.y + (textRect.size.y / 2.0f) });

        sf::FloatRect spriteRect = sprite.getGlobalBounds();
        text.setPosition({ spriteRect.position.x + (spriteRect.size.x / 2.0f),
                           spriteRect.position.y + (spriteRect.size.y / 2.0f) });
        };

    centerText(text_accept, button_accept);
    centerText(text_reject, button_reject);
}

void UIMissionWidget::draw(sf::RenderWindow& window) {
    UIWidget::draw(window);

    window.draw(icon_city);

    window.draw(button_accept);
    window.draw(button_reject);

    window.draw(text_city);
    window.draw(text_country);
    window.draw(text_accept);
    window.draw(text_reject);
}

bool UIMissionWidget::obsluzKlikniecie(const sf::Event& event, const sf::Vector2f& mousePos) {
    if (const auto* mouseEvent = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (mouseEvent->button == sf::Mouse::Button::Left) {

            if (button_accept.getGlobalBounds().contains(mousePos)) {
                if (actionAccept) {
                    actionAccept(); 
                }
                return true;
            }

            if (button_reject.getGlobalBounds().contains(mousePos)) {
                if (actionReject) {
                    actionReject(); 
                }
                return true;
            }
        }
    }
    return false;
}