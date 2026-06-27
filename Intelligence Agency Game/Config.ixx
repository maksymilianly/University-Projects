module;
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include "json.hpp"

export module ConfigMod;

namespace fss = std::filesystem;
using json = nlohmann::json;

/// <summary>
/// Struktura przechowująca parametry transformacji i wyświetlania dla pojedynczego spritea.
/// </summary>
export struct SpriteConfig {
    sf::Vector2f position;
    sf::Vector2f scale;
    sf::Vector2f origin;
    int layer;
};

/// <summary>
/// Główny menedżer konfiguracji. Odpowiada za wczytywanie i przechowywanie danych z plików JSON oraz plików tekstowych.
/// </summary>
export struct Config {

    /// <summary>Mapa przechowująca konfigurację spriteów. Kluczem jest nazwa spritea.</summary>
    std::unordered_map<std::string, SpriteConfig> spritesData;

    /// <summary>Mapa przechowująca zmienne logiczne wczytane z konfiguracji</summary>
    std::unordered_map<std::string, float> logicalData;

    /// <summary>Przechowuje współrzędne miast pogrupowane według identyfikatorów państw</summary>
    std::unordered_map<std::string, std::unordered_map<std::string, std::pair<sf::Vector2f, bool>>> citiesCoords;

    /// <summary>Pula dostępnych imion i pseudonimów dla agentów</summary>
    std::vector<std::string> agentNames;

    /// <summary>Pula dostępnych nazw dla grup deszyfrujących</summary>
    std::vector<std::string> groupNames;

    Config() = default;

    /// <summary>
    /// Pobiera wartość konfiguracyjną na podstawie podanego klucza. Jeśli klucz nie istnieje, przypisuje wartość domyślną
    /// </summary>
    /// <param name="data">Klucz wyszukiwanej wartości logicznej</param>
    /// <param name="variable">Referencja do zmiennej, do której zostanie przypisany wynik</param>
    /// <param name="def">Wartość domyślna, przypisywana w przypadku braku klucza</param>
    template <typename T>
    void loadIn(const std::string& data, T& variable, T def) {
        auto it = logicalData.find(data);
        variable = (it != logicalData.end()) ? static_cast<T>(it->second) : def;
    }

    /// <summary>
    /// Przeszukuje folder "data" i ładuje konfigurację z plików: config.json, agenci.txt, grupy.txt oraz cities.txt
    /// </summary>
    /// <returns>Zwraca true, jeśli pomyślnie załadowano wszystkie wymagane pliki bez błędów krytycznych</returns>
    bool loadConfig()
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
                    for (auto& [name, data] : j["sprites"].items())
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
                    if (ss >> x >> y)
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
};