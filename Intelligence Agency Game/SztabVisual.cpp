#include "SztabVisual.h"
//#include "Assets.h"
//#include "Config.h"
#include "GameState.h"
#include <format>

import AssetsMod;
import ConfigMod;



SztabVisual::SztabVisual(Assets& assets, Config& config)
    : Visual(assets, config, "stuff_"), timeFont(assets.mainFont)
{

}

void SztabVisual::draw(sf::RenderWindow& window)
{
    Visual::draw(window);
}

void SztabVisual::drawDynamic(sf::RenderWindow& window, Assets& assets, GameState& state, bool przesuwanie)
{

    sf::Sprite tempSprite(assets.textures.at("stuff_stol1"));

    for (const auto& stol : state.getStoly())
    {
        int p = stol.getPojemnosc();

        switch (p)
        {
        case 1:
            tempSprite.setTexture(assets.textures.at("stuff_stol1"), true);
            break;
        case 2:
            tempSprite.setTexture(assets.textures.at("stuff_stol2"), true);
            break;
        case 3:
            tempSprite.setTexture(assets.textures.at("stuff_stol3"), true);
            break;
        default:
            continue;
        }
        tempSprite.setPosition(stol.getHitbox().position);
        window.draw(tempSprite);

        if (przesuwanie)
        {
            switch (p)
            {
            case 1:
                tempSprite.setTexture(assets.textures.at("stuff_bounds1"), true);
                break;
            case 2:
                tempSprite.setTexture(assets.textures.at("stuff_bounds2"), true);
                break;
            case 3:
                tempSprite.setTexture(assets.textures.at("stuff_bounds3"), true);
                break;
            default:
                continue;
            }
            window.draw(tempSprite);
        }
        const ProcesDeszyfrowania* szyfrNaStole = stol.getSzyfr();
        if (szyfrNaStole != nullptr)
        {
            sf::Sprite spriteSzyfru(assets.textures.at("szyfry_sheets"));

            sf::Text tempText(timeFont);
            tempText.setOutlineColor(sf::Color::Black);
            tempText.setOutlineThickness(5);
            sf::Vector2i czas = formatujCzas(static_cast<int>(szyfrNaStole->getCzasDoFail() - szyfrNaStole->getCzas()));
            std::string minuty = std::to_string(czas.x);
            std::string sekundy = (czas.y < 10 ? "0" : "") + std::to_string(czas.y);
            tempText.setString(minuty + ":" + sekundy);
            tempText.setFillColor(closeToFail(czas.x) ? sf::Color::Red : sf::Color(0, 255, 65));
            sf::Text tempText2(timeFont);
            tempText2 = tempText;
            tempText2.setFillColor(sf::Color::White);
            tempText2.setString(std::format("{:.2f}", szyfrNaStole->getProgres()) + "%");


            int szerokosc = spriteSzyfru.getTexture().getSize().x / 10;
            int wysokosc = spriteSzyfru.getTexture().getSize().y;
            int poziom = szyfrNaStole->getPoziom();

            spriteSzyfru.setTextureRect(sf::IntRect({ (poziom - 1) * szerokosc, 0 }, { szerokosc, wysokosc }));

            spriteSzyfru.setPosition({ stol.getHitbox().getCenter().x - szerokosc / 2.0f ,stol.getHitbox().getCenter().y - wysokosc / 2.0f });
            tempText.setPosition(stol.getHitbox().position);
            tempText2.setPosition({ stol.getHitbox().position.x,stol.getHitbox().position.y + stol.getHitbox().size.y - 40.0f });
            window.draw(spriteSzyfru);
            window.draw(tempText);
            window.draw(tempText2);
        }
    }
}

