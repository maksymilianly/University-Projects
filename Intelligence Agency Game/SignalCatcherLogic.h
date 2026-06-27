#pragma once
#include <SFML/Graphics.hpp>
import AssetsMod;
import ConfigMod;

/// <summary>
/// Klasa zarządzająca logiką obiektu przechwytującego (catcher) na radarze
/// Odpowiada za poruszanie się, utrzymywanie obiektu w granicach radaru oraz definicję zasięgu interakcji
/// </summary>
class SignalCatcherLogic {
private:
	/// <summary>Aktualna pozycja obiektu przechwytującego</summary>
	sf::Vector2f catcherPos;

	/// <summary>Granice obszaru radaru, wewnątrz których może poruszać się obiekt</summary>
	sf::FloatRect radarBounds;

	/// <summary>Promień interakcji obiektu</summary>
	float catcherRadius;

	/// <summary>Prędkość poruszania się obiektu przechwytującego</summary>
	float catcherMoveSpeed;

public:
	/// <summary>
	/// Inicjalizuje logikę przechwytywania sygnałów, pobierając ustawienia z konfiguracji
	/// </summary>
	/// <param name="assets">Referencja do zasobów</param>
	/// <param name="config">Referencja do konfiguracji gry (z niej pobierane są parametry prędkości i zasięgu)</param>
	SignalCatcherLogic(Assets& assets, Config& config);

	/// <summary>
	/// Przemieszcza obiekt przechwytujący o zadany wektor w czasie
	/// </summary>
	/// <param name="dt">Delta time (czas klatki)</param>
	/// <param name="vector">Wektor kierunkowy ruchu</param>
	void move(float dt, sf::Vector2f vector);

	/// <summary>Zwraca referencję do pozycji obiektu </summary>
	sf::Vector2f& getCatcherPos() { return catcherPos; }

	/// <summary>Zwraca referencję do promienia obiektu</summary>
	float& getRadarRadius() { return catcherRadius; }

	/// <summary>
	/// Wymusza ograniczenie pozycji obiektu do obszaru `radarBounds` (np. zapobiega wyjściu poza tarczę radaru).
	/// </summary>
	void compareWithRadarBounds();
};