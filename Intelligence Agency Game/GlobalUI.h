#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <string>
#include <functional>
#include "UIElement.h"
#include "UIOverlay.h"

import AssetsMod;
import ConfigMod;

class GameState;

/// <summary>
/// Klasa nadrzędna zarządzająca globalnym interfejsem użytkownika (HUD)
/// Odpowiada za wyświetlanie stałych elementów UI, takich jak stan konta
/// </summary>
class GlobalUI {
private:
    /// <summary>Referencja do menedżera zasobów</summary>
    Assets& assets;
    /// <summary>Referencja do konfiguracji gry</summary>
    Config& config;
    /// <summary>Referencja do stanu gry</summary>
    GameState& state;

    /// <summary>Obiekt tekstowy wyświetlający aktualną ilość pieniędzy</summary>
    sf::Text moneyText;

public:
    /// <summary>
    /// Inicjalizuje globalny interfejs użytkownika
    /// </summary>
    /// <param name="_assets">Referencja do zasobów</param>
    /// <param name="_config">Referencja do konfiguracji</param>
    /// <param name="_state">Referencja do stanu gry</param>
    GlobalUI(Assets& _assets, Config& _config, GameState& _state);

    /// <summary>
    /// Renderuje wszystkie globalne elementy UI
    /// </summary>
    /// <param name="window">Referencja do okna renderującego SFML</param>
    void drawGlobalUI(sf::RenderWindow& window);

    /// <summary>
    /// Rysuje informację o stanie finansów na ekranie
    /// </summary>
    /// <param name="window">Referencja do okna renderującego SFML</param>
    void drawMoney(sf::RenderWindow& window);
};