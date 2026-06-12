#pragma once
#include "GameSceneWithUI.h"

#include "MapaVisual.h"
#include "MapaLogic.h"
#include "MisjaManager.h"
#include "CountriesEnums.h"

#include <memory>

struct Assets;
struct Config;
class GameState;

class MapaManager : public GameSceneWithUI {
private:
    MapaVisual visual;
    MapaLogic logika;

	MisjaManager misja_manager;

    bool rysujGranice;
    std::string ktoraGranica;

	std::unique_ptr<UIOverlay> mission_panel;

public:
    MapaManager(Assets& _assets, Config& _config, GameState& _state);

    /*void update(sf::RenderWindow& window, float dt) {
		visual.zoom(dt,window);
    }*/

    void update(float dt) override;

    void draw(sf::RenderWindow& window) override;

    void obslugaZdarzen(const sf::Event& event, const sf::RenderWindow& window) override;

    void obslugaDanych() override;

};