#include "ProcesDeszyfrowania.h"
#include <cmath>
#include <algorithm>
#include <random>   


ProcesDeszyfrowania::ProcesDeszyfrowania()
{
    static std::random_device rd;
    static std::mt19937 engine(rd());

    std::uniform_int_distribution<int> lvl(1, 10);
    std::uniform_int_distribution<int> cnt(0, 7);
    std::uniform_int_distribution<int> skills(100, 100);

    szyfrDane.poziomTrudnosci = lvl(engine);
    szyfrDane.jakiePanstwo = cnt(engine);

    float mnoznikPoziomu = szyfrDane.poziomTrudnosci / 10.0f;

    szyfrDane.efektywnyHakowanie = skills(engine)* mnoznikPoziomu;
    szyfrDane.efektywnyKryptoanaliza = skills(engine)* mnoznikPoziomu;
    szyfrDane.efektywnyNasluch = skills(engine)* mnoznikPoziomu;

    float wplywTrudnosci = std::max(1.0f, static_cast<float>(szyfrDane.poziomTrudnosci));
    float bazaCzasu = std::sqrt(wplywTrudnosci) * 12.0f ; 

    float najslabszySkill = std::min({
        static_cast<float>(szyfrDane.efektywnyHakowanie),
        static_cast<float>(szyfrDane.efektywnyKryptoanaliza),
        static_cast<float>(szyfrDane.efektywnyNasluch)
        });

    float sredniaSkilli = (szyfrDane.efektywnyHakowanie + szyfrDane.efektywnyKryptoanaliza + szyfrDane.efektywnyNasluch) / 3.0f;
    float mocZespolu = (sredniaSkilli * 0.7f) + (najslabszySkill * 0.3f);
    float bonusSkilli = std::sqrt(mocZespolu) * 15.0f;


    std::uniform_real_distribution<float> losowyWspolczynnik(0.9f, 1.1f);

    float ostatecznyCzas = (bazaCzasu + bonusSkilli) * losowyWspolczynnik(engine);
    szyfrDane.czasDofail = std::clamp(static_cast<int>(ostatecznyCzas), 10, 600);
}

bool ProcesDeszyfrowania::checkFail() const {
    return uplynietyCzas >= szyfrDane.czasDofail;
}

SzyfrState ProcesDeszyfrowania::update(float dt,bool czynastole)
{
    uplynietyCzas += dt;

    if (checkFail())
    {
        return SzyfrState::Failed;
    }

    if (czynastole)
    {
        czasNaStole += dt;
        aktualnyProgres += predkoscPostepu * dt;

        if (aktualnyProgres >= 100.0f)
        {
            aktualnyProgres = 100.0f;
            return SzyfrState::Completed;
        }
        return SzyfrState::InProgress;
    }
    else 
    {
        return SzyfrState::Idle;
	}
}

void ProcesDeszyfrowania::calculate_progress(const std::vector<Grupa*>& grupy)
{
    predkoscPostepu = 0.0f;
    if (grupy.empty()) return;

    const float bazowaPredkosc = 3.5f;

    const float mnoznikTrudnosci = 1.0f + (static_cast<float>(szyfrDane.poziomTrudnosci) * 0.5f);

    float mnoznikWydajnosci = 1.0f;
    std::string hardestSkill = getHardest();

    std::string prevSpec = "";
    for (const auto* grupa : grupy)
    {
        //zrobic sorta zeby nie tracila sie 
        if (grupa != nullptr && grupa->getZajety())
        {
            float grHakowanie = static_cast<float>(grupa->getStat("Inzyneria")); 
            float grKrypto = static_cast<float>(grupa->getStat("Kryptoanaliza"));
            float grNasluch = static_cast<float>(grupa->getStat("Nasluch"));
            std::string grSpec = grupa->getObszar();

            constexpr float wplyw_statystyki = 0.2f;

            float efektHakowanie = 1.0f + ((grHakowanie - szyfrDane.efektywnyHakowanie) * wplyw_statystyki);
            float efektKrypto = 1.0f + ((grKrypto - szyfrDane.efektywnyKryptoanaliza) * wplyw_statystyki);
            float efektNasluch = 1.0f + ((grNasluch - szyfrDane.efektywnyNasluch) * wplyw_statystyki);

            efektHakowanie = std::max(0.2f, efektHakowanie);
            efektKrypto = std::max(0.2f, efektKrypto);
            efektNasluch = std::max(0.2f, efektNasluch);

            constexpr float wplyw_expa = 0.02f;
            float bonusZaExp = 1.0f + (static_cast<float>(grupa->getExp()) * wplyw_expa);

            float dopalaczSynergii = 1.0f;
            if (grSpec == hardestSkill) {
                if(prevSpec == grSpec)
                dopalaczSynergii = 1.5f * 1.5f; 
            }

            float calkowitaWydajnoscGrupy = ((efektHakowanie + efektKrypto + efektNasluch) / 3.0f) * bonusZaExp * dopalaczSynergii;

            predkoscPostepu += (bazowaPredkosc * calkowitaWydajnoscGrupy / mnoznikTrudnosci) * mnoznikWydajnosci;

            mnoznikWydajnosci *= 0.6f;
            prevSpec = grSpec;
        }
    }
}

SztabReport ProcesDeszyfrowania::calculate_bonuses(const std::vector<Grupa*>& grupy)
{
    SztabReport raport;
    raport.cnt_id = countryToString(static_cast<Country>(szyfrDane.jakiePanstwo));

    int rewardBase = szyfrDane.poziomTrudnosci * 150;
    float timeMultiplier = 1.0f;

    if (czasNaStole > 0.0f && czasNaStole < szyfrDane.czasDofail) {
        timeMultiplier = 1.0f + 0.5f * (1.0f - (czasNaStole / szyfrDane.czasDofail));
    }

    raport.reward = static_cast<int>(rewardBase * timeMultiplier);

    int exp = szyfrDane.poziomTrudnosci * 0.6f;
    int skills = szyfrDane.poziomTrudnosci * 0.6f;

    for (Grupa* grupa : grupy)
    {
        if (grupa != nullptr)
        {
            GroupReport gReward;
            gReward.nickname = grupa->getNickname(); 
            gReward.earned_exp = exp;
            gReward.earned_skills = skills;

            grupa->addExp(exp);
            grupa->setSkills(skills);

            raport.sztab_report.push_back(gReward);
        }
    }

    return raport;

}

void ProcesDeszyfrowania::resetPostep() { predkoscPostepu = 0.0f; }

void ProcesDeszyfrowania::setSkils(int _efektywnyHakowanie, int _efektywnyKryptoanaliza, int _efektywnyNasluch)
{
    szyfrDane.efektywnyHakowanie = _efektywnyHakowanie;
    szyfrDane.efektywnyKryptoanaliza = _efektywnyKryptoanaliza;
    szyfrDane.efektywnyNasluch = _efektywnyNasluch;
}

std::string ProcesDeszyfrowania::getHardest() const
{
    int maksymalny = std::max({
        szyfrDane.efektywnyHakowanie,
        szyfrDane.efektywnyKryptoanaliza,
        szyfrDane.efektywnyNasluch
        });

    if (maksymalny == szyfrDane.efektywnyHakowanie) {
        return "Inzyneria";
    }
    else if (maksymalny == szyfrDane.efektywnyKryptoanaliza) {
        return "Kryptoanaliza";
    }
    else {
        return "Nasluch";
    }
}
