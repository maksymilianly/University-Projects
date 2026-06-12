#include "Config.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

namespace fss = std::filesystem;
using json = nlohmann::json;

bool Config::loadConfig()
{
	for (const auto& entry : fss::directory_iterator("data"))
	{
		if (entry.path().stem().string() == "config" && entry.path().extension() == ".json")
		{
			std::ifstream konfig(entry.path().string());
			if (!konfig.is_open()) {
				std::cout << "Blad: Nie mozna otworzyc pliku: " << entry.path().string() << std::endl;
				return false;
			}

            json j;
            try {
                konfig >> j;
            }
            catch (json::parse_error& e)
            {
                std::cerr << "[ERROR] : " << entry.path().string() << " - " << e.what() << std::endl;
                return false;
            }

            if (j.contains("sprites"))
            {
                for (auto& [name,data] : j["sprites"].items())
                {
                    SpriteConfig sc;

                    sc.position.x = data["position"][0].get<float>();
                    sc.position.y = data["position"][1].get<float>();

                    sc.scale.x = data["scale"][0].get<float>();
                    sc.scale.y = data["scale"][1].get<float>();

                    sc.origin.x = data["origin"][0].get<float>();
                    sc.origin.y = data["origin"][1].get<float>();

                    sc.layer = data["layer"].get<int>();
                    spritesData[name] = sc;
                
                }
            }

            if (j.contains("logic")) {
                for (auto& [name, value] : j["logic"].items()) {
                    logicalData[name] = value.get<float>();
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

