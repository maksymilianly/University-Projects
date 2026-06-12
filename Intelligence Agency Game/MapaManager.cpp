#include "MapaManager.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm> 
#include <random>
#include "UIMissionWidget.h"
#include "Assets.h"
#include "Config.h"
#include "GameState.h"

MapaManager::MapaManager(Assets& _assets, Config& _config, GameState& _state)
    : GameSceneWithUI(_assets, _config, _state, [](Staff* p) {return dynamic_cast<Agent*>(p) != nullptr; }),
    visual(_assets, config), logika(), misja_manager(_assets, _config, _state) {
    rysujGranice = false;
    ktoraGranica = "";

    mission_panel = std::make_unique<UIOverlay>(sf::Sprite(assets.textures.at("ui_mission_panel")), config.spritesData.at("ui_mission_panel").position, "mission_panel", 5, 1);
}

void MapaManager::update(float dt) {
    obslugaDanych();
    updateUI();

    if (state.shouldRefreshMission()) {
        if (mission_panel->getIsOpen()) {
            mission_panel->setRefresh(true);
        }
        state.clearRefreshMission();
    }

    if (mission_panel->getRefresh()) {
        mission_panel->clearWidgets();
        int idx = 0;

        for (auto& misja : state.getAktywneMisje()) {
            if (countryToString(misja.getKraj()) != ktoraGranica) {
                idx++;
                continue;
            }

            auto widget = std::make_unique<UIMissionWidget>(
                sf::Sprite(assets.textures.at("ui_shop_bounds")),
                sf::Sprite(assets.textures.at("ui_icon_agent")),
                sf::Sprite(assets.textures.at("ui_widgetbutton")),
                sf::Sprite(assets.textures.at("ui_widgetbutton")),
                assets.mainFont,
                misja,
                sf::Vector2f(0, 0),
                [this, idx]() {
                    mission_panel->setRefresh(true);
                },
                [this, idx]() {
                    mission_panel->setRefresh(true);
                }
            );

            mission_panel->addWidget(std::move(widget));
            idx++;
        }
        mission_panel->setRefresh(false);
    }
}

void MapaManager::draw(sf::RenderWindow& window) {
    visual.draw(window);
    visual.drawDynamic(window, config, state);
    if (rysujGranice) {
        visual.drawGranice(window, ktoraGranica);
    }
    drawUI(window);
    mission_panel->draw(window);
}

void MapaManager::obslugaZdarzen(const sf::Event& event, const sf::RenderWindow& window) {

    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    if (mission_panel->obsluzKlikniecie(event, mousePos)) return;
    if (obslugaZdarzenUI(event, window)) return;

    if (const auto* mouseEvent = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (mouseEvent->button == sf::Mouse::Button::Left) {
            sf::Vector2i mPos(static_cast<int>(mouseEvent->position.x), static_cast<int>(mouseEvent->position.y));
            sf::Vector2f tempPos = window.mapPixelToCoords(mPos);

            auto wynik = visual.checkGranice(window, assets, tempPos);
            if (wynik.first) {

                if (ktoraGranica == wynik.second && mission_panel->getIsOpen()) {
                    mission_panel->setIsOpen(false);
                }

                else {
                    ktoraGranica = wynik.second;
                    mission_panel->setIsOpen(true);
                    state.requestRefreshMission();
                }
            }
            else {

                mission_panel->setIsOpen(false);
            }
        }
    }


    if (const auto* mouseEvent = event.getIf<sf::Event::MouseMoved>()) {
        sf::Vector2i mPos(static_cast<int>(mouseEvent->position.x), static_cast<int>(mouseEvent->position.y));
        sf::Vector2f tempPos = window.mapPixelToCoords(mPos);

        rysujGranice = false;
        auto wynik = visual.checkGranice(window, assets, tempPos);

        if (mission_panel->getIsOpen()) {
            rysujGranice = true;
        }
        else if (wynik.first) {
            rysujGranice = true;
            ktoraGranica = wynik.second;
        }
    }
}

void MapaManager::obslugaDanych() {
    misja_manager.obslugaDanych();
}