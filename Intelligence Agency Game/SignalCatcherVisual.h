#pragma once
#include "Visual.h"

struct Assets;
struct Config;


class SignalCatcherVisual : public Visual
{
private:
	sf::Sprite catcher;
public:
	SignalCatcherVisual(Assets& assets, Config& config);

	void update(sf::Vector2f vector);

	void drawDynamic(sf::RenderWindow& window);
	
};
