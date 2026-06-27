#pragma once
#include <string>
#include <vector>

/// <summary>
/// Klasa pomocnicza zawierająca logikę odpowiedzialną za generowanie misji
/// oraz przetwarzanie danych (np. miast) niezbędnych do tworzenia nowych zadań
/// </summary>
class MisjaLogic {
public:
    /// <summary>
    /// Losuje nazwę miasta z podanego kontenera
    /// </summary>
    /// <param name="miasta">Wektor dostępnych nazw miast</param>
    /// <returns>Losowo wybrana nazwa miasta</returns>
    std::string randomMiasto(std::vector<std::string> miasta);

    /// <summary>
    /// Generuje nową misję na podstawie dostarczonych danych surowych
    /// </summary>
    /// <param name="dane">Wektor danych wejściowych</param>
    void genMisja(std::vector<int>& dane);
};