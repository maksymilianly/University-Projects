#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "Ekran.h"
#include "GameScreen.h"


enum class AppState {
    Menu,
    Game,
    GameOver
};

class SceneManager {
private:
    std::vector<std::unique_ptr<Ekran>> gameScreens;

    //globalUImanager?

    Ekran* currentEkran;
    AppState currentState;

public:
    SceneManager();
    ~SceneManager() = default;

    void changeState(AppState newState);
    AppState getCurrentState() const;
    Ekran* getCurrentEkran() const;

    void drawScenes(sf::RenderWindow& window);
    void update(float dt);
    void obslugaZdarzen(const sf::Event& event, const sf::RenderWindow& window);

    void init(Assets& _assets, Config& _config, GameState& state);
};