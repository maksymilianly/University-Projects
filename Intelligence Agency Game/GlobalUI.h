#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <string>
#include <functional>

#include "UIElement.h"
#include "UIOverlay.h"

struct Assets;
struct Config;
class GameState;


class GlobalUI {
private:
    Assets& assets;
    Config& config;
    GameState& state;

    sf::Text moneyText;

public:
    GlobalUI(Assets& _assets, Config& _config, GameState& _state);

    void drawGlobalUI(sf::RenderWindow& window);

    void drawMoney(sf::RenderWindow& window);



};