#include "Stol.h"

#include "ProcesDeszyfrowania.h"
#include "Staff.h"


Stol::Stol(int pojemnosc) : maxGrup(pojemnosc)
{
}

Stol::Stol(sf::FloatRect h, int pojemnosc) : hitbox(h), maxGrup(pojemnosc)
{
	przypisaniPracownicy.reserve(maxGrup);
}

void Stol::dodajGrupe(Grupa* grupaPtr) {
	if (przypisaniPracownicy.size() < maxGrup && !grupaPtr->getZajety()) {
		przypisaniPracownicy.push_back(grupaPtr);
		grupaPtr->setZajety(true);
	}
}

void Stol::wyczyscGrupy()
{
	for (auto& grupa : przypisaniPracownicy)
	{
		grupa->setZajety(false);
	}
	przypisaniPracownicy.clear();
}