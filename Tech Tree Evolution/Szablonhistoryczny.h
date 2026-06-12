#pragma once 

#include <iostream>
#include <memory>    
#include <fstream>
#include <string>
#include <set>

using namespace std;

template <typename T>
class Szablonhistoryczny {
private:
    struct Node {
        T data;
        unique_ptr<Node> dziecko; //lewy node
        unique_ptr<Node> brat; //prawy node
        Node* rodzic;
        Node(const T& val , Node* r = nullptr) : data(val), dziecko(nullptr), brat(nullptr), rodzic(r) {}
    };
    unique_ptr<Node> korzen;

    // Pomocnicza lista
    struct ElementListy {
        T* dane;
        ElementListy* nastepny;
        ElementListy(T* ptr) : dane(ptr), nastepny(nullptr) {}
    };

    ElementListy* glowaListy;

    set<string> rejestrDynastii;

    //Metody
    Node* znajdzWezel(Node* node, const string& nazwaSzukana) const {
        if (!node) return nullptr;
        if (node->data.getNazwa() == nazwaSzukana) return node;

        Node* wDzieciach = znajdzWezel(node->dziecko.get(), nazwaSzukana);
        if (wDzieciach) return wDzieciach;

        return znajdzWezel(node->brat.get(), nazwaSzukana);
    }

    unique_ptr<Node> klonujWezel(const Node* zrodlo , Node* rodzicklona) {
        if (!zrodlo) return nullptr;

        auto nowyWezel = make_unique<Node>(zrodlo->data,rodzicklona);

        nowyWezel->dziecko = klonujWezel(zrodlo->dziecko.get() , nowyWezel.get());
        nowyWezel->brat = klonujWezel(zrodlo->brat.get(),rodzicklona);

        return nowyWezel;
    }

    void printChildren(Node* piewszedziecko, string prefix) const {
        Node* current = piewszedziecko;
        while (current) {
            bool ostatnibrat = (current->brat == nullptr);
            cout << prefix << (ostatnibrat ? "`-- " : "|-- ");
            cout <<  " "  
                 << current->data.getDane() 
                 << endl;

            if (current->dziecko) {
                printChildren(current->dziecko.get(), prefix + (ostatnibrat ? "    " : "|   "));
            }
            current = current->brat.get();
        }
    }

    void aktualizujKategoriePotomkom(Node* wezel, const string& nowaKategoria) {
        if (!wezel) return;

        wezel->data.setKategoria(nowaKategoria);

        aktualizujKategoriePotomkom(wezel->dziecko.get(), nowaKategoria);

        aktualizujKategoriePotomkom(wezel->brat.get(), nowaKategoria);
    }

    void dodajDoListyRekurencyjnie(Node* wezel) {
        if (!wezel) return;
        ElementListy* nowy = new ElementListy(&wezel->data);
        nowy->nastepny = glowaListy;
        glowaListy = nowy;
        dodajDoListyRekurencyjnie(wezel->dziecko.get());
        dodajDoListyRekurencyjnie(wezel->brat.get());
    }

    void wyczyscListe() {
        while (glowaListy) {
            ElementListy* temp = glowaListy;
            glowaListy = glowaListy->nastepny;
            delete temp;
        }
    }

    void Rekser(const unique_ptr<Node>& node, ofstream& ofs) const {
        bool istnieje = (node != nullptr);
        ofs.write(reinterpret_cast<const char*>(&istnieje), sizeof(bool));
        if (istnieje) {
            node->data.zapiszDoStrumienia(ofs);
            Rekser(node->dziecko, ofs);
            Rekser(node->brat, ofs);
        }
    }

    void Rekdeser(unique_ptr<Node>& node, ifstream& ifs) {
        bool istnieje;
        if (!ifs.read(reinterpret_cast<char*>(&istnieje), sizeof(bool))) return;
        if (!istnieje) node = nullptr;
        else {
            T tempData;
            tempData.wczytajstrum(ifs);
            node = make_unique<Node>(tempData);
            Rekdeser(node->dziecko, ifs);
            Rekdeser(node->brat, ifs);
        }
    }

    bool usunRekurencyjnie(unique_ptr<Node>& node, const string& nazwa) {
        if (!node) return false;

        if (node->data.getNazwa() == nazwa) {
            cout << "\n[!] Znaleziono: " << node->data.getWszystko() << endl;
            cout << "[?] Czy na pewno usunac ten element i jego dzieci? (t/n): ";
            char c;
            cin >> c;
            if (cin.peek() == '\n') cin.ignore();
            if (c == 't' || c == 'T') {
                cout << "-> Usuwam..." << endl;
                node = move(node->brat);
                return true;
            }
        }

        if (usunRekurencyjnie(node->dziecko, nazwa)) return true;

        return usunRekurencyjnie(node->brat, nazwa);
    }

    void kopiujdrzewko(Node* zrodlo, int rokbaza, Szablonhistoryczny& noweDrzewo) {
        if (!zrodlo) return;
        if (zrodlo->data.getRok() > rokbaza) {
            string nazwaRodzicaoryginalnego = (zrodlo->rodzic) ? zrodlo->rodzic->data.getNazwa() : "";
            bool czyDodanoJakoDziecko = noweDrzewo.dodajDziecko(nazwaRodzicaoryginalnego, zrodlo->data);

            if (!czyDodanoJakoDziecko) {
                noweDrzewo.dodajKorzen(zrodlo->data);
            }
            noweDrzewo.rejestrDynastii.insert(zrodlo->data.getKategoria());
        }

        kopiujdrzewko(zrodlo->dziecko.get(), rokbaza, noweDrzewo);
        kopiujdrzewko(zrodlo->brat.get(), rokbaza, noweDrzewo);
    }

    void szukajfraze(Node* node, const string& fraza, bool& czyZnalezionocokolwiek) {
        if (!node) return;

        bool wnazwie = node->data.getNazwa().find(fraza) != string::npos;
        bool wopisie = node->data.getOpis().find(fraza) != string::npos;

        if (wnazwie || wopisie) {
            czyZnalezionocokolwiek = true; 

            cout << node->data.getWszystko();
        }

        szukajfraze(node->dziecko.get(), fraza, czyZnalezionocokolwiek);
        szukajfraze(node->brat.get(), fraza, czyZnalezionocokolwiek);
    }
    
    
public:
    Szablonhistoryczny() : korzen(nullptr), glowaListy(nullptr) {}
    ~Szablonhistoryczny() { wyczyscListe(); }

    Szablonhistoryczny(Szablonhistoryczny&& other) noexcept //przenoszacy
        : korzen(move(other.korzen)), 
        rejestrDynastii(move(other.rejestrDynastii)), 
        glowaListy(other.glowaListy) 
    {
        other.glowaListy = nullptr;
    }

    //kopiujacy
    Szablonhistoryczny(const Szablonhistoryczny& other)
        : korzen(nullptr), glowaListy(nullptr) 
    {
        rejestrDynastii = other.rejestrDynastii;

        korzen = klonujWezel(other.korzen.get());

        zbudujListe();
    }

    Szablonhistoryczny& operator=(const Szablonhistoryczny& other) { //op kopiujacy
        if (this != &other) { 

            wyczyscListe();
            korzen.reset(); 
           
            rejestrDynastii = other.rejestrDynastii;
            korzen = klonujWezel(other.korzen.get() , nullptr);

            zbudujListe();
        }
        return *this;
    }

    Szablonhistoryczny& operator=(Szablonhistoryczny&& other) noexcept { //op przenoszacy
        if (this != &other) {
  
            wyczyscListe();
            korzen = move(other.korzen);
            rejestrDynastii = move(other.rejestrDynastii);
            glowaListy = other.glowaListy;

            other.glowaListy = nullptr;
        }
        return *this;
    }

    Szablonhistoryczny stworzPoddrzewo(string nazwaStart , int typ) {
        Szablonhistoryczny noweDrzewo;
        Node* zrodlo = znajdzWezel(korzen.get(), nazwaStart);
        if (typ == 1)
        {
            if (!zrodlo) {
                cout << "[BLAD] Nie znaleziono wezla startowego." << endl;
                return noweDrzewo;
            }
            noweDrzewo.korzen = klonujWezel(zrodlo, nullptr);
            noweDrzewo.zbudujListe();
            noweDrzewo.rejestrDynastii.insert(zrodlo->data.getKategoria());
            return noweDrzewo;
        }
        else if (typ == 2)
        {
            int rokbaza = zrodlo->data.getRok();
            cout <<"Drzewo z technologii mlodszych niz rok " << rokbaza << endl;

            kopiujdrzewko(korzen.get(), rokbaza, noweDrzewo);
            noweDrzewo.zbudujListe();
            noweDrzewo.wyswietlDrzewo();
        }
        else {
            cout << "Bledny typ operacji (wybierz 1 lub 2)." << endl;
        }
        return noweDrzewo; 
        }
                 

    void wczytajzPliku(const string& nazwaPliku) {
        ifstream plik(nazwaPliku);
        if (!plik.is_open()) {
            cout << "[BLAD]Nie mozna otworzyc pliku " << nazwaPliku << endl;
            return;
        }

        string linia;
        int licznik = 0;
        int wszystkich = 0;
        while (getline(plik, linia)) {
            if (linia.empty()) continue;

            string rodzicNazwa;

            T nowyObiekt = T::stworzlinie(linia, rodzicNazwa);

            rejestrDynastii.insert(nowyObiekt.getKategoria());

            if (rodzicNazwa == "BRAK" || rodzicNazwa == "ROOT" || rodzicNazwa == "" || rodzicNazwa == "-") {
                dodajKorzen(nowyObiekt);
            }
            else {
                if (!dodajDziecko(rodzicNazwa, nowyObiekt)) {

                    cout << "[BLAD]Nie ma rodzica '" << rodzicNazwa << "'. Przenosze '" << nowyObiekt.getNazwa() << "' do SIEROT." << endl;

                    if (!dodajDziecko("SIEROTY", nowyObiekt)) {

                        T Sieroty("SIEROTY", 0, "BLEDY", 0 , "");
                        dodajKorzen(Sieroty);

                        dodajDziecko("SIEROTY", nowyObiekt);
                    }
                }
            }
            licznik++;
            wszystkich++;
        }
        plik.close();
        cout << "-> Wczytano " << wszystkich << " obiektow z " << licznik <<" z pliku : "<< nazwaPliku << endl;
    }

    void dodajKorzen(T dane) {
        auto nowy = make_unique<Node>(dane);
        if (!korzen) korzen = move(nowy);
        else {
            Node* t = korzen.get();
            while (t->brat) t = t->brat.get();
            t->brat = move(nowy);
        }
    }

    //Dodawanie z sortowaniem
    bool dodajDziecko(string nazwaRodzica, T daneDziecka) {
        if (!korzen) { dodajKorzen(daneDziecka); return true; }

        Node* rodzic = znajdzWezel(korzen.get(), nazwaRodzica);
        if (!rodzic) return false;

        auto noweDziecko = make_unique<Node>(daneDziecka,rodzic);
        int rokNowego = daneDziecka.getRok();

        if (rodzic->dziecko == nullptr) {
            rodzic->dziecko = move(noweDziecko);
            return true;
        }

        //Sort od najstarszego
        if (rokNowego < rodzic->dziecko->data.getRok()) {
            noweDziecko->brat = move(rodzic->dziecko);
            rodzic->dziecko = move(noweDziecko);
            return true;
        }

        //Sort od najstarszego
        Node* obecny = rodzic->dziecko.get();
        while (obecny->brat != nullptr && obecny->brat->data.getRok() < rokNowego) {
            obecny = obecny->brat.get();
        }

        noweDziecko->brat = move(obecny->brat);
        obecny->brat = move(noweDziecko);
        return true;
    }

    bool porownajDaty(T* node1, T* node2)
    {
        if (node1 == node2) { return true; }
        else { return false; }
    }

    int obliczGlebokosc(Node* n) {
        int glebokosc = 0;
        while (n != nullptr) {
            glebokosc++;
            n = n->rodzic;
        }
        return glebokosc;
    }

    void wypiszDrogeRekurencyjnie(Node* aktualny, Node* stop) {
        if (aktualny == stop || aktualny == nullptr) return;
        wypiszDrogeRekurencyjnie(aktualny->rodzic, stop);
        cout << " -> " << aktualny->data.getNazwa();
    }

    void wskazdroge(string nazwaStart, string nazwaKoniec) {
        Node* start = znajdzWezel(korzen.get(), nazwaStart);
        Node* koniec = znajdzWezel(korzen.get(), nazwaKoniec);

        if (!start || !koniec) {
            cout << "[BLAD] Nie znaleziono elementow." << endl;
            return;
        }

        int d1 = obliczGlebokosc(start);
        int d2 = obliczGlebokosc(koniec);

        Node* p1 = start;
        Node* p2 = koniec;

        while (d1 > d2) {
            p1 = p1->rodzic;
            d1--;
        }
        while (d2 > d1) {
            p2 = p2->rodzic;
            d2--;
        }

        while (p1 != nullptr && p2 != nullptr && p1 != p2) {
            p1 = p1->rodzic;
            p2 = p2->rodzic;
        }

        if (p1 == nullptr || p2 == nullptr) {
            cout << "[INFO] Brak drogi (rozne dynastie/drzewa)." << endl;
            return;
        }

        Node* lca = p1; 
        cout << "Droga: ";
        Node* temp = start;
        bool pierwszy = true;
        while (temp != lca) {
            if (!pierwszy) cout << " -> ";
            cout << temp->data.getNazwa();
            temp = temp->rodzic;
            pierwszy = false;
        }

        if (!pierwszy) cout << " -> ";
        cout << lca->data.getNazwa();
        wypiszDrogeRekurencyjnie(koniec, lca);
        cout << endl;
    }

    void wyswietlDrzewo() const {
        cout << "\n=== DRZEWO CHRONOLOGICZNE ===\n";
        if (korzen) printChildren(korzen.get(), "");
        else cout << "([INFO]Puste)" << endl;
    }
  
    void szukaj(string nazwa) {
        Node* w = znajdzWezel(korzen.get(), nazwa);

        if (w) {
            cout << "[SUKCES]ZNALEZIONO: " << w->data.getWszystko() << endl;
        }
        else {
            cout << "[INFO]Nie znaleziono: " << nazwa << endl;
        }
    }

    T* pobierzWskaznik(string szukanaNazwa) {

        Node* znalezionyNode = znajdzWezel(korzen.get(), szukanaNazwa);

        if (znalezionyNode != nullptr) {
            return &(znalezionyNode->data);
        }

        return nullptr;
    }

    void zmienKategorieMetodaWytnijWklej(string nazwaWezla, string nowaDynastia) {
        Node* cel = znajdzWezel(korzen.get(), nazwaWezla);
        if (!cel) {
            cout << "[BLAD] Nie znaleziono wezla: " << nazwaWezla << endl;
            return;
        }

        cout << "-> Przenoszenie '" << nazwaWezla << "' do dynastii '" << nowaDynastia << endl;

        T dane = cel->data;
        dane.setKategoria(nowaDynastia);

        unique_ptr<Node> uratowaneDzieci = move(cel->dziecko);
        usun(nazwaWezla);
        bool czyIstnieje = (rejestrDynastii.count(nowaDynastia) > 0);
        bool sukcesDodania = false;

        if (!czyIstnieje) {
            cout << "[INFO] Tworze nowa dynastie/galaz." << endl;
            rejestrDynastii.insert(nowaDynastia);
            dodajKorzen(dane);
            sukcesDodania = true;
        }
        else {
            cout << "[INFO] Dynastia '" << nowaDynastia << "' juz istnieje." << endl;
            cout << "Kto ma byc NOWYM OJCEM? (Wpisz 'ROOT' dla korzenia): ";
            if (cin.peek() == '\n') cin.ignore();
            string nowyOjciec;
            getline(cin, nowyOjciec);
            while (!nowyOjciec.empty() && isspace(nowyOjciec.back())) nowyOjciec.pop_back();

            if (nowyOjciec == "ROOT" || nowyOjciec == "") {
                dodajKorzen(dane);
                sukcesDodania = true;
            }
            else {
                sukcesDodania = dodajDziecko(nowyOjciec, dane);
                if (!sukcesDodania) {
                    cout << "[BLAD] Nie znaleziono ojca. Tworze awaryjny korzen." << endl;
                    dodajKorzen(dane);
                    sukcesDodania = true;
                }
            }
        }
        if (sukcesDodania) {
            Node* nowyWezelPtr = znajdzWezel(korzen.get(), nazwaWezla);
            if (nowyWezelPtr != nullptr && uratowaneDzieci != nullptr) {
                nowyWezelPtr->dziecko = move(uratowaneDzieci);
                if (nowyWezelPtr->dziecko) {
                    nowyWezelPtr->dziecko->rodzic = nowyWezelPtr;
                }
                aktualizujKategoriePotomkom(nowyWezelPtr->dziecko.get(), nowaDynastia);
                cout << "[SUKCES] Przeniesiono galezie i potomstwo." << endl;
            }
        }
    }

    void wyszukajslowo(string fraza) {
        cout << "WYSZUKIWARKA POJEC" << endl;
        cout << "Szukam frazy: '" << fraza << endl;

        bool znaleziono = false; 
        szukajfraze(korzen.get(), fraza, znaleziono);

        if (!znaleziono) {
            cout << "[INFO] Nie znaleziono zadnego hasla ani definicji zawierajacej: '" << fraza << "'" << endl;
        }
        else {
            cout << "----------------------------------------" << endl;
            cout << "Koniec wyszukiwania." << endl;
        }
    }

    //Lista
    void zbudujListe() {
        wyczyscListe();
        if (korzen) dodajDoListyRekurencyjnie(korzen.get());
    }

    void sortujListe(int tryb) { // 1=Nazwa, 2=Rok, 3=Waga
        if (!glowaListy) return;
        bool zamiana;
        do {
            zamiana = false;
            ElementListy* obecny = glowaListy;
            while (obecny->nastepny) {
                ElementListy* nast = obecny->nastepny;
                bool swap = false;

                if (tryb == 1 && obecny->dane->getNazwa() > nast->dane->getNazwa()) swap = true;
                else if (tryb == 2 && (*obecny->dane > *nast->dane)) swap = true;
                else if (tryb == 3 && obecny->dane->getWaga() < nast->dane->getWaga()) swap = true;

                if (swap) {
                    T* temp = obecny->dane;
                    obecny->dane = nast->dane;
                    nast->dane = temp;
                    zamiana = true;
                }
                obecny = obecny->nastepny;
            }
        } while (zamiana);
    }

    void wyswietlListe() const {
        cout << "\n=== LISTA ===\n";
        ElementListy* el = glowaListy;
        while (el) {
            cout << el->dane->getWszystko() << endl;
            el = el->nastepny;
        }
    }

    bool usun(string nazwa) {
        return usunRekurencyjnie(korzen, nazwa);
    }

        
    void zapiszbinarnie(const string& sciezka) {
        ofstream plik(sciezka, ios::binary);
        if (plik.is_open()) { Rekser(korzen, plik); cout << "-> Zapisano." << endl; }
    }
    void wczytajbinarnie(const string& sciezka) {
        ifstream plik(sciezka, ios::binary);
        if (plik.is_open()) { korzen = nullptr; Rekdeser(korzen, plik); cout << "-> Wczytano." << endl; }
    }
};
