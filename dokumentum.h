#ifndef DOCUMENTARY_H_INCLUDED
#define DOCUMENTARY_H_INCLUDED

#include "memtrace.h"
#include "film.h"

///Dokumentum osztály, amely a Film osztályból származik
class Dokumentum : public Film
{
    String leiras; ///Plusz adattag, ami leírást ad az adott filmhez
public:
    ///Konstruktor, ami meghívja az õs konstruktorát az inicializáló listán
    Dokumentum(const String& nev = "", int hossz = 0, int ev = 1900, const String& l = "");

    ///Másoló konstruktor
    Dokumentum(const Dokumentum& masik);

    ///Getter az adattag eléréséhez
    String getLeiras() const;

    ///Setter az adattag megváltoztatásához
    void setLeiras(const String& l);

    ///Konstruktor, amely beolvassa a dokumentumfilm adatait egy bemeneti adatfolyamból, és meghívja az ős megfelelő függvényét
    Dokumentum(std::istream& is);

    ///Specializálódott kiíró függvény, ami a plusz adattagot is kiírja
    void film_kiir(std::ostream& os) const;

    ///Két dokumentum film összehasonlítása
    bool operator==(const Dokumentum& masik) const;
};

#endif // DOCUMENTARY_H_INCLUDED
