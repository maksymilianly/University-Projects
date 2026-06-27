#include "RadarManager.h"

//#include "Assets.h"
//#include "Config.h"
#include "GameState.h"

import AssetsMod;
import ConfigMod;


RadarManager::RadarManager(Assets& _assets, Config& _config, GameState& _state)
    : GameScenes(_assets, _config, _state),
    logika(_config, _state), visual(_assets, _config), catcher_visual(_assets,_config)
    , catcher_logic(_assets,_config), zoomed(false), doorOpen(false)
{
    config.loadIn("radar_posX", normalPos.x, 0.0f);
    config.loadIn("radar_posY", normalPos.y, 0.0f);
    config.loadIn("radar_radius", normalRadius, 0.0f);
    config.loadIn("radar_zposX", zoomPos.x, 0.0f);
    config.loadIn("radar_zposY", zoomPos.y, 0.0f);
    config.loadIn("radar_zradius", zoomRadius, 0.0f);
    config.loadIn("radar_zoomScale", zoomScale, 0.0f);
    config.loadIn("radar_unzoomScale", unzoomScale, 0.0f);
}


void RadarManager::update(float dt) {

    if (!logika.getIsRadarOn()) return;

    logika.changePoleState(false);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) logika.changePoleState(true);
    logika.updateSignals(dt, catcher_logic.getCatcherPos(), catcher_logic.getRadarRadius());

    obslugaDanych();


    logika.spawnRandomSignal(dt);

    logika.updateProjector(dt);
    visual.setProjectorAngle(logika.getProjectorAngle());

    sf::Vector2f vector(0.0f, 0.0f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))    vector.y -= 1.0f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))  vector.y += 1.0f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))  vector.x -= 1.0f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) vector.x += 1.0f;

    if (zoomed) { 
        catcher_logic.move(dt, vector);
        catcher_logic.compareWithRadarBounds();
        catcher_visual.update(catcher_logic.getCatcherPos());
    }
}

void RadarManager::draw(sf::RenderWindow& window){
    if (!zoomed)
    {
        visual.draw(window);
    }
    visual.drawDynamic(window, logika.getSygnaly(),
        logika.getSukcesy(), logika.getIsRadarOn(),
        logika.getIsPoleOn(), doorOpen, zoomed);

    if (zoomed)
    {
        catcher_visual.drawDynamic(window);
    }
}

void RadarManager::obslugaZdarzen(const sf::Event & event, const sf::RenderWindow & window) {
    if (const auto* mouseEvent = event.getIf<sf::Event::MouseButtonPressed>())
    {
        if (mouseEvent->button == sf::Mouse::Button::Left) {
            sf::Vector2i mousePos(static_cast<int>(mouseEvent->position.x), static_cast<int>(mouseEvent->position.y));
            sf::Vector2f tempPos = window.mapPixelToCoords(mousePos);
            if (logika.checkPrzycisk(tempPos, visual.przyciskPos()))
            {
                logika.toggleRadar();
            }
            else if (logika.getIsRadarOn() && logika.checkZoom(tempPos, visual.zoomPos()))
            {
                zoomed = !zoomed;
                if (zoomed)
                {
                    logika.przemapujSygnaly(zoomScale, zoomPos);
                    logika.nadpiszPos(zoomRadius, zoomPos);
                }
                else
                {
                    logika.przemapujSygnaly(unzoomScale, normalPos);
                    logika.nadpiszPos(normalRadius, normalPos);
                }
            }
            else if (logika.checkDoor(tempPos, doorOpen ? visual.doorOpenPos() : visual.doorClosedPos()))
            {
                doorOpen = !doorOpen; //pozniej dodac ze jak prawy przycisk przy open doors to close a lewy to przedz do sztabu
            }
        }

    }
}

void RadarManager::obslugaDanych()
{
    const auto transakcje = logika.wyjmijTransakcje();
    if (!transakcje.empty())
    {
        for (auto t : transakcje)
        {
            state.addBank(t);
            if (t == logika.getHostile())
            {
                state.dodajDane(t);
            }
        }
    }
}