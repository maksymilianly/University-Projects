#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <vector>
#include "Visual.h"

import AssetsMod;
import ConfigMod;

class GameState;

/// <summary>
/// Klasa odpowiedzialna za warstwę wizualną interfejsu użytkownika (UI)
/// Zarządza renderowaniem tekstów
/// dla przycisków sklepu i ofert zadań
/// </summary>
class UIVisual : public Visual {
private:
	/// <summary>Elementy tekstowe UI</summary>
	sf::Text kontoText;
	sf::Text sklepText;
	sf::Text pracownicyText;

	/// <summary>Kontenery przechowujące teksty ofert oraz ich obszary kolizji</summary>
	std::vector<sf::Text> opisOfert;
	std::vector<sf::FloatRect> hitboxyKupZadanie;
	std::vector<sf::FloatRect> hitboxyUsunSprzedaj;

public:
	/// <summary>
	/// Inicjalizuje warstwę wizualną interfejsu
	/// </summary>
	/// <param name="assets">Referencja do zasobó</param>
	/// <param name="config">Referencja do konfiguracji gry</param>
	/// <param name="state">Referencja do stanu gry </param>
	UIVisual(Assets& assets, Config& config, GameState& state);

	/// <summary>
	/// Aktualizuje zawartość tekstów w oparciu o aktualny stan gry
	/// </summary>
	/// <param name="state">Stan gry zawierający dane do odświeżenia</param>
	void update(GameState& state);

	/// <summary>
	/// Rysuje podstawowe elementy UI
	/// </summary>
	/// <param name="window">Referencja do okna renderującego</param>
	void draw(sf::RenderWindow& window) override;

	/// <summary>
	/// Rysuje przycisk sklepu, uwzględniając czy aktualnie widoczny jest panel pracowników
	/// </summary>
	/// <param name="window">Referencja do okna renderującego</param>
	/// <param name="czyPracownicy">Czy panel pracowników jest aktywny</param>
	void drawShopButton(sf::RenderWindow& window, bool czyPracownicy);

	/// <summary>
	/// Rysuje dynamicznie generowaną listę ofert w sklepie
	/// </summary>
	/// <param name="window">Referencja do okna renderującego</param>
	/// <param name="shopOpen">Czy sklep jest otwarty</param>
	/// <param name="czyPracownicy">Czy tryb pracowników jest aktywny</param>
	/// <param name="identyfikatory">Lista identyfikatorów ofert do wyświetlenia</param>
	/// <param name="assets">Zasoby potrzebne do rysowania</param>
	/// <param name="config">Konfiguracja wizualna</param>
	void drawDynamic(sf::RenderWindow& window, bool shopOpen, bool czyPracownicy, const std::vector<std::string>& identyfikatory, Assets& assets, Config& config);

	/// <summary>
	/// Zwraca granice przycisku sklepu
	/// </summary>
	sf::FloatRect getShopButton() const& { return sprites.at("ui_shop_button").getGlobalBounds(); }

	/// <summary>
	/// Pobiera i przygotowuje dane ofert sklepu do wyświetlenia
	/// </summary>
	/// <param name="czyPracownicy">Czy ładować oferty dla pracowników</param>
	/// <param name="state">Stan gry</param>
	/// <param name="assets">Zasoby</param>
	/// <returns>Wektor napisów z danymi ofert</returns>
	std::vector<std::string> zaladujDaneSklepu(bool czyPracownicy, GameState& state, Assets& assets);

	/// <summary>
	/// logika kupowania
	/// </summary>
	/// <param name="mousePos">Pozycja kursora myszy</param>
	/// <returns>Indeks klikniętej oferty lub -1, jeśli nie trafiono</returns>
	int sprawdzKlikniecieGora(const sf::Vector2f& mousePos);

	/// <summary>
	/// logika sprzedazy
	/// </summary>
	/// <param name="mousePos">Pozycja kursora myszy</param>
	/// <returns>Indeks klikniętej oferty lub -1, jeśli nie trafiono</returns>
	int sprawdzKlikniecieDol(const sf::Vector2f& mousePos);
};