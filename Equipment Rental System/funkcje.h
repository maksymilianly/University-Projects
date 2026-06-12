#ifndef HEADER_H
#define HEADER_H

#include "sprzet.h"
#include "wypozyczenie.h"
#include "osoba.h"
#include <vector>
#include <string>
#include <iostream>
#include <memory>

using namespace std;

/// <summary>
/// globalna zmienna. Dziala jako iterator dla inicjalizowania kolejnych urzadzen unikatowymi id
/// </summary>
/// <param name="id_sprzet"> id sprzetu </param>
static int id_sprzet = 1;

/// <summary>
/// Odczytuje sprzęt z pliku baza_sprzetu.txt . Zapisuje sprzęt jako unikalny wskaźnik w wektor unikatowych wskaźników
/// </summary>
/// <param name="nazwa_pliku">nazwa pliku</param>
/// <param name="sprzety">Wektor unikatowych wskaźników</param>
void odczyt_sprzet(const string& nazwa_pliku, vector<unique_ptr<sprzet>>& sprzety);

/// <summary>
/// Odczytuje klientów z pliku klienci.txt . Zapisuje te osoby w wektor
/// </summary>
/// <param name="nazwa_pliku">nazwa pliku</param>
/// <param name="klienci">Wektor klientów</param>
void odczyt_klient(const string& nazwa_pliku, vector<osoba>& klienci);

/// <summary>
/// Odczytuje wypożyczenia z pliku wypozyczenia.txt . Odczytuje niezbędne do porównania z poprzednimi wektorami informacje w celu
/// przypisania sobie wszystkich wartości do zmiennych
/// </summary>
/// <param name="nazwa_pliku">nazwa pliku</param>
/// <param name="wypozyczenia">Wektor wypożyczeń</param>
/// <param name="klienci">Wektor klientów</param>
/// <param name="sprzety">Wektor urządzeń</param>
void odczyt_wyp(const string& nazwa_pliku, vector<wypozyczenie>& wypozyczenia, vector<osoba>& klienci, vector<unique_ptr<sprzet>>& sprzety);

/// <summary>
/// Funkcja wylicza ile wypożyczeń już ma sprzęt oraz przypisuje te wartości dla sprzętu w "sprzety" oraz poszczególnego wypożyczenia
/// </summary>
/// <param name="id_sprzet"></param>
/// <param name="wypozyczenia">Wektor wypożyczeń</param>
/// <param name="klienci">Wektor klientów</param>
/// <param name="sprzety">Wektor urządzeń</param>
void wylicz(vector<wypozyczenie>& wypozyczenia, vector<osoba>& klienci, vector<unique_ptr<sprzet>>& sprzety);

/// <summary>
/// Funkcja dekoracyjna tworząca nagłówek 
/// </summary>
/// <param name="tekst">tekst, który jest wypisywany</param>
void naglowek(const char* tekst);

/// <summary>
/// Funkcja dekoracyjna tworząca ozdobiony tekst 
/// </summary>
/// <param name="tekst">tekst, który jest wypisywany</param>
void tekst(const char* tekst);

/// <summary>
/// Funkcja główna. Jest realizowana za pomocą pętli while, która kończy program po wpisaniu liczby 0 
/// </summary>
/// <param name="sprzety">Wektor urządzeń</param>
/// <param name="wypozyczenia">Wektor wypożyczeń</param>
/// <param name="klienci">Wektor klientów</param>
void interface(vector<unique_ptr<sprzet>>& sprzety, vector<wypozyczenie>& wypozyczenia, vector<osoba>& klienci);

/// <summary>
/// Funkcja wypisująca poszczególny sprzęt z wektora sprzętu 
/// </summary>
/// <param name="sprzety">Wektor urządzeń</param>
void sprzet_baza(vector<unique_ptr<sprzet>>& sprzety);

/// <summary>
/// Funkcja wypisująca sprzęt oraz liczbę wypożyczeń dla niego. W przypadku 3 wypożyczeń jest wyświetlany odpowiedni komunikat
/// </summary>
/// <param name="sprzety">Wektor urządzeń</param>
void dostep_sprzet(vector<unique_ptr<sprzet>>& sprzety);

/// <summary>
/// Funkcja wyświetla klientów z wektora klienci 
/// </summary>
/// <param name="klienci">Wektor klientów</param>
void wyswietlanie_klient(vector<osoba>& klienci);

/// <summary>
/// Funkcja umożliwiająca rezerwację przyrządu przy spełnionych warunkach 
/// </summary>
/// <param name="sprzety">Wektor urządzeń</param>
/// <param name="wypozyczenia">Wektor wypożyczeń</param>
/// <param name="klienci">Wektor klientów</param>
void rezerwacja(vector<unique_ptr<sprzet>>& sprzety, vector<wypozyczenie>& wypozyczenia, vector<osoba>& klienci);

/// <summary>
/// Funkcja usuwająca rezerwację podaną przez użytkownika
/// </summary>
/// <param name="sprzety">Wektor urządzeń</param>
/// <param name="wypozyczenia">Wektor wypożyczeń</param>
/// <param name="klienci">Wektor klientów</param>
void usuniecie_rezerwacji(vector<unique_ptr<sprzet>>& sprzety, vector<wypozyczenie>& wypozyczenia, vector<osoba>& klienci);

/// <summary>
/// Funkcja proponująca do wyboru kilka wariantów wyświetlania informacji 
/// </summary>
/// <param name="sprzety">Wektor urządzeń</param>
/// <param name="wypozyczenia">Wektor wypożyczeń</param>
/// <param name="klienci">Wektor klientów</param>
void wypozyczenia_tab(vector<unique_ptr<sprzet>>& sprzety, vector<wypozyczenie>& wypozyczenia, vector<osoba>& klienci);

/// <summary>
/// Funkcja pochodna od funkcji wypozyczenia_tab. Wyświetla informacje dla osoby 
/// </summary>
/// <param name="sprzety">Wektor urządzeń</param>
/// <param name="wypozyczenia">Wektor wypożyczeń</param>
/// <param name="klienci">Wektor klientów</param>
void wys_dla_osoby(int jaki, vector<osoba>& klienci, vector<wypozyczenie>& wypozyczenia, vector<unique_ptr<sprzet>>& sprzety);

/// <summary>
/// Funkcja zapisująca osobę do pliku osoba.txt
/// </summary>
/// <param name="klienci">Wektor klientów</param>
/// <param name="wypozyczenia">Wektor wypożyczeń</param>
void zapisz_osoba(vector<osoba>& klienci, vector<wypozyczenie>& wypozyczenia);

/// <summary>
/// Funkcja pochodna od funkcji wypozyczenia_tab. Wyświetla informacje dla urządzenia 
/// </summary>
/// <param name="sprzety">Wektor urządzeń</param>
/// <param name="wypozyczenia">Wektor wypożyczeń</param>
/// <param name="klienci">Wektor klientów</param>
/// <param name="jaki">id sprzętu dla operacji porównawczych</param>
void wys_dla_urz(vector<unique_ptr<sprzet>>& sprzety, vector<wypozyczenie>& wypozyczenia, vector<osoba>& klienci, int jaki);

/// <summary>
/// Funkcja zapisująca sprzęt do pliku sprzet.txt
/// </summary>
/// <param name="klienci">Wektor klientów</param>
/// <param name="wypozyczenia">Wektor wypożyczeń</param>
/// <param name="sprzety">Wektor urządzeń</param>
void zapisz_sprzet(vector<osoba>& klienci, vector<wypozyczenie>& wypozyczenia, vector<unique_ptr<sprzet>>& sprzety);

/// <summary>
/// Funkcja wypisująca sprzęt do pliku baza_sprzetu.txt
/// </summary>
/// <param name="sprzety">Wektor urządzeń</param>
void wypisz_do_bazy(const vector<unique_ptr<sprzet>>& sprzety);

/// <summary>
/// Funkcja wypisująca wypożyczenia
/// </summary>
/// <param name="wypozyczenia">Wektor wypożyczeń</param>
void wypisz_wypozyczenia(vector<wypozyczenie>& wypozyczenia);

/// <summary>
/// Funkcja ktra jest podfunkcja funkcji wylicz. Wylicza ilosc wypozyczen dla osoby
/// </summary>
/// <param name="kk">Osoba</param>
/// <param name="wypozyczenia">Wektor wypożyczeń</param>
/// <returns>ilość wypożyczeń</returns>
int ilosc_osoba(osoba& kk, const vector<wypozyczenie>& wypozyczenia);

/// <summary>
/// Funkcja ktra jest podfunkcja funkcji wylicz. Wylicza ilosc wypozyczen dla urzdzenia
/// </summary>
/// <param name="ss">Sprzęt</param>
/// <param name="wypozyczenia">Wektor wypożyczeń</param>
/// <returns>ilość wypożyczeń</returns>
int ilosc_sprzet(sprzet& ss, const vector<wypozyczenie>& wypozyczenia);

/// <summary>
/// Funkcja wypisująca klientów
/// </summary>
/// <param name="klienci">Wektor klientów</param>
void wypisz_klientow(vector<osoba>& klienci);

/// <summary>
/// Funkcja proponująca termin wypożyczenia. Najbardziej rozbudowana funkcja. Proponuje nowe daty wypozyczenia w przypadku
/// gdy nowa rezerwacja naklada sie z juz istniejaca rezerwacja.
/// </summary>
/// <param name="wypozyczenia">Wektor wypożyczeń</param>
/// <param name="podzial">Czy był podział</param>
/// <param name="byl_podzial">Liczba podziałów</param>
/// <param name="ile_wyp">Ilość wypożyczeń</param>
/// <param name="id_sprzetu">ID sprzętu</param>
/// <param name="wyp">Wypożyczenie</param>
/// <param name="ww1">Wypożyczenie 1</param>
/// <param name="ww2">Wypożyczenie 2</param>
/// <param name="ww3">Wypożyczenie 3</param>
void proponowanie_terminu(vector<wypozyczenie>& wypozyczenia, bool& podzial, int& byl_podzial, int ile_wyp, int id_sprzetu, wypozyczenie& wyp, wypozyczenie& ww1, wypozyczenie& ww2, wypozyczenie& ww3);

/// <summary>
/// Funkcja wyświetlająca informacje dla daty
/// </summary>
/// <param name="wypozyczenia">Wektor wypożyczeń</param>
/// <param name="wypozyczenie">Wypożyczenie</param>
void wys_dla_daty(vector<wypozyczenie>& wypozyczenia, wypozyczenie& wypozyczenie);

#endif // HEADER_H
