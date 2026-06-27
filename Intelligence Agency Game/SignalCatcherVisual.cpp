#include "SignalCatcherVisual.h"

//#include "Assets.h"
//#include "Config.h"
import AssetsMod;
import ConfigMod;




SignalCatcherVisual::SignalCatcherVisual(Assets& assets, Config& config) : Visual(assets,config,"target_")
, catcher(sprites.at("target_catcher"))
{
}

void SignalCatcherVisual::drawDynamic(sf::RenderWindow& window)
{
	window.draw(catcher);
}

void SignalCatcherVisual::update(sf::Vector2f vector)
{
	catcher.setPosition(vector);
}

