#ifndef FAMILY_H_INCLUDED
#define FAMILY_H_INCLUDED

#include "memtrace.h"
#include "film.h"

///Családi osztály, amely a Film osztályból származik
class Csaladi : public Film
{
    int korhatar; ///Korhatár adattag
public:
    ///Konstruktor, amely meghívja az õs konstruktorát az inicializáló listán
    Csaladi(const String& nev = "", int hossz = 0, int ev = 1900, int kor = 0);

    ///Másoló konstruktor
    Csaladi(const Csaladi& masik);

    ///Getter az adattag eléréséhez
    int getKorhatar() const;

    ///Setter az adattag megváltoztatásához
    void setKorhatar(int k);

    ///Konstruktor, amely beolvassa a családi film adatait egy bemeneti adatfolyamból, és meghívja az ős megfelelő függvényét
    Csaladi(std::istream& is);

    ///Specializálódott kiíró függvény, ami a plusz adattagot is kiírja
    void film_kiir(std::ostream& os) const;

    ///Két családi film összehasonlítása
    bool operator==(const Csaladi& masik) const;
};

#endif // FAMILY_H_INCLUDED
