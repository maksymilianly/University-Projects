#include "osoba.h"

istream& operator>>(istream& is, osoba& o) {
    is >> o.id >> o.imie >> o.nazwisko;
    return is;
}

ostream& operator<<(ostream& os, osoba& osb) {
    os << osb.id << " " << osb.imie << " " << osb.nazwisko << endl;
    return os;
}