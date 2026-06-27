#pragma once
#include "Visual.h"

import AssetsMod;
import ConfigMod;

class GameOverVisual : public Visual {
private:

public:
    GameOverVisual(Assets& assets, Config& config) : Visual(assets, config, "_go") {

	}

	void draw(sf::RenderWindow& window) override {
		Visual::draw(window);
	}

   


};