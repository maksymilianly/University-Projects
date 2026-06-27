#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>


class ProcesDeszyfrowania;
class Grupa;

/// <summary>
/// Reprezentuje stół roboczy w sztabie.
/// Odpowiada za przechowywanie procesu deszyfrowania oraz zarządzanie przypisanymi do niego grupami roboczymi
/// </summary>
class Stol {
private:
	/// <summary>Obszar interakcji stołu w przestrzeni 2D</summary>
	sf::FloatRect hitbox{};
	/// <summary>Maksymalna liczba grup, które mogą jednocześnie pracować przy tym stole</summary>
	int maxGrup;
	/// <summary>Proces deszyfrowania aktualnie przypisany do stołu</summary>
	std::unique_ptr<ProcesDeszyfrowania> lezacySzyfr;
	/// <summary>Wektor wskaźników do grup przypisanych do tego stołu</summary>
	std::vector<Grupa*> przypisaniPracownicy;

public:
	/// <summary>Inicjalizuje stół z określoną pojemnością grup</summary>
	Stol(int pojemnosc);

	/// <summary>Inicjalizuje stół z określonym rozmiarem (hitbox) i pojemnością</summary>
	Stol(sf::FloatRect h, int pojemnosc);

	/// <summary>Sprawdza, czy stół nie posiada przypisanego szyfru</summary>
	/// <returns>True jeśli stół jest wolny, false w przeciwnym razie</returns>
	bool czyPusty() const {
		return lezacySzyfr == nullptr;
	}

	const sf::FloatRect& getHitbox() const { return hitbox; }
	void setHitbox(sf::FloatRect& nowy) { hitbox = nowy; }

	/// <summary>Ustawia nową pozycję stołu na mapie</summary>
	void setStolPos(const sf::Vector2f& pos) { hitbox.position = pos; }

	int getPojemnosc()const { return maxGrup; }

	/// <summary>Zwraca wskaźnik do szyfru znajdującego się na stole (tylko do odczytu)</summary>
	const ProcesDeszyfrowania* getSzyfr() const { return lezacySzyfr.get(); }

	/// <summary>Zwraca wskaźnik do szyfru znajdującego się na stole (z możliwością modyfikacji)</summary>
	ProcesDeszyfrowania* getSzyfr() { return lezacySzyfr.get(); }

	/// <summary>
	/// Pobiera szyfr ze stołu, jednocześnie czyszcząc listę przypisanych grup
	/// Przenosi własność obiektu
	/// </summary>
	/// <returns>Unikalny wskaźnik do procesu deszyfrowania</returns>
	std::unique_ptr<ProcesDeszyfrowania> giveSzyfr() {
		wyczyscGrupy();
		return std::move(lezacySzyfr);
	}

	/// <summary>Przypisuje nowy proces deszyfrowania do stołu</summary>
	/// <param name="szyfr">Unikalny wskaźnik do procesu (przenosi własność).</param>
	void takeSzyfr(std::unique_ptr<ProcesDeszyfrowania> szyfr) { lezacySzyfr = std::move(szyfr); }

	/// <summary>Dodaje grupę roboczą do tego stanowiska</summary>
	/// <param name="grupaPtr">Wskaźnik do grupy</param>
	void dodajGrupe(Grupa* grupaPtr);

	/// <summary>Zwraca listę grup aktualnie przypisanych do tego stołu</summary>
	const std::vector<Grupa*>& getPrzypisaneGrupy() {
		return przypisaniPracownicy;
	}

	/// <summary>Usuwa wszystkie grupy przypisane do stołu</summary>
	void wyczyscGrupy();
};