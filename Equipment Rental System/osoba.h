#pragma once
#include <iostream>
#include <string>

using namespace std;
/// <summary>
/// Klasa osoba
/// </summary>
class osoba {
public:
    int id;
    string imie;
    string nazwisko;
    int osoba_ilosc;

    /// <summary>
    /// Konstruktor bezargumentowy
    /// </summary>
    osoba() : id(0), imie("X"), nazwisko("Y"), osoba_ilosc(0) {}

    /// <summary>
    /// Konstruktor wieloargumentowy
    /// </summary>
    osoba(int _id, const string& _imie, const string& _nazwisko, int _osoba_ilosc)
        : id(_id), imie(_imie), nazwisko(_nazwisko), osoba_ilosc(_osoba_ilosc) {}

    /// <summary>
    /// Wirtualna funkcja wypisujaca dane z id
    /// </summary>
    virtual void wypisz() const {
        cout << id << " " << imie << " " << nazwisko << endl;
    }

    /// <summary>
    /// funkcja wypisujaca dane bez id
    /// </summary>
    void wyp_bez_id() const {
        cout << imie << " " << nazwisko << endl;
    }

    /// <summary>
    /// Operator przeciazony istream
    /// </summary>
    friend istream& operator>>(istream& is, osoba& o);
    /// <summary>
    /// Operator przeciazony ofstream
    /// </summary>
    friend ostream& operator<<(ostream& os, osoba& osb);
    /// <summary>
    /// Operator przeciazony porownania
    /// </summary>
    bool operator==(const osoba& osb) const {
        return (this->id == osb.id);
    }
    /// <summary>
    /// Operator przeciazony przypisania
    /// </summary>
    osoba& operator=(const osoba& os) {
        id = os.id;
        imie = os.imie;
        nazwisko = os.nazwisko;
        osoba_ilosc = os.osoba_ilosc;
        return *this;
    }
};