#pragma once
#include <memory>
#include <SFML/Graphics.hpp> 
#include "UIInfoPanel.h"
#include "EventData.h"
#include "UIButton.h"

import AssetsMod;

/// <summary>
/// Klasa zarządzająca wyświetlaniem i obsługą zdarzeń w grze (np. pop-upów informacyjnych)
/// Odpowiada za aktywację, renderowanie oraz obsługę interakcji użytkownika z panelem zdarzenia
/// </summary>
class Event {
private:
    /// <summary>Panel informacyjny wyświetlany w ramach zdarzenia</summary>
    std::unique_ptr<UIInfoPanel> pop_out;

    /// <summary>Flaga określająca, czy zdarzenie jest obecnie aktywne i powinno być rysowane</summary>
    bool active_pop_out;

public:
    /// <summary>
    /// Inicjalizuje obiekt zdarzenia, przygotowując panel
    /// </summary>
    /// <param name="assets">Referencja do menedżera zasobów</param>
    Event(Assets& assets);

    /// <summary>
    /// Konfiguruje zdarzenie na podstawie przesłanych danych
    /// </summary>
    /// <param name="data">Struktura zawierająca informacje o zdarzeniu (treść, tytuł itp.)</param>
    void setEvent(const EventData& data);

    /// <summary>
    /// Sprawdza, czy zdarzenie jest aktywne
    /// </summary>
    /// <returns>True, jeśli zdarzenie jest aktywne, w przeciwnym razie false</returns>
    bool is_active() { return active_pop_out; }

    /// <summary>
    /// Ustawia status aktywności zdarzenia
    /// </summary>
    /// <param name="val">Wartość ustawiająca status aktywności</param>
    void set_active(bool val) { active_pop_out = val; }

    /// <summary>
    /// Rysuje panel zdarzenia w oknie renderującym, jeśli zdarzenie jest aktywne
    /// </summary>
    /// <param name="window">Referencja do okna SFML</param>
    void drawEvent(sf::RenderWindow& window);

    /// <summary>
    /// Obsługuje kliknięcia użytkownika w obrębie panelu zdarzenia
    /// </summary>
    /// <param name="_event">Zdarzenie wejściowe SFML</param>
    /// <param name="mousePos">Pozycja myszy w przestrzeni ekranu</param>
    /// <returns>True, jeśli kliknięcie zostało "przechwycone" przez panel zdarzenia (np. przycisk OK)</returns>
    bool obsluzKlikniecie(const sf::Event& _event, const sf::Vector2f& mousePos);
};