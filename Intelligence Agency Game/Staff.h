#pragma once
#include <string>
#include <vector>
#include <map>

/// <summary>
/// Specjalizacja agenta, określająca jego główny atut
/// </summary>
enum class Specjalizacja { Brak, Zabojstwo, Kradziez, Wywiad };
std::string specjalizacjaToString(Specjalizacja spec);

/// <summary>
/// Obszar działań grupy (np. rodzaj szyfrowanej komunikacji)
/// </summary>
enum class Obszar { Brak, Telegraficzny, Glosowy, Tekstowy };
std::string obszarToString(Obszar obs);
std::string obszarToSpecjalizacja(Obszar obs);

/// <summary>
/// Klasa bazowa dla wszystkich pracowników sztabu (Agentów oraz Grup)
/// Przechowuje wspólne dane dla każdego pracownika
/// </summary>
class Staff {
protected:
    std::string nickname;
    float payment = 0.0f;
    bool zajety = false;
    int exp = 0;

public:
    /// <summary>Inicjalizuje pracownika z podanym pseudonimem i identyfikatorem</summary>
    Staff(const std::string& _nickname, std::string _id);
    virtual ~Staff() = default;

    std::string getNickname() const { return nickname; }
    float getPayment() const { return payment; }
    void setZajety(bool zaj) { zajety = zaj; }
    bool getZajety() const { return zajety; }
    int getExp() const { return exp; }
    void addExp(int _exp) { exp += _exp; }
    void setExp(int _exp) { exp = _exp; }
    void setPayment(float pay) { payment = pay; }

    /// <summary>Sprawdza, czy obiekt jest agentem. Używane do rozróżniania typów pracownika</summary>
    virtual bool isAgent() const { return true; }

    /// <summary>Zwraca sformatowany ciąg znaków do wyświetlenia w sklepie (UI)</summary>
    virtual std::string shopInfo() const;
    /// <summary>Zwraca pełne dane o pracowniku w formie czytelnego tekstu</summary>
    virtual std::string zwrocDane() const;
    /// <summary>Zwraca status zajętości pracownika jako tekst (np. "Zajęty"/"Wolny")</summary>
    virtual std::string getZajetyString() const;
};

/// <summary>
/// Klasa reprezentująca agenta specjalnego. Posiada specjalizację oraz unikalne statystyki
/// </summary>
class Agent : public Staff {
private:
    Specjalizacja specjalizacja;
    int mnoznikMisji;
    std::map<std::string, int> statystyki;
    std::vector<std::string> unikalneCechy;

public:
    /// <summary>Tworzy nowego agenta z określonym mnożnikiem sukcesu misji</summary>
    Agent(const std::string& _nickname, Specjalizacja _spec, int _mnoznik);

    /// <summary>Ustawia wartość konkretnej statystyki</summary>
    void ustawStatystyke(const std::string& nazwa, int wartosc);
    /// <summary>Dodaje cechę</summary>
    void dodajCeche(const std::string& cecha);
    /// <summary>Zwraca sumę wszystkich punktów statystyk agenta</summary>
    int getSumaPoints() const;

    /// <summary>Zwraca dane agenta sformatowane pod UI</summary>
    std::string zwrocDane() const override;
    virtual bool isAgent() const override { return true; }
};

/// <summary>
/// Klasa reprezentująca grupę deszyfrujacą
/// </summary>
class Grupa : public Staff {
private:
    Obszar obszar;
    int mnoznikObszaru;
    std::map<std::string, int> statystyki;
    std::vector<std::string> unikalneCechy;

public:
    /// <summary>Tworzy nową grupę przypisaną do konkretnego obszaru</summary>
    Grupa(const std::string& _nickname, Obszar _obszar, int _mnoznik);

    /// <summary>Ustawia wartość konkretnej statystyki grupy</summary>
    void ustawStatystyke(const std::string& nazwa, int wartosc);
    /// <summary>Dodaje unikalną cechę grupy</summary>
    void dodajCeche(const std::string& cecha);
    /// <summary>Zwraca sumę punktów statystyk grupy</summary>
    int getSumaPoints() const;

    /// <summary>aktualizuje wszystkie umiejętności grupy o podaną wartość.</summary>
    /// <param name="val">Wartość do dodania do każdej statystyki</param>
    void setSkills(int val);

    /// <summary>Zwraca dane grupy sformatowane pod UI</summary>
    std::string zwrocDane() const override;
    virtual bool isAgent() const override { return false; }

    /// <summary>Pobiera wartość konkretnej statystyki</summary>
    int getStat(std::string stat) const { return statystyki.at(stat); }
    /// <summary>Zwraca nazwę obszaru działań grupy jako string</summary>
    std::string getObszar() const { return obszarToSpecjalizacja(obszar); }
};