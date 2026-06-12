#pragma once
#include "Visual.h"             
#include <SFML/Graphics.hpp>    
#include <vector>              
#include <utility>
#include "ProcesDeszyfrowania.h"

struct Assets;
struct Config;

class SzyfrVisual : public Visual {
private:
    sf::Font& timeFont;
    sf::Vector2i formatujCzas(int czas) { return { czas / 60,czas % 60 }; }
    bool closeToFail(int czas) { return czas == 0; }
    bool checkPoziom(int poziom) { return poziom < 5; }
public:
    SzyfrVisual(Assets& assets, Config& config);

    void drawDynamic(sf::RenderWindow& window, const std::vector<ProcesDeszyfrowania>& szyfry, std::pair<sf::Vector2f, int>& daneSzyfru);

    bool pobierzWymiary(float& startX, float& startY, float& szerokosc, float& wysokosc, float& odstepX);

};