#include "wypozyczenie.h"

istream& operator>>(istream& is, wypozyczenie& wyp) {
    is >> wyp.imie >> wyp.nazwisko >> wyp.nazwa >> wyp.dzien_s >> wyp.separator >> wyp.miesiac_s >> wyp.separator >> wyp.rok_s >> wyp.separator
       >> wyp.dzien_e >> wyp.separator >> wyp.miesiac_e >> wyp.separator >> wyp.rok_e;
    return is;
}

ostream& operator<<(ostream& os, wypozyczenie& wyp) {
    os << wyp.imie << " " << wyp.nazwisko << " " << wyp.nazwa << " " << wyp.dzien_s << wyp.separator << wyp.miesiac_s << wyp.separator << wyp.rok_s << " - "
        << wyp.dzien_e << wyp.separator << wyp.miesiac_e << wyp.separator << wyp.rok_e << endl;
    return os;
}

