#include "filmtar.h"

Filmtar::Filmtar(size_t max_m) : max_meret(max_m)
{
    filmek = new Film * [max_meret]; //Dinamikus mem�riater�let foglal�sa a filmek sz�m�ra
    meret = 0; // A kezdeti m�ret 0, mert m�g egyetlen filmet sem adtunk hozz�
}

Filmtar::Filmtar(const Filmtar& other) :
    filmek(new Film*[other.max_meret]), // �j dinamikus mem�riater�let foglal�sa a m�sik objektum m�ret�vel
    meret(other.meret), // Az �j objektum m�rete megegyezik a m�sik objektum�val
    max_meret(other.max_meret) // Az �j objektum maxim�lis m�rete megegyezik a m�sik objektum�val
{
    for (size_t i = 0; i < meret; ++i) // A m�sik objektumban tal�lhat� filmek m�sol�sa
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
    if(meret >= max_meret) // Ellen�rzi, hogy a filmt�r tele van-e
    {
        delete film; // T�rli a hozz�adni k�v�nt filmet, ha a filmt�r tele van
        std::cerr << "Tele van a filmtar!" << std::endl; // Hiba�zenet ki�r�sa
    }
    else
    {
        filmek[meret] = film; // Hozz�adja a filmet a filmt�rhoz
        meret++; // N�veli a filmt�r m�ret�t
    }
}

bool Filmtar::benne_van(const String& filmnev) const
{
    for (size_t i = 0; i < meret; ++i) // V�gigmegy az �sszes filmen a filmt�rban
    {
        if (filmek[i]->getNev() == filmnev) // �sszehasonl�tja a film nev�t a keresett n�vvel
        {
            return true;
        }
    }
    return false;
}

Film* Filmtar::kereses(const char* filmnev) const
{
    for (size_t i = 0; i < meret; ++i) // V�gigmegy az �sszes filmen a filmt�rban
    {
        const char* cim = filmek[i]->getNev().c_str(); // Lek�ri a film c�m�t C-string form�tumban
        if (strstr(cim, filmnev) != nullptr) // Ellen�rzi, hogy a keresett n�v r�sze-e a film c�m�nek
        {
            return filmek[i];
        }
    }
    std::cerr << "Ervenyes filmnevet adjon meg!" << std::endl; // Hiba�zenet, ha a film nem tal�lhat�
    return nullptr;
}

void Filmtar::modosit(Film* film, const String& uj_nev)
{
    bool talalt = false; // Flag v�ltoz�, ami jelzi, ha megtal�lta a filmet
    for (size_t i = 0; i < meret; ++i) // V�gigmegy a filmt�rban l�v� filmeken
    {
        if (filmek[i] == film) // Ellen�rzi, hogy az aktu�lis film ugyanaz-e, mint a keresett film
        {
            talalt = true; // Ha megtal�lja a filmet, be�ll�tja a talalt flaget igaz �rt�kre
            break;
        }
    }
    if (!talalt) // Ha nem tal�lta meg a filmet a filmt�rban
    {
        std::cerr << "A megadott film nem talalhato a filmtarban!" << std::endl;
        return;
    }

    film->setNev(uj_nev); // A film c�m�t m�dos�tja az �j n�vre
}

///Tov�bbi m�dos�t� f�ggv�nyek is hasonl�an m�k�dnek!
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
    if(index >= meret) // Ellen�rzi, hogy az index �rv�nyes-e
    {
        std::cerr << "Ervenyes indexu elemet adjon meg!" << std::endl; // Hiba�zenet
        return;
    }
    else
    {
        delete filmek[index]; // T�rli az adott indexen l�v� filmet
        for (size_t i = index; i < meret - 1; ++i) // �thelyezi a t�bbi filmet egy helyet el�re
        {
            filmek[i] = filmek[i + 1];
        }
        meret--; // Cs�kkenti a filmt�r m�ret�t
    }
}

void Filmtar::eltavolitas(const String& film)
{
    size_t i = 0;
    while(i < meret) // V�gigmegy a filmt�rban l�v� filmeken
    {
        if(filmek[i]->getNev() == film) // Ellen�rzi, hogy az aktu�lis film neve egyezik-e a keresett n�vvel
        {
            eltavolitas(i); // Ha tal�l egyez�st, elt�vol�tja a filmet az adott indexen
            return;
        }
        i++;
    }
    std::cerr << "Ervenyes filmnevet adjon meg!" << std::endl; // Hiba�zenet
}

void Filmtar::kiir(std::ostream& os) const
{
    size_t i = 0;
    while(i < meret) // V�gigmegy a filmt�rban l�v� filmeken
    {
        filmek[i]->film_kiir(os); // Ki�rja az aktu�lis film adatait az adott kimeneti adatfolyamba
        i++;
    }
}

Filmtar::~Filmtar()
{
    size_t i = 0;
    while(i < meret) // V�gigmegy a filmt�rban l�v� filmeken
    {
        delete filmek[i]; // T�rli az aktu�lis filmet
        i++;
    }
    delete[] filmek; // Felszabad�tja a filmek t�mbj�t
}

Film* Filmtar::operator[](size_t index) const
{
    if(index >= meret) // Ellen�rzi, hogy az index �rv�nyes-e
    {
        std::cerr << "Ervenyes indexu elemet adjon meg!" << std::endl; // Hiba�zenet
        return nullptr; // Visszat�r nullptr �rt�kkel, ha az index �rv�nytelen
    }

    // Dinamikus t�puskonverzi� a filmekhez, hogy lehessen �ket kezelni a lesz�rmazott t�pusuk szerint
    if (Dokumentum* df = dynamic_cast<Dokumentum*>(filmek[index])) // Dokumentumra t�rt�n� konverzi�
    {
        return df; // Visszat�r a dinamikus t�puskonverzi� ut�n kapott pointerrel
    }
    else if (Csaladi* cf = dynamic_cast<Csaladi*>(filmek[index])) // Csal�di filmre t�rt�n� konverzi�
    {
        return cf; // Visszat�r a dinamikus t�puskonverzi� ut�n kapott pointerrel
    }
    else // Ha nincs t�puskonverzi�, akkor a film pointer�t adja vissza
    {
        return filmek[index]; // Visszat�r az adott indexen l�v� film pointer�vel
    }
}

Filmtar& Filmtar::operator=(const Filmtar& masik)
{
    if (this != &masik) // Ellen�rzi, hogy az �rt�kad�s nem t�rt�nik-e meg ugyanarra az objektumra
    {
        delete[] filmek; // Felszabad�tja az aktu�lis objektum �ltal foglalt er�forr�sokat

        meret = masik.meret; // M�solja a m�sik objektum m�ret�t

        filmek = new Film*[max_meret]; // L�trehoz egy �j dinamikus t�mb�t a filmeknek

        for (size_t i = 0; i < meret; ++i) // V�gigmegy a m�sik objektum filmjein
        {
            filmek[i] = new Film(*(masik.filmek[i])); // M�solja a filmeket az �j t�mbbe
        }
    }
    return *this; // Visszat�r az aktu�lis objektum referenci�j�val
}

bool Filmtar::operator==(const Filmtar& masik) const
{
    if (max_meret != masik.max_meret) // Ellen�rzi, hogy a filmt�rak ugyanakkora m�ret�ek-e
        return false;

    if(meret != masik.meret) // Ellen�rzi, hogy a filmt�rak ugyanannyi filmet tartalmaznak-e
    {
        return false;
    }
    else
    {
        size_t i = 0;
        while(i < meret) // V�gigmegy a filmeket tartalmaz� t�mb�k�n
        {
            if(!(*filmek[i] == *masik.filmek[i])) // Ellen�rzi, hogy a filmek egyenl�ek-e
            {
                return false; // Ha legal�bb egy film nem egyenl�, akkor a filmt�rak nem egyenl�ek
            }
            i++;
        }
    }
    return true; // Ha minden film egyenl� volt, akkor a filmt�rak egyenl�ek
}

Filmtar::Filmtar(const char* fajl, size_t max_meret) : filmek(new Film*[max_meret]), meret(0), max_meret(max_meret)
{
    std::ifstream file(fajl); // F�jl megnyit�sa olvas�sra
    if(!file.is_open()) // Ellen�rzi, hogy siker�lt-e megnyitni a f�jlt
    {
        throw "Nem sikerult megnyitni a fajlt!"; // Hiba�zenet
    }
    if(file.is_open())
    {
        while(!file.eof()) // A f�jl feldolgoz�sa, am�g nem �r a v�g�re
        {
            String film_tipusa; // A film t�pus�nak t�rol�s�ra szolg�l� string v�ltoz�
            file >> film_tipusa; // Beolvassa a f�jlb�l a film t�pus�t

            /// Az olvasott t�pusnak megfelel�en l�trehoz �s hozz�ad egy �j filmet a filmt�rhoz
            if(film_tipusa == "Film")
            {
                Film* film = new Film(file); // L�trehoz egy �j Film objektumot a f�jlb�l beolvasott adatokkal
                felvetel(film); // Hozz�adja az �j filmet a filmt�rhoz
            }
            else if(film_tipusa == "Csaladi")
            {
                Csaladi* film = new Csaladi(file); // L�trehoz egy �j Csaladi objektumot a f�jlb�l beolvasott adatokkal
                felvetel(film); // Hozz�adja az �j filmet a filmt�rhoz
            }
            else if(film_tipusa == "Dokumentum")
            {
                Dokumentum* film = new Dokumentum(file); // L�trehoz egy �j Dokumentum objektumot a f�jlb�l beolvasott adatokkal
                felvetel(film); // Hozz�adja az �j filmet a filmt�rhoz
            }
            else if(strcmp(film_tipusa.c_str(), "\n") == 0) // Ellen�rzi, hogy az olvasott sor �res-e
            {
                std::cerr << "Ervenytelen tipus!\n\n"; // Hiba�zenet, ha az olvasott t�pus �rv�nytelen
            }
        }
        file.close(); // F�jl bez�r�sa
    }
}

bool Filmtar::kiir_fajl(const char* fajl)
{
    std::ofstream ofs(fajl); // F�jl l�trehoz�sa
    if (!ofs.is_open()) // Ellen�rzi, hogy siker�lt-e megnyitni a f�jlt
    {
        return false; // Ha nem, akkor hamissal t�r vissza
    }
    kiir(ofs); // Ki�rja a filmt�rat a megadott f�jlba
    ofs.close(); // F�jl bez�r�sa
    return true; // Igazzal t�r vissza, ha sikeres volt a ki�r�s
}

bool ev_alapjan(Film const& egyik, Film const& masik)
{
    bool tmp = egyik.getEv() > masik.getEv(); // �sszehasonl�tja k�t film kiad�si �v�t
    return tmp;
}

bool hossz_alapjan(Film const& egyik, Film const& masik)
{
    bool tmp =  egyik.getHossz() < masik.getHossz(); // �sszehasonl�tja k�t film hossz�t
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
