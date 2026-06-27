#include "SceneManager.h"
#include "GameOverScreen.h"


SceneManager::SceneManager() {
    currentEkran = nullptr;
    currentState = AppState::Game;
}

void SceneManager::init(Assets& _assets, Config& _config, GameState& _state)
{
    gameScreens.push_back(std::make_unique<GameScreen>(_assets, _config, _state));
    currentEkran = gameScreens.back().get();
    gameOverScreen = std::make_unique<GameOverScreen>(_assets, _config, _state);

    m_assets = &_assets;
    m_config = &_config;
    m_state = &_state;
}

void SceneManager::changeState(AppState newState) {
    currentState = newState;

    if (currentState == AppState::GameOver && m_assets && m_config && m_state) {
        invokeGameOverScene();
    }
}

AppState SceneManager::getCurrentState() const {
    return currentState;
}

Ekran* SceneManager::getCurrentEkran() const {
    return currentEkran;
}

void SceneManager::update(float dt) {
    if (currentEkran && currentState != AppState::GameOver)
    {
        currentEkran->update(dt);
    }
    else if (currentState == AppState::GameOver && gameOverScreen) {
		gameOverScreen->update(dt);
	}

}

void SceneManager::drawScenes(sf::RenderWindow& window) {
    if (currentState != AppState::GameOver) {
        currentEkran->draw(window);
    }
    else if (currentState == AppState::GameOver && gameOverScreen) {
        gameOverScreen->draw(window);
    }
}

void SceneManager::invokeGameOverScene()
    {
	gameOverScreen->init(*m_assets, *m_config, *m_state);
    }

void SceneManager::obslugaZdarzen(const sf::Event& event, const sf::RenderWindow& window) {
    if (currentEkran) currentEkran->obslugaZdarzen(event, window);
}