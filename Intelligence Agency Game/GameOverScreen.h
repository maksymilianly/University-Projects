#pragma once
#include "Ekran.h"
#include "RadarManager.h"
#include "SztabManager.h"
#include "MapaManager.h"
#include "GameOverVisual.h"
#include <memory>
#include <vector>

import AssetsMod;
import ConfigMod;

class GameState;

/// <summary>
/// Ekran wyświetlany po zakończeniu gry
/// Zarządza wizualizacją komunikatu o końcu gry 
/// </summary>
class GameOverScreen : public Ekran {
private:
	/// <summary>Moduł odpowiedzialny za renderowanie grafiki ekranu końca gry</summary>
	std::unique_ptr<GameOverVisual> gameOver;

	/// <summary>Czas w sekundach, po którym ekran może zostać automatycznie zamknięty lub zmienić stan</summary>
	float time_to_close = 5.0f;

public:
	/// <summary>
	/// Inicjalizuje ekran końca gry
	/// </summary>
	/// <param name="_assets">Referencja do zasobów</param>
	/// <param name="_config">Referencja do konfiguracji gry</param>
	/// <param name="_state">Referencja do stanu gry</param>
	GameOverScreen(Assets& _assets, Config& _config, GameState& _state);

	/// <summary>
	/// Inicjalizacja zasobów specyficznych dla ekranu
	/// </summary>
	/// <param name="assets">Zasoby</param>
	/// <param name="config">Konfiguracja</param>
	/// <param name="state">Stan gry</param>
	void init(Assets& assets, Config& config, GameState& state);

	/// <summary>
	/// Sprawdza, czy upłynął czas przewidziany na wyświetlanie ekranu
	/// </summary>
	/// <param name="dt">Delta time</param>
	/// <returns>True, jeśli czas do zamknięcia minął</returns>
	bool timeOver(float dt);

	/// <summary>
	/// Rysuje ekran końca gry w oknie
	/// </summary>
	/// <param name="window">Referencja do okna renderującego SFML</param>
	void draw(sf::RenderWindow& window) override;

	/// <summary>
	/// Aktualizuje logikę ekranu końca gry
	/// </summary>
	/// <param name="dt">Delta time</param>
	void update(float dt) override;

	/// <summary>
	/// Obsługuje zdarzenia wejściowe dla ekranu końca gry 
	/// </summary>
	/// <param name="event">Zdarzenie SFML</param>
	/// <param name="window">Okno gry</param>
	void obslugaZdarzen(const sf::Event& event, const sf::RenderWindow& window) override;

	/// <summary>
	/// Synchronizuje dane dla ekranu końca gry
	/// </summary>
	void obslugaDanych() override;
};