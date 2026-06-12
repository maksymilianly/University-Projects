#pragma once
#include <SFML/Graphics.hpp>

struct Assets;
class GameState;

class SztabLogic
{
public:
    sf::Vector2f genRandomXY();

    void placeNowyStol(Assets& assets, GameState& state, int pojemnoscNowegoStolu);

    bool outOfScreenBounds(const sf::FloatRect& posStol);

    bool checkColision(const sf::FloatRect& obj1, const sf::FloatRect& obj2);
};