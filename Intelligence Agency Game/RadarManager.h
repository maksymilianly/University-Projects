#pragma once
#include <SFML/Graphics.hpp>

#include "GameScenes.h"

#include "RadarLogic.h"
#include "RadarVisual.h"

#include "SignalCatcherVisual.h"
#include "SignalCatcherLogic.h"

struct Assets;
struct Config;
class GameState;

class RadarManager : public GameScenes  {
private:
    RadarVisual visual;
    RadarLogic logika;

    SignalCatcherVisual catcher_visual;
    SignalCatcherLogic catcher_logic;

    bool doorOpen;
    bool zoomed;

    sf::Vector2f normalPos;
    float normalRadius;
    sf::Vector2f zoomPos;
    float zoomRadius;
	float zoomScale;
	float unzoomScale;

public:
    RadarManager(Assets& _assets, Config& _config, GameState& _state);

    void update(float dt) override;

    void draw(sf::RenderWindow& window) override;

    void obslugaZdarzen(const sf::Event& event, const sf::RenderWindow& window) override;

    void obslugaDanych() override;
};