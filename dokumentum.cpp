#include "dokumentum.h"

Dokumentum::Dokumentum(const String& nev, int hossz, int ev, const String& l) : Film(nev, hossz, ev), leiras(l) {}

Dokumentum::Dokumentum(const Dokumentum& masik) : Film(masik), leiras(masik.leiras) {}

String Dokumentum::getLeiras() const
{
    return leiras;
}

void Dokumentum::setLeiras(const String& l)
{
    leiras = l;
}

Dokumentum::Dokumentum(std::istream& is) : Film(is)
{
    is >> leiras;
}

void Dokumentum::film_kiir(std::ostream& os) const
{
    os << "Dokumentum " << getNev() << " " << getHossz() << " " << getEv() << " " << leiras <<std::endl;
}

bool Dokumentum::operator==(const Dokumentum& masik) const
{
    bool tmp = (Film::operator==(masik) && leiras == masik.leiras);
    return tmp;
}
