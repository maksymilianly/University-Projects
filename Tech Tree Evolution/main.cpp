#include <iostream>
#include <fstream>
#include <string>
#include "Technologia.h"
#include "Szablonhistoryczny.h" 
#include "Funkcje.h"
#include "Dynastie.h" 

using namespace std;


int main(int argc, char* argv[]) {
    int tryb;
    cout << "Wybierz ktory temat analizujemy" << endl;
    cout << "1. Drzewo Technologii" << endl;
    //cout << "2. Drzewa Dynastyczne" << endl;
    cout << "Wybor: ";
    cin >> tryb;

    if (tryb == 1) {
        uruchomProgram<Technologia>("Technologie.txt");
    }
    //else if (tryb == 2) {
    //    uruchomProgram<Dynastie>("DynastieEuropy.txt");
    //}
    //else {
    //    cout << "[BLAD]Nieznany tryb!" << endl;
    //}

    return 0;
}