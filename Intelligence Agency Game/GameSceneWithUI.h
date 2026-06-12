#pragma once
#include "GameScenes.h"
#include "UIElement.h"
#include "UIOverlay.h"
#include "UIButton.h"
#include "Staff.h"
#include <functional>
#include "Event.h"

struct Assets;
struct Config;
class GameState;

class GameSceneWithUI : public GameScenes
{
protected:
    std::vector<std::unique_ptr<UIElement>> UIelements;

    std::unique_ptr<UIOverlay> shop;
    std::unique_ptr<UIOverlay> possesion;
    std::unique_ptr<Event> event;

    std::function<bool(Staff*)> filter;

    int clickedWorker = -1;

public:
    GameSceneWithUI(Assets& assets, Config& config, GameState& state,
        std::function<bool(Staff*)> _Filter);

    void loadButtons();
    void actionButton(std::string name);
    void updateUI();
    void drawUI(sf::RenderWindow& window);
    bool obslugaZdarzenUI(const sf::Event& event, const sf::RenderWindow& window);

};