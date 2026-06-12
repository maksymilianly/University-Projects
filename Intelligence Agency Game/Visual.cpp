#include "Visual.h"

#include "Assets.h"
#include "Config.h"
#include "GameState.h"

#include <string>
#include <algorithm>


Visual::Visual(Assets& assets, Config& config, const std::string& prefix) {
    {
        for (auto const& [name, data] : config.spritesData) {

            if (name.find(prefix) == 0) {
                if (assets.textures.count(name) == 0) continue;

                sf::Sprite nowySprite(assets.textures.at(name));

                nowySprite.setPosition(data.position);
                nowySprite.setScale(data.scale);

                sf::Vector2u rozmiar = assets.textures.at(name).getSize();
                nowySprite.setOrigin({ rozmiar.x * data.origin.x, rozmiar.y * data.origin.y });

                sprites.insert({ name, nowySprite });

                if (data.layer != -1) {
                    orderedSprites.push_back({ data.layer, name });
                }
            }
        }

        std::sort(orderedSprites.begin(), orderedSprites.end(),
            [](const std::pair<int, std::string>& a, const std::pair<int, std::string>& b) {
                return a.first < b.first;
            });
    }
}

void Visual::draw(sf::RenderWindow& window) {
    for (const auto& os : orderedSprites) {
        window.draw(sprites.at(os.second));
    }
}