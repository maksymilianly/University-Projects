#include "sprzet.h"


istream& operator>>(istream& is, decybelomierz& d) {
    is >> d.cena >> d.waga >> d.nazwa >> d.typ >> d.sprzet_ilosc >> d.maks_pomiar >> d.tryb_pomiarowy >> d.podswietlenie;
    return is;
}

ostream& operator<<(ostream& os, decybelomierz& d) {
    os << "Decybelomierz" << " " << d.cena << " " << d.waga << " " << d.nazwa << " " << d.typ << " " << d.sprzet_ilosc << " " << d.maks_pomiar << d.tryb_pomiarowy << d.podswietlenie << endl;
    return os;
}