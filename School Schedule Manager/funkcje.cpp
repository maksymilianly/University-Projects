#include "funkcje.h"
#include <array>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <utility>
#include <iomanip>
#include <algorithm>
#include <type_traits>
using namespace std;

void main_wyswietlanie(vector<Prowadzacy>& prowadzace, vector<Zajecia>& zajecia, const vector<godziny>& godziny_rozklad)
{
	string odp;
	do
	{
		cout << "Czy chcesz wyswietlic rozklad wedlug okreslonych kryterium lub dokonac modyfikacji aktualnego rozkladu? (Tak/Nie) : " << endl;
		cin >> odp;

		while (odp != "Tak" && odp != "Nie")
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Nieprawidlowa odpowiedz, sprobuj jeszcze raz: " << endl;
			cin >> odp;
		}

		if (odp == "Tak")
		{
			modyfikacje(prowadzace, zajecia, godziny_rozklad);
		}

	} while (odp != "Nie");
}

void modyfikacje(vector<Prowadzacy>& prowadzace, vector<Zajecia>& zajecia,const vector<godziny>& godziny_rozklad)
{
	int choise;
	cout << "Ktorego dzialania chcesz dokonac? : " << endl;
	cout << "0 " << "Wyswietlanie planu" << endl;
	cout << "1 " << "Rozklad dla prowadzacego" << endl;
	cout << "2 " << "Rozklad dla grupy" << endl;
	cout << "3 " << "Rozklad dla przedmiotu" << endl;
	cout << "4 " << "Rozklad dla dnia" << endl;
	cout << "5 " << "Rozklad dla sali" << endl;
	cout << "6 " << "Modyfikacja aktualnego rozkladu" << endl;
	cin >> choise;

	while ((choise != (int)choise) /*cin.fail()*/ == 1 or choise < 0 or choise > 6)
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Nieprawidlowa odpowiedz, sprobuj jeszcze raz: " << endl;
		cin >> choise;
	}

	switch(choise)
	{
	case 0:
		wyswietlanie_planu(zajecia, godziny_rozklad);
		break;
	case 1:
		int idpr;
		cout << "Podaj id prowadzacego ktorego rozklad chcesz wyswietlic: " << endl;
		wyswietlanie_prow(prowadzace);
		cin >> idpr;
		while (cin.fail() or choise < 1 or choise > prowadzace.size()-1)
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Nieprawidlowa odpowiedz, sprobuj jeszcze raz: " << endl;
			cin >> idpr;
		}
		rozklad_dla_prowadzacego(prowadzace, zajecia, idpr);
		// Rozklad dla prowadzacego
		break;
	case 2:
	{
	    string grupa;
		cout << "Podaj grupe ktorej rozklad chcesz wyswietlic (liczby rzymskie): " << endl;
		cin >> grupa;
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Nieprawidlowa odpowiedz, sprobuj jeszcze raz: " << endl;
			cin >> grupa;
		}
		rozklad_dla_grupy(zajecia, grupa);
		// Rozklad dla grupy
		break;
	}
	case 3:
	{
		string przedmiot;
		cout << "Podaj przedmiot ktorego zajecia chcesz wyswietlic : " << endl;
		cin >> przedmiot;
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Nieprawidlowa odpowiedz, sprobuj jeszcze raz: " << endl;
			cin >> przedmiot;
		}
		rozklad_dla_przedmiotu(zajecia,przedmiot);
		// Rozklad dla przedmiotu
		break;
	}
	case 4:
	{
		string dz;
		cout << "Podaj dzien w ktorym chcesz wyswietlic zajecia : " << endl;
		cin >> dz;
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Nieprawidlowa odpowiedz, sprobuj jeszcze raz: " << endl;
			cin >> dz;
		}
		rozklad_dla_dnia(godziny_rozklad ,zajecia, dz);
		// Rozklad dla dnia
		break;
	}
	case 5:
	{
		string sal;
		cout << "Podaj dzien w ktorym chcesz wyswietlic zajecia : " << endl;
		cin >> sal;
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Nieprawidlowa odpowiedz, sprobuj jeszcze raz: " << endl;
			cin >> sal;
		}
		rozklad_dla_sal(godziny_rozklad, zajecia, sal);
		// Rozklad dla sali
		break;
	}
	case 6:
		case6(godziny_rozklad,zajecia,prowadzace);
		// Modyfikacja aktualnego rozkladu
		break;
	default:
		cout << "Blad.";
		break;
	}
}

void odczyt_pliku(vector<Prowadzacy>& prowadzace, vector<Zajecia>& zajecia, string nazwa_pliku)
{
	Prowadzacy prowadzac;
	Zajecia zajecie;
	char separator;
	ifstream file(nazwa_pliku);

	if (!file)
	{
		cerr << "Blad otwarcia pliku" << endl;
		return;
	}
	while (file >> prowadzac.imie >> prowadzac.nazwisko >> zajecie.grupa >> zajecie.przedmiot >> zajecie.sala
		>> zajecie.dzienTygodnia >> zajecie.czasRozpoczecia_god >> separator >> zajecie.czasRozpoczecia_min
		>> separator >> zajecie.czasZakonczenia_god >> separator >> zajecie.czasZakonczenia_min)
	{
		bool istnieje = false;

		for (const auto& prow : prowadzace)
		{
			if (prowadzac.imie == prow.imie && prowadzac.nazwisko == prow.nazwisko)
			{
				prowadzac.id_prow = prow.id_prow;
				istnieje = true;
				break;
			}
		}

		if (!istnieje)
		{
			prowadzac.id_prow = prowadzace.size()+1;
			prowadzace.push_back(prowadzac);
		}
		zajecie.prowadzacy.id_prow = prowadzac.id_prow;
		zajecie.prowadzacy.imie = prowadzac.imie;
		zajecie.prowadzacy.nazwisko = prowadzac.nazwisko;
		zajecia.push_back(zajecie);
	}
	file.close();
	
}

void wyswietlanie_planu( vector<Zajecia>& zajecia, const vector<godziny>& godziny_rozklad)
{
	string odp;
	cout << "Czy chcesz wyswietlic aktualny plan lekcji? (Tak/Nie) : " << endl;
	cin >> odp;
	while (odp != "Tak" && odp != "Nie")
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Nieprawidlowa odpowiedz, sprobuj jeszcze raz: " << endl;
		cin >> odp;
	}

	if (odp == "Tak")
	{
		generowanie_rozkladu(godziny_rozklad, zajecia);
	}
	if (odp == "Nie")
	{
		return;
	}

	while (odp != "Tak" && odp != "Nie")
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Nieprawidlowa odpowiedz, sprobuj jeszcze raz: " << endl;
		cin >> odp;
	}

}

void dek_dla_dni(string dzien)
{
	for (int i = 0; i < dzien.length(); i++)
	{
		cout << "*";
	}
	cout << endl;
	cout << dzien << endl;
	for (int i = 0; i < dzien.length(); i++)
	{
		cout << "*";
	}
	cout << endl;
}

void generowanie_rozkladu(const vector<godziny>& godziny_rozklad, vector<Zajecia>& zajecia)
{
    for (const auto& day : { "Poniedzialek", "Wtorek", "Sroda", "Czwartek", "Piatek" })
    {
        dek_dla_dni(day);
        for (const auto& godzina : godziny_rozklad)
        {
            cout << godzina.hour_s << godzina.separator << std::setw(2) << std::setfill('0') << godzina.minute_s << "-"
                << godzina.hour_e << godzina.separator << std::setw(2) << std::setfill('0') << godzina.minute_e << endl;

            for (const auto& zajecie : zajecia)
            {
                if (day == zajecie.dzienTygodnia and godzina.hour_s == zajecie.czasRozpoczecia_god and godzina.minute_s == zajecie.czasRozpoczecia_min)
                {
					cout << "----------------------------------------------------------------------------" << endl;
                    cout << "prowadzacy" << " " << "grupa" << " " << "przedmiot" << " " << "sala" << endl;
                    cout << zajecie.prowadzacy.imie << " " << zajecie.prowadzacy.nazwisko << " " << zajecie.grupa
                        << " " << zajecie.przedmiot << " " << zajecie.sala << endl;
					cout << "----------------------------------------------------------------------------" << endl;
                }
            }
        }
    }
}

void wyswietlanie_prow(vector<Prowadzacy>& prowadzace)
{
	//int counter = 0;
	for (auto& prowadzacy : prowadzace)
	{
		//counter++;
		/*if (counter > prowadzacy.id_prow)
		{
			break;
		}*/
		cout << "-------------------------------------------------------------------------------" << endl;
		cout << prowadzacy.id_prow << " " << prowadzacy.imie << " " << prowadzacy.nazwisko << endl;
	}
	cout << "-------------------------------------------------------------------------------" << endl;
}

void generowanie_godzin_rozkladu(vector<godziny> & godziny_rozklad)
{
	for (int i = 480; i <= 1080; i += 60)
	{
		godziny godzina;
		godzina.hour_s = i / 60;
		godzina.hour_e = (i + 45) / 60;
		godzina.separator = ':';
		godzina.minute_s = (i) % 60;
		godzina.minute_e = (i + 45) % 60;
		godziny_rozklad.push_back(godzina);
	}
}

void rozklad_dla_prowadzacego(const vector<Prowadzacy>& prowadzace, vector<Zajecia>& zajecia , const int id)
{
	for (auto& prowadzacy : prowadzace)
	{
		if (prowadzacy.id_prow == id)
		{


			cout << "-------------------------------------------------------------------------------" << endl;
			cout << prowadzacy.id_prow << " " << prowadzacy.imie << " " << prowadzacy.nazwisko << endl;
			for (auto& zajecie : zajecia)
			{
				if (prowadzacy.id_prow == zajecie.prowadzacy.id_prow)
				{
					cout << zajecie.przedmiot << endl << zajecie.dzienTygodnia << " "
						<< zajecie.czasRozpoczecia_god
						<< ':' << setw(2) << setfill('0') << zajecie.czasRozpoczecia_min << " - " << zajecie.czasZakonczenia_god << ':'
						<< zajecie.czasZakonczenia_min << " " << "sala: " << zajecie.sala << " " << "grupa: " << zajecie.grupa << endl;

				}
			}
			cout << "-------------------------------------------------------------------------------" << endl;
			break;
		}
	}

}

void rozklad_dla_grupy( vector<Zajecia>& zajecia, const string& grupa)
{
	cout << "-------------------------------------------------------------------------------" << endl;
	cout << "Rozklad zajec dla grupy " << grupa << ":" << endl;

	for (const auto& zajecie : zajecia)
	{
		if (zajecie.grupa == grupa)
		{
			cout << zajecie.przedmiot << endl << zajecie.dzienTygodnia << " "
				<< zajecie.czasRozpoczecia_god << ':' << setw(2) << setfill('0') << zajecie.czasRozpoczecia_min
				<< " - " << zajecie.czasZakonczenia_god << ':' << setw(2) << setfill('0') << zajecie.czasZakonczenia_min
				<< " " << "sala: " << zajecie.sala << endl;
		}
	}

	cout << "-------------------------------------------------------------------------------" << endl;
}

void rozklad_dla_przedmiotu( vector<Zajecia>& zajecia, const string& przedmiot)
{
	cout << "-------------------------------------------------------------------------------" << endl;
	cout << "Rozklad zajec dla: " << przedmiot << endl;

	for (const auto& zajecie : zajecia)
	{
		if (zajecie.przedmiot == przedmiot)
		{
			cout << zajecie.dzienTygodnia << endl 
				<< zajecie.czasRozpoczecia_god << ':' << setw(2) << setfill('0') << zajecie.czasRozpoczecia_min
				<< " - " << zajecie.czasZakonczenia_god << ':' << setw(2) << setfill('0') << zajecie.czasZakonczenia_min
				<< " " << "sala: " << zajecie.sala << " " << "grupa: " << zajecie.grupa << endl;
		}
	}

	cout << "-------------------------------------------------------------------------------" << endl;
}

void rozklad_dla_dnia(const vector<godziny>& godziny_rozklad, vector<Zajecia>& zajecia, const string& dzien)
{
	cout << "-------------------------------------------------------------------------------" << endl;
	cout << "Rozklad zajec dla: " << dzien << endl;

	for (const auto& godzinyy : godziny_rozklad)
	{
		for (const auto& zajecie : zajecia)
		{
			if (godzinyy.hour_s == zajecie.czasRozpoczecia_god && godzinyy.minute_s == zajecie.czasRozpoczecia_min && zajecie.dzienTygodnia == dzien)
			{
				cout << zajecie.przedmiot << endl
					<< zajecie.czasRozpoczecia_god << ':' << setw(2) << setfill('0') << zajecie.czasRozpoczecia_min
					<< " - " << zajecie.czasZakonczenia_god << ':' << setw(2) << setfill('0') << zajecie.czasZakonczenia_min
					<< " " << "sala: " << zajecie.sala << " " << "grupa: " << zajecie.grupa << endl;

			}
		}
	}

	cout << "-------------------------------------------------------------------------------" << endl;
}

void rozklad_dla_sal(const vector<godziny>& godziny_rozklad, vector<Zajecia>& zajecia, const string& sala)
{
	cout << "-------------------------------------------------------------------------------" << endl;
	cout << "Rozklad zajec dla sali: " << sala << endl;

	for (const auto& godzinyy : godziny_rozklad)
	{
		for (const auto& zajecie : zajecia)
		{
			if (godzinyy.hour_s == zajecie.czasRozpoczecia_god && godzinyy.minute_s == zajecie.czasRozpoczecia_min && zajecie.sala == sala)
			{
				cout << zajecie.dzienTygodnia << endl 
					<< zajecie.czasRozpoczecia_god << ':' << setw(2) << setfill('0') << zajecie.czasRozpoczecia_min
					<< " - " << zajecie.czasZakonczenia_god << ':' << setw(2) << setfill('0') << zajecie.czasZakonczenia_min
					<< " " << zajecie.przedmiot << " " << "grupa: " << zajecie.grupa << endl;

			}
		}
	}

	cout << "-------------------------------------------------------------------------------" << endl;
}

void case6(const vector<godziny>& godziny_rozklad, vector<Zajecia>& zajecia,vector<Prowadzacy>& prowadzace)
{
	int wybor;
	cout << "Jakiej modyfikacji chcesz uzyc? : " << endl;
	cout << "1 modyfikacja istniejacego zajecia" << endl
		 << "2 dodanie zajecia" << endl
		 << "3 usuniecie istniejacego zajecia" << endl;
	cin >> wybor;
	while ((wybor != (int)wybor) /*cin.fail()*/ == 1 or wybor < 1 or wybor > 3)
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Nieprawidlowa odpowiedz, sprobuj jeszcze raz: " << endl;
		cin >> wybor;
	}
	switch (wybor)
	{
	case 1 : 
	{
		modyfikacja_rozkladu(prowadzace,zajecia,godziny_rozklad);
	}
	case 2 : 
	{
		dodawanie_do_rozkladu(zajecia, godziny_rozklad,prowadzace);
	}	
	case 3 : 
	{
		usuwanie_z_rozkladu(prowadzace,zajecia, godziny_rozklad);
	}
	default : 
	{
		cout << "Nieprawidlowa odpowiedz, sprobuj jeszcze raz: " << endl;
	}
	}
}

void modyfikacja_rozkladu(vector<Prowadzacy>& prowadzace, vector<Zajecia>& zajecia, const vector<godziny>& godziny_rozklad)
{
	wyswietlanie_planu(zajecia, godziny_rozklad);
	string dzien;
	int godzina;
	int minuta;
	int idprow;
	wyswietlanie_prow(prowadzace);
	cout << "Podaj id prowadzacego: " << endl;
	cin >> idprow;
	while (cin.fail() || (idprow < 1 && idprow > prowadzace.size()))
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Nieprawidlowa odpowiedz, sprobuj jeszcze raz: " << endl;
		cin >> idprow;
	}
	cout << "Podaj dzien odbywania sie lekcji: " << endl;
	cin >> dzien;
	while (cin.fail() || (dzien != "Poniedzialek" && dzien != "Wtorek" && dzien != "Sroda" && dzien != "Czwartek" && dzien != "Piatek"))
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Nieprawidlowa odpowiedz, sprobuj jeszcze raz: " << endl;
		cin >> dzien;
	}
	cout << "Podaj godzine odbywania sie lekcji: " << endl;
	cin >> godzina;
	while (cin.fail() or godzina < 8 or godzina > 19)
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Nieprawidlowa odpowiedz, sprobuj jeszcze raz: " << endl;
		cin >> godzina;
	}
	cout << "Podaj minute odbywania sie lekcji: " << endl;
	cin >> minuta;
	while (cin.fail() or minuta % 15 != 0 or minuta < 0 or minuta > 60)
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Nieprawidlowa odpowiedz, sprobuj jeszcze raz: " << endl;
		cin >> minuta;
	}

	for (int i = zajecia.size() - 1; i >= 0; --i)
	{
		if (idprow == zajecia[i].prowadzacy.id_prow && dzien == zajecia[i].dzienTygodnia && godzina == zajecia[i].czasRozpoczecia_god && minuta == zajecia[i].czasRozpoczecia_min)
		{
			    cout << zajecia[i].prowadzacy.imie << " " << zajecia[i].prowadzacy.nazwisko << " " << zajecia[i].grupa << " " <<
				zajecia[i].przedmiot << " " << zajecia[i].sala << " " << zajecia[i].dzienTygodnia << " " << zajecia[i].czasRozpoczecia_god << ":"
				<< zajecia[i].czasRozpoczecia_min << " " << zajecia[i].czasZakonczenia_god << ":" << zajecia[i].czasZakonczenia_min << endl;
				modyfikacja_zajecia(prowadzace, zajecia, godziny_rozklad,zajecia[i]);
		}
	}
	cout << "Niepoprawne dane" << endl;
	main_wyswietlanie(prowadzace, zajecia, godziny_rozklad);
	exit(0);
}
void modyfikacja_zajecia(vector<Prowadzacy>& prowadzace, vector<Zajecia>& zajecia,const vector<godziny>& godziny_rozklad,Zajecia& zajecie)
{
	Prowadzacy prowadzac;
	Zajecia zajecie_zapis;
	zajecie_zapis = zajecie;
	string wybor = "Tak";
	string grupa,przedmiot,sal,dz;
	int godzina, minuta;
	while (wybor == "Tak") 
	{
		cout << "Czy chcesz zmodyfikowac element zajecia (Tak/Nie): " << endl;
		cin >> wybor;

		if (wybor == "Tak") {
			int choise;
			int idpr;
			cout << "Jakiej modyfikacji chcesz dokonac?: " << endl;
			cout << "1 Prowadzacy" << endl;
			cout << "2 " << "Grupa" << endl;
			cout << "3 " << "Przedmiot" << endl;
			cout << "4 " << "Sala" << endl;
			cout << "5 " << "Dzien" << endl;
			cout << "6 " << "Godzina" << endl;
			cin >> choise;
			while (cin.fail() || choise < 1 || choise > 6) {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Nieprawidlowa odpowiedz, sprobuj jeszcze raz: " << endl;
				cin >> choise;
			}

		    switch (choise)
			{
			   case 1:
			   {
				   cout << "Podaj id nowego prowadzacego z listy lub dodaj nowego prowadzacego wpisujac 0 : " << endl;
				   wyswietlanie_prow(prowadzace);
				   cin >> idpr;
				   bool istnieje = false;
				   if (idpr == 0)
				   {
					   prowadzac.id_prow = prowadzace.size() + 1;
					   cout << "Podaj imie i nazwisko prowadzacego : " << endl;
					   cin >> prowadzac.imie >> prowadzac.nazwisko;
					   for (const auto& prow : prowadzace) {
						   if (prowadzac.imie == prow.imie && prowadzac.nazwisko == prow.nazwisko) {
							   istnieje = true;
							   cout << "Taki prowadzacy juz istnieje!" << endl;
							   break;
						   }
					   }

					   if (!istnieje) {
						   prowadzac.id_prow = prowadzace.size() + 1;
						   prowadzace.push_back(prowadzac);
						   cout << "Nauczyciel zostal dodany!" << endl;
						   ofstream plik("prowadzace.txt", ios::app);
						   if (!plik.is_open()) {
							   cout << "Nie udalo sie otworzyc pliku " << "prowadzacy.txt" << endl;
							   return;
						   }
						   plik << prowadzac.id_prow << " " << prowadzac.imie << " " << prowadzac.nazwisko << endl;
						   plik.close();
					   }
				    
				   }
				   for (auto& prowadzac : prowadzace)
				   {
					   if (idpr == prowadzac.id_prow)
					   {
						   zajecie_zapis.prowadzacy.id_prow = prowadzac.id_prow;
						   zajecie_zapis.prowadzacy.imie = prowadzac.imie;
						   zajecie_zapis.prowadzacy.nazwisko = prowadzac.nazwisko;
					   }
				   }
				   break;
			   }
			   case 2:
			   {
				cout << "Podaj nowa grupe: " << endl;
				cin >> grupa;
				while (cin.fail())
				{
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "Nieprawidlowa odpowiedz, sprobuj jeszcze raz: " << endl;
					cin >> grupa;
				}
				zajecie_zapis.grupa = grupa;
				break;
			   }
			   case 3:
			   {
				cout << "Podaj nowy przedmiot : " << endl;
				cin >> przedmiot;
				while (cin.fail())
				{
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "Nieprawidlowa odpowiedz, sprobuj jeszcze raz: " << endl;
					cin >> przedmiot;
				}
				zajecie_zapis.przedmiot = przedmiot;
				break;
		      	}
			    case 4:
			   {
				cout << "Podaj nowa sale : " << endl;
				cin >> sal;
				while (cin.fail())
				{
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "Nieprawidlowa odpowiedz, sprobuj jeszcze raz: " << endl;
					cin >> sal;
				}
				zajecie_zapis.sala = sal;
				break;
			   }
			   case 5:
			   {
				cout << "Podaj nowy dzien: " << endl;
				cin >> dz;
				while (cin.fail())
				{
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "Nieprawidlowa odpowiedz, sprobuj jeszcze raz: " << endl;
					cin >> dz;
				}
				zajecie_zapis.dzienTygodnia = dz;
				break;
			   }
			   case 6:
			   {
				cout << "Podaj nowa godzine i minute(ze spacja): " << endl;
				cin >> godzina >> minuta;
				while (cin.fail())
				{
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "Nieprawidlowa odpowiedz, sprobuj jeszcze raz: " << endl;
					cin >> godzina >> minuta;
				}
				zajecie_zapis.czasRozpoczecia_god = godzina;
				zajecie_zapis.czasRozpoczecia_min = minuta;
				zajecie_zapis.czasZakonczenia_god = ((godzina * 60 + minuta) + 45) / 60;
				zajecie_zapis.czasZakonczenia_min = ((godzina * 60 + minuta) + 45) % 60;
				break;
			   }
			   default:
			   {
				cout << "Blad.";
				break;
			   }

			}
		

		}
	}
	for (const auto& zajecie_tmp : zajecia)
	{
		if ((zajecie_zapis.prowadzacy.id_prow == zajecie_tmp.prowadzacy.id_prow && zajecie_zapis.dzienTygodnia == zajecie_tmp.dzienTygodnia &&
			(zajecie_tmp.czasRozpoczecia_god * 60 + zajecie_tmp.czasRozpoczecia_min <= zajecie_zapis.czasRozpoczecia_god * 60 + zajecie_zapis.czasRozpoczecia_min) &&
			(zajecie_tmp.czasRozpoczecia_god * 60 + zajecie_tmp.czasRozpoczecia_min + 45 >= zajecie_zapis.czasRozpoczecia_god * 60 + zajecie_zapis.czasRozpoczecia_min)) ||
			(dz == zajecie_tmp.dzienTygodnia && (zajecie_tmp.czasRozpoczecia_god * 60 + zajecie_tmp.czasRozpoczecia_min <= godzina * 60 + minuta) &&
				(zajecie_tmp.czasRozpoczecia_god * 60 + zajecie_tmp.czasRozpoczecia_min + 45 >= zajecie_zapis.czasRozpoczecia_god * 60 + zajecie_zapis.czasRozpoczecia_min) && zajecie_zapis.sala == zajecie_tmp.sala) ||
			(dz == zajecie_tmp.dzienTygodnia && (zajecie_tmp.czasRozpoczecia_god * 60 + zajecie_tmp.czasRozpoczecia_min <= zajecie_zapis.czasRozpoczecia_god * 60 + zajecie_zapis.czasRozpoczecia_min) &&
				(zajecie_tmp.czasRozpoczecia_god * 60 + zajecie_tmp.czasRozpoczecia_min + 45 >= zajecie_zapis.czasRozpoczecia_god * 60 + zajecie_zapis.czasRozpoczecia_min) && zajecie_zapis.grupa == zajecie_tmp.grupa))
		{
			cout << "Prowadzacy lub grupa lub sala juz ma zajecie w podanym terminie" << endl;
			main_wyswietlanie(prowadzace, zajecia, godziny_rozklad);
			exit(0);
		}
	}
	
	zajecie_zapis.czasZakonczenia_god = ((zajecie_zapis.czasRozpoczecia_god * 60 + zajecie_zapis.czasRozpoczecia_min) + 45) / 60;
	zajecie_zapis.czasZakonczenia_min = ((zajecie_zapis.czasRozpoczecia_god * 60 + zajecie_zapis.czasRozpoczecia_min) + 45) % 60;
	cout << zajecie_zapis.prowadzacy.imie << " " << zajecie_zapis.prowadzacy.nazwisko << " "
		<< zajecie_zapis.grupa << " " << zajecie_zapis.przedmiot << " " << zajecie_zapis.sala << " " << zajecie_zapis.dzienTygodnia << " "
		<< zajecie_zapis.czasRozpoczecia_god << ":" << setw(2) << setfill('0') << right << zajecie_zapis.czasRozpoczecia_min << " - "
		<< zajecie_zapis.czasZakonczenia_god << ":" << zajecie_zapis.czasZakonczenia_min << endl;
	cout << "Zajecie zostalo dodane" << endl;
	zajecie = zajecie_zapis;
	zapisz_do_pliku(prowadzace, zajecia, "zajecia.txt");
	wyswietlanie_planu(zajecia, godziny_rozklad);
	main_wyswietlanie(prowadzace, zajecia, godziny_rozklad);
	exit(0);
}
    
void dodawanie_do_rozkladu( vector<Zajecia>& zajecia, const vector<godziny>& godziny_rozklad, vector<Prowadzacy>& prowadzace)
{
	wyswietlanie_planu(zajecia, godziny_rozklad);
	Prowadzacy prowadzac;
	Zajecia zajecie_zapis;
	string odp;
	int jaki;
	cout << "Czy chcesz dodac nowego prowadzacego? (Tak/Nie) : " << endl;
	cin >> odp;

	while (odp != "Tak" && odp != "Nie")
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Nieprawidlowa odpowiedz, sprobuj jeszcze raz: " << endl;
		cin >> odp;
	}
	if (odp == "Tak")
	{
		prowadzac.id_prow = prowadzace.size()+1;
		cout << "Podaj imie i nazwisko prowadzacego : " << endl;
		cin >> prowadzac.imie >> prowadzac.nazwisko;
			bool istnieje = false;
			for (const auto& prow : prowadzace)
			{
				if (prowadzac.imie == prow.imie && prowadzac.nazwisko == prow.nazwisko)
				{ 
					istnieje = true;
					cout << "Taki prowadzacy juz istnieje!" << endl;
					break;
				}
			}

			if (!istnieje)
			{
				prowadzac.id_prow = prowadzace.size() + 1;
				jaki = prowadzace.size()+1;
				prowadzace.push_back(prowadzac);
				cout << "Nauczyciel zostal dodany!" << endl;
				ofstream plik("prowadzace.txt", ios::app);
				if (!plik.is_open())
				{
					cout << "Nie udalo sie otworzyc pliku " << "prowadzacy.txt" << endl;
					return;	
				}
			}  
		
		
		
	}
	else
	{
		cout << "Wybierz prowadzacego z list (id) : " << endl;
		wyswietlanie_prow(prowadzace);
		cin >> jaki;
		while ((jaki != (int)jaki) /*cin.fail()*/ == 1 or jaki < 1 or jaki > prowadzace.size())
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Nieprawidlowa odpowiedz, sprobuj jeszcze raz: " << endl;
			cin >> jaki;
		}
	}
	for (const auto& prowadzacy : prowadzace)
	{
		if (jaki == prowadzacy.id_prow)
		{
			prowadzac.id_prow = prowadzacy.id_prow;
			prowadzac.imie = prowadzacy.imie;
			prowadzac.nazwisko = prowadzacy.nazwisko;
		}
	}
	string dzien;
	int godzina;
	int minuta;
	string sala;
	string grupa;
	cout << "Podaj dzien odbywania sie lekcji: " << endl;
	cin >> dzien;
	while (cin.fail() || (dzien != "Poniedzialek" && dzien != "Wtorek" && dzien != "Sroda" && dzien != "Czwartek" && dzien != "Piatek"))
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Nieprawidlowa odpowiedz, sprobuj jeszcze raz: " << endl;
		cin >> dzien;
	}
	cout << "Podaj godzine odbywania sie lekcji: " << endl;
	cin >> godzina;
	while (cin.fail() or godzina < 8 or godzina > 19)
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Nieprawidlowa odpowiedz, sprobuj jeszcze raz: " << endl;
		cin >> godzina;
	}
	cout << "Podaj minute odbywania sie lekcji: " << endl;
	cin >> minuta;
	while (cin.fail() or minuta % 15 != 0 or minuta < 0 or minuta > 60)
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Nieprawidlowa odpowiedz, sprobuj jeszcze raz: " << endl;
		cin >> minuta;
		Zajecia zajecie;
	}
	for (const auto& zajecie : zajecia)
	{
		if (jaki == zajecie.prowadzacy.id_prow and dzien == zajecie.dzienTygodnia and (zajecie.czasRozpoczecia_god * 60 + zajecie.czasRozpoczecia_min <= godzina * 60 + minuta) and
			(zajecie.czasRozpoczecia_god * 60 + zajecie.czasRozpoczecia_min + 45 >= godzina * 60 + minuta))
		{
			cout << "Prowadzacy juz ma zajecie w podanym terminie" << endl;
			main_wyswietlanie(prowadzace, zajecia, godziny_rozklad);
			exit(0);
		}
	}
	cout << "Podaj sale : " << endl;
	cin >> sala;	
	while (cin.fail() || (sala != "100" && sala != "110" && sala != "200" && sala != "220" && sala != "300" && sala != "330"
		&& sala != "400" && sala != "440" && sala != "500" && sala != "550"))
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Nieprawidlowa numer sali, sprobuj jeszcze raz: " << endl;
		cin >> sala;
	}
	cout << "Podaj grupe : " << endl;
	cin >> grupa;
	while (cin.fail() || grupa != "I" && grupa != "II" && grupa != "III" && grupa != "IV" && grupa != "V" && grupa != "VI"
		&& grupa != "VII" && grupa != "VIII" && grupa != "IX" && grupa != "X")
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Nieprawidlowa grupa, sprobuj jeszcze raz: " << endl;
		cin >> grupa;
	}
	string przedmiot;
	cout << "Podaj przedmiot : " << endl;
	cin >> przedmiot;
	while (cin.fail())
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Nieprawidlowa odpowiedz, sprobuj jeszcze raz: " << endl;
		cin >> przedmiot;
	}
	for (const auto& zajecie : zajecia) {
		if ((jaki == zajecie.prowadzacy.id_prow && dzien == zajecie.dzienTygodnia &&
			(zajecie.czasRozpoczecia_god * 60 + zajecie.czasRozpoczecia_min <= godzina * 60 + minuta) &&
			(zajecie.czasRozpoczecia_god * 60 + zajecie.czasRozpoczecia_min + 45 >= godzina * 60 + minuta)) ||
			(dzien == zajecie.dzienTygodnia && (zajecie.czasRozpoczecia_god * 60 + zajecie.czasRozpoczecia_min <= godzina * 60 + minuta) &&
			(zajecie.czasRozpoczecia_god * 60 + zajecie.czasRozpoczecia_min + 45 >= godzina * 60 + minuta) && sala == zajecie.sala) ||
			(dzien == zajecie.dzienTygodnia && (zajecie.czasRozpoczecia_god * 60 + zajecie.czasRozpoczecia_min <= godzina * 60 + minuta) &&
			(zajecie.czasRozpoczecia_god * 60 + zajecie.czasRozpoczecia_min + 45 >= godzina * 60 + minuta) && grupa == zajecie.grupa)) {

			cout << "Prowadzacy lub grupa lub sala juz ma zajecie w podanym terminie" << endl;
			main_wyswietlanie(prowadzace, zajecia, godziny_rozklad);
			exit(0);
		}
	}
			    zajecie_zapis.prowadzacy.id_prow = prowadzac.id_prow;
				zajecie_zapis.prowadzacy.imie = prowadzac.imie;
				zajecie_zapis.prowadzacy.nazwisko = prowadzac.nazwisko;
				zajecie_zapis.czasRozpoczecia_god = godzina;
				zajecie_zapis.czasRozpoczecia_min = minuta;
				zajecie_zapis.czasZakonczenia_god = ((godzina * 60 + minuta) + 45) / 60;
				zajecie_zapis.czasZakonczenia_min = ((godzina * 60 + minuta) + 45) % 60;
				zajecie_zapis.dzienTygodnia = dzien;
				zajecie_zapis.grupa = grupa;
				zajecie_zapis.przedmiot = przedmiot;
				zajecie_zapis.sala = sala;
				cout << zajecie_zapis.prowadzacy.imie << " " << zajecie_zapis.prowadzacy.nazwisko << " "
				<< zajecie_zapis.grupa << " " << zajecie_zapis.przedmiot << " " << zajecie_zapis.sala << " " << zajecie_zapis.dzienTygodnia << " "
				<< zajecie_zapis.czasRozpoczecia_god << ":" << setw(2) << setfill('0') << right << zajecie_zapis.czasRozpoczecia_min << " - "
				<< zajecie_zapis.czasZakonczenia_god << ":" << zajecie_zapis.czasZakonczenia_min << endl;
				cout << "Zajecie zostalo dodane" << endl;
				zajecia.push_back(zajecie_zapis);
			    zapisz_do_pliku(prowadzace, zajecia, "zajecia.txt");
				wyswietlanie_planu(zajecia, godziny_rozklad);
				main_wyswietlanie(prowadzace, zajecia, godziny_rozklad);
				exit(0);
				
}

void usuwanie_z_rozkladu(vector<Prowadzacy>& prowadzace , vector<Zajecia>& zajecia, const vector<godziny>& godziny_rozklad)
{
	wyswietlanie_planu(zajecia, godziny_rozklad);
	string dzien;
	int godzina;
	int minuta;
	string choise;
	int idprow;
	wyswietlanie_prow(prowadzace);
	cout << "Podaj id prowadzacego: " << endl;
	cin >> idprow;
	while (cin.fail() || (idprow < 1 && idprow > prowadzace.size()-1))
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Nieprawidlowa odpowiedz, sprobuj jeszcze raz: " << endl;
		cin >> idprow;
	}
	cout << "Podaj dzien odbywania sie lekcji: " << endl;
	cin >> dzien;
	while (cin.fail() || (dzien != "Poniedzialek" && dzien != "Wtorek" && dzien != "Sroda" && dzien != "Czwartek" && dzien != "Piatek"))
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Nieprawidlowa odpowiedz, sprobuj jeszcze raz: " << endl;
		cin >> dzien;
	}
	cout << "Podaj godzine odbywania sie lekcji: " << endl;
	cin >> godzina;
	while (cin.fail() || godzina < 8 || godzina > 19)
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Nieprawidlowa odpowiedz, sprobuj jeszcze raz: " << endl;
		cin >> godzina;
	}
	cout << "Podaj minute odbywania sie lekcji: " << endl;
	cin >> minuta;
	while (cin.fail() || minuta % 15 != 0 || minuta < 0 || minuta > 60)
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Nieprawidlowa odpowiedz, sprobuj jeszcze raz: " << endl;
		cin >> minuta;
	}

	for (int i = zajecia.size() - 1; i >= 0; --i)
	{
		if (idprow == zajecia[i].prowadzacy.id_prow && dzien == zajecia[i].dzienTygodnia && godzina == zajecia[i].czasRozpoczecia_god && minuta == zajecia[i].czasRozpoczecia_min)
		{
			cout << zajecia[i].prowadzacy.imie << " " << zajecia[i].prowadzacy.nazwisko << " " << zajecia[i].grupa << " " <<
			zajecia[i].przedmiot << " " << zajecia[i].sala << " " << zajecia[i].dzienTygodnia << " " << zajecia[i].czasRozpoczecia_god << ":"
			<< zajecia[i].czasRozpoczecia_min << " " << zajecia[i].czasZakonczenia_god << ":" << zajecia[i].czasZakonczenia_min << endl;
			cout << "Czy na pewno chcesz usunac dany termin?(Tak/Nie): " << endl;
			cin >> choise;
			while (cin.fail() || (choise != "Tak" && choise != "Nie"))
			{
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Nieprawidlowa odpowiedz, sprobuj jeszcze raz: " << endl;
				cin >> choise;
			}

			if (choise == "Tak")
			{
				zajecia.erase(zajecia.begin()+i);
				cout << "Zajecie zostalo pomyslnie usuniete!" << endl;
				zapisz_do_pliku(prowadzace, zajecia, "zajecia.txt");
				main_wyswietlanie(prowadzace, zajecia, godziny_rozklad);
				exit(0);
				
			}
			if (choise == "Nie")
			{
				main_wyswietlanie(prowadzace, zajecia, godziny_rozklad);
				exit(0);
			}
		}
	}
	wyswietlanie_planu(zajecia, godziny_rozklad);
	exit(0);
	
}

void zapisz_do_pliku(vector<Prowadzacy>& prowadzace,vector<Zajecia>& zajecia, const string& nazwa_pliku) {
	ofstream plik1(nazwa_pliku);
	if (!plik1.is_open()) {
		cerr << "Błąd otwarcia pliku " << nazwa_pliku << endl;
		return;
	}
	for (const auto& zajecie : zajecia) {
		plik1 << zajecie.prowadzacy.imie << " " << zajecie.prowadzacy.nazwisko << " " 
			<< zajecie.grupa << " " << zajecie.przedmiot << " " << zajecie.sala << " " << zajecie.dzienTygodnia << " "
			<< zajecie.czasRozpoczecia_god << ":" << zajecie.czasRozpoczecia_min << " - "
			<< zajecie.czasZakonczenia_god << ":" << zajecie.czasZakonczenia_min << endl;
	}
	plik1.close();
}









