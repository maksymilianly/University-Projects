#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "Ekran.h"
#include "GameScreen.h"
#include "GameState.h"

import AssetsMod;
import ConfigMod;

/// <summary>
/// Definiuje stany, w jakich może znajdować się aplikacja
/// </summary>
enum class AppState {
    Menu,      ///< Ekran głównego menu
    Game,      ///< Aktywna rozgrywka
    GameOver   ///< Ekran końca gry
};

/// <summary>
/// Zarządza stanami gry oraz przełączaniem między różnymi ekranami (np. Menu, Gra, GameOver)
/// Działa jako automat stanów (State Machine) sterujący przepływem aplikacji
/// Oddelegowuje rysowanie, aktualizację i obsługę zdarzeń do aktywnego ekranu
/// </summary>
class SceneManager {
private:
    /// <summary>Kontener na dostępne ekrany gry</summary>
    std::vector<std::unique_ptr<Ekran>> gameScreens;
    /// <summary>Osobny wskaźnik na ekran końca gry</summary>
    std::unique_ptr<Ekran> gameOverScreen;

    /// <summary>Wskaźnik na aktualnie aktywny ekran (nie posiada własności)</summary>
    Ekran* currentEkran;
    /// <summary>Aktualny stan aplikacji</summary>
    AppState currentState;

    /// <summary>Wskaźniki na współdzielone zasoby gry</summary>
    Assets* m_assets = nullptr;
    Config* m_config = nullptr;
    GameState* m_state = nullptr;

public:
    /// <summary>Konstruktor domyślny</summary>
    SceneManager();
    ~SceneManager() = default;

    /// <summary>
    /// Zmienia stan aplikacji na nowy. Obsługuje przełączenie wskaźnika aktualnego ekranu
    /// </summary>
    /// <param name="newState">Docelowy stan aplikacji</param>
    void changeState(AppState newState);

    /// <summary>Zwraca aktualny stan aplikacji</summary>
    AppState getCurrentState() const;

    /// <summary>Zwraca wskaźnik do aktualnie aktywnego ekranu</summary>
    Ekran* getCurrentEkran() const;

    /// <summary>Deleguje renderowanie do aktywnego ekranu</summary>
    /// <param name="window">Referencja do okna SFML</param>
    void drawScenes(sf::RenderWindow& window);

    /// <summary>Deleguje aktualizację logiki do aktywnego ekranu</summary>
    /// <param name="dt">Czas trwania klatki</param>
    void update(float dt);

    /// <summary>Deleguje obsługę zdarzeń wejściowych do aktywnego ekranu</summary>
    /// <param name="event">Zdarzenie SFML</param>
    /// <param name="window">Okno gry</param>
    void obslugaZdarzen(const sf::Event& event, const sf::RenderWindow& window);

    /// <summary>
    /// Inicjalizuje menedżera zasobami i stanem gry
    /// </summary>
    /// <param name="_assets">Zasoby</param>
    /// <param name="_config">Konfiguracja</param>
    /// <param name="state">Stan gry</param>
    void init(Assets& _assets, Config& _config, GameState& state);

    /// <summary>Wywołuje przejście do ekranu końca gry</summary>
    void invokeGameOverScene();
};