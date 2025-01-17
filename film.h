#ifndef MOVIE_H_INCLUDED
#define MOVIE_H_INCLUDED

#include <fstream>

#include "memtrace.h"
#include "string.h"

///Film õsosztály
class Film
{
    String nev; ///Film címe
    int hossz; ///Film hossza (percben)
    int ev; ///Film kiadási ideje
public:
    ///Konstruktor, ami egy Film objektumot hoz létre, három paraméterrel
    Film(const String& n = "", int h = 0, int e = 1900);

    ///Másoló konstruktor, amely egy másik Film objektum alapján inicializálja az új Film objektumot.
    Film(const Film& masik);

    ///Getterek a megfelelõ adattagok lekérdezéséhez
    String getNev() const;
    int getHossz() const;
    int getEv() const;

    ///Setterek az adattagok beállításához
    void setNev(const String& n);
    void setHossz(int h);
    void setEv(int e);

    /// Ez a konstruktor egy std::istream referenciát vesz át bemeneti paraméterként.
    /// Célja, hogy inicializálja a Film objektumot a bemeneti adatfolyamból olvasott adatok alapján.
    Film(std::istream& is);

    /// Tagfüggvény, amely kiírja a Film objektum adatait egy kimeneti adatfolyamba.
    virtual void film_kiir(std::ostream& os) const;

    ///Operátor túlterhelés az egyenlőség összehasonlítására két Film objektum között.
    virtual bool operator==(const Film& masik) const;

    ///Virtuális destruktor a megfelelõ memóriakezelés céljából
    virtual ~Film(){}
};

#endif // MOVIE_H_INCLUDED
