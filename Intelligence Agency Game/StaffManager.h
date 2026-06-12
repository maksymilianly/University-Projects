#pragma once

#include "StaffLogic.h"

struct Assets;
struct Config;
class GameState;

class StaffManager
{
private:
	StaffLogic logika;
public:
    StaffManager(Assets& assets, Config& config, GameState& _state);

    void update(GameState& state);
};
