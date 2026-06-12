#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

class ProcesDeszyfrowania;
class Grupa;


class Stol
{
private:
	sf::FloatRect hitbox{};
	int maxGrup;
	std::unique_ptr<ProcesDeszyfrowania> lezacySzyfr;
	std::vector<Grupa*> przypisaniPracownicy;
public:
	Stol(int pojemnosc);

	Stol(sf::FloatRect h, int pojemnosc);

	bool czyPusty() const {
		return lezacySzyfr == nullptr;
	}
	const sf::FloatRect& getHitbox() const { return hitbox; }
	void setHitbox(sf::FloatRect& nowy) { hitbox = nowy; }
	void setStolPos(const sf::Vector2f& pos) { hitbox.position = pos; }
	int getPojemnosc()const { return maxGrup; }

	const ProcesDeszyfrowania* getSzyfr() const {return lezacySzyfr.get();}
	ProcesDeszyfrowania* getSzyfr() { return lezacySzyfr.get(); }

	std::unique_ptr<ProcesDeszyfrowania> giveSzyfr() {
		wyczyscGrupy();
		return std::move(lezacySzyfr);
	}

	void takeSzyfr(std::unique_ptr<ProcesDeszyfrowania> szyfr) { lezacySzyfr = std::move(szyfr); }

	void dodajGrupe(Grupa* grupaPtr);

     const std::vector<Grupa*>& getPrzypisaneGrupy() {
		return przypisaniPracownicy;
	}

	 void wyczyscGrupy();
};