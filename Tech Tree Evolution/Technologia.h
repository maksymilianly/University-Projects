#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class Technologia {
private:
    string nazwa;
    int rok;
    string kategoria;
    double waga; 
    string opis;
public:
    Technologia() : nazwa(""), rok(0), kategoria(""), waga(0.0) {}
    Technologia(string n, int r, string k, double w, string o)
        : nazwa(n), rok(r), kategoria(k), waga(w), opis(o) {
    }
    string getNazwa() const { return nazwa; }
    int getRok() const { return rok; }
    int getRokKoniec() const { return 0; }
    double getWaga() const { return waga; }
    string getKategoria() const { return kategoria; }
    string getOpis() const { return opis; }
    string getDane() const {
        return   getNazwa() + " " +
            to_string(getRok());
        
    }

    void setRok(int r) { rok = r; }
    void setRokKoniec(int r) {}
    void setKategoria(string k) { kategoria = k; } 
    void setWaga(double w) { waga = w; }
    void setOpis(string o) { opis = o; }
    string getWszystko() const {
        return "Nazwa: " + getNazwa() +
            ", Rok odkrycia: " + to_string(getRok()) +
            ", Kategoria: " + getKategoria() +
            ", Waga technologii: " + to_string(getWaga()) +
            ", Opis: " + getOpis()
            ;
    }

    static Technologia stworzlinie(string linia, string& outRodzic) {
        stringstream ss(linia);
        string segment, n, k, o , op;
        int r; double w;

        getline(ss, n, ';');
        getline(ss, segment, ';'); r = stoi(segment);
        getline(ss, k, ';');
        getline(ss, segment, ';'); w = stod(segment);
        getline(ss, o, ';');
        getline(ss, op);

        while (!o.empty() && isspace(o.back())) o.pop_back();
        while (!op.empty() && isspace(op.back())) op.pop_back();
        outRodzic = o;

        return Technologia(n, r, k, w, op);
    }

    string edytujInteraktywnie() {
        string staraKategoria = kategoria;
        bool edycjaTrwa = true;

        while (edycjaTrwa) {
            cout << "\n--- EDYCJA TECHNOLOGII: " << nazwa << " ---" << endl;
            cout << "1. Zmien Rok Wynalezienia (obecnie: " << rok << ")" << endl;
            cout << "2. Zmien Kategorie        (obecnie: " << kategoria << ")" << endl;
            cout << "3. Zmien Wage/Koszt       (obecnie: " << waga << ")" << endl;
            cout << "4. Zmien Opis/Definicje   (obecnie: " << (opis.length() > 20 ? opis.substr(0, 20) + "..." : opis) << endl; 
            cout << "0. Zakoncz edycje" << endl;
            cout << "Wybor: ";

            int wybor;
            if (!(cin >> wybor)) {
                cin.clear(); cin.ignore(10000, '\n');
                continue;
            }
            cin.ignore();

            switch (wybor) {
            case 1:
                cout << "Nowy rok: ";
                cin >> rok;
                break;
            case 2:
                cout << "Nowa kategoria: ";
                getline(cin, kategoria);
                break;
            case 3:
                cout << "Nowa waga: ";
                cin >> waga;
                break;
            case 4: 
                cout << "Nowy opis: ";
                getline(cin, opis);
                break;
            case 0:
                edycjaTrwa = false;
                cout << "[INFO] Koniec edycji tego elementu." << endl;
                break;
            default:
                cout << "Nieznana opcja." << endl;
            }
        }

        if (kategoria != staraKategoria) {
            return kategoria;
        }

        return ""; 
    }

    void wyswietl() const {
        cout << nazwa << " (" << rok << ") [" << kategoria << "] Waga: " << waga << endl;
    }

    string przygotujDozapisu(string nazwaRodzica) const {
        return nazwaRodzica + ";" + nazwa + ";" + to_string(rok) + ";" + kategoria + ";" + to_string(waga) + ";" + opis;
    }

    void zapiszDoStrumienia(ofstream& ofs) const {
        size_t len = nazwa.size();
        ofs.write(reinterpret_cast<const char*>(&len), sizeof(len));
        ofs.write(nazwa.c_str(), len);

        ofs.write(reinterpret_cast<const char*>(&rok), sizeof(rok));

        len = kategoria.size();
        ofs.write(reinterpret_cast<const char*>(&len), sizeof(len));
        ofs.write(kategoria.c_str(), len);

        ofs.write(reinterpret_cast<const char*>(&waga), sizeof(waga));

        len = opis.size();
        ofs.write((char*)&len, sizeof(len)); 
        ofs.write(opis.c_str(), len);
    }

    void wczytajstrum(ifstream& ifs) {
        size_t len;

        if (!ifs.read(reinterpret_cast<char*>(&len), sizeof(len))) return;
        char* temp = new char[len + 1];
        ifs.read(temp, len);
        temp[len] = '\0';
        nazwa = temp;
        delete[] temp;

        ifs.read(reinterpret_cast<char*>(&rok), sizeof(rok));

        ifs.read(reinterpret_cast<char*>(&len), sizeof(len));
        temp = new char[len + 1];
        ifs.read(temp, len);
        temp[len] = '\0';
        kategoria = temp;
        delete[] temp;

        ifs.read(reinterpret_cast<char*>(&waga), sizeof(waga));

        ifs.read((char*)&len, sizeof(len));
        opis.resize(len);
        ifs.read(&opis[0], len);
    }

    bool operator>(const Technologia& other) const { return rok > other.rok; }
    bool operator<(const Technologia& other) const { return rok < other.rok; }
    bool operator==(const Technologia& other) const { return (rok == other.rok && nazwa == other.nazwa) ; }
};