#include "filmtar.h"

Filmtar::Filmtar(size_t max_m) : max_meret(max_m)
{
    filmek = new Film * [max_meret]; //Dinamikus memóriaterület foglalása a filmek számára
    meret = 0; // A kezdeti méret 0, mert még egyetlen filmet sem adtunk hozzá
}

Filmtar::Filmtar(const Filmtar& other) :
    filmek(new Film*[other.max_meret]), // Új dinamikus memóriaterület foglalása a másik objektum méretével
    meret(other.meret), // Az új objektum mérete megegyezik a másik objektuméval
    max_meret(other.max_meret) // Az új objektum maximális mérete megegyezik a másik objektuméval
{
    for (size_t i = 0; i < meret; ++i) // A másik objektumban található filmek másolása
    {
        if (other.filmek[i])
            filmek[i] = new Film(*other.filmek[i]);
        else
            filmek[i] = nullptr;
    }
}

size_t Filmtar::getMeret() const
{
    return meret;
}

size_t Filmtar::getMax_meret() const
{
    return max_meret;
}

void Filmtar::felvetel(Film* film)
{
    if(meret >= max_meret) // Ellenõrzi, hogy a filmtár tele van-e
    {
        delete film; // Törli a hozzáadni kívánt filmet, ha a filmtár tele van
        std::cerr << "Tele van a filmtar!" << std::endl; // Hibaüzenet kiírása
    }
    else
    {
        filmek[meret] = film; // Hozzáadja a filmet a filmtárhoz
        meret++; // Növeli a filmtár méretét
    }
}

bool Filmtar::benne_van(const String& filmnev) const
{
    for (size_t i = 0; i < meret; ++i) // Végigmegy az összes filmen a filmtárban
    {
        if (filmek[i]->getNev() == filmnev) // Összehasonlítja a film nevét a keresett névvel
        {
            return true;
        }
    }
    return false;
}

Film* Filmtar::kereses(const char* filmnev) const
{
    for (size_t i = 0; i < meret; ++i) // Végigmegy az összes filmen a filmtárban
    {
        const char* cim = filmek[i]->getNev().c_str(); // Lekéri a film címét C-string formátumban
        if (strstr(cim, filmnev) != nullptr) // Ellenõrzi, hogy a keresett név része-e a film címének
        {
            return filmek[i];
        }
    }
    std::cerr << "Ervenyes filmnevet adjon meg!" << std::endl; // Hibaüzenet, ha a film nem található
    return nullptr;
}

void Filmtar::modosit(Film* film, const String& uj_nev)
{
    bool talalt = false; // Flag változó, ami jelzi, ha megtalálta a filmet
    for (size_t i = 0; i < meret; ++i) // Végigmegy a filmtárban lévõ filmeken
    {
        if (filmek[i] == film) // Ellenõrzi, hogy az aktuális film ugyanaz-e, mint a keresett film
        {
            talalt = true; // Ha megtalálja a filmet, beállítja a talalt flaget igaz értékre
            break;
        }
    }
    if (!talalt) // Ha nem találta meg a filmet a filmtárban
    {
        std::cerr << "A megadott film nem talalhato a filmtarban!" << std::endl;
        return;
    }

    film->setNev(uj_nev); // A film címét módosítja az új névre
}

///További módosító függvények is hasonlóan mûködnek!
void Filmtar::modosit(Film* film, const int uj_hossz)
{
    bool talalt = false;
    for (size_t i = 0; i < meret; ++i)
    {
        if (filmek[i] == film)
        {
            talalt = true;
            break;
        }
    }
    if (!talalt)
    {
        std::cerr << "A megadott film nem talalhato a filmtarban!" << std::endl;
        return;
    }

    film->setHossz(uj_hossz);
}

void Filmtar::modosit_overload(Film* film, const int uj_ev)
{
    bool talalt = false;
    for (size_t i = 0; i < meret; ++i)
    {
        if (filmek[i] == film)
        {
            talalt = true;
            break;
        }
    }
    if (!talalt)
    {
        std::cerr << "A megadott film nem talalhato a filmtarban!" << std::endl;
        return;
    }

    film->setEv(uj_ev);
}

void Filmtar::modosit(Csaladi* film, const int uj_korhatar)
{
    bool talalt = false;
    for (size_t i = 0; i < meret; ++i)
    {
        if (filmek[i] == film)
        {
            talalt = true;
            break;
        }
    }
    if (!talalt)
    {
        std::cerr << "A megadott film nem talalhato a filmtarban!" << std::endl;
        return;
    }

    film->setKorhatar(uj_korhatar);
}

void Filmtar::modosit(Dokumentum* film, const String& uj_leiras)
{
    bool talalt = false;
    for (size_t i = 0; i < meret; ++i)
    {
        if (filmek[i] == film)
        {
            talalt = true;
            break;
        }
    }
    if (!talalt)
    {
        std::cerr << "A megadott film nem talalhato a filmtarban!" << std::endl;
        return;
    }

    film->setLeiras(uj_leiras);
}

void Filmtar::eltavolitas(size_t index)
{
    if(index >= meret) // Ellenõrzi, hogy az index érvényes-e
    {
        std::cerr << "Ervenyes indexu elemet adjon meg!" << std::endl; // Hibaüzenet
        return;
    }
    else
    {
        delete filmek[index]; // Törli az adott indexen lévõ filmet
        for (size_t i = index; i < meret - 1; ++i) // Áthelyezi a többi filmet egy helyet elõre
        {
            filmek[i] = filmek[i + 1];
        }
        meret--; // Csökkenti a filmtár méretét
    }
}

void Filmtar::eltavolitas(const String& film)
{
    size_t i = 0;
    while(i < meret) // Végigmegy a filmtárban lévõ filmeken
    {
        if(filmek[i]->getNev() == film) // Ellenõrzi, hogy az aktuális film neve egyezik-e a keresett névvel
        {
            eltavolitas(i); // Ha talál egyezést, eltávolítja a filmet az adott indexen
            return;
        }
        i++;
    }
    std::cerr << "Ervenyes filmnevet adjon meg!" << std::endl; // Hibaüzenet
}

void Filmtar::kiir(std::ostream& os) const
{
    size_t i = 0;
    while(i < meret) // Végigmegy a filmtárban lévõ filmeken
    {
        filmek[i]->film_kiir(os); // Kiírja az aktuális film adatait az adott kimeneti adatfolyamba
        i++;
    }
}

Filmtar::~Filmtar()
{
    size_t i = 0;
    while(i < meret) // Végigmegy a filmtárban lévõ filmeken
    {
        delete filmek[i]; // Törli az aktuális filmet
        i++;
    }
    delete[] filmek; // Felszabadítja a filmek tömbjét
}

Film* Filmtar::operator[](size_t index) const
{
    if(index >= meret) // Ellenõrzi, hogy az index érvényes-e
    {
        std::cerr << "Ervenyes indexu elemet adjon meg!" << std::endl; // Hibaüzenet
        return nullptr; // Visszatér nullptr értékkel, ha az index érvénytelen
    }

    // Dinamikus típuskonverzió a filmekhez, hogy lehessen õket kezelni a leszármazott típusuk szerint
    if (Dokumentum* df = dynamic_cast<Dokumentum*>(filmek[index])) // Dokumentumra történõ konverzió
    {
        return df; // Visszatér a dinamikus típuskonverzió után kapott pointerrel
    }
    else if (Csaladi* cf = dynamic_cast<Csaladi*>(filmek[index])) // Családi filmre történõ konverzió
    {
        return cf; // Visszatér a dinamikus típuskonverzió után kapott pointerrel
    }
    else // Ha nincs típuskonverzió, akkor a film pointerét adja vissza
    {
        return filmek[index]; // Visszatér az adott indexen lévõ film pointerével
    }
}

Filmtar& Filmtar::operator=(const Filmtar& masik)
{
    if (this != &masik) // Ellenõrzi, hogy az értékadás nem történik-e meg ugyanarra az objektumra
    {
        delete[] filmek; // Felszabadítja az aktuális objektum által foglalt erõforrásokat

        meret = masik.meret; // Másolja a másik objektum méretét

        filmek = new Film*[max_meret]; // Létrehoz egy új dinamikus tömböt a filmeknek

        for (size_t i = 0; i < meret; ++i) // Végigmegy a másik objektum filmjein
        {
            filmek[i] = new Film(*(masik.filmek[i])); // Másolja a filmeket az új tömbbe
        }
    }
    return *this; // Visszatér az aktuális objektum referenciájával
}

bool Filmtar::operator==(const Filmtar& masik) const
{
    if (max_meret != masik.max_meret) // Ellenõrzi, hogy a filmtárak ugyanakkora méretûek-e
        return false;

    if(meret != masik.meret) // Ellenõrzi, hogy a filmtárak ugyanannyi filmet tartalmaznak-e
    {
        return false;
    }
    else
    {
        size_t i = 0;
        while(i < meret) // Végigmegy a filmeket tartalmazó tömbökön
        {
            if(!(*filmek[i] == *masik.filmek[i])) // Ellenõrzi, hogy a filmek egyenlõek-e
            {
                return false; // Ha legalább egy film nem egyenlõ, akkor a filmtárak nem egyenlõek
            }
            i++;
        }
    }
    return true; // Ha minden film egyenlõ volt, akkor a filmtárak egyenlõek
}

Filmtar::Filmtar(const char* fajl, size_t max_meret) : filmek(new Film*[max_meret]), meret(0), max_meret(max_meret)
{
    std::ifstream file(fajl); // Fájl megnyitása olvasásra
    if(!file.is_open()) // Ellenõrzi, hogy sikerült-e megnyitni a fájlt
    {
        throw "Nem sikerult megnyitni a fajlt!"; // Hibaüzenet
    }
    if(file.is_open())
    {
        while(!file.eof()) // A fájl feldolgozása, amíg nem ér a végére
        {
            String film_tipusa; // A film típusának tárolására szolgáló string változó
            file >> film_tipusa; // Beolvassa a fájlból a film típusát

            /// Az olvasott típusnak megfelelõen létrehoz és hozzáad egy új filmet a filmtárhoz
            if(film_tipusa == "Film")
            {
                Film* film = new Film(file); // Létrehoz egy új Film objektumot a fájlból beolvasott adatokkal
                felvetel(film); // Hozzáadja az új filmet a filmtárhoz
            }
            else if(film_tipusa == "Csaladi")
            {
                Csaladi* film = new Csaladi(file); // Létrehoz egy új Csaladi objektumot a fájlból beolvasott adatokkal
                felvetel(film); // Hozzáadja az új filmet a filmtárhoz
            }
            else if(film_tipusa == "Dokumentum")
            {
                Dokumentum* film = new Dokumentum(file); // Létrehoz egy új Dokumentum objektumot a fájlból beolvasott adatokkal
                felvetel(film); // Hozzáadja az új filmet a filmtárhoz
            }
            else if(strcmp(film_tipusa.c_str(), "\n") == 0) // Ellenõrzi, hogy az olvasott sor üres-e
            {
                std::cerr << "Ervenytelen tipus!\n\n"; // Hibaüzenet, ha az olvasott típus érvénytelen
            }
        }
        file.close(); // Fájl bezárása
    }
}

bool Filmtar::kiir_fajl(const char* fajl)
{
    std::ofstream ofs(fajl); // Fájl létrehozása
    if (!ofs.is_open()) // Ellenõrzi, hogy sikerült-e megnyitni a fájlt
    {
        return false; // Ha nem, akkor hamissal tér vissza
    }
    kiir(ofs); // Kiírja a filmtárat a megadott fájlba
    ofs.close(); // Fájl bezárása
    return true; // Igazzal tér vissza, ha sikeres volt a kiírás
}

bool ev_alapjan(Film const& egyik, Film const& masik)
{
    bool tmp = egyik.getEv() > masik.getEv(); // Összehasonlítja két film kiadási évét
    return tmp;
}

bool hossz_alapjan(Film const& egyik, Film const& masik)
{
    bool tmp =  egyik.getHossz() < masik.getHossz(); // Összehasonlítja két film hosszát
    return tmp;
}

void fomenu()
{
    std::cout << "[1] Uj film hozzaadasa\n";
    std::cout << "[2] Film torlese\n";
    std::cout << "[3] Kereses film neve alapjan\n";
    std::cout << "[4] Modositasok\n";
    std::cout << "[5] Filmtar kiirasa\n";
    std::cout << "[6] Rendezesek\n";
    std::cout << "[7] Tesztek\n";
    std::cout << "[0] Kilepes\n";
    std::cout << "Valasztas: ";
}

void logo()
{
    std::cout << "*------------------*" << std::endl;
    std::cout << "|  FILMTAR KEZELO  |" << std::endl;
    std::cout << "*------------------*" << std::endl;
}

void almenu4()
{
    std::cout << "*------------------*" << std::endl;
    std::cout << "|      FILMEK      |" << std::endl;
    std::cout << "*------------------*" << std::endl;
}

void almenu5()
{
    std::cout << "[1] Ev alapjan\n";
    std::cout << "[2] Film hossza alapjan\n";
    std::cout << "[0] Visszalepes\n";
    std::cout << "Valasztas: ";
}
