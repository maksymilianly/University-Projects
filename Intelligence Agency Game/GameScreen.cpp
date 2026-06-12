#include "GameScreen.h"


#include "Assets.h"
#include "Config.h"
#include "GameState.h"


GameScreen::GameScreen(Assets& _assets, Config& _config, GameState& _state) : Ekran(_assets, _config, _state)
{
	currentView = GameScene::Radar;

	gameScenes.push_back(std::make_unique<RadarManager>(assets, config, state)); //0
	gameScenes.push_back(std::make_unique<SztabManager>(assets, config, state)); //1
	gameScenes.push_back(std::make_unique<MapaManager>(assets, config, state)); //2
}


void GameScreen::update(float dt)
{
	for (auto& scene : gameScenes)
	{
		scene->update(dt);
	}
}

void GameScreen::draw(sf::RenderWindow& window)
{
	if (currentView == GameScene::Radar) gameScenes[0]->draw(window);
	else if (currentView == GameScene::Sztab) gameScenes[1]->draw(window);
	else if (currentView == GameScene::Mapa) gameScenes[2]->draw(window);
}

void GameScreen::obslugaZdarzen(const sf::Event& event, const sf::RenderWindow& window)
{
	if (const auto* key = event.getIf<sf::Event::KeyPressed>())
	{
		if (key->scancode == sf::Keyboard::Scancode::Num1
			|| key->scancode == sf::Keyboard::Scancode::Numpad1)
		{
			currentView = GameScene::Radar;
		}
		else if (key->scancode == sf::Keyboard::Scancode::Num2
			|| key->scancode == sf::Keyboard::Scancode::Numpad2)
		{
			currentView = GameScene::Sztab;
		}
		else if (key->scancode == sf::Keyboard::Scancode::Num3
			|| key->scancode == sf::Keyboard::Scancode::Numpad3)
		{
			currentView = GameScene::Mapa;
		}
	}

	if (currentView == GameScene::Radar) gameScenes[0]->obslugaZdarzen(event, window);
	else if (currentView == GameScene::Sztab) gameScenes[1]->obslugaZdarzen(event, window);
	else if (currentView == GameScene::Mapa) gameScenes[2]->obslugaZdarzen(event, window);
}

void GameScreen::obslugaDanych() 
{
	for (auto& scene : gameScenes)
	{
		scene->obslugaDanych();
	}
}