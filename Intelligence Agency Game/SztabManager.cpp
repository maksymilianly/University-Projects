#include "GameSceneWithUI.h"
#include "ProcesDeszyfrowania.h"
#include "Staff.h"
#include "Stol.h"
#include "GameState.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm> 
#include "SztabManager.h"


SztabManager::SztabManager(Assets& _assets, Config& _config, GameState& _state)
    : GameSceneWithUI(_assets, _config, _state, [](Staff* p) { return dynamic_cast<Grupa*>(p) != nullptr; }),
    szyfr_logika(_config, _state), szyfrvisual(_assets, _config),
    sztabvisual(_assets, _config), staff_manager(_assets, _config, _state)
{
    placeStoly(1);
    placeStoly(2);
    placeStoly(3);

}

void SztabManager::update(float dt){
    szyfr_logika.dodajSzyfr(state);
    szyfr_logika.aktualizujProcesy(state, dt);
    staff_manager.update(state);

    if (state.sztab_queue_has_reports() && !event->is_active())
    {
        event->setEvent(state.take_out_sztab_report());
        event->set_active(true);
    }

    updateUI();
}


void SztabManager::draw(sf::RenderWindow& window){
    sztabvisual.draw(window);
    sztabvisual.drawDynamic(window, assets, state, przesuniecieStol);
    szyfrvisual.drawDynamic(window, state.getAktywneSzyfry(), XYSzyfru);
    drawUI(window);
}

void SztabManager::obslugaZdarzen(const sf::Event& event, const sf::RenderWindow& window){

    if (obslugaZdarzenUI(event, window)) return;

    if (const auto* mouseEvent = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (mouseEvent->button == sf::Mouse::Button::Left) {
            float startX, startY, szer, wys, odstep;
            sf::Vector2i mousePos(static_cast<int>(mouseEvent->position.x), static_cast<int>(mouseEvent->position.y));
            sf::Vector2f tempPos = window.mapPixelToCoords(mousePos);

            // check szyfry
            if (szyfrvisual.pobierzWymiary(startX, startY, szer, wys, odstep)) {
                std::pair<sf::Vector2f, int> posind = szyfr_logika.sprawdzKlikniecie(tempPos, state.getAktywneSzyfry(), startX, startY, szer, wys, odstep);
                if (posind.second != -1) {
                    przesuniecieSzyfr = true;
                    XYSzyfru.second = posind.second;
                    przesuniecie = posind.first - tempPos;
                    XYSzyfru.first = posind.first;
                }
            }

            // check stoly
            if (!przesuniecieSzyfr)
            {
                int idx = 0;
                for (auto& stol : state.getStoly())
                {
                    if (stol.getHitbox().contains(tempPos))
                    {
                        int wybranyId = state.getWybranyPracownik();

                        if (wybranyId != -1)
                        {
                            if (!stol.czyPusty())
                            {
                                Staff* pracownik = state.getPracownik(wybranyId);
                                Grupa* grupa = dynamic_cast<Grupa*>(pracownik);

                                if (stol.getPojemnosc() > stol.getPrzypisaneGrupy().size() &&
                                    grupa != nullptr && !grupa->getZajety())
                                {
                                    stol.dodajGrupe(grupa);
                                    grupa->setZajety(true);

                                    stol.getSzyfr()->calculate_progress(stol.getPrzypisaneGrupy());
                                    state.setWybranyPracownik(-1);
                                    state.requestRefreshStaff();
                                }
                            }
                        }
                        else
                        {
                            przesuniecieStol = true;

                            idxStolu = idx;
                            originalXY = { stol.getHitbox().position.x, stol.getHitbox().position.y };
                            przesuniecie = stol.getHitbox().position - tempPos;
                        }
                    }
                    idx++;
                }
            }
        }
        else if (mouseEvent->button == sf::Mouse::Button::Right)
        {
            sf::Vector2i mousePos(static_cast<int>(mouseEvent->position.x), static_cast<int>(mouseEvent->position.y));
            sf::Vector2f tempPos = window.mapPixelToCoords(mousePos);

            for (auto& stol : state.getStoly())
            {
                if (stol.getHitbox().contains(tempPos) && !stol.czyPusty())
                {
                    std::unique_ptr<ProcesDeszyfrowania> tempPtr = stol.giveSzyfr();
                    tempPtr->resetPostep();
                    state.dodajAktywnySzyfr(std::move(*tempPtr));
                }
            }
        }
    }

    if (const auto* mouseEvent = event.getIf<sf::Event::MouseMoved>())
    {
        if (przesuniecieSzyfr)
        {
            sf::Vector2i mousePos(static_cast<int>(mouseEvent->position.x), static_cast<int>(mouseEvent->position.y));
            sf::Vector2f tempPos = window.mapPixelToCoords(mousePos);
            XYSzyfru.first = tempPos + przesuniecie;
        }
        if (przesuniecieStol)
        {
            sf::Vector2i mousePos(static_cast<int>(mouseEvent->position.x), static_cast<int>(mouseEvent->position.y));
            sf::Vector2f tempPos = window.mapPixelToCoords(mousePos);
            state.setStolXY(tempPos + przesuniecie, idxStolu);
        }
    }

    if (const auto* mouseEvent = event.getIf<sf::Event::MouseButtonReleased>())
    {
        if (mouseEvent->button == sf::Mouse::Button::Left && przesuniecieStol)
        {
            const auto& stoly = state.getStoly();
            if (sztablogika.outOfScreenBounds(stoly[idxStolu].getHitbox()))
            {
                state.setStolXY(originalXY, idxStolu);
            }
            bool kolizja = false;
            for (int i = 0; i < stoly.size(); i++)
            {
                if (i == idxStolu) continue;

                if (sztablogika.checkColision(stoly[idxStolu].getHitbox(), stoly[i].getHitbox()))
                {
                    kolizja = true;
                    break;
                }
            }

            if (kolizja)
            {
                state.setStolXY(originalXY, idxStolu);
            }
            przesuniecieStol = false;
        }
        if (mouseEvent->button == sf::Mouse::Button::Left && przesuniecieSzyfr)
        {
            sf::Vector2i mousePos(static_cast<int>(mouseEvent->position.x), static_cast<int>(mouseEvent->position.y));
            sf::Vector2f tempPos = window.mapPixelToCoords(mousePos);

            auto& stoly = state.getStoly();
            auto& szyfry = state.getAktywneSzyfry();

            for (auto& stol : stoly)
            {
                if (stol.getHitbox().contains(tempPos) && stol.czyPusty())
                {
                    stol.takeSzyfr(std::make_unique<ProcesDeszyfrowania>(std::move(szyfry[XYSzyfru.second])));

                    szyfry.erase(szyfry.begin() + XYSzyfru.second);
                    break;
                }
            }
            przesuniecieSzyfr = false;
            XYSzyfru.second = -1;
        }
    }
}

void SztabManager::obslugaDanych()
{

}

void SztabManager::placeStoly(int pojemnosc)
{
    sztablogika.placeNowyStol(assets, state, pojemnosc);
}