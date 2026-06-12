#pragma once
#include <string>

enum class Country
{
	cz,
	fr,
	gb,
	it,
	leftgermany,
	rightgermany,
	pl,
	ussr
};

inline std::string countryToString(Country c) {
    switch (c) {
    case Country::cz:  return "cz";
    case Country::ussr: return "ussr";
    case Country::fr: return "fr";
    case Country::gb: return "gb";
    case Country::it: return "it";
    case Country::leftgermany: return "leftgermany";
    case Country::rightgermany: return "rightgermany";
    case Country::pl: return "pl";

    default: return "-";
    }
}