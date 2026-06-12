#include "GameState.h"

#include <iostream>
#include <algorithm>

void GameState::dodajDane(int t) {
    zadania.transakcjeSygnalowe.push_back(t);
}


void GameState::dodajPracownika(std::unique_ptr<Staff> nowyPracownik) {
    staff.pracownicy.push_back(std::move(nowyPracownik));
    requestRefreshStaff();
}


void GameState::sortWorkers() {
    std::stable_sort(staff.pracownicy.begin(), staff.pracownicy.end(),
        [](const std::unique_ptr<Staff>& a, const std::unique_ptr<Staff>& b) {
            return a->getZajety() < b->getZajety();
        });
}

Staff* GameState::pobierzOferte(int ktory) const
{
    if (ktory >= 0 && ktory < staff.rynekPracy.size()) {
        return staff.rynekPracy[ktory].get();
    }
    return nullptr;
}


void GameState::dodajStol(Stol&& nowy) { sprites.stoly.push_back(std::move(nowy)); }
void GameState::setStolXY(const sf::Vector2f& pos, int idx) { sprites.stoly[idx].setStolPos(pos); }

void GameState::dodajOferte(std::unique_ptr<Staff> nowaOferta) {
    staff.rynekPracy.push_back(std::move(nowaOferta));
}

std::unique_ptr<Staff> GameState::wyjmijOferte(int index) {
    if (index >= 0 && index < staff.rynekPracy.size()) {
        auto wyjety = std::move(staff.rynekPracy[index]);
        staff.rynekPracy.erase(staff.rynekPracy.begin() + index);
        return wyjety;
    }
    return {};
}

void GameState::dodajAktywnySzyfr(const ProcesDeszyfrowania& nowySzyfr) {
    auto miejsce = std::lower_bound(
        zadania.aktywnaDeszyfracja.begin(),
        zadania.aktywnaDeszyfracja.end(),
        nowySzyfr,
        [](const ProcesDeszyfrowania& a, const ProcesDeszyfrowania& b) {
            return a.getProgres() > b.getProgres();
        });

    zadania.aktywnaDeszyfracja.insert(miejsce, std::move(nowySzyfr));


}

std::unique_ptr<Staff> GameState::wyjmijPracownika(int index) {
    if (index >= 0 && index < staff.pracownicy.size()) {
        auto wyjety = std::move(staff.pracownicy[index]);
        staff.pracownicy.erase(staff.pracownicy.begin() + index);
        return wyjety;
    }
    return {};
}

void GameState::addMisja(std::string miasto, Country kraj, sf::Vector2f pozycja)
{
    Misja nowaMisja(miasto, kraj, pozycja);
    zadania.aktywneMisje.push_back(nowaMisja);
}

void GameState::cleanS() {
    zadania.transakcjeSygnalowe.clear();
}
/*void GameState::cleanM() {
    zadania.missjeDoWygenerowania.clear();
}*/