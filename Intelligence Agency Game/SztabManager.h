#pragma once
#include "SzyfrLogic.h"
#include "SzyfrVisual.h"
#include "SztabVisual.h"
#include "SztabLogic.h"
#include "StaffManager.h"
#include "GameSceneWithUI.h"

import AssetsMod;
import ConfigMod;

class GameState;

/// <summary>
/// Menedżer sceny sztabu. Odpowiada za koordynację logiki zadań (szyfrów)
/// zarządzanie personelem oraz wizualną reprezentację sztabu
/// Klasa ta zarządza interakcjami użytkownika, takimi jak przesuwanie stołów czy wybór zadań
/// </summary>
class SztabManager : public GameSceneWithUI {
private:
    /// <summary>Logika procesów deszyfrowania</summary>
    SzyfrLogic szyfr_logika;
    /// <summary>Wizualizacja procesów deszyfrowania</summary>
    SzyfrVisual szyfrvisual;
    /// <summary>Wizualizacja pomieszczenia sztabu</summary>
    SztabVisual sztabvisual;
    /// <summary>Logika zarządzania przestrzenią sztabu</summary>
    SztabLogic sztablogika;
    /// <summary>Zarządca zasobów ludzkich</summary>
    StaffManager staff_manager;

    /// <summary>Flaga określająca, czy aktualnie trwa operacja przesuwania stołu</summary>
    bool przesuniecieStol;
    /// <summary>Indeks aktualnie przesuwanego stołu</summary>
    int idxStolu;
    /// <summary>Oryginalne współrzędne przed rozpoczęciem przesuwania</summary>
    sf::Vector2f originalXY;
    /// <summary>Wektor przesunięcia używany podczas operacji drag & drop</summary>
    sf::Vector2f przesuniecie;
    /// <summary>Para przechowująca pozycję wizualną i indeks ostatnio klikniętego szyfru</summary>
    std::pair<sf::Vector2f, int> XYSzyfru{ {-1, -1}, -1 };
    /// <summary>Flaga określająca, czy aktualnie trwa operacja przesuwania szyfru</summary>
    bool przesuniecieSzyfr;

public:
    /// <summary>
    /// Inicjalizuje menedżera sztabu
    /// </summary>
    /// <param name="_assets">Referencja do menedżera zasobów</param>
    /// <param name="_config">Referencja do konfiguracji gry</param>
    /// <param name="_state">Referencja do globalnego stanu gry</param>
    SztabManager(Assets& _assets, Config& _config, GameState& _state);

    /// <summary>
    /// Główna pętla aktualizacji logiki sceny sztabu
    /// </summary>
    /// <param name="dt">Delta time</param>
    void update(float dt) override;

    /// <summary>
    /// Renderuje wszystkie elementy sceny sztabu
    /// </summary>
    /// <param name="window">Referencja do okna renderującego</param>
    void draw(sf::RenderWindow& window) override;

    /// <summary>
    /// Obsługuje zdarzenia wejściowe
    /// </summary>
    /// <param name="event">Zdarzenie SFML</param>
    /// <param name="window">Okno gry</param>
    void obslugaZdarzen(const sf::Event& event, const sf::RenderWindow& window) override;

    /// <summary>
    /// Synchronizuje dane między menedżerem a stanem gry
    /// </summary>
    void obslugaDanych();

    /// <summary>
    /// Inicjuje rozmieszczenie nowych stołów w sztabie
    /// </summary>
    /// <param name="pojemnosc">Liczba stanowisk przy nowym stole</param>
    void placeStoly(int pojemnosc);
};