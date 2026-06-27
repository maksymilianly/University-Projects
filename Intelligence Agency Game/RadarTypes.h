#pragma once
#include <SFML/Graphics.hpp>

/// <summary>
/// Typy obiektów możliwych do wykrycia przez system radarowy
/// </summary>
enum class TypSygnalu {
    /// <summary>Brak określonego typu</summary>
    Brak,
    /// <summary>Obiekt pływający (np. łódź, okręt)</summary>
    Ship,
    /// <summary>Obiekt latający</summary>
    Plane,
    /// <summary>Obiekt naziemny</summary>
    Ground
};

/// <summary>
/// Definiuje wzorce matematyczne ruchu obiektu wykorzystywane w obliczeniach trajektorii
/// </summary>
enum class TypKierunku {
    none,
    sin,
    cos,
    ln,
    exp,
    /// <summary>Stała pomocnicza służąca do określania liczby dostępnych typów kierunków</summary>
    count
};

/// <summary>
/// Reprezentuje pojedynczy sygnał (obiekt) wykryty na radarze
/// Zawiera parametry fizyczne, stan logiczny oraz wzorce ruchu
/// </summary>
struct Signal {
    float x;
    float y;
    float flightAngle;
    float speed;
    float strength;
    /// <summary>czas życia sygnału (Time To Live). Potzebny m.in do wyliczania odchylenia</summary>
    float timeToLive = 0.0f;
    /// <summary>Typ obiektu (np. statek, samolot)</summary>
    TypSygnalu typ;
    /// <summary>Wzór matematyczny opisujący sposób poruszania się obiektu</summary>
    TypKierunku newDirection;
    /// <summary>Amplituda sygnału</summary>
    float amplituda;
    /// <summary>Częstotliwość fali sygnału</summary>
    float czestotliwosc;
    /// <summary>Współczynnik modyfikujący parametry lotu lub sygnału</summary>
    float modyfikator;
    /// <summary>Flaga określająca, czy obiekt jest wrogi</summary>
    bool hostile;
};

/// <summary>
/// Struktura przechowująca informacje o powodzeniu próby przechwycenia sygnału
/// Służy do wyświetlania wizualnego feedbacku dla gracza
/// </summary>
struct SukcesWylapania {
    /// <summary>Status ostatniej operacji wylapania</summary>
    bool sukcesOstatniegoWylapania;
    /// <summary>Współrzędne miejsca, w którym nastąpiło wylapanie</summary>
    sf::Vector2f pozycjaCelu;
    /// <summary>Timer kontrolujący czas wyświetlania ikony sukcesu/porażki</summary>
    sf::Clock iconTimer;
    /// <summary>Informacja czy cel był wrogi (wpływa na kolor/typ ikony)</summary>
    bool wrogi;
};