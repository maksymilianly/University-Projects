#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "UIElement.h"
#include "UIInfoPanel.h"
#include "UIEmployerWidget.h"
#include <functional>
#include <memory>


import AssetsMod;

/// <summary>
/// Klasa zarządzająca panelem interfejsu (nakładką) 
/// Przechowuje i układa elementy (widgety) w siatce, zarządza stanem widoczności oraz wyświetlaniem podpowiedzi (tooltipów)
/// </summary>
class UIOverlay : public UIElement {
private:
	/// <summary>Sprite tła nakładki</summary>
	sf::Sprite tlo;
	/// <summary>Status widoczności nakładki</summary>
	bool isOpen;
	/// <summary>Flaga wymagająca odświeżenia zawartości (np. po zmianie danych)</summary>
	bool refresh;
	/// <summary>Indeks ostatnio klikniętego widgetu (-1 oznacza brak)</summary>
	int lastClickedIdx = -1;

	/// <summary>Liczba wierszy w siatce</summary>
	int gridRows = 3;
	/// <summary>Liczba kolumn w siatce</summary>
	int gridCols = 3;

	/// <summary>Identyfikator nakładki</summary>
	std::string identifier;

	/// <summary>Kontener na ogólne elementy UI</summary>
	std::vector<std::unique_ptr<UIElement>> Elements;
	/// <summary>Kontener na widgety specyficzne dla nakładki (np. karty pracowników)</summary>
	std::vector<std::unique_ptr<UIWidget>> Widgets;

	/// <summary>Panel podpowiedzi wyświetlany po najechaniu na widget</summary>
	std::unique_ptr<UIInfoPanel> tooltip;
	bool show_tooltip = false;

public:
	/// <summary>
	/// Inicjalizuje nakładkę (overlay) z określonym wyglądem i parametrami siatki
	/// </summary>
	/// <param name="podaneTlo">Sprite tła</param>
	/// <param name="pozTla">Pozycja tła</param>
	/// <param name="ident">Unikalny identyfikator nakładki</param>
	/// <param name="rows">Liczba wierszy siatki</param>
	/// <param name="cols">Liczba kolumn siatki</param>
	UIOverlay(sf::Sprite podaneTlo, sf::Vector2f pozTla, std::string ident, int rows, int cols);

	/// <summary>Inicjalizuje panel podpowiedzi (tooltip) dla tej nakładki</summary>
	void initTooltip(sf::Sprite tooltipBg, sf::Font& font);

	/// <summary>Rysuje tło oraz wszystkie aktywne widgety w nakładce</summary>
	void draw(sf::RenderWindow& window);

	/// <summary>Zwraca indeks danego widgetu w nakładce</summary>
	int getWidgetIdx(UIEmployerWidget* widget);

	/// <summary>Zwraca identyfikator ostatnio klikniętego elementu</summary>
	const int getId() { return lastClickedIdx; }

	/// <summary>Obsługuje kliknięcia w obrębie nakładki i deleguje je do odpowiednich widgetów</summary>
	bool obsluzKlikniecie(const sf::Event& event, const sf::Vector2f& mousePos) override;

	/// <summary>Przełącza stan widoczności i oznacza nakładkę do odświeżenia</summary>
	void toogle() {
		isOpen = !isOpen;
		refresh = true;
	}

	bool getRefresh() const { return refresh; }
	void setRefresh(bool value) { refresh = value; }
	bool getIsOpen() const { return isOpen; }
	void setIsOpen(bool value) { isOpen = value; }

	/// <summary>
	/// Pomocnicza metoda obliczająca pozycję siatki (wiersz, kolumna) na podstawie indeksu
	/// </summary>
	/// <param name="X">Liczba kolumn</param>
	/// <param name="Y">Liczba wierszy</param>
	/// <param name="pozycja">Indeks elementu</param>
	sf::Vector2i wierszKolumnaXxY(int X, int Y, int pozycja)
	{
		return { pozycja / X, pozycja % Y };
	}

	bool hasTooltip() const { return tooltip != nullptr; }

	/// <summary>Oblicza pozycję dla nowego widgetu na podstawie zajętego miejsca w siatce</summary>
	sf::Vector2f getNewWidgetPosition();

	/// <summary>Dodaje nowy widget do nakładki</summary>
	void addWidget(std::unique_ptr<UIWidget> widget);

	/// <summary>Usuwa wszystkie widgety z nakładki</summary>
	void clearWidgets() { Widgets.clear(); }
};