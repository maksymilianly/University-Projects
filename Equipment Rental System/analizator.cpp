#include "sprzet.h"

istream& operator>>(istream& is, analizator& a) {
    is >> a.cena >> a.waga >> a.nazwa >> a.typ >> a.sprzet_ilosc >> a.wagaa ;
    return is;
}

ostream& operator<<(ostream& os, analizator& a) {
    os << "Oscyloskop" << " " << a.cena << " " << a.waga << " " << a.nazwa << " " << a.typ << " " << a.sprzet_ilosc << " " << a.wagaa << endl;
    return os;
}