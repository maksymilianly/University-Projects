#include "UIOverlay.h"

#include "UIElement.h"
#include "UIInfoPanel.h"


//#include "Assets.h"

#include <functional>
#include <memory>
#include <vector> 
#include <string>

#include <iostream>

import AssetsMod;


UIOverlay::UIOverlay(sf::Sprite podaneTlo, sf::Vector2f pozTla, std::string ident, int rows, int cols)
	: tlo(podaneTlo), isOpen(false), refresh(false),
	identifier(ident), gridRows(rows), gridCols(cols)
{
	tlo.setPosition(pozTla);
}

void UIOverlay::initTooltip(sf::Sprite tooltipBg, sf::Font& font) {
	tooltip = std::make_unique<UIInfoPanel>(tooltipBg, font);
}

void UIOverlay::draw(sf::RenderWindow& window)
{
	if (!isOpen) return;

	window.draw(tlo);

	for (const auto& widget : Widgets) {
		widget->draw(window);
	}

	if (show_tooltip && tooltip) {
		tooltip->draw(window);
	}
}

int UIOverlay::getWidgetIdx(UIEmployerWidget* widget)
{
	sf::FloatRect wBounds = widget->getWidgetBounds();
	sf::FloatRect tBounds = tlo.getGlobalBounds();

	float localX = wBounds.position.x - tBounds.position.x;
	float localY = wBounds.position.y - tBounds.position.y;

	float cellWidth = tBounds.size.x / 3.0f;
	float cellHeight = tBounds.size.y / 4.0f;

	int col = static_cast<int>(localX / cellWidth);
	int row = static_cast<int>(localY / cellHeight);
	return row * 3 + col;
}

bool UIOverlay::obsluzKlikniecie(const sf::Event& event, const sf::Vector2f& mousePos) {
	if (!isOpen) return false;

	if (const auto* mouseEvent = event.getIf<sf::Event::MouseMoved>())
	{
		show_tooltip = false;
		for (const auto& widget : Widgets) {
			if (widget->hovered(mousePos))
			{
				if (tooltip && widget->hasTooltip()) {
					tooltip->refreshData(widget->getTooltipText(), mousePos);
					show_tooltip = true;
					break;
				}
			}
		}
		return false;
	}


	for (const auto& widget : Widgets) {
		if (widget->obsluzKlikniecie(event, mousePos)) {
			if (identifier == "possesion") {
				isOpen = false;
			}
			return true;
		}
	}

	return false;
}


sf::Vector2f UIOverlay::getNewWidgetPosition() {

	int nowyWidgetIdx = Widgets.size();
	if (nowyWidgetIdx >= gridCols * gridRows) {
		return { -1.0f, -1.0f };
	}

	int col = nowyWidgetIdx % gridCols;
	int row = nowyWidgetIdx / gridCols;

	sf::FloatRect tempBounds = tlo.getGlobalBounds();

	float szerokoscWidgetu = 368.0f;
	float wysokoscWidgetu = 191.0f;

	float odstep = 15.0f;

	float startY = (identifier == "mission_panel") ? 30.0f : 150.0f;

	float x = tempBounds.position.x + 20.0f + (col * (szerokoscWidgetu + odstep));
	float y = tempBounds.position.y + startY + (row * (wysokoscWidgetu + odstep));

	return { x, y };
}

void UIOverlay::addWidget(std::unique_ptr<UIWidget> widget) { 
	sf::Vector2f nowaPozycja = getNewWidgetPosition();

	if (nowaPozycja.x < 0 || nowaPozycja.y < 0) {
		return;
	}
	widget->setWidgetPos(nowaPozycja);

	Widgets.push_back(std::move(widget));
}

/*void UIOverlay::createWidget(const std::vector<std::unique_ptr<Staff>>& oferty, Assets& assets,
	std::function<void(int)> buy, std::function<void(int)> remove, std::function<bool(Staff*)> filter = nullptr)
{
	if (!isOpen) return;
	Widgets.clear();

	if (!tooltip) {
		tooltip = std::make_unique<UIInfoPanel>(
			sf::Sprite(assets.textures.at("ui_info_panel")), assets.mainFont);
	}



	int idx = 0;
	for (const auto& oferta : oferty)
	{
		if (filter != nullptr && filter(oferta.get()) == false) {
			idx++; continue;
		}

		sf::Sprite ikonaPracownika = oferta->isAgent() //optymalizacja zrobic to sprawdzanie pred petla (stworzyc obiekt np agent i jezeli true to wszyscy pozostali tez beda agentami)
			? sf::Sprite(assets.textures.at("ui_icon_agent"))
			: sf::Sprite(assets.textures.at("ui_icon_group"));

		Widgets.push_back(std::make_unique<UIEmployerWidget>(
			sf::Sprite(assets.textures.at("ui_shop_bounds")),
			ikonaPracownika,
			sf::Sprite(assets.textures.at("ui_widgetbutton")),
			sf::Sprite(assets.textures.at("ui_widgetbutton")),
			assets.mainFont, *oferta,
			getNewWidgetPosition(),
			[buy, idx]() {buy(idx); },
			[remove, idx]() {remove(idx); }
		));

		idx++;
	}
}*/