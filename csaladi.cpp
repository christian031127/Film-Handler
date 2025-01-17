#include "csaladi.h"

//Õs konstruktorának meghívása
Csaladi::Csaladi(const String& nev, int hossz, int ev, int kor) : Film(nev, hossz, ev), korhatar(kor) {}

//Õs konstruktorának meghívása
Csaladi::Csaladi(const Csaladi& masik) : Film(masik), korhatar(masik.korhatar) {}

int Csaladi::getKorhatar() const
{
    return korhatar;
}

void Csaladi::setKorhatar(int k)
{
    korhatar = k;
}

Csaladi::Csaladi(std::istream& is) : Film(is)
{
    is >> korhatar;
}

void Csaladi::film_kiir(std::ostream& os) const
{
    os << "Csaladi " << getNev() << " " << getHossz() << " " << getEv() << " " << korhatar <<std::endl;
}

bool Csaladi::operator==(const Csaladi& masik) const
{
    bool tmp = (Film::operator==(masik) && korhatar == masik.korhatar);
    return tmp;
}

