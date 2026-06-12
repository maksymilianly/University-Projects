#pragma once
#include <string>
#include <vector>
#include <map>

enum class Specjalizacja { Brak, Zabojstwo, Kradziez, Wywiad };
std::string specjalizacjaToString(Specjalizacja spec);

enum class Obszar { Brak, Telegraficzny, Glosowy, Tekstowy };
std::string obszarToString(Obszar obs);
std::string obszarToSpecjalizacja(Obszar obs);

class Staff {
protected:
    std::string nickname;
    float payment = 0.0f;
    bool zajety = false;
    int exp = 0;

public:
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
    virtual bool isAgent() const { return true; }

    virtual std::string shopInfo() const;
    virtual std::string zwrocDane() const;
    virtual std::string getZajetyString() const;
};

class Agent : public Staff {
private:
    Specjalizacja specjalizacja;
    int mnoznikMisji;
    std::map<std::string, int> statystyki;
    std::vector<std::string> unikalneCechy;

public:
    Agent(const std::string& _nickname, Specjalizacja _spec, int _mnoznik);

    void ustawStatystyke(const std::string& nazwa, int wartosc);
    void dodajCeche(const std::string& cecha);
    int getSumaPoints() const;
    std::string zwrocDane() const override;
    virtual bool isAgent() const override { return true; } // Jednolinijkowiec zostaje
};

class Grupa : public Staff {
private:
    Obszar obszar;
    int mnoznikObszaru;
    std::map<std::string, int> statystyki;
    std::vector<std::string> unikalneCechy;

public:
    Grupa(const std::string& _nickname, Obszar _obszar, int _mnoznik);

    void ustawStatystyke(const std::string& nazwa, int wartosc);
    void dodajCeche(const std::string& cecha);
    int getSumaPoints() const;
    void setSkills(int val)
    {
        for (auto& [name, data] : statystyki)
        {
            data += val;
        }
    }
    std::string zwrocDane() const override;
    virtual bool isAgent() const override { return false; } // Jednolinijkowiec zostaje

    int getStat(std::string stat) const { return statystyki.at(stat); }
    std::string getObszar() const { return obszarToSpecjalizacja(obszar); }
};