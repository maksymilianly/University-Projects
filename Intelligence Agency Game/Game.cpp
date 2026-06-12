#include "Game.h"

Game::Game() : 
	window(sf::VideoMode({ 1920, 1080 }), "CIAgame"),
    assets(),
	config(),
	ekrany(),
    state() 
{
	window.setFramerateLimit(60);
}

void Game::run()
{
    if (!assets.loadAssets() || !config.loadConfig())
    {
        return;
    }

    ekrany.init(assets, config,state);
    UIManager = std::make_unique<GlobalUI>(assets, config, state);

    sf::Clock clock;
    while (window.isOpen())
    {
        float dt = clock.restart().asSeconds();

        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            /*sf::Vector2i kliknieteUI = uimanager->obslugaZdarzen(*event, window, state);
            if (kliknieteUI.x == 1)
            {
                if (kliknieteUI.y != -1) {
                    state.setWybranyPracownik(kliknieteUI.y);
                }
                continue;
            }
            else if (kliknieteUI.x == -1) //jesli uimanger nie obsluzyl klilniecie
            {
                ekrany.obslugaZdarzen(*event, window);
            }
            */
            ekrany.obslugaZdarzen(*event, window);
        }

        ekrany.update(dt);
        //ekrany.zoom(dt, window);
        //uimanager->update();
        window.clear();

        ekrany.drawScenes(window);
        UIManager->drawGlobalUI(window);

        window.display();

    }
}
