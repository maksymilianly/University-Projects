#pragma once
#include <vector>
#include "Staff.h" 
#include "EventData.h"
#include "CountriesEnums.h"

struct DaneSzyfru {
    int poziomTrudnosci = 0;
    int jakiePanstwo = 0;
    int czasDofail = 0;
    int efektywnyHakowanie = 0;
    int efektywnyKryptoanaliza = 0;
    int efektywnyNasluch = 0;
};

enum class SzyfrState
{
    InProgress,
    Completed,
    Failed,
    Idle
};

struct GroupReport
{
    std::string nickname;
    int earned_exp;
    int earned_skills;

    std::string convert_to_string() const 
    {
        return "Otrzymano: \n" + nickname
            + "\n" + "exp: +" + std::to_string(earned_exp) + "\n"
            + "skills: +" + std::to_string(earned_skills) + "\n";
    }
};

struct SztabReport : public EventData
{
    int reward;
    std::string cnt_id;
    std::vector<GroupReport> sztab_report;

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
    void setSkils(int _efektywnyHakowanie, int _efektywnyKryptoanaliza, int _efektywnyNasluch);
    DaneSzyfru getDane() const
    {
        return  szyfrDane;
    }
    void setDane(const DaneSzyfru& dane) {
        szyfrDane = dane;
    }

    SzyfrState update(float dt,bool czynastole);
    bool checkFail() const;
	void calculate_progress(const std::vector<Grupa*>& grupy);
    SztabReport calculate_bonuses(const std::vector<Grupa*>& grupy);
	int jakiePanstwo() const { return szyfrDane.jakiePanstwo; }
    void resetPostep();

    std::string getHardest() const;

};