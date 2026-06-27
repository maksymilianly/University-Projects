#pragma once
#include <SFML/Graphics.hpp>
import ConfigMod;

class GameState;


class UILogic {
private:
    /// <summary>Flaga określająca, czy okno sklepu jest obecnie otwarte</summary>
    bool shopOpen;

    /// <summary>Flaga określająca, czy okno zarządzania pracownikami jest obecnie aktywne</summary>
    bool czyPracownicy;

public:
    /// <summary>
    /// Inicjalizuje logikę UI
    /// </summary>
    /// <param name="config">Referencja do menedżera konfiguracji</param>
    /// <param name="state">Referencja do globalnego stanu gry</param>
    UILogic(Config& config, GameState& state);

    /// <summary>
    /// Sprawdza, czy kursor myszy znajduje się w obszarze przycisku sklepu
    /// Ułatwia obsługę zdarzeń kliknięcia w głównym menedżerze UI
    /// </summary>
    /// <param name="mousePos">Aktualna pozycja kursora myszy</param>
    /// <param name="przycisk">Granice prostokąta (hitbox) przycisku</param>
    /// <returns>True, jeśli kursor wskazuje na przycisk</returns>
    bool checkShopButton(const sf::Vector2f& mousePos, const sf::FloatRect& przycisk);

    /// <summary>Zwraca informację, czy panel sklepu jest otwarty</summary>
    bool getShopOpen() { return shopOpen; }

    /// <summary>Zwraca informację, czy panel pracowników jest otwarty</summary>
    bool getCzyPracownicy() { return czyPracownicy; }
};