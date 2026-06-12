#include "RadarLogic.h"

#include "Config.h"
#include "GameState.h"
#include "Math.h"

#include <random>
#include <cstdint>
#include <vector>
#include <iostream>
#include <algorithm>


RadarLogic::RadarLogic(Config& config,GameState& state) 
{
    current_odbiornik_angle = 0.0f;
    current_projektor_angle = 0.0f;
    isRadarOn = false;
    isPoleOn = false;
    timer = 0.0f;

    config.loadIn("radar_radius", radar_radius, 0.0f);
    config.loadIn("radar_posX", radar_posX, 0.0f);
    config.loadIn("radar_posY", radar_posY, 0.0f);
    config.loadIn("radar_projektor_rotation", radar_projektor_rotation, 0.0f);
    config.loadIn("radar_odbiornik_rotation", radar_odbiornik_rotation, 0.0f);
    config.loadIn("radar_odbiornik_sector", radar_odbiornik_sector, 0.0f);
    config.loadIn("radar_friendly_payment", radar_friendly_payment, 0);
    config.loadIn("radar_hostile_payment", radar_hostile_payment, 0);
    config.loadIn("radar_max_signals", radar_max_signals,0);
    config.loadIn("radar_spawn_time", radar_spawn_time, 60.0f);
}

void RadarLogic::updateProjector(float dt)
{
    current_projektor_angle += radar_projektor_rotation * dt;
    if (current_projektor_angle >= 360.0f) {
        current_projektor_angle -= 360.0f;
    }
}

void RadarLogic::updateOdbiornik(bool goradol, float dt)
{
    if (goradol) { setOdbiornikAngle(-radar_odbiornik_rotation, dt); }
    else { setOdbiornikAngle(radar_odbiornik_rotation, dt); }

}

void RadarLogic::addSignal(float x, float y, float fAngle, float speed, float strength,int randomType, bool hostile)
{
    Signal s;
    s.x = x;
    s.y = y;
    s.flightAngle = fAngle;
    s.speed = speed;
    s.strength = strength;
    s.hostile = hostile;
    s.timeToLive = 0.0f;
    
    auto randomFloat = [](float min, float max) {
        return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX) / (max - min));
        };
    s.amplituda = randomFloat(10.0f, 45.0f);
    s.czestotliwosc = randomFloat(0.5f, 3.0f);
    s.modyfikator = randomFloat(1.0f, 2.5f);

    if (randomType % 10 < 3)
    {
        s.typ = TypSygnalu::Ship;
    }
    else
    {
		s.typ = TypSygnalu::Plane;
		s.speed < 1.5f ? (s.speed+=0.5f) *=  4.0f : s.speed *= 3.0f;
    }

    signals.push_back(s);
}

void RadarLogic::spawnRandomSignal(float dt) {
    if (signals.size() >= radar_max_signals)
    {
        return;
    }
    if (timer < radar_spawn_time)
    {
        timer += dt;
        return;
    }
    timer = 0.0;

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 100);
    std::uniform_int_distribution<int> type(1, 100);
    std::uniform_real_distribution<float> Celangle(0.f, 360.f);
    std::uniform_real_distribution<float> CelFlightAngle(-45.0f, 45.0f);
    std::uniform_real_distribution<float> speedDist(1.0f, 3.0f);
    std::uniform_real_distribution<float> spawnCords(radar_radius * 0.85f, radar_radius * 0.96f);
    float randomAngle = Celangle(gen);
    float randomFlightAngle = CelFlightAngle(gen);
    float randomSpeed = speedDist(gen);
    float randowSpawn = spawnCords(gen);
	int randomType = type(gen);

    float radianyAngle = randomAngle * (Math::Radar::PI / 180.f);
    float startX = radar_posX + (std::cos(radianyAngle) * randowSpawn);
    float startY = radar_posY + (std::sin(radianyAngle) * randowSpawn);

    float flightAngle = randomAngle + 180.0f + randomFlightAngle;
    int roll = dist(gen);
    if (roll > 50)
    {
        addSignal(startX, startY, flightAngle, randomSpeed, 0.0f,randomType, true);
    }
    else { addSignal(startX, startY, flightAngle, randomSpeed, 0.0f, randomType, false); }
}

void RadarLogic::updateSignals(float dt,sf::Vector2f& catcherPos,float& catcherRadius)
{
    std::erase_if(sukcesWylapania, [this](const SukcesWylapania& sw) {
        if (sw.iconTimer.getElapsedTime().asSeconds() > 1.0f)
        {
            if (!sw.wrogi)
            {
                transakcje.push_back(sw.sukcesOstatniegoWylapania ? radar_friendly_payment : -radar_friendly_payment);
            }
            else
            {

                transakcje.push_back(sw.sukcesOstatniegoWylapania ? radar_hostile_payment : -radar_hostile_payment);
            }
            return true;
        }
        return false;
        });

    std::erase_if(signals, [&,dt](Signal& s) {
        s.strength -= Math::Radar::SIGNAL_DECAY * dt;
		s.timeToLive += dt;
        float odchylenie = 0.0f;
        switch (s.newDirection) {
        case TypKierunku::none: 
            odchylenie = 0.0f;
            break;
        case TypKierunku::sin:
            odchylenie = s.amplituda * std::sin(s.timeToLive * s.czestotliwosc);
            break;
        case TypKierunku::cos:
            odchylenie = s.amplituda * std::cos(s.timeToLive * s.czestotliwosc);
            break;
        case TypKierunku::exp:
            odchylenie = std::exp(s.timeToLive * s.modyfikator);
            break;
        }

        float aktualnyKat = s.flightAngle + odchylenie;
        float radianyLotu = aktualnyKat * (Math::Radar::PI / 180.f);

        if (s.strength < 0.0f) { s.strength = 0.0f; }
        radianyLotu = s.flightAngle * (Math::Radar::PI / 180.f);
        s.x += s.speed * std::cos(radianyLotu) * dt;
        s.y += s.speed * std::sin(radianyLotu) * dt;

        float dx = s.x - radar_posX;
        float dy = s.y - radar_posY;
        float dystans = std::sqrt(dx * dx + dy * dy);

        if (dystans >= radar_radius) {
            sf::Vector2f pozycjaUcieczki = { s.x, s.y };
            bool fate = s.hostile;
            sukcesWylapania.push_back({ false, pozycjaUcieczki, sf::Clock(), fate });
            return true;
        }

        else if (isRadarOn && isPoleOn)
        {
            if (checkTrafienie(s,catcherPos,catcherRadius)) {
                bool fate = s.hostile;
                sukcesWylapania.push_back({ true, {s.x, s.y}, sf::Clock(),fate });
                return true;
            }
        }


        float katWzgledemSrodkaRad = std::atan2(dy, dx);
        float katWzgledemSrodkaStopnie = katWzgledemSrodkaRad * (180.0f / Math::Radar::PI);

        if (katWzgledemSrodkaStopnie < 0) katWzgledemSrodkaStopnie += 360.0f;

        float diff = std::abs(current_projektor_angle - katWzgledemSrodkaStopnie);
        if (diff > 180.0f) diff = 360.0f - diff;

        if (diff < 5.0f) {
            s.strength = 1.0f;
        }
        return false;
        });
}

bool RadarLogic::checkTrafienie(const Signal& signal,sf::Vector2f& catcherPos,float& catcherRadius)
{
    float dx = signal.x - catcherPos.x;
    float dy = signal.y - catcherPos.y;

    float distance = (std::sqrt(dx * dx + dy * dy));

    return distance < catcherRadius;

    /*float katWzgledemSrodkaRad = std::atan2(dy, dx);
    float katWzgledemSrodkaStopnie = katWzgledemSrodkaRad * (180.0f / Math::Radar::PI);

    float normalisedOdbiornik = std::fmod(current_odbiornik_angle, 360.0f);
    float normalisedSygnal = std::fmod(katWzgledemSrodkaStopnie, 360.0f);

    if (normalisedOdbiornik < 0) {
        normalisedOdbiornik += 360.0f;
    }
    if (normalisedSygnal < 0) {
        normalisedSygnal += 360.0f;
    }

    float diff = std::abs(normalisedSygnal - normalisedOdbiornik);
    if (diff > 180.0f) {
        diff = 360.0f - diff;
    }

    return diff < radar_odbiornik_sector;*/
}

void RadarLogic::nadpiszPos(float nr,sf::Vector2f pos)
{
    radar_posX = pos.x;
    radar_posY = pos.y;
    radar_radius = nr;
}

void RadarLogic::przemapujSygnaly(float skala,sf::Vector2f newPos)
{
    
    for (auto& s : signals)
    {
        float dx = s.x - radar_posX;
        float dy = s.y - radar_posY;

        s.x = newPos.x + (dx * skala);
        s.y = newPos.y + (dy * skala);


    }
}






