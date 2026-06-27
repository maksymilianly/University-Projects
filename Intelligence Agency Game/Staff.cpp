#include "Staff.h"

std::string specjalizacjaToString(Specjalizacja spec) {
    switch (spec) {
    case Specjalizacja::Zabojstwo: return "Zabojstwo";
    case Specjalizacja::Kradziez: return "Kradziez";
    case Specjalizacja::Wywiad: return "Wywiad";
    default: return "Brak";
    }
}

std::string obszarToString(Obszar obs) {
    switch (obs) {
    case Obszar::Telegraficzny: return "Deszyfrowanie Telegraficzne";
    case Obszar::Glosowy: return "Deszyfrowanie Radiowe";
    case Obszar::Tekstowy: return "Deszyfrowanie Tekstowe";
    default: return "Brak";
    }
}

std::string obszarToSpecjalizacja(Obszar obs) {
    switch (obs) {
    case Obszar::Telegraficzny: return "Inzyneria";
    case Obszar::Glosowy: return "Nasluch";
    case Obszar::Tekstowy: return "Kryptoanaliza";
    default: return "Brak";
    }
}

Staff::Staff(const std::string& _nickname, std::string _id) : nickname(_nickname) {}

std::string Staff::shopInfo() const {
    return nickname + "\nCena: $" + std::to_string((int)payment);
}

std::string Staff::zwrocDane() const {
    return "Doswiadczenie: " + std::to_string(exp);
}

std::string Staff::getZajetyString() const {
    return zajety ? "Zajety" : "Wolny";
}

Agent::Agent(const std::string& _nickname, Specjalizacja _spec, int _mnoznik)
    : Staff(_nickname, "A"), specjalizacja(_spec), mnoznikMisji(_mnoznik)
{
    statystyki["Charisma"] = 0;
    statystyki["Aim"] = 0;
    statystyki["Agility"] = 0;
}

void Agent::ustawStatystyke(const std::string& nazwa, int wartosc) {
    statystyki[nazwa] = wartosc;
}

void Agent::dodajCeche(const std::string& cecha) {
    unikalneCechy.push_back(cecha);
}

int Agent::getSumaPoints() const {
    int suma = 0;
    for (const auto& para : statystyki) {
        suma += para.second;
    }
    return suma;
}

std::string Agent::zwrocDane() const {
    std::string tempText = "";
    tempText += Staff::zwrocDane();
    for (const auto& [name, points] : statystyki) {
        tempText += "\n";
        tempText += name;
        tempText += " ";
        tempText += std::to_string(points);
    }
    tempText += "\n";
    tempText += specjalizacjaToString(specjalizacja);

    return tempText;
}

Grupa::Grupa(const std::string& _nickname, Obszar _obszar, int _mnoznik)
    : Staff(_nickname, "G"), obszar(_obszar), mnoznikObszaru(_mnoznik)
{
    statystyki["Inzyneria"] = 0;
    statystyki["Kryptoanaliza"] = 0;
    statystyki["Nasluch"] = 0;
}

void Grupa::ustawStatystyke(const std::string& nazwa, int wartosc) {
    statystyki[nazwa] = wartosc;
}

void Grupa::dodajCeche(const std::string& cecha) {
    unikalneCechy.push_back(cecha);
}

int Grupa::getSumaPoints() const {
    int suma = 0;
    for (const auto& para : statystyki) {
        suma += para.second;
    }
    return suma;
}

std::string Grupa::zwrocDane() const {
    std::string tempText = "";
    tempText += Staff::zwrocDane();
    for (const auto& [name, points] : statystyki) {
        tempText += "\n";
        tempText += name;
        tempText += " ";
        tempText += std::to_string(points);
    }
    tempText += "\n";
    tempText += obszarToString(obszar);

    return tempText;
}

void Grupa::setSkills(int val)
{
    return;
}