#include "sprzet.h"

istream& operator>>(istream& is, oscyloskop& o) {
    is >> o.cena >> o.waga >> o.nazwa >> o.typ >> o.sprzet_ilosc >> o.ilosc_kanalow >> o.max_czestotliwosc >> o.pojemnosc_pamiec;
    return is;
}

ostream& operator<<(ostream& os, oscyloskop& o) {
    os << "Oscyloskop" << " " << o.cena << " " << o.waga << " " << o.nazwa << " " << o.typ << " " << o.sprzet_ilosc << " " << o.ilosc_kanalow << " " << o.max_czestotliwosc << " " << o.pojemnosc_pamiec << endl;
    return os;
}