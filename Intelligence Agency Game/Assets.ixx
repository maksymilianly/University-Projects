module;
#include <SFML/Graphics.hpp>
#include <SFML/Config.hpp>
#include <unordered_map>
#include <string>
#include <filesystem>
#include <fstream>
#include <iostream>

export module AssetsMod;

namespace fss = std::filesystem;

/// <summary>
/// Przechowuje i zarządza globalnymi zasobami gry, takimi jak tekstury i czcionki
/// </summary>
export struct Assets {

    /// <summary>Mapa przechowująca załadowane tekstury. Kluczem jest nazwa pliku (bez rozszerzenia)</summary>
    std::unordered_map<std::string, sf::Texture> textures;

    /// <summary>Główna czcionka wykorzystywana w interfejsie użytkownika</summary>
    sf::Font mainFont;

    Assets() = default;

    /// <summary>
    /// Ładuje wszystkie pliki .png z folderu "textures" do pamięci oraz wczytuje czcionkę "mainFont.ttf".
    /// </summary>
    /// <returns>Zwraca true po zakończeniu ładowania zasobów.</returns>
    bool loadAssets() {
        for (const auto& entry : fss::directory_iterator("textures")) {
            if (entry.path().extension() == ".png") {
                sf::Texture tempTexture;
                tempTexture.loadFromFile(entry.path().string());
                textures[entry.path().stem().string()] = tempTexture;
            }
        }
        if (!mainFont.openFromFile("mainFont.ttf")) {
            std::cerr << "Blad ladowania czcionki!" << std::endl;
        }

        return true;
    }
};