#include "film.h"

Film::Film(const String& n, int h, int e) : nev(n), hossz(h), ev(e) {}

Film::Film(const Film& masik) : nev(masik.nev), hossz(masik.hossz), ev(masik.ev) {}

String Film::getNev() const
{
    return nev;
}

int Film::getHossz() const
{
    return hossz;
}

int Film::getEv() const
{
    return ev;
}

void Film::setNev(const String& n)
{
    nev = n;
}

void Film::setHossz(int h)
{
    hossz = h;
}

void Film::setEv(int e)
{
    ev = e;
}

Film::Film(std::istream& is)
{
    is >> nev >> hossz >> ev;
}

void Film::film_kiir(std::ostream& os) const
{
    os << "Film " << nev << " " << hossz << " " << ev <<std::endl;
}

bool Film::operator==(const Film& masik) const
{
    bool tmp = (nev == masik.nev && hossz == masik.hossz && ev == masik.ev);
    return tmp;
}
