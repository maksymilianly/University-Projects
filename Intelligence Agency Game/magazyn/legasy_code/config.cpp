#include "Config.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

namespace fss = std::filesystem;

bool Config::loadConfig()
{
	for (const auto& entry : fss::directory_iterator("data"))
	{
		if (entry.path().stem().string() == "config" && entry.path().extension() == ".txt")
		{
			std::ifstream konfig(entry.path().string());
			if (!konfig.is_open()) {
				std::cout << "Blad: Nie mozna otworzyc pliku: " << entry.path().string() << std::endl;
				return false;
			}
			std::string liniaPomocnicza;
            while (std::getline(konfig, liniaPomocnicza))
            {
                if (liniaPomocnicza.empty() || liniaPomocnicza[0] == '#') {
                    continue;
                }

                std::stringstream ss(liniaPomocnicza);
                std::string typ;
                ss >> typ;

                if (typ == "SPRITE")
                {
                    std::string nazwa;
                    float posX, posY, scaleX, scaleY, originX, originY;
                    int layer = 0;
                    ss >> nazwa >> posX >> posY >> scaleX >> scaleY >> originX >> originY;
                    spriteCoords[nazwa] = { posX,posY };
                    spriteOrigin[nazwa] = { originX,originY };
                    spriteScale[nazwa] = { scaleX,scaleY };

                    if (ss >> layer) {
                        spriteLayers[nazwa] = layer;
                    }
                    else {
                        spriteLayers[nazwa] = 0;
                    }

                }
                else if (typ == "LOGIC")
                {
                    std::string nazwa;
                    float wartosc;
                    ss >> nazwa >> wartosc;
                    logicalData[nazwa] = wartosc;
                }
            }
		}
        if (entry.path().stem().string() == "agenci" && entry.path().extension() == ".txt")
        {
            std::ifstream wej(entry.path().string());
            if (!wej.is_open()) {
                std::cout << "Blad: Nie mozna otworzyc pliku: " << entry.path().string() << std::endl;
                return false;
            }
            std::string liniaPomocnicza;
            while (getline(wej, liniaPomocnicza)) {
                if (!liniaPomocnicza.empty())
                {
                    agentNames.push_back(liniaPomocnicza);
                }
            }
        }
        if (entry.path().stem().string() == "grupy" && entry.path().extension() == ".txt")
        {
            std::ifstream wej(entry.path().string());
            if (!wej.is_open()) {
                std::cout << "Blad: Nie mozna otworzyc pliku: " << entry.path().string() << std::endl;
                return false;
            }
            std::string liniaPomocnicza;
            while (getline(wej, liniaPomocnicza)) {
                if (!liniaPomocnicza.empty()) {
                    groupNames.push_back(liniaPomocnicza);
                }
            }
        }

        if (entry.path().stem().string() == "cities" && entry.path().extension() == ".txt")
        {
            std::ifstream miasta(entry.path().string());
            if (!miasta.is_open()) {
                std::cout << "Blad: Nie mozna otworzyc pliku: " << entry.path().string() << std::endl;
                return false;
            }
            std::string liniaPomocnicza;
            std::string identifier = "";
            while (std::getline(miasta, liniaPomocnicza))
            {
                if (liniaPomocnicza.empty() || liniaPomocnicza[0] == '#') {
                    continue;
                }

                std::stringstream ss(liniaPomocnicza);
                std::string nazwa;
                float x, y;
                ss >> nazwa;
                if (ss >> x >> y) //znaczy ze nie indetifier a miasto
                {
                    citiesCoords[identifier][nazwa] = { {x, y}, 0 };
                }
                else
                {
                    identifier = nazwa;
                }
            }
        }
	}

    return true;
}

