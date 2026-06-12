#pragma once
#include "Visual.h"

struct Assets;
struct Config;
class GameState;


class MapaVisual : public Visual {
private:
    std::unordered_map<std::string, sf::Image> maskiKolizji;
public:
    MapaVisual(Assets& assets, Config& config);

    void draw(sf::RenderWindow& window) override;

    void drawDynamic(sf::RenderWindow& window, Config& config, GameState& state);

    bool checkMyszke(const sf::FloatRect& obj1, const sf::Vector2f& posMyszy)
    {
        return obj1.contains(posMyszy);
    }

    std::pair<bool, std::string> checkGranice(const sf::RenderWindow& window, const Assets& assets, const sf::Vector2f& posMyszy);

    void drawGranice(sf::RenderWindow& window, std::string panstwo);

    /*void zoom(float dt, sf::RenderWindow& window)
    {
        sf::View tempView = window.getView();

        if (tempView.getSize().x < 400.0f) {
            return;
        }

        float zoomFactor = 1.0f - (std::exp2f(((tempView.getSize().x/500.0f)-2)) * dt);

        tempView.zoom(zoomFactor);
        window.setView(tempView);
    }*/ //zoom kamery

    void drawMiasto(sf::RenderWindow& window, Config& config, sf::Vector2f pozycja);
}; 
