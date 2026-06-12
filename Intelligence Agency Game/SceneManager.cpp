#include "SceneManager.h"

SceneManager::SceneManager() {
    currentEkran = nullptr;
    currentState = AppState::Game;
}

void SceneManager::init(Assets& _assets, Config& _config, GameState& _state)
{
    gameScreens.push_back(std::make_unique<GameScreen>(_assets, _config, _state));
    currentEkran = gameScreens.back().get();
}

void SceneManager::changeState(AppState newState) {
    currentState = newState;
}

AppState SceneManager::getCurrentState() const {
    return currentState;
}

Ekran* SceneManager::getCurrentEkran() const {
    return currentEkran;
}

void SceneManager::update(float dt) {
    if (currentEkran) currentEkran->update(dt);
}

void SceneManager::drawScenes(sf::RenderWindow& window) {
    if (currentEkran) currentEkran->draw(window);
}

void SceneManager::obslugaZdarzen(const sf::Event& event, const sf::RenderWindow& window) {
    if (currentEkran) currentEkran->obslugaZdarzen(event, window);
}