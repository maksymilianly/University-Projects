#pragma once
#include "RadarTypes.h"
#include "Visual.h"

struct Assets;
struct Config;

class RadarVisual : public Visual {
private:
    sf::Clock swiatlaClock;
public:
    RadarVisual(Assets& assets, Config& config);

    void draw(sf::RenderWindow& window) override;

    void setProjectorAngle(float angle);

    void setOdbiornikAngle(float angle);

    void drawDynamic(sf::RenderWindow& window, const std::vector<Signal>& sygnaly,
        const std::vector<SukcesWylapania>& sukcesy,
        bool isRadarOn, bool isPoleOn, bool doorOpen,
        bool zoomed);

    void drawSwiatla(sf::RenderWindow& window);

    sf::FloatRect przyciskPos() {
        return sprites.at("radar_button_onoff").getGlobalBounds();
    }
    sf::FloatRect doorClosedPos() {
        return sprites.at("radar_doors_closed").getGlobalBounds();
    }
    sf::FloatRect doorOpenPos() {
        return sprites.at("radar_doors_open").getGlobalBounds();
    }
    sf::FloatRect zoomPos() {
        return sprites.at("radar_button_zoom").getGlobalBounds();
    }
};