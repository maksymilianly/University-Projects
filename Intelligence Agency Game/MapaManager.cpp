#include "MapaManager.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm> 
#include <random>
#include "UIMissionWidget.h"
#include "UIInteractableObject.h"
//#include "Assets.h"
//#include "Config.h"
#include "GameState.h"
#include <thread>

import AssetsMod;
import ConfigMod;

MapaManager::MapaManager(Assets& _assets, Config& _config, GameState& _state)
    : GameSceneWithUI(_assets, _config, _state, [](Staff* p) {return dynamic_cast<Agent*>(p) != nullptr; }),
    visual(_assets, config), logika(), misja_manager(_assets, _config, _state) {
    rysujGranice = false;
    ktoraGranica = "";

    mission_widgets_panel = std::make_unique<UIOverlay>(sf::Sprite(assets.textures.at("ui_mission_panel")), config.spritesData.at("ui_mission_panel").position, "mission_panel", 5, 1);
	mission_panel = std::make_unique<UIOverlay>(sf::Sprite(assets.textures.at("ui_mission_panel")), config.spritesData.at("ui_mission_panel").position, "mission_panel", 1, 1);
}

void MapaManager::update(float dt) {
    obslugaDanych();
    updateUI();

    if (missionEnd.load()) {
        mission_panel->setIsOpen(false);
        mission_panel->clearWidgets();
        missionEnd.store(false);
        missionInProgress.store(false);

        if (agentOnMission) {
            state.dodajPracownika(std::move(agentOnMission));
        }

        state.clearRefreshStaff();
        state.requestRefreshMission();
    }

    if (startMinigame) {
        startMinigame = false; 
        missionInProgress.store(true);
        isTargetClicked.store(false);
        missionEnd.store(false);
        timeForMission.store(5);

        mission_panel->clearWidgets();
        auto cel = std::make_unique<UIInteractableObject>(
            sf::Sprite(assets.textures.at("ui_info_panel")),
            sf::Vector2f(500.0f, 400.0f),
            assets.mainFont,
            [this]() { isTargetClicked.store(true); }
        );
        mission_panel->addWidget(std::move(cel));

        if (missionToRemowe >= 0 && missionToRemowe < state.getAktywneMisje().size()) {
            state.getAktywneMisje().erase(state.getAktywneMisje().begin() + missionToRemowe);
        }
        state.requestRefreshStaff();

        std::thread([this]() {
            while (timeForMission.load() > 0 && !isTargetClicked.load()) {
                std::this_thread::sleep_for(std::chrono::seconds(1));
                timeForMission--;
            }
            if (isTargetClicked.load()) std::cout << "SUKCES!\n";
            else std::cout << "PORAZKA!\n";

            missionEnd.store(true);
            }).detach();
    }

    if (state.shouldRefreshMission()) {
        if (mission_panel->getIsOpen() && !missionInProgress.load()) {
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
                    int wybranyIdx = state.getWybranyPracownik();
                    if (wybranyIdx != -1) {
                        Staff* sprawdzanyPracownik = state.getPracownik(wybranyIdx);
                        if (sprawdzanyPracownik && dynamic_cast<Agent*>(sprawdzanyPracownik) != nullptr) {

                            agentOnMission = state.wyjmijPracownika(wybranyIdx);
                            state.resetWybranyPracownik();
                            missionToRemowe = idx;
                            startMinigame = true;

                        }
                        else {
                            std::cout << "Wybierz Agenta!\n";
                        }
                    }
                },
                [this, idx]() { mission_panel->setRefresh(true); }
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