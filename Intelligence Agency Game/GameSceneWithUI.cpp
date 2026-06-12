#include "GameSceneWithUI.h" 
#include <memory>
#include "Assets.h"
#include "Config.h"
#include "GameState.h"
#include "UIButton.h"

#include "UIEmployerWidget.h"
#include "Staff.h"

GameSceneWithUI::GameSceneWithUI(Assets& assets, Config& config, GameState& state,
    std::function<bool(Staff*)> _Filter)
    : GameScenes(assets, config, state),
    filter(_Filter)
{
    shop = std::make_unique<UIOverlay>(sf::Sprite(assets.textures.at("ui_shop_bg")), config.spritesData.at("ui_shop_bg").position, "shop0", 3, 3);
    possesion = std::make_unique<UIOverlay>(sf::Sprite(assets.textures.at("ui_shop_bg")), config.spritesData.at("ui_shop_bg").position, "possesion", 3, 3);
    event = std::make_unique<Event>(assets);

    shop->initTooltip(sf::Sprite(assets.textures.at("ui_info_panel")), assets.mainFont);
    possesion->initTooltip(sf::Sprite(assets.textures.at("ui_info_panel")), assets.mainFont);

    loadButtons();
}

void GameSceneWithUI::loadButtons()
{
    for (auto const& [nazwa, sprite] : assets.textures)
    {
        if (nazwa.starts_with("ui_button_"))
        {
            std::string actionName = nazwa.substr(std::string("ui_button_").length());
            UIelements.push_back(std::make_unique<UIButton>(
                sf::Sprite(sprite),
                config.spritesData.at(nazwa).position,
                [this, actionName]() { this->actionButton(actionName); }
            ));
        }
    }
}

void GameSceneWithUI::actionButton(std::string name)
{
    if (name == "shop") {
        shop->toogle();
        if (possesion->getIsOpen()) {
            possesion->setIsOpen(false);
        }
    }
    else if (name == "workers") {
        possesion->toogle();
        if (shop->getIsOpen()) {
            shop->setIsOpen(false);
        }
    }
}

void GameSceneWithUI::updateUI()
{
    if (state.shouldRefreshStaff()) {
        possesion->setRefresh(true);
        shop->setRefresh(true);
        state.clearRefreshStaff();
    }

    if (shop->getRefresh()) {
        shop->clearWidgets();

        int idx = 0;
        for (const auto& oferta : state.getRynekPracy()) {
            if (filter != nullptr && filter(oferta.get()) == false) {
                idx++; continue;
            }

            sf::Sprite ikona = oferta->isAgent()
                ? sf::Sprite(assets.textures.at("ui_icon_agent"))
                : sf::Sprite(assets.textures.at("ui_icon_group"));

            auto widget = std::make_unique<UIEmployerWidget>(
                sf::Sprite(assets.textures.at("ui_shop_bounds")),
                ikona,
                sf::Sprite(assets.textures.at("ui_widgetbutton")),
                sf::Sprite(assets.textures.at("ui_widgetbutton")),
                assets.mainFont, *oferta,
                sf::Vector2f(0, 0), 
                [this, idx]() { 
                    auto kupionaOferta = state.wyjmijOferte(idx);
                    if (kupionaOferta) {
                        if (!state.checkMoney(kupionaOferta->getPayment())) return;

                        state.addBank(-kupionaOferta->getPayment());
                        state.dodajPracownika(std::move(kupionaOferta));
                        shop->setRefresh(true);
                        possesion->setRefresh(true);
                    }
                },
                [this, idx]() { 
                    auto tempOf = state.wyjmijOferte(idx);
                    shop->setRefresh(true);
                }
            );

            shop->addWidget(std::move(widget));
            idx++;
        }
        shop->setRefresh(false);
    }


    if (possesion->getRefresh()) {
        state.sortWorkers();
        possesion->clearWidgets();

        int idx = 0;
        for (const auto& pracownik : state.getPracownicy()) {
            if (filter != nullptr && filter(pracownik.get()) == false) {
                idx++; continue;
            }

            sf::Sprite ikona = pracownik->isAgent()
                ? sf::Sprite(assets.textures.at("ui_icon_agent"))
                : sf::Sprite(assets.textures.at("ui_icon_group"));

            auto widget = std::make_unique<UIEmployerWidget>(
                sf::Sprite(assets.textures.at("ui_shop_bounds")),
                ikona,
                sf::Sprite(assets.textures.at("ui_widgetbutton")),
                sf::Sprite(assets.textures.at("ui_widgetbutton")),
                assets.mainFont, *pracownik,
                sf::Vector2f(0, 0),
                [this, idx]() { 
                    state.setWybranyPracownik(idx);
                    possesion->setIsOpen(false);
                },
                [this, idx]() { 
                    possesion->setRefresh(true);
                }
            );

            possesion->addWidget(std::move(widget));
            idx++;
        }
        possesion->setRefresh(false);
    }
}

void GameSceneWithUI::drawUI(sf::RenderWindow& window)
{
    for (const auto& element : UIelements) {
        element->draw(window);
    }

    if (shop->getIsOpen()) {
        shop->draw(window);
    }

    if (possesion->getIsOpen()) {
        possesion->draw(window);
    }

    if (event->is_active())
    {
        event->drawEvent(window);
    }
}

bool GameSceneWithUI::obslugaZdarzenUI(const sf::Event& _event, const sf::RenderWindow& window)
{
    clickedWorker = -1;
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    if (event->obsluzKlikniecie(_event, mousePos))
    {
        return true;
    }

    if (shop->obsluzKlikniecie(_event, mousePos))
    {
        return true;
    }


    if (possesion->obsluzKlikniecie(_event, mousePos))
    {
        return true;
    }

    for (const auto& element : UIelements) {
        if (element->obsluzKlikniecie(_event, mousePos)) {
            return true;
        }
    }
    return false;
}