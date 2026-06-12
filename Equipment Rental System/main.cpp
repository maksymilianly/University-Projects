#include "funkcje.h"
#include <iostream>
#include <vector>
#include <string>
#include <memory>

using namespace std;

int main() {
    vector<osoba> klienci;
    vector<unique_ptr<sprzet>> sprzety;
    vector<wypozyczenie> wypozyczenia;
    odczyt_sprzet("baza_sprzetu.txt",sprzety);
    odczyt_klient("klienci.txt", klienci);
    odczyt_wyp("wypozyczenia.txt", wypozyczenia,klienci,sprzety);
    wylicz(wypozyczenia, klienci, sprzety);

    //sprzet_baza(sprzety);
    //dostep_sprzet(sprzety);
    interface(sprzety,wypozyczenia,klienci);
    //wyswietlanie_klient(klienci);
    //rezerwacja(sprzety, wypozyczenia, klienci);
    //wypozyczenia_tab(wypozyczenia, klienci);
    //wys_dla_urz(sprzety, wypozyczenia, klienci, 5);
    //wypisz_do_bazy(sprzety);

   
    
}
