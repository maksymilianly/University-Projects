#pragma once
#include <string>

/// <summary>
/// Interfejs bazowy dla danych reprezentujących zdarzenia w grze
/// Wszystkie klasy zdarzeń muszą dziedziczyć po tej strukturze i zaimplementować 
/// metodę serializacji do formatu tekstowego.
/// </summary>
struct EventData {
    /// <summary>
    /// Konwertuje dane zdarzenia na czytelny format tekstowy
    /// Jest to przydatne przy logowaniu zdarzeń do pliku, konsoli lub wyświetlaniu ich w oknie UI.
    /// </summary>
    /// <returns>Tekstowa reprezentacja danych zdarzenia</returns>
    virtual std::string convert_to_string() const = 0;

    /// <summary>
    /// Wirtualny destruktor
    /// </summary>
    virtual ~EventData() = default;
};