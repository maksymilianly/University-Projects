#pragma once
#include <string>

struct EventData
{
	virtual std::string convert_to_string() const = 0;
	virtual ~EventData() = default;
};