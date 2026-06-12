#pragma once
#include "SFML/Graphics.hpp"

struct Assets;
struct Config;
class GameState;

class GameScenes 
{
protected:
	Assets& assets;
	Config& config;
	GameState& state;
public:
	GameScenes(Assets& _assets, Config& _config, GameState& _state)
		: assets(_assets), config(_config), state(_state) {
	}
	virtual ~GameScenes() = default;
	virtual void update(float dt) = 0;
	virtual void draw(sf::RenderWindow& window) = 0;
	virtual void obslugaZdarzen(const sf::Event& event, const sf::RenderWindow& window) = 0;
	virtual void obslugaDanych() = 0;
};