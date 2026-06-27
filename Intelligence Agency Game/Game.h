#pragma once


#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "SceneManager.h"
#include "GameState.h"
#include "GlobalUI.h"


import AssetsMod;
import ConfigMod;

/// <summary>
/// Główna klasa zarządzająca cyklem życia aplikacji
/// Odpowiada za inicjalizację silnika, pętlę główną (main loop), 
/// zarządzanie oknem gry oraz koordynację systemów (UI, sceny, zasoby).
/// </summary>
class Game {
private:
    /// <summary>Główne okno renderujące aplikacji SFML</summary>
    sf::RenderWindow window;

    /// <summary>Menedżer zasobów przechowujący tekstury i czcionki</summary>
    Assets assets;

    /// <summary>Menedżer konfiguracji wczytujący dane z plików JSON i tekstowych</summary>
    Config config;

    /// <summary>Zarządca scen odpowiadający za przełączanie ekranów gry</summary>
    SceneManager ekrany;

    /// <summary>Obiekt stanu gry przechowujący dane logiczne (budżet, kadry, misje)</summary>
    GameState state;

    /// <summary>Inteligentny wskaźnik zarządzający interfejsem użytkownika (UI).</summary>
    std::unique_ptr<GlobalUI> UIManager;

public:
    /// <summary>
    /// Inicjalizuje okno, wczytuje zasoby, ładuje konfigurację 
    /// oraz przygotowuje początkowy stan gry
    /// </summary>
    Game();

    /// <summary>
    /// Uruchamia główną pętlę gry. Odpowiada za przetwarzanie zdarzeń,
    /// aktualizację logiki scen oraz renderowanie klatek.
    /// </summary>
    void run();
};