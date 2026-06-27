#pragma once
#include <vector>
#include <string>
#include "Staff.h" 
#include "EventData.h"
#include "CountriesEnums.h"

/// <summary>
/// Kontener danych określający parametry trudności i charakterystykę procesu deszyfrowania
/// </summary>
struct DaneSzyfru {
    int poziomTrudnosci = 0;
    int jakiePanstwo = 0;
    int czasDofail = 0;
    int efektywnyHakowanie = 0;
    int efektywnyKryptoanaliza = 0;
    int efektywnyNasluch = 0;
};

/// <summary>
/// Definiuje możliwe stany procesu deszyfrowania
/// </summary>
enum class SzyfrState {
    InProgress, ///< Proces w toku
    Completed,  ///< Proces zakończony sukcesem
    Failed,     ///< Proces zakończony niepowodzeniem (timeout lub błąd)
    Idle        ///< Proces oczekujący (np. nieprzypisany do stołu)
};

/// <summary>
/// Raport z pracy pojedynczej grupy deszyfrującej
/// </summary>
struct GroupReport {
    std::string nickname;
    int earned_exp;
    int earned_skills;

    /// <summary>Generuje czytelny opis podsumowania pracy grupy</summary>
    std::string convert_to_string() const
    {
        return "Otrzymano: \n" + nickname
            + "\n" + "exp: +" + std::to_string(earned_exp) + "\n"
            + "skills: +" + std::to_string(earned_skills) + "\n";
    }
};

/// <summary>
/// Raport końcowy dla całego procesu deszyfrowania, dziedziczący po EventData
/// </summary>
struct SztabReport : public EventData {
    int reward;
    std::string cnt_id;
    std::vector<GroupReport> sztab_report;

    /// <summary>Konwertuje raport sztabu na format tekstowy do wyświetlenia w UI</summary>
    std::string convert_to_string() const override
    {
        std::string tempString = "--- Ukonczono prace nad szyfrem\n ---\n";
        tempString += "Zdobyte fundusze: $" + std::to_string(reward) + "\n";

        tempString += "Szczegoly zespolow:\n";
        for (const auto& report : sztab_report) {
            tempString += report.convert_to_string();
        }

        return tempString;
    }
};

/// <summary>
/// Klasa zarządzająca logiką pojedynczego procesu deszyfrowania
/// Odpowiada za śledzenie postępu, obliczanie bonusów oraz obsługę stanów (sukces/porażka)
/// </summary>
class ProcesDeszyfrowania {
private:
    DaneSzyfru szyfrDane;

    float aktualnyProgres = 0.0f;
    float uplynietyCzas = 0.0f;
    float czasNaStole = 0.0f;

    float predkoscPostepu = 0.0f;

public:
    ProcesDeszyfrowania();
    ~ProcesDeszyfrowania() = default;

    float getCzas()const { return uplynietyCzas; };
    int getPoziom() const { return szyfrDane.poziomTrudnosci; }
    int getCzasDoFail()const { return szyfrDane.czasDofail; }
    float getProgres()const { return aktualnyProgres; }
    void setCzas(float plus) { uplynietyCzas += plus; }
    float getPredkoscPostepu()const { return predkoscPostepu; }

    /// <summary>Ustawia skuteczność poszczególnych umiejętności grupy w odniesieniu do tego szyfru</summary>
    void setSkils(int _efektywnyHakowanie, int _efektywnyKryptoanaliza, int _efektywnyNasluch);

    DaneSzyfru getDane() const { return szyfrDane; }
    void setDane(const DaneSzyfru& dane) { szyfrDane = dane; }

    /// <summary>
    /// Aktualizuje stan procesu w czasie
    /// </summary>
    /// <param name="dt">Czas klatki</param>
    /// <param name="czynastole">Czy proces jest aktualnie przypisany do aktywnego stołu</param>
    /// <returns>Aktualny stan szyfru (SzyfrState)</returns>
    SzyfrState update(float dt, bool czynastole);

    /// <summary>Sprawdza, czy proces przekroczył dopuszczalny czas</summary>
    bool checkFail() const;

    /// <summary>Oblicza postęp prac na podstawie umiejętności przypisanych grup</summary>
    /// <param name="grupy">Lista grup pracujących nad tym szyfrem</param>
    void calculate_progress(const std::vector<Grupa*>& grupy);

    /// <summary>Oblicza nagrody końcowe dla grup na podstawie ich wkładu</summary>
    SztabReport calculate_bonuses(const std::vector<Grupa*>& grupy);

    int jakiePanstwo() const { return szyfrDane.jakiePanstwo; }

    /// <summary>Zeruje progres i czas procesu</summary>
    void resetPostep();

    /// <summary>Zwraca opis najtrudniejszego aspektu deszyfrowanego szyfru</summary>
    std::string getHardest() const;
};