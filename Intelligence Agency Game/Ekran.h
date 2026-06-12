#pragma once
#include <SFML/Graphics.hpp>

struct Assets;
struct Config;
class GameState;

class Ekran {
protected:
    Assets& assets;
    Config& config;
	GameState& state;
public:
    Ekran(Assets& _assets, Config& _config, GameState& _state)
        : assets(_assets), config(_config), state(_state) {
    }

    virtual void init(Assets& assets,Config& config,GameState& state) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void update(float dt) = 0;
    virtual void obslugaZdarzen(const sf::Event& event, const sf::RenderWindow& window) = 0;
    virtual void obslugaDanych() = 0;
    virtual ~Ekran() = default;
};