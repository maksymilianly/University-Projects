#pragma once
#include "Ekran.h"

#include "RadarManager.h"
#include "SztabManager.h"
#include "MapaManager.h"


#include "GameScenes.h"

#include <memory>
#include <vector>

struct Assets;
struct Config;
class GameState;


enum class GameScene {
	Radar,
	Sztab,
	Mapa
};

class GameScreen : public Ekran
{
private:
	std::vector<std::unique_ptr<GameScenes>> gameScenes;
	GameScene currentView;
public:

	GameScreen(Assets& _assets, Config& _config, GameState& _state);
			
	void init(Assets& assets, Config& config, GameState& state) override {};

	void update(float dt) override;

	void draw(sf::RenderWindow& window) override;

	void obslugaZdarzen(const sf::Event& event, const sf::RenderWindow& window) override;

	GameScene getCurrentView()
	{
		return currentView;
	}

	void obslugaDanych() override;
};