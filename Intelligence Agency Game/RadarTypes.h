#pragma once
#include <SFML/Graphics.hpp>


enum class TypSygnalu {
    Brak,
    Ship,
    Plane,
    Ground,
};

enum class TypKierunku {
    none,
    sin,
    cos,
    ln,
    exp,
    count 
};

struct Signal {
    float x;
    float y;
    float flightAngle;
    float speed;
    float strength;
    bool hostile;
    float timeToLive = 0.0f;
	TypSygnalu typ;
	TypKierunku newDirection;
    float amplituda;     
    float czestotliwosc; 
    float modyfikator;
};

struct SukcesWylapania {
    bool sukcesOstatniegoWylapania;
    sf::Vector2f pozycjaCelu;
    sf::Clock iconTimer;
    bool wrogi;
};