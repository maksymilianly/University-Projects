#pragma once
#include <memory>
#include "UIInfoPanel.h"
#include "EventData.h"
#include "UIButton.h"


struct Assets;

class Event
{
private:
	std::unique_ptr<UIInfoPanel> pop_out;
	bool active_pop_out;
public:
	Event(Assets& assets);

	void setEvent(const EventData& data);
	bool is_active() { return active_pop_out; }
	void set_active(bool val) { active_pop_out = val; }

	void drawEvent(sf::RenderWindow& window);
	bool obsluzKlikniecie(const sf::Event& _event, const sf::Vector2f& mousePos);
};