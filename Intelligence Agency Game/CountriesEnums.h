#pragma once
#include <string>

/// <summary>
/// Reprezentuje dostępne państwa na mapie świata w grze.
/// </summary>
enum class Country {
    /// <summary>Czechosłowacja</summary>
    cz,
    /// <summary>Francja</summary>
    fr,
    /// <summary>Wielka Brytania</summary>
    gb,
    /// <summary>Włochy</summary>
    it,
    /// <summary>RFN (Niemcy Zachodnie)</summary>
    leftgermany,
    /// <summary>NRD (Niemcy Wschodnie)</summary>
    rightgermany,
    /// <summary>Polska</summary>
    pl,
    /// <summary>Związek Radziecki (ZSRR)</summary>
    ussr
};

/// <summary>
/// Konwertuje wartość wyliczeniową Country na odpowiadający jej łańcuch znaków (std::string)
/// Wykorzystywane głównie do dopasowywania nazw tekstur, kluczy w plikach JSON lub identyfikatorów na mapie
/// </summary>
/// <param name="c">Wartość państwa do przekonwertowania.</param>
/// <returns>Skrócony kod państwa w formie tekstowej (np. "pl", "ussr") lub "-" w przypadku niezdefiniowanej wartości</returns>
inline std::string countryToString(Country c) {
    switch (c) {
    case Country::cz:           return "cz";
    case Country::ussr:         return "ussr";
    case Country::fr:           return "fr";
    case Country::gb:           return "gb";
    case Country::it:           return "it";
    case Country::leftgermany:  return "leftgermany";
    case Country::rightgermany: return "rightgermany";
    case Country::pl:           return "pl";

    default: return "-";
    }
}