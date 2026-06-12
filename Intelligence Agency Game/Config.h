#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include "json.hpp"

struct SpriteConfig {
	sf::Vector2f position;
	sf::Vector2f scale;
	sf::Vector2f origin;
	int layer;
};


struct Config
{
	std::unordered_map<std::string, SpriteConfig> spritesData;
	std::unordered_map<std::string, float> logicalData;


	std::unordered_map<std::string, std::unordered_map<std::string,std::pair<sf::Vector2f,bool>>> citiesCoords;

	std::vector<std::string> agentNames;
	std::vector<std::string> groupNames;

	Config() = default;
	bool loadConfig();

	template <typename T>
	void loadIn(const std::string& data, T& variable, T def) {
		auto it = logicalData.find(data);
		variable = (it != logicalData.end()) ? static_cast<T>(it->second) : def;
	}

};
