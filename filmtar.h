#ifndef FILMTAR_H_INCLUDED
#define FILMTAR_H_INCLUDED

#include "memtrace.h"

#include "film.h"
#include "csaladi.h"
#include "dokumentum.h"

///Heterogén kollekcióként szolgáló osztály
///Filmeket tartalmaz
class Filmtar
{
    Film** filmek; ///Filmek tömbje
    size_t meret; ///Gyűjtemény aktuális mérete
    const size_t max_meret; ///Maximális méret
public:
    ///Konstruktor
    Filmtar(size_t max_m = 0);

    ///Másoló konstruktor
    Filmtar(const Filmtar& masik);

    ///Getterek a méretek lekérdezéséhez
    size_t getMeret() const;
    size_t getMax_meret() const;

    ///Új könyv felvétele a gyűjteménybe
    void felvetel(Film* film);

    ///Adott film benne van-e a tárban (film címe alapján)
    bool benne_van(const String& filmnev) const;

    ///Adott film keresése a címe alapján
    Film* kereses(const char* filmnev) const;

    ///Adott adattagot módosító tagfüggvények
    void modosit(Film* film, const String& uj_nev); ///Név
    void modosit(Film* film, const int uj_hossz); ///Hossz
    void modosit_overload(Film* film, const int uj_ev); ///Kiadási év
    void modosit(Csaladi* film, const int uj_korhatar); ///Korhatár
    void modosit(Dokumentum* film, const String& uj_leiras); ///Leírás

    ///Film eltávolítása az indexe alapján
    void eltavolitas(size_t index);
    ///Film eltávolítása a címe alapján
    void eltavolitas(const String& film);

    ///Teljes tár kiíratása adott pillanatba
    void kiir(std::ostream& os) const;

    ///Destruktor
    ~Filmtar();

    ///Index operátor az adattagok eléréséhez
    Film* operator[](size_t index) const;

    ///Értékadó operátor
    Filmtar& operator=(const Filmtar& masik);
    ///Egyenlőség operátor
    bool operator==(const Filmtar& masik) const;

    ///Konstruktor, ami egy adott fájl tartalmából állítja elő a filmtárat
    Filmtar(const char* fajl, size_t max_meret);
    ///Filmtár kiiratása fájlba
    bool kiir_fajl(const char* falj);

    ///Rendező függvény adott predikátum alapján
    template<typename P>
    void rendezes(P pred)
    {
        for(size_t i = 1; i < meret; i++)
        {
            Film* tmp = filmek[i];
            int j = i - 1;
            while(j >= 0 && pred(*tmp, *filmek[j]))
            {
                filmek[j + 1] = filmek[j];
                j--;
            }
            filmek[j + 1] = tmp;
        }
    }
};

///Két film összehasonlítása a kiadási évük alapján
bool ev_alapjan(const Film& egyik, const Film& masik);

///Két film összehasonlítása a hosszuk alapján
bool hossz_alapjan(const Film& egyik, const Film& masik);

///Felhasználói interface-hez
///A menürendszerhez bizonyos szövegek kiiratása

void fomenu();

void logo();

void almenu4();

void almenu5();

#endif // FILMTAR_H_INCLUDED
