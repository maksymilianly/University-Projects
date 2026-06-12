#pragma once
#include <iostream>
#include <string>
#include <memory>

using namespace std;

/// <summary>
/// Klasa sprzet
/// </summary>
class sprzet {
public:
    int id_spr;
    float cena, waga;
    string nazwa;
    string typ;
    int sprzet_ilosc;

    /// <summary>
    /// Konstruktor bezargumentowy
    /// </summary>
    sprzet() : id_spr(), cena(), waga(), nazwa("X"), typ(), sprzet_ilosc(0) {}
    /// <summary>
    /// Konstruktor wieloargumentowy
    /// </summary>
    sprzet(int _id, float _cena, float _waga, const string& _nazwa, const string& _typ, int _sprzet_ilosc)
        : id_spr(_id), cena(_cena), waga(_waga), nazwa(_nazwa), typ(_typ), sprzet_ilosc(_sprzet_ilosc) {}

    /// <summary>
    /// Wirtualny destruktor
    /// </summary>
    virtual ~sprzet();

    /// <summary>
    /// wirtualna metoda wypisujaca dane klasy
    /// </summary>
    virtual void wypisz() const {
        cout << "ID sprzetu: " << id_spr << "|Cena: " << cena << "|" << "|Waga: " << waga << "|" << "|Nazwa: " << nazwa << "|" << "|Typ: " << typ << "| " << "|Ilosc_wypozyczen: " << sprzet_ilosc << "| ";
    }

    /// <summary>
   /// metoda wypisujaca dane klasy bez id
   /// </summary>
    void wyp_bez_id() const {
        cout << "|Cena: " << cena << "|" << "|Waga: " << waga << "|" << "|Nazwa: " << nazwa << "|" << "|Typ: " << typ << "|";
    }

    /// <summary>
   /// wirtualna metoda ktora wypisuje typ objektu
   /// </summary>
    virtual string co()
    {

        return "Sprzet";
    }

    /// <summary>
   /// wirtualna metoda dla funkcji dostep_sprzet
   /// </summary>
    virtual void dostepny() 
    {
        co();
        cout << "ID sprzetu: " << id_spr << "|Nazwa: " << nazwa << "| " << "|Ilosc_wypozyczen: " << sprzet_ilosc << "| " <<endl;
    }

    /// <summary>
   /// wirtualna metoda wypisujaca dane do pliku
   /// </summary>
    virtual void wypisz_do_pliku(ostream& os) const {
        os << cena << " " << waga << " " << nazwa << " " << typ << " " << sprzet_ilosc;
    }

    /// <summary>
   /// operator przeciazony ostream
   /// </summary>
    friend ostream& operator<<(ostream& os, const sprzet& s);

};

/// <summary>
/// klasa multimetr dziedzicaca sprzet
/// </summary>
class multimetr : public virtual sprzet {
public:

    string wyswietlanie;
    float max_wartosc_wyswietlania;

    /// <summary>
    /// Konstruktor domyślny klasy multimetr.
    /// </summary>
    multimetr() : sprzet(), wyswietlanie(), max_wartosc_wyswietlania() {}

    /// <summary>
    /// Konstruktor z parametrami klasy multimetr.
    /// </summary>
    /// <param name="_id">ID multimetru.</param>
    /// <param name="_cena">Cena multimetru.</param>
    /// <param name="_waga">Waga multimetru.</param>
    /// <param name="_nazwa">Nazwa multimetru.</param>
    /// <param name="_typ">Typ multimetru.</param>
    /// <param name="_sprzet_ilosc">Ilość dostępnych multimetrów.</param>
    /// <param name="_wyswietlanie">Tryb wyświetlania multimetru.</param>
    /// <param name="_max_wartosc">Maksymalna wartość wyświetlania multimetru.</param>
    multimetr(int _id, float _cena, float _waga, const string& _nazwa, const string& _typ, int _sprzet_ilosc, const string& _wyswietlanie, float _max_wartosc)
        : sprzet(_id, _cena, _waga, _nazwa, _typ, _sprzet_ilosc), wyswietlanie(_wyswietlanie), max_wartosc_wyswietlania(_max_wartosc) {}

    /// <summary>
    /// metoda override Wypisuje informacje o multimetrze.
    /// </summary>
    void wypisz() const override {
        cout << "|Multimetr| ";
        sprzet::wypisz();
        cout << "|Wyswietlanie: " << wyswietlanie << "|" << "|Maksymalna Wartosc Wyswietlania: " << max_wartosc_wyswietlania << "|" << endl;
    }

    /// <summary>
    /// Zwraca typ multimetru jako string.
    /// </summary>
    string co() override
    {
        return "Multimetr";
    }

    /// <summary>
    /// metoda dla funkci dostep_sprzet
    /// </summary>
    void dostepny() override
    {
        co();
        cout << "ID sprzetu: " << id_spr << "|Nazwa: " << nazwa << "| " << "|Ilosc_wypozyczen: " << sprzet_ilosc << "| " << endl;
    }

    /// <summary>
    /// Zapisuje informacje o multimetrze do strumienia ostream.
    /// </summary>
    /// <param name="os">Strumień wyjsciowy.</param>
    void wypisz_do_pliku(ostream& os) const override {
        os << "Multimetr" << " ";
        sprzet::wypisz_do_pliku(os);
        os << " " << wyswietlanie << " " << max_wartosc_wyswietlania << endl;
    }

    /// <summary>
    /// Operator przeciazony istream
    /// </summary>
    friend istream& operator>>(istream& is, multimetr& m);
    /// <summary>
    /// Operator przeciazony ostream
    /// </summary>
    friend ostream& operator<<(ostream& os, const multimetr& m);

};

/// <summary>
/// Klasa oscyloskop dziedzicaca sprzet
/// </summary>
class oscyloskop : public virtual sprzet {
public:
    int ilosc_kanalow;
    float max_czestotliwosc;
    float pojemnosc_pamiec;

    /// <summary>
    /// Konstruktor domyślny klasy oscyloskop.
    /// </summary>
    oscyloskop() : sprzet(), ilosc_kanalow(), max_czestotliwosc(), pojemnosc_pamiec() {}

    /// <summary>
    /// Konstruktor z parametrami klasy oscyloskop.
    /// </summary>
    /// <param name="_id">ID oscyloskopu.</param>
    /// <param name="_cena">Cena oscyloskopu.</param>
    /// <param name="_waga">Waga oscyloskopu.</param>
    /// <param name="_nazwa">Nazwa oscyloskopu.</param>
    /// <param name="_typ">Typ oscyloskopu.</param>
    /// <param name="_sprzet_ilosc">Ilość dostępnych oscyloskopów.</param>
    /// <param name="_ilosc_kanalow">Ilość kanałów oscyloskopu.</param>
    /// <param name="_max_czestotliwosc">Maksymalna częstotliwość oscyloskopu.</param>
    /// <param name="_pojemnosc_pamiec">Pojemność pamięci oscyloskopu.</param>
    oscyloskop(int _id, float _cena, float _waga, const string& _nazwa, const string& _typ, int _sprzet_ilosc, int _ilosc_kanalow, float _max_czestotliwosc, float _pojemnosc_pamiec)
        : sprzet(_id, _cena, _waga, _nazwa, _typ, _sprzet_ilosc), ilosc_kanalow(_ilosc_kanalow), max_czestotliwosc(_max_czestotliwosc), pojemnosc_pamiec(_pojemnosc_pamiec) {}

    /// <summary>
    /// metoda override wypisuje informacje o oscyloskopie.
    /// </summary>
    void wypisz() const override {
        cout << "|Oscyloskop| ";
        sprzet::wypisz();
        cout << "|Ilosc Kanalow: " << ilosc_kanalow << "|" << "|Maksymalna Czestotliwosc: " << max_czestotliwosc << "|" << "|Pojemnosc Pamieci: " << pojemnosc_pamiec << "|" << endl;
    }

    /// <summary>
    /// operator przeciazony istream
    /// </summary>
    friend istream& operator>>(istream& is, oscyloskop& o);
    /// <summary>
    /// Operator przeciazony ostream
    /// </summary>
    friend ostream& operator<<(ostream& os, const oscyloskop& o);

    /// <summary>
    /// Zwraca typ oscyloskopu jako string.
    /// </summary>
    string co() override
    {
        return "Oscyloskop";
    }

    /// <summary>
    /// Metoda dla funkcji dostep_sprzet
    /// </summary>
    void dostepny() override
    {
        co();
        cout << "ID sprzetu: " << id_spr << "|Nazwa: " << nazwa << "| " << "|Ilosc_wypozyczen: " << sprzet_ilosc << "| " << endl;
    }

    /// <summary>
    /// Zapisuje informacje o oscyloskopie do strumienia ostream .
    /// </summary>
    /// <param name="os">Strumień wyjściowy.</param>
    void wypisz_do_pliku(ostream& os) const override {
        os << "Oscyloskop" << " ";
        sprzet::wypisz_do_pliku(os);
        os << " " << ilosc_kanalow << " " << max_czestotliwosc << " " << pojemnosc_pamiec << endl;
    }

};

/// <summary>
/// Klasa decybelomierz dziedzicaca sprzet
/// </summary>
class decybelomierz : public virtual sprzet 
{
public:
    int maks_pomiar;
    string tryb_pomiarowy;
    bool podswietlenie;

    /// <summary>
    /// Konstruktor domyślny klasy decybelomierz.
    /// </summary>
    decybelomierz() : sprzet(), maks_pomiar(1), tryb_pomiarowy("1"), podswietlenie(true) {}

    /// <summary>
    /// Konstruktor z parametrami klasy decybelomierz.
    /// </summary>
    /// <param name="_id">ID decybelomierza.</param>
    /// <param name="_cena">Cena decybelomierza.</param>
    /// <param name="_waga">Waga decybelomierza.</param>
    /// <param name="_nazwa">Nazwa decybelomierza.</param>
    /// <param name="_typ">Typ decybelomierza.</param>
    /// <param name="_sprzet_ilosc">Ilość dostępnych decybelomierzy.</param>
    /// <param name="_maks_pomiar">Maksymalny pomiar decybelomierza.</param>
    /// <param name="_tryb_pomiarowy">Tryb pomiarowy decybelomierza.</param>
    /// <param name="_podwietlenie">Informacja o podświetleniu decybelomierza.</param>
    decybelomierz(int _id, float _cena, float _waga, const string& _nazwa, const string& _typ, int _sprzet_ilosc, int _maks_pomiar, string _tryb_pomiarowy, bool _podwietlenie)
        : sprzet(_id, _cena, _waga, _nazwa, _typ, _sprzet_ilosc), maks_pomiar(_maks_pomiar), tryb_pomiarowy(_tryb_pomiarowy), podswietlenie(_podwietlenie) {}

    /// <summary>
    /// Wypisuje informacje o decybelomierzu.
    /// </summary>
    void wypisz() const override {
        cout << "|Decybelomierz| ";
        sprzet::wypisz();
        cout << "|Maksymalny pomiar: " << maks_pomiar << "|" << "|Tryb pomiarowy: " << tryb_pomiarowy << "|" << "|Podswietlenie: " << podswietlenie << "|" << endl;
    }

    friend istream& operator>>(istream& is, decybelomierz& d);
    friend ostream& operator<<(ostream& os, const decybelomierz& d);

    /// <summary>
    /// Zwraca typ decybelomierza jako string.
    /// </summary>
    string co() override
    {
        return "Decybelomierz";
    }

    /// <summary>
    /// metoda dla funkcji dostep_sprzet
    /// </summary>
    void dostepny() override
    {
        co();
        cout << "ID sprzetu: " << id_spr << "|Nazwa: " << nazwa << "| " << "|Ilosc_wypozyczen: " << sprzet_ilosc << "| " << endl;
    }

    /// <summary>
    /// wypisuje do pliku z strumieniem ostream
    /// </summary>
    /// <param name="os">Strumień wyjściowy.</param>
    void wypisz_do_pliku(ostream& os) const override {
        os << "Decybelomierz" << " ";
        sprzet::wypisz_do_pliku(os);
        os << " " << maks_pomiar << " " << tryb_pomiarowy << " " << podswietlenie << endl;
    }


};

class analizator : public virtual sprzet
{
public:
    float wagaa;

    analizator() : sprzet(), wagaa() {}

    analizator(int _id, float _cena, float _waga, const string& _nazwa, const string& _typ, int _sprzet_ilosc, float _wagaa)
        : sprzet(_id, _cena, _waga, _nazwa, _typ, _sprzet_ilosc), wagaa(_wagaa) {}


    string co() override
    {
        return "Analizator";
    }

    void wypisz_do_pliku(ostream& os) const override {
        os << "Analizator" << " ";
        sprzet::wypisz_do_pliku(os);
        os << " " << wagaa << endl;
    }

    void wypisz() const override {
        cout << "|Analizator| ";
        sprzet::wypisz();
        cout << "|Waga: " << wagaa << endl;
    }

    friend istream& operator>>(istream& is, analizator& a);
    friend ostream& operator<<(ostream& os, const analizator& a);

    void dostepny() override
    {
        co();
        cout << "ID sprzetu: " << id_spr << "|Nazwa: " << nazwa << "| " << "|Ilosc_wypozyczen: " << sprzet_ilosc << "| " << endl;
    }
};
