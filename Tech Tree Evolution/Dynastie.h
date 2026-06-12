#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class Dynastie {
private:
    string imie;
    int rokPoczatek;
    int rokKoniec;
    string dynastia; 
    int czyKrol;     // 1 = Król, 0 = Inny
    string imieOjca;
    string opis;

public:
    Dynastie() : imie(""), rokPoczatek(0), rokKoniec(0), dynastia(""), czyKrol(0), imieOjca("BRAK"),opis("") {}

    Dynastie(string i, int r, string d, double p)
        : imie(i), rokPoczatek(r), rokKoniec(0), dynastia(d), czyKrol((int)p) {
    }

    Dynastie(string i, int r1, int r2, string d, double p)
        : imie(i), rokPoczatek(r1), rokKoniec(r2), dynastia(d), czyKrol((int)p) {
    }

    string getNazwa() const { return imie; }
    int getRok() const { return rokPoczatek; }
    int getRokKoniec() const { return rokKoniec; }
    int getWaga() const { return (int)czyKrol; }
    string getKategoria() const { return (string)dynastia;}
    string getWszystko() const {
        return "Nazwa: " + getNazwa() +
            ", Rok poczatku panowania: " + to_string(getRok()) +
            ", Rok konca panowania: " + to_string(getRokKoniec()) +
            ", Kategoria: " + getKategoria()
            ;
    }
 
    void setRok(int r) {
        rokPoczatek = r;
        if (rokKoniec < rokPoczatek) {
            rokKoniec = rokPoczatek; 
        }
    }
    void setRokKoniec(int k) {
        rokKoniec = k;
        if (rokKoniec < rokPoczatek) {
            rokKoniec = rokPoczatek;
        }
    }
    void setKategoria(string d) { dynastia = d; } 
    void setWaga(int w) { czyKrol = w; }

    static Dynastie stworzlinie(string linia, string& Rrodzic) {
        stringstream ss(linia);
        string segment, imie, rola, rodzic, dataString;
        int rokOd = 0, rokDo = 0;
        double waga;

        getline(ss, imie, ';');

        getline(ss, dataString, ';');
        size_t myslnik = dataString.find('-');
        if (myslnik != string::npos) {
            rokOd = stoi(dataString.substr(0, myslnik));
            rokDo = stoi(dataString.substr(myslnik + 1));
        }
        else {
            rokOd = stoi(dataString);
            rokDo = 0;
        }

        getline(ss, rola, ';');
        getline(ss, segment, ';'); waga = stod(segment);
        getline(ss, rodzic, ';');

        while (!rodzic.empty() && isspace(rodzic.back())) rodzic.pop_back();

        Rrodzic = rodzic;
        return Dynastie(imie, rokOd, rokDo, rola, waga);
    }

    string edytujInteraktywnie() {
        bool edycjaTrwa = true;
        string zadaniePrzeniesienia = "";
        while (edycjaTrwa) {
            cout << "\n--- EDYCJA W DYNASTII: " << getKategoria() << " ---" << endl;
            cout << "1. Zmien Rok Poczatku (obecnie: " << rokPoczatek << ")" << endl;
            cout << "2. Zmien Rok Konca    (obecnie: " << rokKoniec << ")" << endl;
            cout << "3. Zmien Dynastie     (obecnie: " << dynastia << ")" << endl;
            cout << "4. Zmien Status Krola (obecnie: " << (czyKrol == 1.0 ? "TAK" : "NIE") << ")" << endl;
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
                cout << "Nowy rok poczatku: ";
                cin >> rokPoczatek;
                break;
            case 2:
                cout << "Nowy rok konca: ";
                cin >> rokKoniec;
                break;
            case 3: {
                cout << "Podaj nowa nazwe dynastii (To spowoduje przeniesienie!): ";
                string nowa;
                getline(cin, nowa);
                if (nowa != dynastia) {
                    zadaniePrzeniesienia = nowa;
                    edycjaTrwa = false;
                }
                break;
            }
            case 4:
                cout << "Czy jest krolem? (1 - Tak, 0 - Nie): ";
                cin >> czyKrol;
                break;
            case 0:
                edycjaTrwa = false;
                cout << "[INFO] Koniec edycji tego elementu." << endl;
                break;
            default:
                cout << "Nieznana opcja." << endl;
            }
        
        }
        return zadaniePrzeniesienia;
    }

    void wyswietl() const {
        string status = (czyKrol == 1) ? "[KROL]" : "[    ]";

        cout << status << " " << imie << " (" << rokPoczatek;
        if (rokKoniec > 0) cout << "-" << rokKoniec;

        cout << ") [" << dynastia << "]" << endl;
    }

    string getOpis() const {
        if (czyKrol == 1) {
            string opis = "[KROL] " + imie + " (" + to_string(rokPoczatek) + " - " + to_string(rokKoniec) + ")" + " " + dynastia;
            return opis;
        }
        else {
            return "[    ] " + imie + " " + dynastia;
        }
    }

    void zapiszDoStrumienia(ofstream& ofs) const {
        size_t len = imie.size();
        ofs.write(reinterpret_cast<const char*>(&len), sizeof(len));
        ofs.write(imie.c_str(), len);
        ofs.write(reinterpret_cast<const char*>(&rokPoczatek), sizeof(rokPoczatek));
        ofs.write(reinterpret_cast<const char*>(&rokKoniec), sizeof(rokKoniec));

        len = dynastia.size();
        ofs.write(reinterpret_cast<const char*>(&len), sizeof(len));
        ofs.write(dynastia.c_str(), len);

        double tempWaga = (double)czyKrol;
        ofs.write(reinterpret_cast<const char*>(&tempWaga), sizeof(tempWaga));
    }

    void wczytajstrum(ifstream& ifs) {
        size_t len;
        if (!ifs.read(reinterpret_cast<char*>(&len), sizeof(len))) return;
        char* temp = new char[len + 1];
        ifs.read(temp, len);
        temp[len] = '\0';
        imie = temp;
        delete[] temp;

        ifs.read(reinterpret_cast<char*>(&rokPoczatek), sizeof(rokPoczatek));
        ifs.read(reinterpret_cast<char*>(&rokKoniec), sizeof(rokKoniec));

        ifs.read(reinterpret_cast<char*>(&len), sizeof(len));
        temp = new char[len + 1];
        ifs.read(temp, len);
        temp[len] = '\0';
        dynastia = temp;
        delete[] temp;

        double tempWaga;
        ifs.read(reinterpret_cast<char*>(&tempWaga), sizeof(tempWaga));
        czyKrol = (int)tempWaga;
    }

    bool operator>(const Dynastie& other) const { return rokPoczatek > other.rokPoczatek; }
    bool operator<(const Dynastie& other) const { return rokPoczatek < other.rokPoczatek; }

    // dla umpersndy
    //trza stworzyc przenoszenia i wszystko
    //semantyka n wartosci
};