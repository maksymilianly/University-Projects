#include "SzyfrLogic.h"
#include <random>
#include <iostream>

#include "Config.h"
#include "GameState.h"


SzyfrLogic::SzyfrLogic(Config& config,GameState& state)
{
    //w przyslosci mozna zainicjalizowac zmienne z configa typu kara za fail
}


std::pair<sf::Vector2f,int> SzyfrLogic::sprawdzKlikniecie(sf::Vector2f mousePos,const std::vector<ProcesDeszyfrowania>& szyfry, float startX, float startY, float szerokosc, float wysokosc, float odstepX) {

    for (size_t i = 0; i < szyfry.size(); ++i) {
        float currentX = startX + (i * odstepX);
        sf::FloatRect bounds({ currentX, startY }, { szerokosc, wysokosc });

        if (bounds.contains(mousePos)) {
            return {bounds.position,i};
        }
    }
    return { {-1.0f,-1.0f},-1 };
}


 void SzyfrLogic::dodajSzyfr(GameState& state)
{
    auto temp = state.podgladSygnalow();
    if (!temp.empty())
    {
        for (int i = 0; i < temp.size(); i++)
        {
            state.dodajAktywnySzyfr(ProcesDeszyfrowania());
        }
    }
    state.cleanS();

}

/*void ProcesDeszyfrowania::dodajDoProcesu(Staff* grupaPtr)
{
    if (Grupa* g = dynamic_cast<Grupa*>(grupaPtr))
    {
        if (!grupaPtr->getZajety())
        {
            przypisaniPracownicy.push_back(g);
            grupaPtr->setZajety(true);
        }
    }
}*/


 void SzyfrLogic::aktualizujProcesy(GameState& state, float dt)
 {
     auto& aktywneSzyfry = state.getAktywneSzyfry();
     for (int i = aktywneSzyfry.size() - 1; i >= 0; --i)
     {
         if (aktywneSzyfry[i].update(dt, false) == SzyfrState::Failed)
         {
             state.setBank(state.getBank() - 100);
             state.usunSzyfr(i);
         }
     }

     for (auto& stol : state.getStoly())
     {
         if (!stol.czyPusty())
         {
             SzyfrState tempSzyfr = stol.getSzyfr()->update(dt, true);
             if (tempSzyfr == SzyfrState::Failed || tempSzyfr == SzyfrState::Completed)
             {
                 if (tempSzyfr == SzyfrState::Failed) {
                     state.setBank(state.getBank() - 100);
                 }
                 else if (tempSzyfr == SzyfrState::Completed) {
                     SztabReport newReport = stol.getSzyfr()->calculate_bonuses(stol.getPrzypisaneGrupy());
                     state.setBank(state.getBank() + newReport.reward);
                     state.wpiszMisjeDoWygenerowania(stol.getSzyfr()->jakiePanstwo());

                     state.addReport(newReport);
                 }

                 /*for (auto* grupa : stol.getPrzypisaneGrupy())
                 {
                     if (grupa != nullptr) {
                         grupa->setZajety(false);
                     }
                 }*/
                 stol.wyczyscGrupy();
                 state.requestRefreshStaff();
                 stol.takeSzyfr(nullptr); 
             }
         }
         else if (stol.czyPusty() && !stol.getPrzypisaneGrupy().empty())
         {
             stol.wyczyscGrupy();
         }
     }
 }