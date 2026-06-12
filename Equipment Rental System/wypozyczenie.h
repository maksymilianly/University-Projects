#pragma once
#include "osoba.h"
#include "sprzet.h"
#include <vector>
#include <cmath>

/// <summary>
/// Klasa wypozyczenie, dziedziczy po klasach osoba i sprzet.
/// </summary>
class wypozyczenie : public osoba, public sprzet {
public:
    int dzien_s; ///< Dzień rozpoczęcia wypożyczenia
    int miesiac_s; ///< Miesiąc rozpoczęcia wypożyczenia
    int rok_s; ///< Rok rozpoczęcia wypożyczenia
    int dzien_e; ///< Dzień zakończenia wypożyczenia
    int miesiac_e; ///< Miesiąc zakończenia wypożyczenia
    int rok_e; ///< Rok zakończenia wypożyczenia
    char separator; ///< Separator daty

    /// <summary>
    /// Konstruktor domyślny klasy wypozyczenie.
    /// </summary>
    wypozyczenie()
        : osoba(0, "X", "Y", 0), sprzet(0, 0, 0, "0", "0", 0), dzien_s(0), miesiac_s(0), rok_s(0), dzien_e(0), miesiac_e(0), rok_e(0), separator('.') {}

    /// <summary>
    /// Konstruktor parametryczny klasy wypozyczenie.
    /// </summary>
    /// <param name="_id">Id osoby</param>
    /// <param name="_imie">Imię osoby</param>
    /// <param name="_nazwisko">Nazwisko osoby</param>
    /// <param name="_il_wyp">Ilość wypożyczeń</param>
    /// <param name="_iid">Id sprzętu</param>
    /// <param name="_cena">Cena sprzętu</param>
    /// <param name="_waga">Waga sprzętu</param>
    /// <param name="_nazwa">Nazwa sprzętu</param>
    /// <param name="_typ">Typ sprzętu</param>
    /// <param name="_sprzet_ilosc">Ilość sprzętu</param>
    /// <param name="_dzien_s">Dzień rozpoczęcia wypożyczenia</param>
    /// <param name="_miesiac_s">Miesiąc rozpoczęcia wypożyczenia</param>
    /// <param name="_rok_s">Rok rozpoczęcia wypożyczenia</param>
    /// <param name="_dzien_e">Dzień zakończenia wypożyczenia</param>
    /// <param name="_miesiac_e">Miesiąc zakończenia wypożyczenia</param>
    /// <param name="_rok_e">Rok zakończenia wypożyczenia</param>
    /// <param name="_separator">Separator daty</param>
    wypozyczenie(int _id, const string& _imie, const string& _nazwisko, int _il_wyp, int _iid, float _cena, float _waga, const string& _nazwa, const string& _typ, int _sprzet_ilosc,
        int _dzien_s, int _miesiac_s, int _rok_s, int _dzien_e, int _miesiac_e, int _rok_e, char _separator)
        : osoba(_id, _imie, _nazwisko, _il_wyp), sprzet(_iid, _cena, _waga, _nazwa, _typ, _sprzet_ilosc), dzien_s(_dzien_s), miesiac_s(_miesiac_s), rok_s(_rok_s),
        dzien_e(_dzien_e), miesiac_e(_miesiac_e), rok_e(_rok_e), separator(_separator) {}

    /// <summary>
    /// Wyświetla informacje o wypożyczeniu.
    /// </summary>
    void wypisz() const override {
        osoba::wyp_bez_id();
        sprzet::wypisz();
        cout << dzien_s << separator << miesiac_s << separator << rok_s << " - "
            << dzien_e << separator << miesiac_e << separator << rok_e << " |" << endl;
    }

    /// <summary>
    /// Wyświetla datę wypożyczenia.
    /// </summary>
    void wypisz_date() const {
        cout << "|" << dzien_s << separator << miesiac_s << separator << rok_s << " - "
            << dzien_e << separator << miesiac_e << separator << rok_e << "|" << endl;
    }

    /// <summary>
    /// Wyświetla informacje dla klienta.
    /// </summary>
    void wypisz_dla_klienta() const {
        cout << "|" << nazwa << "|";
        wypisz_date();
    }

    /// <summary>
    /// Wyświetla informacje dla sprzętu.
    /// </summary>
    void wypisz_dla_spr() const {
        cout << "|" << nazwa << "|";
        wypisz_date();
    }

    /// <summary>
    /// Wyświetla nazwę sprzętu.
    /// </summary>
    void co() const {
        cout << nazwa << " ";
    }

    friend istream& operator>>(istream& is, wypozyczenie& wyp);
    friend ostream& operator<<(ostream& is, wypozyczenie& wyp);

    /// <summary>
    /// Operator porównania wypożyczeń.
    /// </summary>
    /// <param name="ww">Obiekt wypozyczenie do porównania</param>
    wypozyczenie& operator==(wypozyczenie& ww) {
        id = ww.id;
        imie = ww.imie;
        nazwisko = ww.nazwisko;
        osoba_ilosc = ww.osoba_ilosc;
        id_spr = ww.id_spr;
        cena = ww.cena;
        waga = ww.waga;
        nazwa = ww.nazwa;
        typ = ww.typ;
        sprzet_ilosc = ww.sprzet_ilosc;
        return *this;
    }

    /// <summary>
    /// Ustawia dane osoby w wypożyczeniu.
    /// </summary>
    /// <param name="os">Obiekt osoba</param>
    void wypozyczenie_osoba(const osoba& os) {
        id = os.id;
        imie = os.imie;
        nazwisko = os.nazwisko;
        osoba_ilosc = os.osoba_ilosc;
    }

    /// <summary>
    /// Ustawia dane sprzętu w wypożyczeniu.
    /// </summary>
    /// <param name="spr">Obiekt sprzet</param>
    void wypozyczenie_sprzet(const sprzet& spr) {
        id_spr = spr.id_spr;
        cena = spr.cena;
        waga = spr.waga;
        nazwa = spr.nazwa;
        typ = spr.typ;
        sprzet_ilosc = spr.sprzet_ilosc;
    }

    /// <summary>
    /// Sprawdza, czy daty końcowe są równe.
    /// </summary>
    /// <param name="ww">Obiekt wypozyczenie</param>
    auto czy_rowna_data_e(wypozyczenie& ww) {
        return ((abs(this->dzien_e - ww.dzien_e) + abs((this->miesiac_e - ww.miesiac_e) * 12) + abs((this->rok_e - ww.rok_e) * 365)) == 0);
    }

    /// <summary>
    /// Sprawdza, czy daty początkowe są równe.
    /// </summary>
    /// <param name="ww">Obiekt wypozyczenie</param>
    auto czy_rowna_data_s(wypozyczenie& ww) {
        return ((abs(this->dzien_s - ww.dzien_s) + abs((this->miesiac_s - ww.miesiac_s) * 12) + abs((this->rok_s - ww.rok_s) * 365)) == 0);
    }

    /// <summary>
    /// Sprawdza, czy data końcowa jest większa od początkowej.
    /// </summary>
    bool czy_wieksza_data() const {
        if (this->rok_e > this->rok_s) {
            return true;
        }
        else if (this->rok_e == this->rok_s) {
            if (this->miesiac_e > this->miesiac_s) {
                return true;
            }
            else if (this->miesiac_e == this->miesiac_s) {
                if (this->dzien_e > this->dzien_s) {
                    return true;
                }
            }
        }
        return false;
    }

    /// <summary>
    /// Sprawdza, czy data początkowa jest wieksza od 1.07.2024 .
    /// </summary>
    bool czy_lipiec() const {
        if (this->rok_s > 2024) {
            return false;
        }
        else if (this->rok_s == 2024) {
            if (this->miesiac_s > 6) {
                return false;
            }
        }
        return true;
    }

    /// <summary>
    /// Sprawdza, czy data końcowa nakłada się na początkową innego wypożyczenia.
    /// </summary>
    /// <param name="ww">Obiekt wypozyczenie</param>
    bool czy_nakladanie_koniec_pocz(wypozyczenie& ww) {
        if (this->rok_e > ww.rok_s) {
            return true;
        }
        else if (this->rok_e == ww.rok_s) {
            if (this->miesiac_e > ww.miesiac_s) {
                return true;
            }
            else if (this->miesiac_e == ww.miesiac_s) {
                if (this->dzien_e > ww.dzien_s) {
                    return true;
                }
            }
        }
        return false;
    }

    /// <summary>
    /// Sprawdza, czy data końcowa jest większa od końcowej innego wypożyczenia.
    /// </summary>
    /// <param name="ww">Obiekt wypozyczenie</param>
    bool czy_koncowa_wieksza_koncowa(wypozyczenie& ww) {
        if (this->rok_e > ww.rok_e) {
            return true;
        }
        else if (this->rok_e == ww.rok_e) {
            if (this->miesiac_e > ww.miesiac_e) {
                return true;
            }
            else if (this->miesiac_e == ww.miesiac_e) {
                if (this->dzien_e > ww.dzien_e) {
                    return true;
                }
            }
        }
        return false;
    }

    /// <summary>
    /// Sprawdza, czy data początkowa jest większa od początkowej innego wypożyczenia.
    /// </summary>
    /// <param name="ww">Obiekt wypozyczenie</param>
    bool czy_poczatkowa_wieksza_poczatkowa(wypozyczenie& ww) {
        if (this->rok_s > ww.rok_s) {
            return true;
        }
        else if (this->rok_s == ww.rok_s) {
            if (this->miesiac_s > ww.miesiac_s) {
                return true;
            }
            else if (this->miesiac_s == ww.miesiac_s) {
                if (this->dzien_s > ww.dzien_s) {
                    return true;
                }
            }
        }
        return false;
    }

    /// <summary>
    /// Proponuje nową datę początkową.
    /// </summary>
    /// <param name="ww">Obiekt wypozyczenie</param>
    auto proponowanie_daty_pocz(wypozyczenie& ww) {
        ww.dzien_s = this->dzien_e;
        ww.miesiac_s = this->miesiac_e;
        ww.rok_s = this->rok_e;
        return ww;
    }

    /// <summary>
    /// Proponuje nową datę końcową.
    /// </summary>
    /// <param name="ww">Obiekt wypozyczenie</param>
    auto proponowanie_daty_konc(wypozyczenie& ww) {
        ww.dzien_e = this->dzien_s;
        ww.miesiac_e = this->miesiac_s;
        ww.rok_e = this->rok_s;
        return ww;
    }

    /// <summary>
    /// Dodaje jeden dzień do daty początkowej.
    /// </summary>
    auto dodanie_jednego_dnia_s() 
        {
            if (dzien_s == 31 && miesiac_s == 12) {
                dzien_s = 1;
                miesiac_s = 1;
                rok_s += 1;
                return this;
            }
            if (miesiac_s == 2) {
                if ((rok_s % 4 == 0 && rok_s % 100 != 0) || (rok_s % 400 == 0)) {
                    if (dzien_s == 29) {
                        dzien_s = 1;
                        miesiac_s += 1;
                        return this;
                    }
                }
                else {
                    if (dzien_s == 28) {
                        dzien_s = 1;
                        miesiac_s += 1;
                        return this;
                    }
                }
            }
            if (miesiac_s == 4 || miesiac_s == 6 || miesiac_s == 9 || miesiac_s == 11) {
                if (dzien_s == 30) {
                    dzien_s = 1;
                    miesiac_s += 1;
                    return this;
                }
            }
            else {
                if (dzien_s == 31) {
                    dzien_s = 1;
                    miesiac_s += 1;
                    return this;
                }
            }
            dzien_s += 1;
            return this;
        }
        /// <summary>
        /// Dodaje jeden dzień do daty końcowej.
        /// </summary>
        auto dodanie_jednego_dnia_e()
        {
            if (dzien_e == 31 && miesiac_e == 12) {
                dzien_e = 1;
                miesiac_e = 1;
                rok_e += 1;
                return this;
            }

            if (miesiac_e == 2) {
                if ((rok_e % 4 == 0 && rok_e % 100 != 0) || (rok_e % 400 == 0)) {
                    if (dzien_e == 29) {
                        dzien_e = 1;
                        miesiac_e += 1;
                        return this;
                    }
                }
                else {
                    if (dzien_e == 28) {
                        dzien_e = 1;
                        miesiac_e += 1;
                        return this;
                    }
                }
            }
            else if (miesiac_e == 4 || miesiac_e == 6 || miesiac_e == 9 || miesiac_e == 11) {
                if (dzien_e == 30) {
                    dzien_e = 1;
                    miesiac_e += 1;
                    return this;
                }
            }
            else {
                if (dzien_e == 31) {
                    dzien_e = 1;
                    miesiac_e += 1;
                    return this;
                }
            }

            dzien_e += 1;
            return this;
        }
        
        /// <summary>
        /// Odejmuje jeden dzień od daty końcowej.
        /// </summary>
        auto odejm_jednego_dnia_e()
        {
            if (dzien_e == 1 && miesiac_e == 1) {
                dzien_e = 31;
                miesiac_e = 12;
                rok_e -= 1;
                return this;
            }

            if (dzien_e == 1) {
                miesiac_e -= 1;
                switch (miesiac_e) {
                case 1: case 3: case 5: case 7: case 8: case 10: case 12:
                    dzien_e = 31;
                    break;
                case 4: case 6: case 9: case 11:
                    dzien_e = 30;
                    break;
                case 2:
                    if ((rok_e % 4 == 0 && rok_e % 100 != 0) || (rok_e % 400 == 0)) {
                        dzien_e = 29;
                    }
                    else {
                        dzien_e = 28;
                    }
                    break;
                }
            }
            else {
                dzien_e -= 1;
            }

            return this;
        }

        /// <summary>
        /// data poczatku rowna koncu podanego objektu .
        /// </summary>
        auto poczatkowa_rowna_konc(wypozyczenie& ww)
        {
            this->dzien_s = ww.dzien_e;
            this->miesiac_s = ww.miesiac_e;
            this->rok_s = ww.rok_e;
        }
        /// <summary>
        /// data konca rezerwacji rowna poczatku objektu
        /// </summary>
        auto koncowa_rowna_pocz(wypozyczenie& ww)
        {
            this->dzien_e = ww.dzien_s;
            this->miesiac_e = ww.miesiac_s;
            this->rok_e = ww.rok_s;
        }
        /// <summary>
        /// data poczatku rowna poczatkowi podanego objektu .
        /// </summary>
        auto poczatkowa_rowna_poczatkowa(wypozyczenie& ww)
        {
            this->dzien_s = ww.dzien_s;
            this->miesiac_s = ww.miesiac_s;
            this->rok_s = ww.rok_s;
        }

    
};

