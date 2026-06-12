#pragma once
#include "SFML/Graphics.hpp"

struct Config;
class GameState;


class UILogic
{
private:
	bool shopOpen;
	bool czyPracownicy;
public:
    UILogic(Config& config, GameState& state);

    bool checkShopButton(const sf::Vector2f& mousePos, const sf::FloatRect& przycisk);

    bool getShopOpen() { return shopOpen; }
    bool getCzyPracownicy() { return czyPracownicy; }

};