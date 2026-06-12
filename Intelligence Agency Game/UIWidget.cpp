#include "UIWidget.h"

UIWidget::UIWidget(sf::Sprite bg, sf::Font& mainFont, sf::Vector2f bgPos)
	: widget_bg(bg), info(mainFont)
{
	widget_bg.setPosition(bgPos);
	widget_bounds = widget_bg.getGlobalBounds();
}

void UIWidget::setInfo(std::string informacja)
{
	info.setString(informacja);
	info.setCharacterSize(12);
	info.setFillColor(sf::Color::White);
}

void UIWidget::draw(sf::RenderWindow & window) 
{
	window.draw(widget_bg);
	window.draw(info);
}

sf::FloatRect UIWidget::getWidgetBounds() const
{
	return widget_bounds;
}

bool UIWidget::hovered(const sf::Vector2f& mousePos){
	return getWidgetBounds().contains(mousePos);
}