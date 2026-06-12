#include <iostream>
#include "funkcje.h"
#include <fstream>
#include <string>
#include <vector>
#include< sstream >
#include <utility>
#include <iomanip>
#include <algorithm>
#include <ctype.h>
using namespace std;

int main(int argc, char* argv[]) 
{
	vector<Prowadzacy> prowadzace;
	vector<Zajecia> zajecia;
	vector<godziny> godziny_rozklad;
	cout << "-----------------------------------------------------------------------------------------------------------\n";
	cout << "Grupy : I-X" << endl;
	cout << "Sale : 100,110,200,220,300,330,400,440,500,550 " << endl;
	if (argc >= 2 && std::string(argv[1]) == "zajecia.txt") {
		odczyt_pliku(prowadzace,zajecia,argv[1]);
	}
	else {
		std::cout << "Brak niezbednych danych lub niepoprawna nazwa pliku" << std::endl;
		return 1;
	}

	
	
	generowanie_godzin_rozkladu(godziny_rozklad);
	main_wyswietlanie(prowadzace,zajecia,godziny_rozklad);
	//wyswietlanie_planu(zajecia, godziny_rozklad);
	//modyfikacje(prowadzace, zajecia, godziny_rozklad);
	//generowanie_rozkladu(godziny_rozklad, zajecia);
	//rozklad_dla_prowadzacego(prowadzace, zajecia,1);
	//rozklad_dla_grupy(zajecia,"III");
	//rozklad_dla_przedmiotu(zajecia, "Informatyka");
	//rozklad_dla_dnia(godziny_rozklad,zajecia, "Poniedzialek");
	//rozklad_dla_sal(godziny_rozklad,zajecia,"100");
	//wyswietlanie_prow(prowadzace);
	//dodawanie_do_rozkladu(zajecia, godziny_rozklad, prowadzace);
	//zapisz_do_pliku(prowadzace, zajecia,"zajecia.txt");
	//modyfikacja_rozkladu(prowadzace, zajecia, godziny_rozklad);
	return 0;
}

 

