#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <vector>

import AssetsMod;
import ConfigMod;

/// <summary>
/// Klasa bazowa dla wszystkich komponentów wizualnych w grze
/// Zarządza kolekcją sprite'ów, przechowuje je w mapie dla szybkiego dostępu
/// oraz dba o kolejność rysowania (warstwy) dzięki wektorowi porządkującemu (nieaktualne)
/// </summary>
class Visual {
protected:
    /// <summary>Mapa przechowująca spritey przypisane do unikalnych identyfikatorów</summary>
    std::unordered_map<std::string, sf::Sprite> sprites;

    /// <summary>
    /// Wektor par (indeks warstwy, klucz sprite'a) określający kolejność renderowania
    /// Wyższy indeks oznacza rysowanie "później" (na wierzchu innych elementów).
    /// </summary>
    std::vector<std::pair<int, std::string>> orderedSprites;

public:
    /// <summary>
    /// Inicjalizuje komponent wizualny
    /// </summary>
    /// <param name="assets">Referencja do menedżera zasobów (używana do pobierania tekstur)</param>
    /// <param name="config">Referencja do konfiguracji (używana do ustawień wizualnych)</param>
    /// <param name="prefix">Prefiks używany do ładowania odpowiedniego zestawu zasobów dla tego komponentu</param>
    Visual(Assets& assets, Config& config, const std::string& prefix);

    /// <summary>Wirtualny destruktor gwarantujący poprawne usuwanie obiektów klas pochodnych</summary>
    virtual ~Visual() = default;

    /// <summary>
    /// Rysuje wszystkie spritey w oknie, zachowując kolejność zdefiniowaną w orderedSprites
    /// </summary>
    /// <param name="window">Referencja do okna renderującego SFML</param>
    virtual void draw(sf::RenderWindow& window);
};