#pragma once
#include <SFML/Graphics.hpp>

#include "RadarTypes.h"

struct Config;
class GameState;

#include <vector>

class RadarLogic
{
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
	RadarLogic(Config& config, GameState& state);
	bool getIsRadarOn() const { return isRadarOn; }
	void changeRadarState(bool x) { isRadarOn = x;}
	bool getIsPoleOn() const { return isPoleOn; }
	void changePoleState(bool x) { isPoleOn = x; }
	void toggleRadar() { isRadarOn = !isRadarOn; }

	float getProjectorAngle() const { return current_projektor_angle; }
	void setProjectorAngle(float angle) { current_projektor_angle += angle; }
	float getOdbiornikAngle() const { return current_odbiornik_angle; }
	void setOdbiornikAngle(float angle, float dt) { current_odbiornik_angle += angle * dt / 2; }
	void updateProjector(float dt);
	void updateOdbiornik(bool goradol, float dt);

	bool czyPusteSygnaly() { return signals.empty(); }
	const std::vector<Signal>& getSygnaly() const { return signals; }
	const std::vector<SukcesWylapania>& getSukcesy() const { return sukcesWylapania; }

	void addSignal(float x, float y, float angle, float speed, float strenght,int typSygnalu, bool hostile);
	void spawnRandomSignal(float dt);

	void updateSignals(float dt,sf::Vector2f& catcherPos,float& catcherRadius);
	bool checkTrafienie(const Signal& signal, sf::Vector2f& catcherPos, float& catcherRadius);

	size_t getSignalSize() const {
		return getSygnaly().size();
	}
	size_t getIkonkiSize() const {
		return getSukcesy().size();
	}
	std::vector<int> wyjmijTransakcje() {
		return std::move(transakcje);
	}
	int getHostile() { return radar_hostile_payment; }
	bool checkPrzycisk(sf::Vector2f& mouseEvent, sf::FloatRect przycisk)
	{
		return przycisk.contains(mouseEvent);
	}
	bool checkDoor(sf::Vector2f& mouseEvent, sf::FloatRect doorsSprite)
	{
		return doorsSprite.contains(mouseEvent);
	}
	bool checkZoom(sf::Vector2f& mouseEvent, sf::FloatRect zoomPrzycisk)
	{
		return zoomPrzycisk.contains(mouseEvent);
	}
	void nadpiszPos(float nr, sf::Vector2f pos);
	void przemapujSygnaly(float skala,sf::Vector2f newPos);

};