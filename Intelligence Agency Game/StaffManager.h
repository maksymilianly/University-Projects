#pragma once
#include "StaffLogic.h"

import AssetsMod;
import ConfigMod;

class GameState;

/// <summary>
/// Menedżer nadrzędny odpowiedzialny za system kadr w grze
/// Koordynuje logikę generowania i zarządzania pracownikami
/// </summary>
class StaffManager {
private:

    StaffLogic logika;

public:
    /// <summary>
    /// Inicjalizuje menedżera personelu
    /// </summary>
    /// <param name="assets">Referencja do menedżera zasobów</param>
    /// <param name="config">Referencja do konfiguracji gry</param>
    /// <param name="_state">Referencja do globalnego stanu gry</param>
    StaffManager(Assets& assets, Config& config, GameState& _state);

    /// <summary>
    /// Aktualizuje stan kadrowy w danej klatce (np. odświeżanie dostępnych ofert)
    /// </summary>
    /// <param name="state">Referencja do globalnego stanu gry</param>
    void update(GameState& state);
};