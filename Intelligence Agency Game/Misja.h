#pragma once
#include "SFML/Graphics.hpp"
#include <string>

#include "CountriesEnums.h"

class Misja
{
private:
	std::string nazwaMiasta;
	Country kraj;
	sf::Vector2f pozycjaMiasta;
public:
	Misja(std::string n, Country k, sf::Vector2f p);
	const std::string& getNazwa() const { return nazwaMiasta; }
	Country getKraj() const { return kraj; }
	const sf::Vector2f& getPozycjaMiasta() const { return pozycjaMiasta; }
};