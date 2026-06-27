#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include "RadarTypes.h"

import ConfigMod;

class GameState;

/// <summary>
/// Główna klasa logiki radaru. Odpowiada za rotację głowicy (projektor/odbiornik), 
/// zarządzanie wykrytymi sygnałami, detekcję kolizji oraz logikę płatności za przechwycone obiekty
/// </summary>
class RadarLogic {
private:
	float current_projektor_angle;
	float current_odbiornik_angle;

	float radar_projektor_rotation;
	float radar_odbiornik_rotation;

	float radar_odbiornik_sector;
	bool isPoleOn;

	std::vector<Signal> signals;
	std::vector<SukcesWylapania> sukcesWylapania;
	std::vector<int> transakcje;

	bool isRadarOn;
	float radar_posX;
	float radar_posY;
	float radar_radius;

	int radar_friendly_payment;
	int radar_hostile_payment;

	float timer;
	float radar_spawn_time;
	int radar_max_signals;

public:
	/// <summary>Inicjalizuje logikę radaru z dostępem do konfiguracji i stanu gry</summary>
	RadarLogic(Config& config, GameState& state);

	/// <summary>Sprawdza, czy radar jest aktualnie włączony</summary>
	bool getIsRadarOn() const { return isRadarOn; }

	/// <summary>Ustawia stan aktywności radaru</summary>
	void changeRadarState(bool x) { isRadarOn = x; }

	/// <summary>Sprawdza, czy pole skanowania jest włączone</summary>
	bool getIsPoleOn() const { return isPoleOn; }

	/// <summary>Ustawia stan aktywności pola skanowania</summary>
	void changePoleState(bool x) { isPoleOn = x; }

	/// <summary>Zmienia stan radaru na przeciwny (włącz/wyłącz)</summary>
	void toggleRadar() { isRadarOn = !isRadarOn; }

	/// <summary>Pobiera aktualny kąt projektora</summary>
	float getProjectorAngle() const { return current_projektor_angle; }

	/// <summary>Modyfikuje kąt projektora o zadaną wartość</summary>
	void setProjectorAngle(float angle) { current_projektor_angle += angle; }

	/// <summary>Pobiera aktualny kąt odbiornika</summary>
	float getOdbiornikAngle() const { return current_odbiornik_angle; }

	/// <summary>Aktualizuje kąt odbiornika z uwzględnieniem czasu klatki</summary>
	void setOdbiornikAngle(float angle, float dt) { current_odbiornik_angle += angle * dt / 2; }

	/// <summary>Aktualizuje rotację projektora w czasie</summary>
	void updateProjector(float dt);

	/// <summary>Aktualizuje rotację odbiornika</summary>
	/// <param name="goradol">Kierunek obrotu (góra/dół lub lewo/prawo)</param>
	void updateOdbiornik(bool goradol, float dt);

	/// <summary>Sprawdza, czy kontener sygnałów jest pusty</summary>
	bool czyPusteSygnaly() { return signals.empty(); }

	/// <summary>Pobiera referencję do listy wszystkich sygnałów</summary>
	const std::vector<Signal>& getSygnaly() const { return signals; }

	/// <summary>Pobiera referencję do listy sukcesów przechwycenia</summary>
	const std::vector<SukcesWylapania>& getSukcesy() const { return sukcesWylapania; }

	/// <summary>Dodaje nowy sygnał do systemu radaru</summary>
	void addSignal(float x, float y, float angle, float speed, float strenght, int typSygnalu, bool hostile);

	/// <summary>Generuje losowy sygnał w systemie</summary>
	void spawnRandomSignal(float dt);

	/// <summary>Aktualizuje pozycję i stan wszystkich sygnałów</summary>
	void updateSignals(float dt, sf::Vector2f& catcherPos, float& catcherRadius);

	/// <summary>Sprawdza, czy sygnał został trafiony przez "catcher"</summary>
	bool checkTrafienie(const Signal& signal, sf::Vector2f& catcherPos, float& catcherRadius);

	/// <summary>Zwraca liczbę aktywnych sygnałów</summary>
	size_t getSignalSize() const { return getSygnaly().size(); }

	/// <summary>Zwraca liczbę ikon sukcesów</summary>
	size_t getIkonkiSize() const { return getSukcesy().size(); }

	/// <summary>Pobiera i czyści listę transakcji</summary>
	std::vector<int> wyjmijTransakcje() { return std::move(transakcje); }

	/// <summary>Pobiera kwotę wypłaty za wykrycie wrogiego obiektu</summary>
	int getHostile() { return radar_hostile_payment; }

	/// <summary>Sprawdza czy kursor znajduje się w obrębie przycisku</summary>
	bool checkPrzycisk(sf::Vector2f& mouseEvent, sf::FloatRect przycisk) { return przycisk.contains(mouseEvent); }

	/// <summary>Sprawdza czy kursor znajduje się w obrębie drzwi</summary>
	bool checkDoor(sf::Vector2f& mouseEvent, sf::FloatRect doorsSprite) { return doorsSprite.contains(mouseEvent); }

	/// <summary>Sprawdza czy kursor znajduje się w obrębie przycisku Zoom</summary>
	bool checkZoom(sf::Vector2f& mouseEvent, sf::FloatRect zoomPrzycisk) { return zoomPrzycisk.contains(mouseEvent); }

	/// <summary>Nadpisuje pozycję elementu w systemie radaru</summary>
	void nadpiszPos(float nr, sf::Vector2f pos);

	/// <summary>Przelicza współrzędne sygnałów po zmianie skali lub pozycji radaru</summary>
	void przemapujSygnaly(float skala, sf::Vector2f newPos);
};