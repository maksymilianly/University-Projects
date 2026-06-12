#include "RadarVisual.h"

#include "Assets.h"
#include "Config.h"


RadarVisual::RadarVisual(Assets& assets, Config& config)
    : Visual(assets, config, "radar_")
{
}

void RadarVisual::draw(sf::RenderWindow& window){
    Visual::draw(window);
}

void RadarVisual::setProjectorAngle(float angle) {
    if (sprites.count("radar_projector")) {
        sprites.at("radar_projector").setRotation(sf::degrees(angle));
    }
}


void RadarVisual::setOdbiornikAngle(float angle) {
    if (sprites.count("radar_odbiornik")) {
        sprites.at("radar_odbiornik").setRotation(sf::degrees(angle));
    }
    if (sprites.count("radar_odbiornik_pole")) {
        sprites.at("radar_odbiornik_pole").setRotation(sf::degrees(angle));
    }
}

void RadarVisual::drawDynamic(sf::RenderWindow& window, const std::vector<Signal>& sygnaly,
    const std::vector<SukcesWylapania>& sukcesy,
    bool isRadarOn, bool isPoleOn, bool doorOpen,
    bool zoomed)
{
    if (!zoomed)
    {
        if (isRadarOn)
        {
            drawSwiatla(window);
        }
        else
        {
            window.draw(sprites.at("radar_off"));
        }

        if (doorOpen)
        {
            window.draw(sprites.at("radar_doors_open"));
        }
        else
        {
            window.draw(sprites.at("radar_doors_closed"));
        }
    }
    else if (zoomed)
    {
        window.draw(sprites.at("radar_zoomed"));
        window.draw(sprites.at("radar_projector"), sf::BlendAdd);
    }
    if (isRadarOn)
    {
        if (sprites.count("radar_plane") && sprites.count("radar_ship")) {
            auto& planeSprite = sprites.at("radar_plane");
            auto& shipSprite = sprites.at("radar_ship");

            for (const auto& s : sygnaly) {
                if (s.strength > 0.0f) {
                    sf::Sprite* ptr = nullptr;
                    if (s.typ == TypSygnalu::Plane) {
                        ptr = &planeSprite;
                    }
                    else if (s.typ == TypSygnalu::Ship) {
                        ptr = &shipSprite;
                    }
                    ptr->setPosition({ s.x, s.y });
                    ptr->setRotation(sf::degrees(s.flightAngle));
                    if (ptr != nullptr)
                    {
                        auto alpha = static_cast<std::uint8_t>(s.strength * 255);
                        if (s.typ == TypSygnalu::Plane)
                        {
                            s.hostile ? ptr->setColor(sf::Color(255, 0, 0, alpha)) : ptr->setColor(sf::Color(0, 255, 0, alpha));
                        }
                        else if (s.typ == TypSygnalu::Ship)
                        {
                            s.hostile ? ptr->setColor(sf::Color(255, 0, 0, alpha)) : ptr->setColor(sf::Color(0, 0, 255, alpha));
                        }
                        window.draw(*ptr);
                    }
                }
            }
        }
        if (sprites.count("radar_checkmark") && sprites.count("radar_xmark")) {
            auto& checkmark = sprites.at("radar_checkmark");
            auto& xmark = sprites.at("radar_xmark");
            for (const auto& ikonka : sukcesy) {
                if (ikonka.iconTimer.getElapsedTime().asSeconds() < 1.0f) {
                    if (ikonka.sukcesOstatniegoWylapania) {
                        checkmark.setPosition(ikonka.pozycjaCelu);
                        window.draw(checkmark);
                    }
                    else {
                        xmark.setPosition(ikonka.pozycjaCelu);
                        window.draw(xmark);
                    }
                }
            }
        }
    }
    if (zoomed) {
        window.draw(sprites.at("radar_zoomed_bounds"));
    }
}

void RadarVisual::drawSwiatla(sf::RenderWindow& window) {
    static int typ = 0;
    if (swiatlaClock.getElapsedTime().asSeconds() >= 0.5f) {
        typ = rand() % 3;
        swiatlaClock.restart();
    }

    std::string nazwaSprite = "radar_ekran" + std::to_string(typ);
    if (sprites.count(nazwaSprite)) {
        window.draw(sprites.at(nazwaSprite));
        window.draw(sprites.at("radar_button_onoff"));
        window.draw(sprites.at("radar_button_zoom"));
    }
}