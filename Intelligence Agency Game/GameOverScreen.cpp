#include "GameOverScreen.h"
//#include "Assets.h"
//#include "Config.h"
#include "GameState.h"

import AssetsMod;
import ConfigMod;


GameOverScreen::GameOverScreen(Assets& _assets, Config& _config, GameState& _state) : Ekran(_assets, _config, _state)
{

}


bool GameOverScreen::timeOver(float dt)
{
	if (gameOver == nullptr) {
		return false;
	}
	time_to_close -= dt;
	if (time_to_close <= 0.0f) {
		return true;
	}
	return false;
}

void GameOverScreen::init(Assets& assets, Config& config, GameState& state) {
	gameOver = std::make_unique<GameOverVisual>(assets, config);
}

void GameOverScreen::draw(sf::RenderWindow& window)
{
	gameOver->draw(window);
}


void GameOverScreen::update(float dt) {
	
	timeOver(dt);
}

void GameOverScreen::obslugaZdarzen(const sf::Event& event, const sf::RenderWindow& window) {
	
}

void GameOverScreen::obslugaDanych() {
}