#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "Visual.h"

struct Assets;
struct Config;
class GameState;

	class UIVisual : public Visual
	{
	private:
		sf::Text kontoText;
		sf::Text sklepText;
		sf::Text pracownicyText;

		std::vector<sf::Text> opisOfert;
		std::vector<sf::FloatRect> hitboxyKupZadanie; 
		std::vector<sf::FloatRect> hitboxyUsunSprzedaj;

	public:
		UIVisual(Assets& assets, Config& config, GameState& state);

		void update(GameState& state);


		void draw(sf::RenderWindow& window) override;

		void drawShopButton(sf::RenderWindow& window, bool czyPracownicy);

		void drawDynamic(sf::RenderWindow& window, bool shopOpen, bool czyPracownicy, const std::vector<std::string>& identyfikatory, Assets& assets, Config& config);

		sf::FloatRect getShopButton() const& { return sprites.at("ui_shop_button").getGlobalBounds(); }

		std::vector<std::string> zaladujDaneSklepu(bool czyPracownicy, GameState& state, Assets& assets);

		int sprawdzKlikniecieGora(const sf::Vector2f& mousePos);

		int sprawdzKlikniecieDol(const sf::Vector2f& mousePos);

	};