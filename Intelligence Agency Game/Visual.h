#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <vector>

struct Assets;
struct Config;

class Visual {
protected:
    std::unordered_map<std::string, sf::Sprite> sprites;
    std::vector<std::pair<int, std::string>> orderedSprites;
public:
    Visual(Assets& assets, Config& config, const std::string& prefix);

    virtual ~Visual() = default;
    virtual void draw(sf::RenderWindow& window);
};