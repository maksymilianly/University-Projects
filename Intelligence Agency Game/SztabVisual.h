#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

#include "Visual.h"


struct Assets;
struct Config;
class GameState;

class SztabVisual : public Visual {
private:
    sf::Font& timeFont;
    sf::Vector2i formatujCzas(int czas) { return { czas / 60,czas % 60 }; }
    bool closeToFail(int czas) { return czas == 0; }
public:
    SztabVisual(Assets& assets, Config& config);

    void draw(sf::RenderWindow& window);

    void drawDynamic(sf::RenderWindow& window, Assets& assets, GameState& state, bool przesuwanie);

};