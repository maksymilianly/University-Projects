#pragma once
#include "SFML/Graphics.hpp"


struct Assets;
struct Config;

class SignalCatcherLogic
{
private:
	sf::Vector2f catcherPos;
	sf::FloatRect radarBounds;
	float catcherRadius;
	float catcherMoveSpeed;

public:
	SignalCatcherLogic(Assets& assets, Config& config);

	void move(float dt, sf::Vector2f vector);

	sf::Vector2f& getCatcherPos() { return catcherPos; }
	float& getRadarRadius() { return catcherRadius; }

	void compareWithRadarBounds();

};