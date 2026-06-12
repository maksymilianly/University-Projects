#pragma once
#include "SFML/Graphics.hpp"

#include "MisjaLogic.h"
#include "MisjaVisual.h"

struct Assets;
struct Config;
class GameState;

class MisjaManager
{
private:
	MisjaLogic logika;
	MisjaVisual visual;

	Assets& assets;
	Config& config;
	GameState& state;

public:
	MisjaManager(Assets& _assets, Config& _config, GameState& _state);

	void update(float dt);

	void draw(sf::RenderWindow& window);

	std::vector<std::string> checkCities(std::string panstwo);

	void obslugaZdarzen(const sf::Event& event, const sf::RenderWindow& window);

	void obslugaDanych();

};