#include "sprzet.h"

sprzet::~sprzet() {}

ostream& operator<<(ostream& os, const sprzet& s) {
    os << s.cena << " " << s.waga << " " << s.nazwa << " " << s.typ << " " << s.sprzet_ilosc;
    return os;
}