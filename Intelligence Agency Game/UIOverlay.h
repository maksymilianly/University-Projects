#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "UIElement.h"
#include "UIInfoPanel.h"
#include "UIEmployerWidget.h"

#include <functional>

#include "Assets.h"


struct Assets;

class UIOverlay : public UIElement
{
private:
	sf::Sprite tlo;

	bool isOpen;
	bool refresh;
	int lastClickedIdx = -1;

	int gridRows = 3;
	int gridCols = 3;

	std::string identifier;

	std::vector<std::unique_ptr<UIElement>> Elements;
	std::vector<std::unique_ptr<UIWidget>> Widgets;

	std::unique_ptr<UIInfoPanel> tooltip;
	bool show_tooltip = false;

public:
	UIOverlay(sf::Sprite podaneTlo, sf::Vector2f pozTla, std::string ident, int rows, int cols);
	
	void initTooltip(sf::Sprite tooltipBg, sf::Font& font);

	void draw(sf::RenderWindow& window);

	int getWidgetIdx(UIEmployerWidget* widget);

	const int getId() { return lastClickedIdx; }

	bool obsluzKlikniecie(const sf::Event& event, const sf::Vector2f& mousePos) override;

	void toogle()
	{
		isOpen = !isOpen;
		refresh = true; 
	}

	bool getRefresh() const
	{
		return refresh;
	}

	void setRefresh(bool value)
	{
		refresh = value;
	}
	
	bool getIsOpen() const
	{
		return isOpen;
	}

	void setIsOpen(bool value)
	{
		isOpen = value;
	}

	sf::Vector2i wierszKolumnaXxY(int X, int Y, int pozycja)
	{
		return { pozycja / X, pozycja % Y };
	}

	bool hasTooltip() const { return tooltip != nullptr; }

	sf::Vector2f getNewWidgetPosition();

	void addWidget(std::unique_ptr<UIWidget> widget);

	void clearWidgets() {
		Widgets.clear();
	}

	/*void createWidget(const std::vector<std::unique_ptr<Staff>>& oferty, Assets& assets,
	std::function<void(int)> buy, std::function<void(int)> remove, std::function<bool(Staff*)> filter);
	*/
};