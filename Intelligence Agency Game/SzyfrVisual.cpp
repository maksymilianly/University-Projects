#include "SzyfrVisual.h"

#include "Visual.h"
//#include "Assets.h"
#include "ProcesDeszyfrowania.h"
#include "GameState.h"
#include <format>

import AssetsMod;


SzyfrVisual::SzyfrVisual(Assets& assets, Config& config) : Visual(assets, config, "szyfry_"), timeFont(assets.mainFont) {}

void SzyfrVisual::drawDynamic(sf::RenderWindow& window, const std::vector<ProcesDeszyfrowania>& szyfry, std::pair<sf::Vector2f, int>& daneSzyfru) {
    if (szyfry.empty() || sprites.count("szyfry_sheets") == 0) return;

    auto& arkuszOryginal = sprites.at("szyfry_sheets");
    int szerokosc = arkuszOryginal.getTexture().getSize().x / 10;
    int wysokosc = arkuszOryginal.getTexture().getSize().y;

    sf::Vector2f startPos = arkuszOryginal.getPosition();
    float odstepX = szerokosc + 15.0f;

    int i = 0;
    sf::Text tempText(timeFont);
    tempText.setOutlineColor(sf::Color::Black);
    tempText.setOutlineThickness(5);
    sf::Text tempText2(timeFont);
    tempText2 = tempText;
    tempText2.setFillColor(sf::Color::White);
    for (const auto& szyfr : szyfry) {
        if (!(i > 8))
        {
            sf::Sprite spriteDoRysowania = arkuszOryginal;
            sf::Vector2i czas = formatujCzas(static_cast<int>(szyfr.getCzasDoFail() - szyfr.getCzas()));
            std::string minuty = std::to_string(czas.x);
            std::string sekundy = (czas.y < 10 ? "0" : "") + std::to_string(czas.y);
            tempText.setString(minuty + ":" + sekundy);
            tempText2.setString(std::format("{:.2f}", szyfr.getProgres()) + "%");
            int poziom = szyfr.getPoziom();
            tempText.setFillColor(closeToFail(czas.x) ? sf::Color::Red : sf::Color(0, 255, 65));//moze nie robic tutaj tylko 1 raz gdzeis

            spriteDoRysowania.setTextureRect(sf::IntRect({ (poziom - 1) * szerokosc, 0 }, { szerokosc, wysokosc }));

            if (i == daneSzyfru.second)
            {
                spriteDoRysowania.setPosition(daneSzyfru.first);
                tempText.setPosition(daneSzyfru.first);
                tempText2.setPosition({ daneSzyfru.first.x,daneSzyfru.first.y + wysokosc / 1.5f });
            }
            else
            {
                sf::Vector2f normalnaPozycja(startPos.x + (i * odstepX), startPos.y);
                spriteDoRysowania.setPosition(normalnaPozycja);
                tempText.setPosition(normalnaPozycja);
                tempText2.setPosition({ normalnaPozycja.x,normalnaPozycja.y + wysokosc / 1.5f });
            }
            window.draw(spriteDoRysowania);
            window.draw(tempText);
            window.draw(tempText2);
            i++;
        }
    }
}

bool SzyfrVisual::pobierzWymiary(float& startX, float& startY, float& szerokosc, float& wysokosc, float& odstepX) {
    if (sprites.count("szyfry_sheets") == 0) return false;
    auto& arkusz = sprites.at("szyfry_sheets");
    szerokosc = arkusz.getTexture().getSize().x / 10.0f;
    wysokosc = arkusz.getTexture().getSize().y;
    startX = arkusz.getPosition().x;
    startY = arkusz.getPosition().y;
    odstepX = szerokosc + 15.0f;
    return true;
}
