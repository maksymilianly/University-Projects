#include "MapaVisual.h"

#include <cmath>

//#include "Assets.h"
//#include "Config.h"
#include "GameState.h"

import AssetsMod;
import ConfigMod;


MapaVisual::MapaVisual(Assets& assets, Config& config)
    : Visual(assets, config, "map_")
{
    for (auto const& [nazwa, tekstura] : assets.textures) {
        if (nazwa.starts_with("map_cnt_")) {
            maskiKolizji[nazwa] = tekstura.copyToImage();
        }
    }
}

void MapaVisual::draw(sf::RenderWindow& window)
{
    Visual::draw(window);

}

void MapaVisual::drawDynamic(sf::RenderWindow& window, Config& config, GameState& state)
{
    /*if (!sprites.count("map_circle")) { return; }

        sf::Sprite tempSprite = sprites.at("map_circle");

        auto const& tempCoords = config.citiesCoords;

        for (auto const& [panstwo, miasta] : tempCoords)
        {
            for (auto const& [nazwaMiasta, wspolrzedne] : miasta)
            {
                tempSprite.setPosition({ (float)wspolrzedne.x, (float)wspolrzedne.y });
                window.draw(tempSprite);
            }
        } *///prawdzanie pozyji na mapie

    for (const auto& misja : state.getAktywneMisje())
    {
        drawMiasto(window, config, misja.getPozycjaMiasta());
    }
}

std::pair<bool, std::string> MapaVisual::checkGranice(const sf::RenderWindow& window, const Assets& assets, const sf::Vector2f& posMyszy)
{
    for (auto& [nazwa, sprite] : sprites)
    {
        if (nazwa.starts_with("map_cnt_"))
        {
            if (checkMyszke(sprite.getGlobalBounds(), posMyszy))
            {
                sf::Vector2f localPos = sprite.getInverseTransform().transformPoint(posMyszy);
                const sf::Image& maska = maskiKolizji.at(nazwa);
                if (localPos.x >= 0 && localPos.x < maska.getSize().x &&
                    localPos.y >= 0 && localPos.y < maska.getSize().y)
                {
                    sf::Color tempColor = maska.getPixel(static_cast<sf::Vector2u>(localPos));

                    if (tempColor.a > 0)
                    {
                        return { true, nazwa.substr(8) };
                    }
                }
            }
        }
    }
    return { false, "" };
}

void MapaVisual::drawGranice(sf::RenderWindow& window, std::string panstwo)
{
    sf::Sprite& tempSprite = sprites.at("map_cnt_" + panstwo);
    window.draw(tempSprite);
}

void MapaVisual::drawMiasto(sf::RenderWindow& window, Config& config, sf::Vector2f pozycja)
{
    if (!sprites.count("map_circle")) { return; }
    sf::Sprite tempSprite = sprites.at("map_circle");
    tempSprite.setPosition(pozycja);
    window.draw(tempSprite);
}