#pragma once

#include "SzyfrLogic.h"
#include "SzyfrVisual.h"
#include "SztabVisual.h"
#include "SztabLogic.h"
#include "StaffManager.h"

#include "GameSceneWithUI.h"

struct Assets;
struct Config;
class GameState;

class SztabManager : public GameSceneWithUI {
private:
    SzyfrLogic szyfr_logika;
    SzyfrVisual szyfrvisual;
    SztabVisual sztabvisual;
    SztabLogic sztablogika;
    StaffManager staff_manager;

    bool przesuniecieStol;
    int idxStolu;
    sf::Vector2f originalXY;
    sf::Vector2f przesuniecie;
    std::pair<sf::Vector2f, int> XYSzyfru{{-1,-1},-1};
    bool przesuniecieSzyfr;

public:
    SztabManager(Assets& _assets, Config& _config, GameState& _state);

    void update(float dt) override;

    void draw(sf::RenderWindow& window) override;

    void obslugaZdarzen(const sf::Event& event, const sf::RenderWindow& window) override;

    void obslugaDanych();

    void placeStoly(int pojemnosc);
};