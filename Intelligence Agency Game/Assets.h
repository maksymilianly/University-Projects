#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>


struct Assets {
    std::unordered_map<std::string, sf::Texture> textures;
    sf::Font mainFont;


    Assets() = default;
    bool loadAssets();

};