#pragma once

#include "ProcesDeszyfrowania.h"
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>

struct Config;
class GameState;

class SzyfrLogic {
private:


public:
    SzyfrLogic(Config& config,GameState& state);
    std::pair<sf::Vector2f,int> sprawdzKlikniecie(sf::Vector2f mousePos, const std::vector<ProcesDeszyfrowania>& szyfry, float startX, float startY, float szerokosc, float wysokosc, float odstepX);
    void dodajSzyfr(GameState& state);
    void aktualizujProcesy(GameState& state, float dt);
};