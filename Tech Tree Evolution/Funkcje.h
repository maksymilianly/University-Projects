#ifndef FUNKCJE_H
#define FUNKCJE_H

#include <string>
#include "Szablonhistoryczny.h"
#include "Funkcje.h"


using namespace std;

struct DaneLinii {
    string calaLinia;
    string nazwa;
    string ojciec;
    bool czyZapisany;
};

static void uruchomhelp() {
    cout << "--- INFORMACJA OGOLNA PROGRAMU---" << endl;
    cout << "--- MOZLIWOSCI PROGRAMU ---" << endl;
    cout << "[1] Struktury:     Drzewo n-binarne oparte na wskaznikach (unique_ptr) oraz lista (tablica dynamiczna) dla umozliwienia sortowania danych." << endl;
    cout << "[2] Dane:          Obsluga Dynastii oraz Technologii (Szablony) lub jakiejkolwiek klasy na zasadzie przechowywania LCRS(Left child right siblings)." << endl;
    cout << "[3] Pliki:         Import/Eksport tekstowy (.txt) oraz BINARNY (.bin, zapisuje aktualny stan programu w bin)." << endl;
    cout << "[4] Edycja:        Pelna edycja wezlow i naprawa blednych zapisow(Dodawanie , usuwanie , edycja)." << endl;
    cout << "[5] Zaawansowane:  Przenoszenie calych galezi (Metoda Wytnij-Wklej)" << endl;
    cout << "                   z zachowaniem potomstwa i struktury." << endl;
    cout << "---------------------------" << endl;
    cout << "--- GLOWNE ZASADY PROGRAMU ---" << endl;
    cout << "[1] Idealnym ukladem danych wejsciowych jest struktura 'najpierw wszystkie ojcowie potem dzieci'" << endl;
    cout << "[2] Na poczatku program zaproponuje istniejacy SAVE, w przeciwnym przypadku naprawi plik zgodnie ze struktura w p.[1]'" << endl;
    cout << "[3] Nastepnie uzytkownik moze wybrac na jakim pliku operowac(surowym lub tym naprawionym)'" << endl;
    cout << "[4] Zeby program poprawnie wyswietlal drzewko musi pobrac dane o ojcu dokladnie na 5 pozycji danych w linii'" << endl;
    cout << "[5] Wagi w klasie dynastii sa wykorzystywane dla identyfikacji krola (1 - Krol , 0 - Nie)" << endl;
    cout << "---------------------------" << endl;

    cout << "\n[Nacisnij ENTER, aby wrocic do menu...]";


    if (cin.peek() == '\n') cin.ignore();
    cin.get();
}

bool naprawPlik(string plikWejsciowy, string plikWyjsciowy) {
    ifstream wej(plikWejsciowy);
    if (!wej.is_open()) {
        cout << "Blad: Nie mozna otworzyc pliku: " << plikWejsciowy << endl;
        return false;
    }
    int liczbaLinii = 0;
    string liniaPomocnicza;
    while (getline(wej, liniaPomocnicza)) {
        if (!liniaPomocnicza.empty()) liczbaLinii++;
    }

    wej.clear();
    wej.seekg(0);

    if (liczbaLinii == 0) { wej.close(); return false; }
    DaneLinii* tablica = new DaneLinii[liczbaLinii];
    int index = 0;
    while (getline(wej, liniaPomocnicza)) {
        if (liniaPomocnicza.empty()) continue;

        tablica[index].calaLinia = liniaPomocnicza;
        tablica[index].czyZapisany = false;

        stringstream ss(liniaPomocnicza);
        string segment;
        getline(ss, tablica[index].nazwa, ';');
        getline(ss, segment, ';');
        getline(ss, segment, ';');
        getline(ss, segment, ';');
        getline(ss, tablica[index].ojciec, ';');
        while (!tablica[index].nazwa.empty() && isspace((unsigned char)tablica[index].nazwa.back())) {
            tablica[index].nazwa.pop_back();
        }

        while (!tablica[index].ojciec.empty() && isspace((unsigned char)tablica[index].ojciec.back())) {
            tablica[index].ojciec.pop_back();
        }
        if (tablica[index].ojciec.empty()) tablica[index].ojciec = "BRAK";

        index++;
    }
    wej.close();
    string* buforWynikowy = new string[liczbaLinii];
    int licznikWynikowy = 0;
    int iloscZapisanych = 0;
    bool postepWTejTurze = true;

    while (postepWTejTurze && iloscZapisanych < liczbaLinii) {
        postepWTejTurze = false;
        for (int i = 0; i < liczbaLinii; i++) {
            if (tablica[i].czyZapisany) continue;

            bool moznaZapisac = false;
            if (tablica[i].ojciec == "BRAK" || tablica[i].ojciec == "ROOT" || tablica[i].ojciec == "-" || tablica[i].ojciec == "Start") {
                moznaZapisac = true;
            }
            else {
                for (int j = 0; j < liczbaLinii; j++) {
                    if (tablica[j].nazwa == tablica[i].ojciec && tablica[j].czyZapisany) {
                        moznaZapisac = true;
                        break;
                    }
                }
            }

            if (moznaZapisac) {
                buforWynikowy[licznikWynikowy] = tablica[i].calaLinia;
                licznikWynikowy++;
                tablica[i].czyZapisany = true;
                iloscZapisanych++;
                postepWTejTurze = true;
            }
        }
    }
    if (iloscZapisanych < liczbaLinii) {
        for (int i = 0; i < liczbaLinii; i++) {
            if (!tablica[i].czyZapisany) {
                buforWynikowy[licznikWynikowy] = tablica[i].calaLinia;
                licznikWynikowy++;
            }
        }
    }
    ofstream wyj(plikWyjsciowy);
    if (wyj.is_open()) {
        for (int i = 0; i < liczbaLinii; i++) {
            wyj << buforWynikowy[i] << endl;
        }
        wyj.close();
        cout << "-> Utworzono naprawiony plik: " << plikWyjsciowy << endl;
    }

    delete[] tablica;
    delete[] buforWynikowy;

    return true;
}

void wyswietlMenu() {
    cout << "\n=== MENU GLOWNE ===" << endl;
    cout << "1. Edytuj dane elementu (Zmien rok, nazwe, opis)" << endl;
    cout << "2. Dodaj element recznie" << endl;
    cout << "3. Usun element" << endl;
    cout << "4. Wyszukaj element" << endl;
    cout << "5. Wyswietlanie" << endl;
    cout << "6. Zapisz save" << endl;
    cout << "7. Wczytaj ostatni save" << endl;
    cout << "8. Zmien Kategorie/Dynastie" << endl;
    cout << "9. Informacja Glowna" << endl;
    cout << "0. Wyjscie" << endl;
    cout << "Wybor: ";
}

template <typename T>
void uruchomProgram(string domyslnyPlik) {
    string bazaNazwy = domyslnyPlik;
    size_t kropka = bazaNazwy.find_last_of(".");
    if (kropka != string::npos) {
        bazaNazwy = bazaNazwy.substr(0, kropka);
    }

    string bin_surowy = bazaNazwy + ".bin";          
    string bin_fixed = bazaNazwy + "_fixed.bin";   
    string txt_fixed = bazaNazwy + "_fixed.txt";    

    Szablonhistoryczny<T> drzewo;

    cout << "--- START: " << domyslnyPlik << " ---" << endl;

    bool wczytanoDanych = false;
   
    string nazwa_zapisu_bin = bin_surowy;

    
    bool jestSur = false;
    bool jestFix = false;

    { ifstream f(bin_surowy); if (f.good()) jestSur = true; }
    { ifstream f(bin_fixed);  if (f.good()) jestFix = true; }

    string wybranyBin = "";

    if (jestSur && jestFix) {
        cout << "\n[!] Znaleziono DWA pliki zapisu binarnego:" << endl;
        cout << "1. " << bin_surowy << " (Zapis oryginalny)" << endl;
        cout << "2. " << bin_fixed << " (Zapis wersji naprawionej)" << endl;
        cout << "0. Pomin (Wczytaj z pliku tekstowego)" << endl;
        cout << "Wybor: ";
        int dec;
        cin >> dec;
        if (cin.peek() == '\n') cin.ignore();

        if (dec == 1) wybranyBin = bin_surowy;
        else if (dec == 2) wybranyBin = bin_fixed;
    }
    
    else if (jestSur) {
        cout << "\n[!] Znaleziono zapis: " << bin_surowy << endl;
        cout << "Wczytac? (t/n): ";
        char c; cin >> c; if (cin.peek() == '\n') cin.ignore();
        if (c == 't' || c == 'T') wybranyBin = bin_surowy;
    }
    
    else if (jestFix) {
        cout << "\n[!] Znaleziono zapis: " << bin_fixed << endl;
        cout << "Wczytac? (t/n): ";
        char c; cin >> c; if (cin.peek() == '\n') cin.ignore();
        if (c == 't' || c == 'T') wybranyBin = bin_fixed;
    }


    if (!wybranyBin.empty()) {
        cout << "-> Wczytuje binarnie: " << wybranyBin << "..." << endl;
        drzewo.wczytajbinarnie(wybranyBin);
        wczytanoDanych = true;
        nazwa_zapisu_bin = wybranyBin; 
    }

    
    if (!wczytanoDanych) {
        bool jestroznica = naprawPlik(domyslnyPlik, txt_fixed);

        if (!jestroznica) {
            cout << "-> Plik tekstowy poprawny. Wczytuje oryginal: " << domyslnyPlik << endl;
            drzewo.wczytajzPliku(domyslnyPlik);
            nazwa_zapisu_bin = bin_surowy; 
        }
        else {
            cout << "\n[?] Wykryto bledy w kolejnosci pliku tekstowego." << endl;
            cout << "1. Wczytaj NAPRAWIONY plik (Zalecane - " << txt_fixed << ")" << endl;
            cout << "2. Wczytaj ORYGINALNY plik (Ryzyko utraty danych - " << domyslnyPlik << ")" << endl;
            cout << "Wybor (1/2): ";

            char wyborPliku;
            cin >> wyborPliku;
            if (cin.peek() == '\n') cin.ignore();

            if (wyborPliku == '2') {
                cout << "-> Wczytuje plik SUROWY: " << domyslnyPlik << endl;
                drzewo.wczytajzPliku(domyslnyPlik);
                nazwa_zapisu_bin = bin_surowy; 
            }
            else {
                cout << "-> Wczytuje plik NAPRAWIONY: " << txt_fixed << endl;
                drzewo.wczytajzPliku(txt_fixed);
                nazwa_zapisu_bin = bin_fixed; 
            }
        }
    }

    bool running = true;
    int wybor;

    while (running) {
        wyswietlMenu();
        if (!(cin >> wybor)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Niepoprawny wybor!" << endl;
            continue;
        }
        cin.ignore();

        switch (wybor) {
        case 1: {
            string cel;
            cout << "\n--- EDYCJA DANYCH ---" << endl;
            cout << "Podaj nazwe elementu do edycji: ";
            getline(cin, cel);

            T* obiekt = drzewo.pobierzWskaznik(cel);

            if (obiekt != nullptr) {
                string zadanie = obiekt->edytujInteraktywnie();
                obiekt->edytujInteraktywnie();
                if (zadanie != "") {
                    cout << "\nWykryto zmiane dynastii/kategorii." << endl;
                    drzewo.zmienKategorieMetodaWytnijWklej(cel, zadanie);
                }
                else {
                    cout << "\nDane zaktualizowane" << endl;
                }
            }
            break;
        }

        case 2: {
            string n, k, o , op;
            int r; double w;
            cout << "Nazwa / Imie: "; getline(cin, n);
            cout << "Rok: "; cin >> r;
            cout << "Kategoria / Rola: "; cin.ignore(); getline(cin, k);
            cout << "Waga / Potega (1-10): "; cin >> w; cin.ignore();
            cout << "Rodzic (BRAK dla korzenia): "; getline(cin, o);

            while (!o.empty() && isspace(o.back())) o.pop_back();

            T nowa(n, r, k, w, op);

            if (o == "BRAK" || o == "ROOT" || o == "" || o == "-") {
                drzewo.dodajKorzen(nowa);
                cout << "Dodano jako korzen." << endl;
            }
            else {
                if (drzewo.dodajDziecko(o, nowa)) {
                    cout << "Dodano sukcesywnie jako dziecko " << o << "." << endl;
                }
                else {
                    cout << "BLAD: Nie znaleziono ojca o nazwie: [" << o << "]" << endl;
                }
            }
            break;
        }
        case 3: {
            string cel;
            cout << "Podaj nazwe elementu do usuniecia: ";
            getline(cin, cel);
            if (drzewo.usun(cel)) {
                cout << "Usunieto." << endl;
            }
            else {
                cout << "Element nie znaleziono lub odwolano usuwanie " << endl;
            }
            break;
        }
        case 4: {
            string cel;
            cout << "Szukaj: "; getline(cin, cel);
            drzewo.szukaj(cel);
            break;
        }

 //ile lat od technologii
 //co wynaleziono po tranzystorze
 //ktotkie definicje ala word net co to np tranzystor 
 //krotki wyszukiwanie po slowach
        case 5: {
            int podWybor;
            cout << "\n   --- MENU WYSWIETLANIA ---" << endl;
            cout << "   1. Drzewo (Hierarchia)" << endl;
            cout << "   2. Lista (Sort: Nazwa)" << endl;
            cout << "   3. Lista (Sort: Rok)" << endl;
            cout << "   4. Lista (Sort: Waga)" << endl;
            cout << "   5. Odleglosc technologii(lat) oraz droga" << endl;
            cout << "   6. Co wynazeliono po" << endl;
            cout << "   7. Definicja technologii" << endl;
            cout << "   8. Wyszukaj technologie to opisie" << endl;
            cout << "   0. Wroc" << endl;
            cout << "   Wybor: ";
            cin >> podWybor;

            switch (podWybor) {
            case 1: drzewo.wyswietlDrzewo(); break;
            case 2: drzewo.zbudujListe(); drzewo.sortujListe(1); drzewo.wyswietlListe(); break;
            case 3: drzewo.zbudujListe(); drzewo.sortujListe(2); drzewo.wyswietlListe(); break;
            case 4: drzewo.zbudujListe(); drzewo.sortujListe(3); drzewo.wyswietlListe(); break;
            case 5: {
                cin.ignore();
                string cel;
                cout << "Podaj nazwe technologii wzgledem ktorej szukamy odleglosc w czasie: ";
                getline(cin, cel);
                T* obiekt1 = drzewo.pobierzWskaznik(cel);
                if (obiekt1 == nullptr) {
                    cout << "Nie znaleziono Podanej technologii" << endl;
                }
                else {
                    cout << "Podaj nazwe technologii do ktorej liczymy: ";
                    getline(cin, cel);
                    T* obiekt2 = drzewo.pobierzWskaznik(cel);
                    if (obiekt2 == nullptr) {
                        cout << "Nie znaleziono Podanej technologii" << endl;
                    }
                    if (drzewo.porownajDaty(obiekt1, obiekt2)) { cout << "Podales ta sama technologie 2 razy" << endl; break; }
                    else {
                        int odl = abs(obiekt1->getRok() - obiekt2->getRok());
                        cout << "odleglosc technologii: " << obiekt1->getNazwa() << " " << "od technologii: " << obiekt2->getNazwa() << " " << "wynosi: " << odl << endl;
                        drzewo.wskazdroge(obiekt1->getNazwa(), obiekt2->getNazwa());
                    }
                }
                break;
            }
            case 6: {
                cin.ignore();
                string cel;
                int typ;
                cout << "Podaj nazwe technologii wzgledem ktorej stworzymy drzewo technologii ponzniejszych od niej: ";
                getline(cin, cel);
                if (drzewo.pobierzWskaznik(cel) == nullptr) {
                    cout << "[BLAD]Nie znaleziono obiektu" << endl;
                    return;
                }
                cout << "Jakiego typu drzewo chcesz stworzyc: ";
                cout << "1. Poddrzewo rodzinne " << endl;
                cout << "2. Poddrzewo wszystkich pozniejszych technologii " << endl;
                cin >> typ;
                if (cin.peek() == '\n') cin.ignore();
                Szablonhistoryczny<T> poddrzewo = drzewo.stworzPoddrzewo(cel , typ);

                if (poddrzewo.pobierzWskaznik(cel) != nullptr) {
                cout << "--- Wygenerowano nowe poddrzewo ---" << endl;
                poddrzewo.wyswietlDrzewo();
                } 

                break;
            }
            case 7: {
                cin.ignore();
                string cel;
                cout << "Podaj nazwe technologii  ktorej definicje chcesz przeczytac: ";
                getline(cin, cel);
                T* obiekt = drzewo.pobierzWskaznik(cel);
                if (obiekt != nullptr)
                {
                    cout << "DEFINICJA: " << obiekt->getNazwa() << endl;
                    cout << obiekt->getOpis() << endl;
                }
                else { 
                    cout << "[INFO]Nie znaleziono technologii" << endl; 
                }
                break;
            }
            case 8: { 
                cin.ignore(); 
                string fraza;
                cout << "Podaj slowo lub fragment opisu do wyszukania: ";
                getline(cin, fraza);
                drzewo.wyszukajslowo(fraza);

                break;
                 }
            case 0: break;
            default: cout << "Nieznana opcja." << endl;
            }
            break;
        }
        case 6:
            drzewo.zapiszbinarnie(nazwa_zapisu_bin);
            cout << "Zapisano do pliku: " << nazwa_zapisu_bin << endl;
            break;
        case 7:
        {
            ifstream f(nazwa_zapisu_bin);
            if (f.good()) {
                f.close();
                drzewo.wczytajbinarnie(nazwa_zapisu_bin);
                cout << "Wczytano stan z pliku binarnego." << endl;
            }
            else {
                cout << "[BLAD] Nie znaleziono pliku zapisu (" << nazwa_zapisu_bin << ")" << endl;
            }
        }
        break;

        case 8: {
            cout << "\nZmiana kategorii/rodu" << endl;
            string cel, nowaDynastia;
            cout << "Podaj nazwe technologii/osoby do przeniesienia: ";
            getline(cin, cel);

            cout << "Podaj nazwe nowej kategorii/dynastii: ";
            getline(cin, nowaDynastia);
            drzewo.zmienKategorieMetodaWytnijWklej(cel, nowaDynastia);
            break;
        }
        case 9:
        {
            uruchomhelp();
            break;
        }
        case 0:
            running = false;
            cout << "Koniec..." << endl;
            break;
        default:
            cout << "Nieznana opcja." << endl;
        }
    }
}
//teoria + praktyka

#endif