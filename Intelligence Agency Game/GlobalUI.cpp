#include "GlobalUI.h"
#include <SFML/Graphics.hpp>

#include "UIVisual.h"
#include "UILogic.h"
#include "UIEmployerWidget.h"
#include "UIButton.h"

#include "GameState.h"
//#include "Config.h"
//#include "Assets.h"
#include <vector>
#include <memory>

import AssetsMod;
import ConfigMod; 

GlobalUI::GlobalUI(Assets& _assets, Config& _config, GameState& _state)
    : assets(_assets), config(_config), state(_state),moneyText(_assets.mainFont)
{
    moneyText.setPosition({20.0f,20.0f});
    moneyText.setFillColor(sf::Color::Yellow);
    moneyText.setOutlineColor(sf::Color::Black);
}


void GlobalUI::drawGlobalUI(sf::RenderWindow& window)
{
    drawMoney(window);
    window.draw(moneyText);
}

void GlobalUI::drawMoney(sf::RenderWindow& window)
{
    moneyText.setString("$: " + std::to_string(state.getBank()));
}