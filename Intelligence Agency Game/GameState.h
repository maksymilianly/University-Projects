#pragma once
#include <vector>
#include <queue>
#include <memory>
#include "ProcesDeszyfrowania.h"
#include "Staff.h"
#include "Stol.h"
#include "Misja.h"
#include "CountriesEnums.h"


struct SektorKadr
{
    std::vector<std::unique_ptr<Staff>> pracownicy; //kontener pracownikow(ktorych mamy w posiadaniu)
    std::vector<std::unique_ptr<Staff>> rynekPracy; //kontener prawocnikow ktorych mozemy kupic w sklepie
};

struct SektorZadan
{
    std::vector<int> transakcjeSygnalowe;//to raczej do nowego mediatora gamescreen
    std::vector<ProcesDeszyfrowania> aktywnaDeszyfracja; //w przyszlosci transakcje szyfrow zdeszyfrowanych(potrzebne m.in dla generacji misji)

	std::queue<int> missjeDoWygenerowania; //to raczej do nowego mediatora gamescreen

    std::vector<Misja> aktywneMisje; //kontener misji
};

struct SektorSprite
{
    std::vector<Stol> stoly;
};

class GameState
{
private:
    SektorKadr staff;
    SektorZadan zadania;
    SektorSprite sprites;

    bool UIrefreshStaff = false;
    bool UIrefreshMission = false;

    std::queue<SztabReport> sztab_reports_queue;

    int bank = 100000;



    int wybranyPracownik = -1;

public:
    void requestRefreshStaff() { UIrefreshStaff = true; }
    bool shouldRefreshStaff() const { return UIrefreshStaff; }
    void clearRefreshStaff() { UIrefreshStaff = false; }

    void requestRefreshMission() { UIrefreshMission = true; }
    bool shouldRefreshMission() const { return UIrefreshMission; }
    void clearRefreshMission() { UIrefreshMission = false; }

    void addReport(const SztabReport& report)
    {
        sztab_reports_queue.push(report);
    }

    bool sztab_queue_has_reports() const
    {
        return !sztab_reports_queue.empty();
    }

    const SztabReport take_out_sztab_report()
    {
        SztabReport fifo_report = sztab_reports_queue.front();
        sztab_reports_queue.pop();
        return fifo_report;
    }


    void dodajDane(int t);
    const std::vector<int>& podgladSygnalow() const { return zadania.transakcjeSygnalowe; }
    /*void dodajDane(const std::vector<Szyfr>& noweTransakcje) {
       zadania.transakcjeSzyfrowe.insert(zadania.transakcjeSzyfrowe.end(),noweTransakcje.begin(),noweTransakcje.end());
   }*/

    void setWybranyPracownik(int index) { wybranyPracownik = index; }
    int getWybranyPracownik() const { return wybranyPracownik; }
    void resetWybranyPracownik() { wybranyPracownik = -1; }

    void dodajPracownika(std::unique_ptr<Staff> nowyPracownik);

    void sortWorkers();

    Staff* pobierzOferte(int ktory) const;

    const std::vector<std::unique_ptr<Staff>>& getPracownicy() const {
        return staff.pracownicy;
    }

    Staff* getPracownik(int index) const {
        if (index >= 0 && index < staff.pracownicy.size()) {
            return staff.pracownicy[index].get();
        }
        return nullptr;
	}

    std::vector<Stol>& getStoly() {
        return sprites.stoly;
    }
    void dodajStol(Stol&& nowy);
    void setStolXY(const sf::Vector2f& pos, int idx);

    void dodajOferte(std::unique_ptr<Staff> nowaOferta);

    std::unique_ptr<Staff> wyjmijOferte(int index);

    const std::vector<std::unique_ptr<Staff>>& getRynekPracy() const {
        return staff.rynekPracy;
    }

    void dodajAktywnySzyfr(const ProcesDeszyfrowania& nowySzyfr);

    void usunSzyfr(int index) {
        if (index >= 0 && index < zadania.aktywnaDeszyfracja.size()) {
            zadania.aktywnaDeszyfracja.erase(zadania.aktywnaDeszyfracja.begin() + index);
        }
	}


    std::vector<ProcesDeszyfrowania>& getAktywneSzyfry() {
        return zadania.aktywnaDeszyfracja;
    }
    const std::vector<ProcesDeszyfrowania>& getAktywnySzyfry(int i) const {
        return zadania.aktywnaDeszyfracja;
    }

    std::unique_ptr<Staff> wyjmijPracownika(int index);

    //void dodajProces(ProcesDeszyfrowania* nowy) { zadania.aktywnaDeszyfracja.push_back(nowy); }
    //std::vector<ProcesDeszyfrowania*>& getProcesy() { return zadania.aktywnaDeszyfracja; }

    int getBank()const& { return bank; }
    void setBank(int _bank) { bank = _bank; }
    void addBank(int amount) { bank += amount; }
    bool checkMoney(int amount) { return (bank >= amount); }

	void wpiszMisjeDoWygenerowania(int dane) 
    {
        zadania.missjeDoWygenerowania.push(dane);
    }
	std::queue<int>& getMisjeDoWygenerowania() { return zadania.missjeDoWygenerowania; }
    void addMisja(std::string miasto, Country kraj, sf::Vector2f pozycja);

	std::vector<Misja>& getAktywneMisje() { return zadania.aktywneMisje;}

    void cleanS();
    //void cleanM();




};