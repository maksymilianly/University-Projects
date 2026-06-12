#ifndef FUNKCJE_H
#define FUNKCJE_H
#include <array>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <utility>
using namespace std;


const string nazwa_pliku;

void dek_dla_dni(string dzien);

struct godziny {
    int hour_s;
    int hour_e;
    char separator;
    int minute_s;
    int minute_e;
};

struct Prowadzacy {
    int id_prow;
    string imie;
    string nazwisko;
    };


struct Zajecia {
    Prowadzacy prowadzacy;
    string grupa;
    string przedmiot;
    string sala;
    string dzienTygodnia;
    int czasRozpoczecia_god;
    int czasRozpoczecia_min;
    int czasZakonczenia_god;
    int czasZakonczenia_min;
};
/// <summary>
/// Glowna funkcja. Proponuje dokonac modyfikacji rozkladu lub jego wyswietlania.
/// </summary>
/// <param name="prowadzace">Wektor prowadzacych</param>
/// <param name="zajecia">Wektor zajec</param>
/// <param name="godziny_rozklad">Wygenerowane godziny dla rozkladu</param>
void main_wyswietlanie(vector<Prowadzacy>& prowadzace, vector<Zajecia>& zajecia, const vector<godziny>& godziny_rozklad);
/// <summary>
/// Funkcja sterujaca funkcjami za pomoca switch. Z jej pomoca mamy dostep do poszczegolnych funkcji
/// </summary>
/// <param name="prowadzace">Wektor prowadzacych</param>
/// <param name="zajecia">Wektor zajec</param>
/// <param name="godziny_rozklad">Wygenerowane godziny dla rozkladu</param>
void modyfikacje(vector<Prowadzacy>& prowadzace, vector<Zajecia>& zajecia, const vector<godziny>& godziny_rozklad);
/// <summary>
/// Generuje godziny dla rozkladu od 8 do 18
/// </summary>
/// <param name="godziny_rozklad">GWygenerowane godziny dla rozkladu</param>
void generowanie_godzin_rozkladu(vector<godziny>& godziny_rozklad);
/// <summary>
/// Generuje rozklad za pomoca funkcji generowania godzin i wektora zajec
/// </summary>
/// <param name="godziny_rozklad">Wygenerowane godziny dla rozkladu</param>
/// <param name="zajecia">Wektor zajec</param>
void generowanie_rozkladu(const vector<godziny>& godziny_rozklad, vector<Zajecia>& zajecia);
/// <summary>
/// Funkcja wyswietla wszystkich prowadzacych z wektora
/// </summary>
/// <param name="prowadzace">Wektor prowadzacych</param>
void wyswietlanie_prow(vector<Prowadzacy>& prowadzace);
/// <summary>
/// Wyswietla rozklad dla podanego prowadzacego
/// </summary>
/// <param name="prowadzace">Wektor prowadzacych</param>
/// <param name="zajecia">Wektor zajec</param>
/// <param name="id">Id rowadzacego do podania</param>
void rozklad_dla_prowadzacego(const vector<Prowadzacy>& prowadzace, vector<Zajecia>& zajecia, int id);
/// <summary>
/// Wyswietla rozklad dla podanej grupy
/// </summary>
/// <param name="zajecia">Wektor zajec</param>
/// <param name="grupa">Numer grupy do podania</param>
void rozklad_dla_grupy(vector<Zajecia>& zajecia, const string& grupa);
/// <summary>
/// Wyswietla rozklad dla podanego predmiotu
/// </summary>
/// <param name="zajecia">Wektor zajec</param>
/// <param name="przedmiot">Przedmiot do podania</param>
void rozklad_dla_przedmiotu(vector<Zajecia>& zajecia, const string& przedmiot);
/// <summary>
/// Wyswietla rozklad dla podanego dnia
/// </summary>
/// <param name="godziny_rozklad"Wygenerowane godziny dla rozkladu></param>
/// <param name="zajecia">Wektor zajec</param>
/// <param name="dzien">Dzien do podania</param>
void rozklad_dla_dnia(const vector<godziny>& godziny_rozklad, vector<Zajecia>& zajecia, const string& dzien);
/// <summary>
/// Wyswietla rozklad dla podanej sali
/// </summary>
/// <param name="godziny_rozklad">Wygenerowane godziny dla rozkladu</param>
/// <param name="zajecia">Wektor zajec</param>
/// <param name="sala">Sala do podania</param>
void rozklad_dla_sal(const vector<godziny>& godziny_rozklad, vector<Zajecia>& zajecia, const string& sala);
/// <summary>
/// Wyswitla aktualny plan zajec
/// </summary>
/// <param name="zajecia">Wektor zajec</param>
/// <param name="godziny_rozklad">Wygenerowane godziny dla rozkladu</param>
void wyswietlanie_planu(vector<Zajecia>& zajecia, const vector<godziny>& godziny_rozklad);
/// <summary>
/// Funkcja sterujaca funkcjami modyfikacji okreslonego zajecia(zmiana,usuwanie,dodawanie)
/// </summary>
/// <param name="godziny_rozklad">Wygenerowane godziny dla rozkladu</param>
/// <param name="zajecia">Wektor zajec</param>
/// <param name="prowadzace">Wektor prowadzacych</param>
void case6(const vector<godziny>& godziny_rozklad, vector<Zajecia>& zajecia, vector<Prowadzacy>& prowadzace);
/// <summary>
/// Funkcja zapisujaca dane z wektorow prowadzacych i zajec w pliki
/// </summary>
/// <param name="prowadzace">Wektor prowadzacych</param>
/// <param name="zajecia">Wektor zajec</param>
/// <param name="nazwa_pliku">Nazwa pliku</param>
/// <param name="nazwa_pliku1">Nazwa pliku</param>
void zapisz_do_pliku(vector<Prowadzacy>& prowadzace,vector<Zajecia>& zajecia, const string& nazwa_pliku);
/// <summary>
/// Odczytuje dane z pliku zajec
/// </summary>
/// <param name="prowadzace">Wektor prowadzacych</param>
/// <param name="zajecie">Wektor zajec</param>
/// <param name="nazwa_pliku">Nazwa pliku</param>
void odczyt_pliku(vector<Prowadzacy>& prowadzace, vector<Zajecia>& zajecie, string nazwa_pliku);
/// <summary>
/// Funkcja znajduje zajecie ktore podlega modyfikacji
/// </summary>
/// <param name="prowadzace">Wektor prowadzacych</param>
/// <param name="zajecia">Wektor zajec</param>
/// <param name="godziny_rozklad">Wygenerowane godziny dla rozkladu</param>
void modyfikacja_rozkladu(vector<Prowadzacy>& prowadzace, vector<Zajecia>& zajecia, const vector<godziny>& godziny_rozklad);
/// <summary>
/// Funkcja zmienia dane zajecia i sprawdza mozliwosc zmiany elementow zajecia 
/// </summary>
/// <param name="prowadzace">Wektor prowadzacych</param>
/// <param name="zajecia">Wektor zajec</param>
/// <param name="godziny_rozklad">Wygenerowane godziny dla rozkladu</param>
/// <param name="zajecie">Zajecie znalezione w funkcji 'modyfikacja_rozkladu'</param>
void modyfikacja_zajecia(vector<Prowadzacy>& prowadzace, vector<Zajecia>& zajecia, const vector<godziny>& godziny_rozklad, Zajecia& zajecie);
/// <summary>
/// Dodaje zajecie do rozkladu sprawdzajac mozliwosc dodania zajecia
/// </summary>
/// <param name="zajecia">Wektor zajec</param>
/// <param name="godziny_rozklad">Wygenerowane godziny dla rozkladu</param>
/// <param name="prowadzace">Wektor prowadzacych</param>
void dodawanie_do_rozkladu( vector<Zajecia>& zajecia, const vector<godziny>& godziny_rozklad,vector<Prowadzacy>& prowadzace);
/// <summary>
/// Usuwa zajecie z wektora
/// </summary>
/// <param name="prowadzace">Wektor prowadzacych</param>
/// <param name="zajecia">Wektor zajec</param>
/// <param name="godziny_rozklad">Wygenerowane godziny rozkladu</param>
void usuwanie_z_rozkladu(vector<Prowadzacy>& prowadzace,vector<Zajecia>& zajecia, const vector<godziny>& godziny_rozklad);



#endif 