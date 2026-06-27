#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <functional>
#include "GameScenes.h"
#include "UIElement.h"
#include "UIOverlay.h"
#include "UIButton.h"
#include "Staff.h"
#include "Event.h"


import AssetsMod;
import ConfigMod;


class GameState;

/// <summary>
/// Klasa rozszerzająca bazową scenę o funkcjonalność interfejsu użytkownika (UI)
/// Odpowiada za zarządzanie nakładkami (sklep, posiadane zasoby), obsługę zdarzeń systemowych 
/// oraz filtrowanie logiki pracowników prezentowanych w interfejsie.
/// </summary>
class GameSceneWithUI : public GameScenes {
protected:
    /// <summary>Kontener elementów interfejsu użytkownika (przyciski, panele)</summary>
    std::vector<std::unique_ptr<UIElement>> UIelements;

    /// <summary>Nakładka widoku sklepu</summary>
    std::unique_ptr<UIOverlay> shop;
    /// <summary>Nakładka widoku posiadanych zasobów/pracowników</summary>
    std::unique_ptr<UIOverlay> possesion;
    /// <summary>Obiekt zarządzający zdarzeniami typu pop-up</summary>
    std::unique_ptr<Event> event;

    /// <summary>Funkcja, określająca regułę filtrowania pracowników</summary>
    std::function<bool(Staff*)> filter;

    /// <summary>Indeks pracownika wybranego przez użytkownika (-1 oznacza brak wyboru)</summary>
    int clickedWorker = -1;

public:
    /// <summary>
    /// Inicjalizuje scenę z UI, konfigurując logikę filtrowania wyświetlanych pracowników
    /// </summary>
    /// <param name="assets">Referencja do menedżera zasobów</param>
    /// <param name="config">Referencja do konfiguracji gry</param>
    /// <param name="state">Referencja do stanu gry</param>
    /// <param name="_Filter">Funkcja sprawdzająca czy pracownik spełnia kryteria wyświetlania</param>
    GameSceneWithUI(Assets& assets, Config& config, GameState& state,
        std::function<bool(Staff*)> _Filter);

    /// <summary>Wczytuje definicje przycisków z konfiguracji i dodaje je do listy elementów UI</summary>
    void loadButtons();

    /// <summary>
    /// Wykonuje akcję przypisaną do przycisku o podanej nazwie
    /// </summary>
    /// <param name="name">Unikalna nazwa przycisku (np. "btn_buy", "btn_sell")</param>
    void actionButton(std::string name);

    /// <summary>Aktualizuje stan elementów UI (np. odświeżenie tekstu, widoczność)</summary>
    void updateUI();

    /// <summary>
    /// Rysuje wszystkie aktywne elementy interfejsu w oknie gry
    /// </summary>
    /// <param name="window">Referencja do okna SFML</param>
    void drawUI(sf::RenderWindow& window);

    /// <summary>
    /// Obsługuje zdarzenia wejściowe (mysz) dla elementów UI
    /// </summary>
    /// <param name="event">Zdarzenie SFML</param>
    /// <param name="window">Okno gry (do mapowania pozycji myszy)</param>
    /// <returns>True, jeśli zdarzenie zostało przechwycone przez UI (np. kliknięto przycisk)</returns>
    bool obslugaZdarzenUI(const sf::Event& event, const sf::RenderWindow& window);
};