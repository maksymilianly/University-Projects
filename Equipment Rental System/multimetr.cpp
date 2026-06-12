#include "sprzet.h"

istream& operator>>(istream& is, multimetr& m) {
    is >> m.cena >> m.waga >> m.nazwa >> m.typ >> m.sprzet_ilosc >> m.wyswietlanie >> m.max_wartosc_wyswietlania;
    return is;
}

ostream& operator<<(ostream& os, multimetr& m) {
    os << "Multimetr" << " " << m.cena << " " << m.waga << " " << m.nazwa << " " << m.typ << " " << m.sprzet_ilosc << " " << m.wyswietlanie << " " << m.max_wartosc_wyswietlania << endl;
    return os;
}