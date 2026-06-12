#include <SFML/Config.hpp>
#include "Assets.h"
#include <filesystem>
#include <fstream>
#include <iostream>


namespace fss = std::filesystem;


bool Assets::loadAssets()
{
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
