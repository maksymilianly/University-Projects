#include "MisjaManager.h"

#include "Assets.h"
#include "Config.h"
#include "GameState.h"



MisjaManager::MisjaManager(Assets& _assets, Config& _config, GameState& _state) : visual(_assets, _config), logika(), assets(_assets), config(_config), state(_state)
{
}

void MisjaManager::update(float dt) {
}

void MisjaManager::draw(sf::RenderWindow& window) {

}

void MisjaManager::obslugaZdarzen(const sf::Event& event, const sf::RenderWindow& window) {
}


std::vector<std::string> MisjaManager::checkCities(std::string panstwo)
{
    auto krajId = config.citiesCoords.find(panstwo);
    std::vector<std::string> listaMiastWolnych;

    if (krajId != config.citiesCoords.end())
    {
        for (auto& [nazwaMiasta, daneMiasta] : krajId->second)
        {
            if (daneMiasta.second == false)
            {
                listaMiastWolnych.push_back(nazwaMiasta);
            }
        }
    }
    return listaMiastWolnych;
}

void MisjaManager::obslugaDanych() {
    if (!state.getMisjeDoWygenerowania().empty())
    {
        std::queue<int>& misjeQueue = state.getMisjeDoWygenerowania();
        while (!misjeQueue.empty())
        {
            int misja = misjeQueue.front();
            misjeQueue.pop();
            Country kraj = static_cast<Country>(misja);
            std::string krajStr = countryToString(kraj);
            std::string miasto = logika.randomMiasto(checkCities(krajStr));
            state.addMisja(miasto, kraj, config.citiesCoords[krajStr][miasto].first);
            //misja_manager.genMisja(state, misja);
        }

    }
}