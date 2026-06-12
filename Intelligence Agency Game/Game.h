#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Assets.h"
#include "Config.h"
#include "SceneManager.h"
#include "GameState.h"
#include "GlobalUI.h"
#include <memory>



class Game {
private:
    sf::RenderWindow window;
    Assets assets;
    Config config;
    SceneManager ekrany;
    GameState state;
    std::unique_ptr<GlobalUI> UIManager;
public:
    Game();
    void run();
};