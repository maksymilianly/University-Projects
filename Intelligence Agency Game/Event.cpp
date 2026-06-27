#include "Event.h"

//#include "Assets.h"

import AssetsMod;


Event::Event(Assets& assets)
{
	active_pop_out = false;
	pop_out = std::make_unique<UIInfoPanel>(sf::Sprite(assets.textures.at("ui_info_panel")),assets.mainFont,
		sf::Sprite(assets.textures.at("radar_checkmark")), [this]() {this->set_active(false); });
}

void Event::setEvent(const EventData& data)
{
	std::string event_data = data.convert_to_string();
	pop_out->refreshData(event_data, { 1920.0f / 4.0f,1080.0f / 4.0f });
}

void Event::drawEvent(sf::RenderWindow& window)
{
	pop_out->draw(window);
	pop_out->draw_additions(window);
}

bool Event::obsluzKlikniecie(const sf::Event& _event, const sf::Vector2f& mousePos)
{
	if (pop_out->obsluzKlikniecie(_event, mousePos))
	{
		return true;
	}
	return false;
}
