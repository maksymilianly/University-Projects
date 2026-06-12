#include "funkcje.h"
#include "sprzet.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <memory>
#include <string>

using namespace std;
void naglowek(const char* tekst) {
    int szerokosc = 104;
    int tekstdl = static_cast<int>(strlen(tekst));
    int zapelnienie = ((szerokosc - 2 - tekstdl) / 2);

    cout << " " << string(szerokosc - 2, '-') << " " << endl;
    cout << "|";
    for (int i = 0; i < zapelnienie; i++) {
        cout << " ";
    }
    cout << tekst;
    if (tekstdl % 2 == 0) {
        for (int i = 0; i < zapelnienie; i++) {
            cout << " ";
        }
    }
    else {
        for (int i = 0; i < zapelnienie + 1; i++) {
            cout << " ";
        }
    }
    cout << "|" << endl;
    cout << " " << string(szerokosc - 2, '-') << " " << endl;
}
void tekst(const char* tekst) {
    cout << "| ";
    cout << tekst;
    cout << " |" << endl;
}

//sprzet z pliku
void odczyt_sprzet(const string& nazwa_pliku, vector<unique_ptr<sprzet>>& sprzety) {
    ifstream file(nazwa_pliku);

    if (!file) {
        cerr << "Blad otwarcia pliku" << endl;
        return;
    }

    string Urzadzenie;
    while (file >> Urzadzenie) {
        if (Urzadzenie == "Multimetr") {
            multimetr mltr;
            file >> mltr;
            mltr.id_spr = id_sprzet++;
            sprzety.push_back(make_unique<multimetr>(mltr));
        }
        else if (Urzadzenie == "Oscyloskop") {
            oscyloskop osck;
            file >> osck;
            osck.id_spr = id_sprzet++;
            sprzety.push_back(make_unique<oscyloskop>(osck));
        }
        else if (Urzadzenie == "Decybelomierz") {
            decybelomierz dcbl;
            file >> dcbl;
            dcbl.id_spr = id_sprzet++;
            sprzety.push_back(make_unique<decybelomierz>(dcbl));
        }
        else if (Urzadzenie == "Analizator") {
            analizator anl;
            file >> anl;
            anl.id_spr = id_sprzet++;
            sprzety.push_back(make_unique<analizator>(anl));
        }
    }
}
//klienci z pliku
void odczyt_klient(const string& nazwa_pliku, vector<osoba>& klienci) {
    ifstream file(nazwa_pliku);
    if (!file) {
        cerr << "Blad otwarcia pliku" << endl;
        return;
    }
    osoba klient;
    while (file >> klient) {
        klienci.push_back(klient);
    }



    file.close(); 
}
//wypozyczenia z pliku
void odczyt_wyp(const string& nazwa_pliku, vector<wypozyczenie>& wypozyczenia , vector<osoba>& klienci , vector<unique_ptr<sprzet>>& sprzety) {
    ifstream file(nazwa_pliku);
    if (!file ) {
        cerr << "Blad otwarcia pliku" << endl;
        return;
    }
    if (file.peek() == ifstream::traits_type::eof() == 1) {
        return;
    }

    wypozyczenie wyp;
    while (file >> wyp) 
    {
        for (auto& osoba : klienci)
        {
            if (wyp.imie == osoba.imie && wyp.nazwisko == osoba.nazwisko)
            {
                wyp.id = osoba.id;
            }
        }
        for (auto& ss : sprzety)
        {
            if (wyp.nazwa == (*ss).nazwa) {
                wyp.wypozyczenie_sprzet(*ss);
            }
        }
        wypozyczenia.push_back(wyp);
    }
}
//wylicza iloma osobami jest zajety sprzet i ile urzadzen wypozycza osoba
void wylicz(vector<wypozyczenie>& wypozyczenia, vector<osoba>& klienci, vector<unique_ptr<sprzet>>& sprzety)
{
    for (auto& osoba : klienci)
    {   
        osoba.osoba_ilosc = ilosc_osoba(osoba, wypozyczenia);
        for (auto& ww : wypozyczenia)
        {
            if (ww.imie == osoba.imie || ww.nazwisko == osoba.nazwisko)
            {
                ww.wypozyczenie_osoba(osoba);
            }
        }
        
    }
    for (auto& ss : sprzety)
    {
        ss->sprzet_ilosc = ilosc_sprzet(*ss, wypozyczenia);
        for (auto& ww : wypozyczenia)
        {
            if (ww.id_spr == ss->id_spr)
            {
                ww.wypozyczenie_sprzet(*ss);
            }
        }
    }
    
}
//glowna
void interface(vector<unique_ptr<sprzet>>& sprzety, vector<wypozyczenie>& wypozyczenia, vector<osoba>& klienci) {
    int choise;
    naglowek("Urzadzenia sa wypozyczane od 1 lipca 2024 (1.7.2024)");
    naglowek("Nie mozna wypozyczac urzadzenie w dzien jego oddania");
    naglowek("Osobny sprzet moze byc wypozyczony maksymalnie 3 razy");
    do
    {
        naglowek("Strona Glowna");
        tekst("Ktorego dzialania chcesz dokonac?");
        cout << "1" << " - " << "Sprzet w posiadaniu firmy" << endl;
        cout << "2" << " - " << "Dostepny sprzet" << endl;
        cout << "3" << " - " << "Tablica wypozyczen" << endl;
        cout << "4" << " - " << "Rezerwacja przyrzadu" << endl;
        cout << "5" << " - " << "Usuniecie rezerwacji przyrzadu" << endl;
        cout << "6" << " - " << "Wydruk zajetosci przyrzadu" << endl;
        cout << "7" << " - " << "Wydruk informacji o osobie" << endl;
        cout << "0" << " - " << "Zakoncz program" << endl;
        cin >> choise;

        while ((choise != (int)choise) or choise < 0 or choise > 7)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Nieprawidlowa odpowiedz, sprobuj jeszcze raz: " << endl;
            cin >> choise;
        }

        switch (choise)
        {
           case 1:
               sprzet_baza(sprzety);
               break;
           case 2:
               dostep_sprzet(sprzety);
               break;
           case 3:
               wypozyczenia_tab(sprzety,wypozyczenia,klienci);
               break;
           case 4:
               rezerwacja(sprzety, wypozyczenia, klienci);
               break;
           case 5:
               usuniecie_rezerwacji(sprzety, wypozyczenia, klienci);
               break;
           case 6:
               zapisz_sprzet(klienci,wypozyczenia,sprzety);
               break;
           case 7: 
               zapisz_osoba(klienci,wypozyczenia);
               break;

        }


    } while (choise != 0);
}
//caly sprzet
void sprzet_baza(vector<unique_ptr<sprzet>>& sprzety) {
    naglowek("Sprzet w posiadaniu firmy");


    for (const auto& ss : sprzety) {
       /*if (ss->co() == "Multimetr") {
            ss->wypisz();  
        }
        else if (ss->co() == "Oscyloskop") {
            ss->wypisz();  
        }
        else if (ss->co() == "Decybelomierz") {
            ss->wypisz();  
        }
        cout << endl;*/
        ss->wypisz();
        cout << endl;
    }
}
//dostepny dla wypozyczenia
void dostep_sprzet(vector<unique_ptr<sprzet>>& sprzety) {
    naglowek("Dostepny sprzet");
    for (const auto& ss : sprzety) {
        if (ss->sprzet_ilosc < 3) {
            ss->dostepny();
            cout << endl;
        }
        else
        {
            cout << ss->co() << " " << ss->nazwa << " " << "ma maksymalna ilosc wypozyczen!" << endl;
            cout << endl;
        }
    }
}
//wyswietla klientow
void wyswietlanie_klient(vector<osoba>& klienci) {
    naglowek("Klienci");
    for (auto& klient : klienci) {
        klient.wypisz();
    }
}

void rezerwacja(vector<unique_ptr<sprzet>>& sprzety, vector<wypozyczenie>& wypozyczenia, vector<osoba>& klienci) {
    osoba klient;
    wypozyczenie wyp;
    string odp;
    int jaki;

    if (!klienci.empty()) {
        cout << "Czy chcesz dodac nowego klienta? (Tak/Nie) : ";
        cin >> odp;

        while (odp != "Tak" && odp != "Nie") {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Nieprawidlowa odpowiedz, sprobuj jeszcze raz: ";
            cin >> odp;
        }

        if (odp == "Tak") {
            cout << "Podaj imie i nazwisko nowego klienta : ";
            cin >> klient.imie >> klient.nazwisko;

            bool istnieje = false;
            for (const auto& klient_ : klienci) {
                if (klient.imie == klient_.imie && klient.nazwisko == klient_.nazwisko) {
                    istnieje = true;
                    cout << "Taki klient juz istnieje!" << endl;
                    return;
                }
            }

            if (!istnieje) {
                klient.id = klienci.size() + 1;
              
                
            }
        }
        else {
            cout << "Wybierz klienta z listy (id) : ";
            wyswietlanie_klient(klienci);
            cin >> jaki;

            while (jaki < 1 || jaki > klienci.size()) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Nieprawidlowa odpowiedz, sprobuj jeszcze raz: ";
                cin >> jaki;
            }

            for (const auto& klient1 : klienci) {
                if (jaki == klient1.id) {
                    klient = klient1;
                    break;
                }
            }
        }
    }
    else {
        cout << "Podaj imie i nazwisko nowego klienta : ";
        cin >> klient.imie >> klient.nazwisko;
        klient.id = klienci.size() + 1;
        klienci.push_back(klient);
        cout << "Klient zostal dodany!" << endl;
    }

    wyp.wypozyczenie_osoba(klient);
    dostep_sprzet(sprzety);

    int sprz;
    int ile_wyp = 0;
    bool zero_wyp = false;
    tekst("Wybierz urzadzenie (ID): ");
    cin >> sprz;

    while (sprz < 1 || sprz > id_sprzet) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Nieprawidlowa odpowiedz, sprobuj jeszcze raz: ";
        cin >> sprz;
    }

    for (auto& ss : sprzety) {
        if (ss->id_spr == sprz) {
            if (ss->sprzet_ilosc == 3) {
                tekst("Dla danego urzadzenia osiagnieto limit wypozyczen!");
                return;
            }
            else if (ss->sprzet_ilosc == 0)
            {
                zero_wyp = true;
                wyp.wypozyczenie_sprzet(*ss);
            }
            else {
                ile_wyp = ss->sprzet_ilosc;
                wyp.wypozyczenie_sprzet(*ss);
            }
        }
    }

    tekst("Podaj date odbioru oraz powrotu urzadzenia (DD MM RRRR DD MM RRRR): ");
    cin >> wyp.dzien_s >> wyp.miesiac_s >> wyp.rok_s >> wyp.dzien_e >> wyp.miesiac_e >> wyp.rok_e;
    if (!wyp.czy_wieksza_data() || wyp.czy_lipiec()) {
        tekst("Wprowadzone terminy wypozyczenia sa bledne!");
        return;
    }

    wypozyczenie ww1, ww2, ww3, tmp1;
    bool podzial = false;
    int static byl_podzial = 0;
    if (!zero_wyp)
    {
        proponowanie_terminu(wypozyczenia, podzial, byl_podzial, ile_wyp, sprz, wyp, ww1,
            ww2, ww3);

        if (podzial && !byl_podzial) {
            tekst("Nie mozna wypozyczyc sprzetu w takim terminie!");
            tekst("Proponowane rezerwacje to: ");
            ww1.wypisz();
            ww2.wypisz();

            do {
                cout << "Czy chcesz dokonac rezerwacji w jednym z tych terminow? (Tak/Nie): ";
                cin >> odp;
            } while (odp != "Tak" && odp != "Nie");

            if (odp == "Tak") {
                int wybor;
                tekst("Która opcja jest bardziej dogodna?");
                cin >> wybor;

                while (cin.fail() || wybor < 1 || wybor > 2) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Nieprawidlowa odpowiedz, sprobuj jeszcze raz: ";
                    cin >> wybor;
                }

                switch (wybor) {
                case 1:
                    wyp = ww1;
                    break;
                case 2:
                    wyp = ww2;
                    break;
                }

                for (auto& ss : sprzety) {
                    if (sprz == ss->id_spr) {
                        ss->sprzet_ilosc += 1;
                        wyp.wypozyczenie_osoba(klient);
                        wyp.wypozyczenie_sprzet(*ss);
                    }
                }
                wypozyczenia.push_back(wyp);
                tekst("Nowa rezerwacja zostala pomyslnie dodana!");
                wyp.wypisz();

                wypisz_do_bazy(sprzety);
                wypisz_klientow(klienci);
                wypisz_wypozyczenia(wypozyczenia);
                for (auto& kk : klienci)
                {
                    if (kk.id == klient.id)
                    {
                        return;
                    }
                }
                klienci.push_back(klient);
                return;
            }
            else {
                tekst("Niestety nie dokonales rezerwacji");
                return;
            }

        }
        else if (podzial && byl_podzial == 1)
        {
            tekst("Nie mozna wypozyczyc sprzetu w takim terminie!");
            tekst("Proponowane rezerwacje to: ");
            ww1.wypisz();
            ww2.wypisz();
            ww3.wypisz();

            do {
                cout << "Czy chcesz dokonac rezerwacji w jednym z tych terminow? (Tak/Nie): ";
                cin >> odp;
            } while (odp != "Tak" && odp != "Nie");

            if (odp == "Tak") {
                int wybor;
                tekst("Która opcja jest bardziej dogodna?");
                cin >> wybor;

                while (cin.fail() || wybor < 1 || wybor > 3) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Nieprawidlowa odpowiedz, sprobuj jeszcze raz: ";
                    cin >> wybor;
                }

                switch (wybor) {
                case 1:
                    wyp = ww1;
                    break;
                case 2:
                    wyp = ww2;
                    break;

                case 3:
                    wyp = ww3;
                    break;
                }

                for (auto& ss : sprzety) {
                    if (sprz == ss->id_spr) {
                        ss->sprzet_ilosc += 1;
                        wyp.wypozyczenie_osoba(klient);
                        wyp.wypozyczenie_sprzet(*ss);
                    }
                }
                wypozyczenia.push_back(wyp);
                tekst("Nowa rezerwacja zostala pomyslnie dodana!");
                wyp.wypisz();
                wypisz_do_bazy(sprzety);
                wypisz_klientow(klienci);
                wypisz_wypozyczenia(wypozyczenia);
                for (auto& kk : klienci)
                {
                    if (kk.id == klient.id)
                    {
                        return;
                    }
                }
                klienci.push_back(klient);
                return;
            }
            else {
                tekst("Niestety nie dokonales rezerwacji");
                return;
            }

        }
        
    }

       tekst("Proponowana rezerwacja to: ");
        wyp.wypisz();
        
    
        do {
            cout << "Czy potwierdzasz proponowana rezerwacje? (Tak/Nie): ";
            cin >> odp;
        } while (odp != "Tak" && odp != "Nie");

        if (odp == "Nie") {
            return;
        }

        for (auto& ss : sprzety) {
            if (sprz == ss->id_spr) {
                ss->sprzet_ilosc += 1;
                wyp.wypozyczenie_osoba(klient);
                wyp.wypozyczenie_sprzet(*ss);
            }
        }
        wypozyczenia.push_back(wyp);
        tekst("Nowa rezerwacja zostala pomyslnie dodana!");
        wyp.wypisz();
        wypisz_do_bazy(sprzety);
        wypisz_klientow(klienci);
        wypisz_wypozyczenia(wypozyczenia);
        for (auto& kk : klienci)
        {
            if (kk.id == klient.id)
            {
                return;
            }
        }
        klienci.push_back(klient);
        return;
}
    

void usuniecie_rezerwacji(vector<unique_ptr<sprzet>>& sprzety, vector<wypozyczenie>& wypozyczenia, vector<osoba>& klienci) {
    osoba klient;
    wypozyczenie wyp;
    string odp;
    int jaki;

    wyswietlanie_klient(klienci);
    tekst("Podaj id klienta wypozyczenie ktorego chcesz usunac");
    cin >> jaki;
    while (jaki < 1 || jaki > klienci.size()) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Nieprawidlowa odpowiedz, sprobuj jeszcze raz: ";
        cin >> jaki;
    }

   
    klient = klienci[jaki - 1];

    wys_dla_osoby(jaki,klienci,wypozyczenia,sprzety);

    int sprz;
    tekst("Wybierz urzadzenie (ID): ");
    cin >> sprz;

    while (sprz < 1 || sprz > id_sprzet) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Nieprawidlowa odpowiedz, sprobuj jeszcze raz: ";
        cin >> sprz;
    }

    
    for (auto& ww : wypozyczenia) {
        if (ww.id == klient.id && ww.id_spr == sprz) {
            wyp = ww;
        }
    }

    tekst("Czy na pewno chcesz usunac podane wypozyczenie?");
    wyp.wypisz();

    cin >> odp;
    while (odp != "Tak" && odp != "Nie") {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Nieprawidlowa odpowiedz, sprobuj jeszcze raz: ";
        cin >> odp;
    }

    if (odp == "Tak") {
       
        wypozyczenia.erase(remove_if(wypozyczenia.begin(), wypozyczenia.end(),
            [&klient, sprz](const wypozyczenie& ww) {
                return ww.id == klient.id && ww.id_spr == sprz;
            }),
            wypozyczenia.end());

        
        for (auto& ss : sprzety)
        {
            if (ss->id_spr == sprz)
            {
                ss->sprzet_ilosc -= 1;
            }
        }

        klient.osoba_ilosc -= 1;
        if (klient.osoba_ilosc == 0)
        {
            klienci.erase(remove_if(klienci.begin(), klienci.end(),
                [&klient](const osoba& k) {
                    return k.id == klient.id;
                }),
                klienci.end());
            cout << "Z powodu braku wypozyczen klient "; 
            klient.wyp_bez_id(); 
            cout << " zostal usuniety!";
        }

        tekst("Wypozyczenie zostalo pomyslne usuniete!");
    }
    else {
        return;
    }
    int id_klient = 1;
    for (auto& kk : klienci)
    {
        kk.id += id_klient;
    }
    wypisz_do_bazy(sprzety);
    wypisz_klientow(klienci);
    wypisz_wypozyczenia(wypozyczenia);
}
//tablica wypozyczen    
void wypozyczenia_tab(vector<unique_ptr<sprzet>>& sprzety, vector<wypozyczenie>& wypozyczenia, vector<osoba>& klienci)
{
    tekst("Wedlug czego chesz wyswitlic tablice?");
    tekst("1 - Osoby");
    tekst("2 - Urzadzenia");
    tekst("3 - Daty");
    tekst("4 - Wszystkie wypozyczenia");
    int choise;
    cin >> choise;
    while ((choise != (int)choise) or choise < 1 or choise > 4)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Nieprawidlowa odpowiedz, sprobuj jeszcze raz: " << endl;
        cin >> choise;
    }

    switch (choise)
    {
    case 1:
    {

        tekst("Wypozyczenia ktorego klienta chcesz wyswietlic?(ID)");
        wyswietlanie_klient(klienci);
        int jaki;
        cin >> jaki;

        while (jaki < 1 || jaki > klienci.size()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Nieprawidlowa odpowiedz, sprobuj jeszcze raz: " << std::endl;
            cin >> jaki;
        }

        wys_dla_osoby(jaki,klienci, wypozyczenia,sprzety);
        break;
    }
    case 2:
    {
        sprzet_baza(sprzety);
        tekst("Status jakiego urzadzenia chcesz wyswietlic?(ID)");
        int jaki;
        cin >> jaki;
        while (jaki < 1 || jaki > id_sprzet) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Nieprawidlowa odpowiedz, sprobuj jeszcze raz: " << std::endl;
            cin >> jaki;
        }
        wys_dla_urz(sprzety,wypozyczenia,klienci,jaki);
        break;
    }
    case 3:
    { 
        wypozyczenie wyp;
        tekst("Podaj granice w ktorych chcesz zobaczyc wypozyczenia: ");
        cin >> wyp.dzien_s >> wyp.miesiac_s >> wyp.rok_s >> wyp.dzien_e >> wyp.miesiac_e >> wyp.rok_e;
        if (!wyp.czy_wieksza_data() || wyp.czy_lipiec()) {
            tekst("Wprowadzone terminy wypozyczenia sa bledne!");
            return;
        }
        wys_dla_daty(wypozyczenia , wyp);
        break;
    }
    case 4:
    {
        for (auto& ww : wypozyczenia)
        {
            ww.wypisz();
        }
        break;
    }
    }

}
//wypozyczenia wedlug osoby
void wys_dla_osoby(int jaki,vector<osoba>& klienci,vector<wypozyczenie>& wypozyczenia, vector<unique_ptr<sprzet>>& sprzety) {
        wypozyczenie ww;
        naglowek("Wyswietlenie dla osoby");
        for (auto& kk : klienci)
        {
            if (kk.id == jaki)
            {
                kk.wyp_bez_id();
            }
        }
        for (const auto& ww : wypozyczenia) {
            if (ww.id == jaki) {
                       
                ww.wypisz_dla_klienta();
                        
                        
                   
            }
        }

}
//wydruk osoby
void zapisz_osoba(vector<osoba>& klienci, vector<wypozyczenie>& wypozyczenia){
    tekst("Wypozyczenia ktorego klienta chcesz wydrukowac?(ID)");
    wyswietlanie_klient(klienci);
    int jaki;
    cin >> jaki;
    osoba kl;
    while (jaki < 1 || jaki > klienci.size()) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Nieprawidlowa odpowiedz, sprobuj jeszcze raz: " << std::endl;
        cin >> jaki;
    }
    ofstream plik("osoba.txt");
    if (!plik.is_open()) {
        cout << "Nie udalo sie otworzyc pliku osoba.txt" << endl;
        return;
    }
    for (auto& ww : wypozyczenia)
    {
        if (ww.id == jaki)
        {
            plik << ww;
        }
    }
    plik.close();
}
//wypozyczenia wedlug urzadzenia
void wys_dla_urz(vector<unique_ptr<sprzet>>& sprzety, vector<wypozyczenie>& wypozyczenia, vector<osoba>& klienci, int jaki) {
    for (const auto& ss : sprzety) {
        if (ss->id_spr == jaki) {
            if (ss->sprzet_ilosc == 0) {
                cout << "Dany " << ss->co() << " nie jest wypozyczony" << endl;
            }
            else {
                cout << "|" << ss->co() << "|" << endl;
                for (const auto& ww : wypozyczenia) {
                    if (ww.id_spr == jaki) {
                        ww.wypisz_dla_spr();
                    }
                }
            }
            return;
        }
    }
} 
//wydruk sprzet
void zapisz_sprzet(vector<osoba>& klienci, vector<wypozyczenie>& wypozyczenia, vector<unique_ptr<sprzet>>& sprzety){
    sprzet_baza(sprzety);
    tekst("Status jakiego urzadzenia chcesz wydrukowac?(ID)");
    int jaki;
    cin >> jaki;
    while (jaki < 1 || jaki > id_sprzet) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Nieprawidlowa odpowiedz, sprobuj jeszcze raz: " << std::endl;
        cin >> jaki;
    }
    ofstream plik("przyrzad.txt");
    if (!plik.is_open()) {
        cout << "Nie udalo sie otworzyc pliku przyrzad.txt" << endl;
        return;
    }
    
    for (auto& ss : sprzety) {
        if (ss->id_spr == jaki) 
        {
            if (ss->sprzet_ilosc == 0) 
            {
                cout << "Dany " << ss->co() << " nie jest wypozyczony" << endl;
            }
            else 
            {
                for (auto& ww : wypozyczenia) 
                {
                    if (ww.id_spr == jaki) 
                    {
                        plik << ww;
                        tekst("Dane przyrzadu zostaly wydrukowane!");
                    }
                }
            }
            return;
        }
    }
    plik.close();
}
//zapisuje sprzet z wektora
void wypisz_do_bazy(const vector<unique_ptr<sprzet>>& sprzety) {
    ofstream plik("baza_sprzetu.txt");
    if (!plik.is_open()) {
        cout << "Nie udalo sie otworzyc pliku baza_sprzetu.txt" << std::endl;
        return;
    }
    for (auto& ss : sprzety)
    {
        ss->wypisz_do_pliku(plik);
    }

    plik.close();
}
//zapisuje klientow w plik
void wypisz_klientow(vector<osoba>& klienci)
{
    ofstream plik("klienci.txt");
    if (!plik.is_open()) {
        cout << "Nie udalo sie otworzyc pliku " << "klienci.txt" << endl;
        return;
    }
    for (auto& klient : klienci)
    {
        plik << klient;
    }
    plik.close();
}
//zapisuje wypozyczenie w plik
void wypisz_wypozyczenia(vector<wypozyczenie>& wypozyczenia) {
    ofstream plik("wypozyczenia.txt");
    if (!plik.is_open()) {
        cout << "Nie udalo sie otworzyc pliku " << "wypozyczenia.txt" << endl;
        return;
    }
    for (auto& wypy : wypozyczenia)
    {
        plik << wypy;
    }
    plik.close();
}

int ilosc_osoba(osoba& kk,const vector<wypozyczenie>& wypozyczenia) {
        int ilosc = 0;
        for (const auto& ww : wypozyczenia) {
            if (ww.id == kk.id) {
                ilosc++;
            }
        }
        return ilosc; 
    }

int ilosc_sprzet(sprzet& ss, const vector<wypozyczenie>& wypozyczenia) {
    int ilosc = 0;
    for (const auto& ww : wypozyczenia) {
        if (ww.id_spr == ss.id_spr) {
            ilosc++;
        }
    }
    return ilosc;

}

void proponowanie_terminu(vector<wypozyczenie>& wypozyczenia, bool& podzial, int& byl_podzial, int const ile_wyp, int id_sprzetu,
    wypozyczenie& wyp, wypozyczenie& ww1, wypozyczenie& ww2, wypozyczenie& ww3)
{
    
    if (ile_wyp < 2)
    {
        for (auto& ww : wypozyczenia) {
            if (ww.id_spr == id_sprzetu)
                if (!wyp.czy_wieksza_data()) {
                    continue;
                }
                else if (!ww.czy_nakladanie_koniec_pocz(wyp)) {
                    continue;
                }
                else if (wyp.czy_rowna_data_e(ww) && wyp.czy_rowna_data_s(ww)) {
                    tekst("Nie da sie wypozyczyc sprzetu w takim terminie!");
                    return;
                }
                else if (wyp.czy_koncowa_wieksza_koncowa(ww) && wyp.czy_rowna_data_s(ww)) {
                    podzial = false;
                    ww.proponowanie_daty_pocz(wyp);
                    wyp.dodanie_jednego_dnia_s();
                }
                else if (wyp.czy_poczatkowa_wieksza_poczatkowa(ww) && wyp.czy_rowna_data_e(ww)) {
                    tekst("Nie da sie wypozyczyc sprzetu w takim terminie!");
                    return;
                }
                else if (!wyp.czy_poczatkowa_wieksza_poczatkowa(ww) && wyp.czy_rowna_data_e(ww)) {
                    if (podzial == true)
                    {
                        podzial = false;
                        wyp = ww1;
                    }
                    else {
                        ww.proponowanie_daty_pocz(wyp);
                        wyp.odejm_jednego_dnia_e();
                    }
                }
                else if (wyp.czy_koncowa_wieksza_koncowa(ww) && !wyp.czy_poczatkowa_wieksza_poczatkowa(ww)) {
                    podzial = true;
 
                    ww1 = wyp;
                    ww.proponowanie_daty_konc(ww1);
                    ww1.odejm_jednego_dnia_e();
                    ww2 = wyp;
                    ww.proponowanie_daty_pocz(ww2);
                    ww2.dodanie_jednego_dnia_s();
                }
                else if (!wyp.czy_koncowa_wieksza_koncowa(ww) && !wyp.czy_poczatkowa_wieksza_poczatkowa(ww)) {
                    podzial = true;
             
                    ww1 = wyp;
                    ww1.koncowa_rowna_pocz(ww);
                    ww1.odejm_jednego_dnia_e();
                    ww2 = wyp;
                    ww2.poczatkowa_rowna_konc(ww);
                    ww2.dodanie_jednego_dnia_s();
                }
                else if (wyp.czy_koncowa_wieksza_koncowa(ww) && wyp.czy_poczatkowa_wieksza_poczatkowa(ww)) {
                    podzial = false;
                    ww.proponowanie_daty_pocz(wyp);
                    wyp.dodanie_jednego_dnia_s();
                }
                else if (!wyp.czy_koncowa_wieksza_koncowa(ww) && !wyp.czy_poczatkowa_wieksza_poczatkowa(ww)) {
                    podzial = false;
                }
                else if (!wyp.czy_koncowa_wieksza_koncowa(ww) && wyp.czy_poczatkowa_wieksza_poczatkowa(ww)) {
                    tekst("Nie da sie wypozyczyc sprzetu w takim terminie!");
                    return;
                }
        }
    }
    else if (ile_wyp == 2)
    {
        bool pd = false;
        wypozyczenie tmp, tmp1;
        for (auto& ww : wypozyczenia) {
            if (ww.id_spr == id_sprzetu)
            {
                if (!pd)
                {
                    tmp = ww;
                    pd = true;
                }
                if (pd)
                {
                    tmp1 = ww;
                }
            }
        }
        if (wyp.czy_koncowa_wieksza_koncowa(tmp) && wyp.czy_koncowa_wieksza_koncowa(tmp1))
        {
            if (tmp.czy_koncowa_wieksza_koncowa(tmp1))
            {
                podzial = true;
                byl_podzial = 1;
                ww1 = wyp;
                tmp1.proponowanie_daty_konc(ww1);
                ww1.odejm_jednego_dnia_e();


                ww3 = wyp;
                tmp1.proponowanie_daty_pocz(ww3);
                ww3.dodanie_jednego_dnia_s();
                tmp.proponowanie_daty_konc(ww3);
                ww3.odejm_jednego_dnia_e();
                if (ww3.czy_wieksza_data())
                {
                    byl_podzial = 1;
                }

                ww2 = wyp;
                ww2.poczatkowa_rowna_konc(tmp);
                ww2.dodanie_jednego_dnia_s();
            }
            else
            {
                podzial = true;
                byl_podzial = 0;
                ww1 = wyp;
                tmp.proponowanie_daty_konc(ww1);
                ww1.odejm_jednego_dnia_e();


                ww3 = wyp;
                tmp.proponowanie_daty_pocz(ww3);
                ww3.dodanie_jednego_dnia_s();
                tmp1.proponowanie_daty_konc(ww3);
                ww3.odejm_jednego_dnia_e();
                if (ww3.czy_wieksza_data())
                {
                    byl_podzial = 0;
                }

                ww2 = wyp;
                ww2.poczatkowa_rowna_konc(tmp1);
                ww2.dodanie_jednego_dnia_s();
            }

        }
        else { (proponowanie_terminu(wypozyczenia, podzial, byl_podzial, 1 , id_sprzetu, wyp, ww1, ww2, ww3)); }
        
    }
}


void wys_dla_daty(vector<wypozyczenie>& wypozyczenia, wypozyczenie& wyp)
{
    for (auto& ww : wypozyczenia)
    {
        if(wyp.czy_rowna_data_e(ww) && wyp.czy_rowna_data_s(ww)) {
            ww.wypisz();
                }
        else if (wyp.czy_koncowa_wieksza_koncowa(ww) && !wyp.czy_poczatkowa_wieksza_poczatkowa(ww))
        {
            ww.wypisz();
        }
        else if (wyp.czy_koncowa_wieksza_koncowa(ww) && wyp.czy_rowna_data_s(ww)) {
            ww.wypisz();
        }
        else if (!wyp.czy_poczatkowa_wieksza_poczatkowa(ww) && wyp.czy_rowna_data_e(ww)) {
            ww.wypisz();
        }
    }
}
    











