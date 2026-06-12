#include "StaffLogic.h"

#include "Assets.h"



StaffLogic::StaffLogic(Assets&_assets,Config&_config,GameState&_state) : assets(_assets),config(_config),state(_state) {}

std::unique_ptr<Staff> StaffLogic::buyPracownik(int index)
{
    return state.wyjmijOferte(index);
}

void StaffLogic::usunOferte(int ktory, bool czyUsun)
{
    auto wyjety = state.wyjmijOferte(ktory);

    if (wyjety != nullptr)
    {
        if (czyUsun)
        {
            if (wyjety->isAgent()) {
                config.agentNames.push_back(wyjety->getNickname());
            }
            else if (!wyjety->isAgent()) {
                config.groupNames.push_back(wyjety->getNickname());
            }
        }
    }
}

void StaffLogic::regen(GameState& state)
{
    const int MAX_RYNEK = 18;
    const int MAX_GRUP = 9;
    const int MAX_AGENTOW = 9;

    auto& rynek = state.getRynekPracy();

    if (rynek.size() < MAX_RYNEK)
    {
        int liczbaGrup = 0;
        int liczbaAgentow = 0;

        for (const auto& pracownik : rynek)
        {
            if (dynamic_cast<Grupa*>(pracownik.get()))
            {
                liczbaGrup++;
            }
            else if (dynamic_cast<Agent*>(pracownik.get()))
            {
                liczbaAgentow++;
            }
        }

        if (liczbaGrup < MAX_GRUP && liczbaAgentow < MAX_AGENTOW)
        {
            static std::random_device rd;
            static std::mt19937 engine(rd());
            std::uniform_int_distribution<int> id(0, 1);

            if (id(engine) == 0) gen<Agent>();
            else gen<Grupa>();
        }
        else if (liczbaGrup < MAX_GRUP)
        {
            gen<Grupa>();
        }
        else if (liczbaAgentow < MAX_AGENTOW)
        {
            gen<Agent>();
        }
    }
}