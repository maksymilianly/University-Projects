#pragma once

/// <summary>
/// Główny obszar nazw dla stałych i narzędzi matematycznych wykorzystywanych w różnych systemach gry
/// </summary>
namespace Math {

    /// <summary>
    /// Obszar nazw zawierający stałe matematyczne specyficzne dla systemu radaru
    /// </summary>
    namespace Radar {
        /// <summary>Stała matematyczna Pi, używana do obliczeń kątów, rotacji i funkcji trygonometrycznych</summary>
        constexpr float PI = 3.14159f;

        /// <summary>
        /// Współczynnik zaniku sygnału 
        /// Określa tempo, w jakim sygnał traci swoją intensywność (siłę) w czasie
        /// </summary>
        constexpr float SIGNAL_DECAY = 0.8f;
    }
}