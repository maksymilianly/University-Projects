#include "SztabLogic.h"

#include "Stol.h"
#include <random>

//#include "Assets.h"
#include "GameState.h"

import AssetsMod;

sf::Vector2f SztabLogic::genRandomXY()
{
	static std::random_device rd;
	static std::mt19937 engine(rd());

	std::uniform_real_distribution<float> X(0.0f, 1920.0f);
	std::uniform_real_distribution<float> Y(0.0f, 540.0f);

	return { X(engine),Y(engine) };
}

void SztabLogic::placeNowyStol(Assets& assets, GameState& state, int pojemnoscNowegoStolu)
{
    std::string key = "stuff_stol" + std::to_string(pojemnoscNowegoStolu);
    float szerokosc = assets.textures.at(key).getSize().x;
    float wysokosc = assets.textures.at(key).getSize().y;

    bool colision;
    sf::Vector2f tempXY;
    sf::FloatRect nowyHitbox;

    do
    {
        colision = false;
        tempXY = genRandomXY();
        if (tempXY.x + szerokosc > 1920.0f) tempXY.x = 1920.0f - szerokosc;
        if (tempXY.y + wysokosc > 910.0f) tempXY.y = 1080.0f - wysokosc;

        nowyHitbox = sf::FloatRect({ tempXY.x, tempXY.y }, { szerokosc, wysokosc });

        for (const auto& istniejacyStol : state.getStoly())
        {
            if (checkColision(nowyHitbox, istniejacyStol.getHitbox()))
            {
                colision = true;
                break;
            }
        }

    } while (colision);

    Stol tempStol(nowyHitbox, pojemnoscNowegoStolu);
    state.dodajStol(std::move(tempStol));
}

bool SztabLogic::outOfScreenBounds(const sf::FloatRect& posStol)
{
    return (posStol.position.x + posStol.size.x > 1920.0f || posStol.position.x < 0.0f ||
        posStol.position.y + posStol.size.y > 910.0f || posStol.position.y < 0.0f);
}

bool SztabLogic::checkColision(const sf::FloatRect& obj1, const sf::FloatRect& obj2)
{
    return obj1.findIntersection(obj2).has_value();
}