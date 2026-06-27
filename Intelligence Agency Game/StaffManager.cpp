#include "StaffManager.h"

#include "GameState.h"
//#include "Assets.h"
//#include "Config.h"
import AssetsMod;
import ConfigMod;


StaffManager::StaffManager(Assets& assets, Config& config, GameState& _state)
    : logika(assets, config, _state)
{
}

void StaffManager::update(GameState& state)
{
    logika.regen(state);

}