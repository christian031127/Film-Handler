#include <sstream>

#include "memtrace.h"

#include "gtest_lite.h"
#include "filmtar.h"

using std::cout;
using std::endl;
using std::cin;

///gtest_lite tesztek
void teszt()
{
    //Tesztek a String osztályra

    TEST(String, ures_string)
        String ures;
        EXPECT_EQ((size_t)0, ures.size());

        /// Ellenõrizzük, hogy üres sztringet ("") kaptunk-e vissza
        EXPECT_STREQ("", ures.c_str());
    END


    TEST(String, karakterbol_string)
        char ch = 'a';
        String a(ch);
        EXPECT_EQ((size_t)1, a.size());
        EXPECT_STREQ("a", a.c_str());

        String b('a');    // konstansból is megy
        EXPECT_STREQ("a", b.c_str());
    END

    TEST(String, karakterbol_string)
        const char *hello = "Hello sztring";
        String a(hello);
        EXPECT_EQ(strlen(hello), a.size());
        EXPECT_STREQ(hello, a.c_str());

        /// Ellenõrizzük, hogy lemásolta-e a sztringet. Nem elég a pointert!
        char cpp[] = { 'C', '+', '+', '\0' };
        String b(cpp);
        cpp[0] = 'X';
        EXPECT_STRNE(cpp, b.c_str());
    END

    TEST(String, konstruktor)
        const char *hello = "Hello sztring";
        String a(hello);
        String b = a;
        EXPECT_EQ(strlen(hello), b.size());
        EXPECT_STREQ(hello, b.c_str());

        /// Ellenõrizzük, hogy lemásolta-e a sztringet. Nem elég a pointert!
        if (a.c_str() == b.c_str())     // Ha a két pointer egyezik, akkor nem másolta le az adatot
            FAIL();

        EXPECT_STREQ(hello, a.c_str());
        EXPECT_EQ(strlen(hello), a.size());

        const String c = a;
        String d = c;     // konstansból is megy
        EXPECT_STREQ(hello, d.c_str());
    END

    TEST(String, konstruktor_nullptr)
        String d0;
        String ures = d0;     // üres sztringet is le tudja másolni
        EXPECT_EQ((size_t)0, ures.size());

        /// Ellenõrizzük, hogy üres sztringet ("") kaptunk-e vissza?
        EXPECT_STREQ("", ures.c_str());
    END

    TEST(String, operator=)
        const char *hello = "Hello sztring";
        String a(hello);
        String b("Duma1"), c("Duma2");
        EXPECT_STRNE(a.c_str(), b.c_str());
        a = a;
        EXPECT_EQ(strlen(hello), a.size());
        EXPECT_STREQ(hello, a.c_str());
        c = b = a;

        /// Ellenõrizzük, hogy lemásolta-e a sztringet
        if (a.c_str() == b.c_str())     // Ha a két pointer egyezik, akkor nem másolta le az adatot
            FAIL();

        EXPECT_EQ(strlen(hello), a.size());
        EXPECT_STREQ(hello, a.c_str());
        EXPECT_EQ(strlen(hello), b.size());
        EXPECT_STREQ(hello, b.c_str());
        EXPECT_EQ(strlen(hello), c.size());
        EXPECT_STREQ(hello, c.c_str());

        const String d("Konst.");
        c = d;        // konstansból is megy
        EXPECT_EQ(c.size(), c.size());
        EXPECT_STREQ(d.c_str(), c.c_str());
    END

    TEST(String, operator=_nullptr)
        String d0;
        String c = d0;     // üres sztringet is le tudja másolni
        EXPECT_EQ((size_t)0, c.size());

        /// Ellenõrizzük, hogy üres sztringet ("") kaptunk-e vissza?
        EXPECT_STREQ("", c.c_str());
    END

    TEST(String, string_plusz_string)
        String a("Hello ");
        String b("sztring");
        String c;
        c = a + b;
        EXPECT_STREQ("Hello sztring", c.c_str());
        EXPECT_STREQ("Hello ", a.c_str());
        EXPECT_STREQ("sztring", b.c_str());
        const String a1 = a, b1 = b;

        String c1;
        c1 = a1 + b1;          // konstansból is megy
        EXPECT_STREQ("Hello sztring", c1.c_str());
    END

    TEST(String, string_plusz_karakter)
        String a("Hello ");
        String b;
        b = a + 'B';
        EXPECT_STREQ("Hello B", b.c_str());
        EXPECT_STREQ("Hello ", a.c_str());

        const String a1 = a;
        String b1;
        b1 = a1 + 'B';          // konstansból is megy
        EXPECT_STREQ("Hello B", b1.c_str());
        EXPECT_STREQ("Hello ", a1.c_str());
    END

    TEST(String, karakter_plusz_string)
        String a("ello");
        String b;
        char h = 'H';
        b = h + a;
        EXPECT_STREQ("Hello", b.c_str());
        EXPECT_STREQ("ello", a.c_str());

        String b1;
        b1 = 'H' + a;  // konstanssal is megy
        EXPECT_STREQ("Hello", b.c_str());
    END

    TEST(String, index)
        String a("Hello 678");
        EXPECT_NO_THROW(a[0]);
        EXPECT_NO_THROW(a[7]);
        EXPECT_NO_THROW(a[8]);
        EXPECT_THROW(a[9], const char *);
        EXPECT_THROW(a[-1], const char *);
        EXPECT_EQ('7', a[7]);
        a[7] = '.';
        EXPECT_EQ('.', a[7]);
        try
        {
            a[15];
        }
        catch (const char* hiba)
        {
            ;
        }
    END

    TEST(String, inserter)
        String a("Hello sztring");
        std::stringstream ss;
        ss << a;
        EXPECT_STREQ("Hello sztring", ss.str().c_str());
    END

    TEST(String, extractor)
        String a("Hello   sztring \n Lajos12");
        std::stringstream ss;
        ss << a;
        String in1, in2, in3;
        ss >> in1 >> in2;         // fûzhetõnek kell lenni
        while (ss >> in3);
        EXPECT_STREQ("Hello", in1.c_str());
        EXPECT_STREQ("sztring", in2.c_str());
        EXPECT_STREQ("Lajos12", in3.c_str());
    END

    TEST(String, karakter_plusz_sztring)
        String s0("World");
        String result = 'H' + s0;
        EXPECT_EQ(result, "HWorld");
    END

    TEST(String, global_operator=)
        String s1("Hello");
        String s2("Hello");
        String s3("World");
        EXPECT_TRUE(s1 == s2);
        EXPECT_FALSE(s1 == s3);
    END

//Tesztek a Film osztályra

    TEST(Film, konstruktor_getter_setter)
        Film film;
        EXPECT_EQ(String(""), film.getNev());
        EXPECT_EQ(0, film.getHossz());
        EXPECT_EQ(1900, film.getEv());

        film.setNev("Matrix");
        film.setHossz(125);
        film.setEv(2011);
        EXPECT_EQ(String("Matrix"), film.getNev());
        EXPECT_EQ(125, film.getHossz());
        EXPECT_EQ(2011, film.getEv());

        Film proba("Nagyfiuk", 105, 2015);
        EXPECT_EQ(String("Nagyfiuk"), proba.getNev());
        EXPECT_EQ(105, proba.getHossz());
        EXPECT_EQ(2015, proba.getEv());
    END

    TEST(Film, cpy_konstruktor)
        Film eredeti("Titanic", 195, 1997);
        Film masolat(eredeti);
        EXPECT_EQ(masolat.getNev(), String("Titanic"));
        EXPECT_EQ(masolat.getHossz(), 195);
        EXPECT_EQ(masolat.getEv(), 1997);
    END

    TEST(Film, input_stream)
        std::stringstream ss("Titanic 195 1997");
        Film film(ss);
        EXPECT_EQ(film.getNev(), String("Titanic"));
        EXPECT_EQ(film.getHossz(), 195);
        EXPECT_EQ(film.getEv(), 1997);
    END

    TEST(Film, film_kiir)
        Film film("Titanic", 195, 1997);
        std::stringstream ss;
        film.film_kiir(ss);
        EXPECT_EQ(ss.str(), "Film Titanic 195 1997\n");
    END

    TEST(Film, operator==)
        Film film1("Titanic", 195, 1997);
        Film film2("Titanic", 195, 1997);
        Film film3("Avatar", 162, 2009);
        EXPECT_TRUE(film1 == film2);
        EXPECT_FALSE(film1 == film3);
    END

//Tesztek a Csaladi osztályra

    TEST(Csaladi, konstruktor_getter_setter)
        Csaladi film;
        EXPECT_EQ(String(""), film.getNev());
        EXPECT_EQ(0, film.getHossz());
        EXPECT_EQ(1900, film.getEv());
        EXPECT_EQ(0, film.getKorhatar());

        film.setNev("Matrix");
        film.setHossz(125);
        film.setEv(2011);
        film.setKorhatar(12);
        EXPECT_EQ(String("Matrix"), film.getNev());
        EXPECT_EQ(125, film.getHossz());
        EXPECT_EQ(2011, film.getEv());
        EXPECT_EQ(12, film.getKorhatar());

        Csaladi proba("Nagyfiuk", 105, 2015, 12);
        EXPECT_EQ(String("Nagyfiuk"), proba.getNev());
        EXPECT_EQ(105, proba.getHossz());
        EXPECT_EQ(2015, proba.getEv());
        EXPECT_EQ(12, proba.getKorhatar());
    END

    TEST(Csaladi, cpy_konstruktor)
        Csaladi eredeti("Titanic", 195, 1997, 12);
        Csaladi masolat(eredeti);
        EXPECT_EQ(masolat.getNev(), String("Titanic"));
        EXPECT_EQ(masolat.getHossz(), 195);
        EXPECT_EQ(masolat.getEv(), 1997);
        EXPECT_EQ(masolat.getKorhatar(), 12);
    END

    TEST(Csaladi, input_stream)
        std::stringstream ss;
        ss << "Szerelem 120 2022 16";
        Csaladi csaladi(ss);
        ASSERT_EQ(csaladi.getNev(), String("Szerelem"));
        ASSERT_EQ(csaladi.getHossz(), 120);
        ASSERT_EQ(csaladi.getEv(), 2022);
        ASSERT_EQ(csaladi.getKorhatar(), 16);
    END

    TEST(Csaladi, film_kiir)
        Csaladi film("Titanic", 195, 1997, 12);
        std::stringstream ss;
        film.film_kiir(ss);
        EXPECT_EQ(ss.str(), "Csaladi Titanic 195 1997 12\n");
    END

    TEST(Csaladi, operator==)
        Csaladi film1("Titanic", 195, 1997, 12);
        Csaladi film2("Titanic", 195, 1997, 12);
        Csaladi film3("Avatar", 162, 2009, 16);
        EXPECT_TRUE(film1 == film2);
        EXPECT_FALSE(film1 == film3);
    END

//Tesztek a Dokumentum osztályra

    TEST(Dokumentum, konstruktor_getter_setter)
        Dokumentum film;
        EXPECT_EQ(String(""), film.getNev());
        EXPECT_EQ(0, film.getHossz());
        EXPECT_EQ(1900, film.getEv());
        EXPECT_EQ(String(""), film.getLeiras());

        film.setNev("Piramis");
        film.setHossz(125);
        film.setEv(2011);
        film.setLeiras("Antik faraok tortenete");
        EXPECT_EQ(String("Piramis"), film.getNev());
        EXPECT_EQ(125, film.getHossz());
        EXPECT_EQ(2011, film.getEv());
        EXPECT_EQ(String("Antik faraok tortenete"), film.getLeiras());

        Dokumentum proba("Piramis", 105, 2015, "Antik faraok tortenete");
        EXPECT_EQ(String("Piramis"), proba.getNev());
        EXPECT_EQ(105, proba.getHossz());
        EXPECT_EQ(2015, proba.getEv());
        EXPECT_EQ(String("Antik faraok tortenete"), proba.getLeiras());
    END

    TEST(Dokumentum, cpy_konstruktor)
        Dokumentum eredeti("Piramis", 195, 1997, "Antik faraok tortenete");
        Dokumentum masolat(eredeti);
        EXPECT_EQ(masolat.getNev(), String("Piramis"));
        EXPECT_EQ(masolat.getHossz(), 195);
        EXPECT_EQ(masolat.getEv(), 1997);
        EXPECT_EQ(masolat.getLeiras(), String("Antik faraok tortenete"));
    END


    TEST(Dokumentum, input_stream)
        std::stringstream ss;
        ss << "Piramis 120 2022 Antik_faraok_tortenete\n";
        Dokumentum csaladi(ss);
        ASSERT_EQ(csaladi.getNev(), String("Piramis"));
        ASSERT_EQ(csaladi.getHossz(), 120);
        ASSERT_EQ(csaladi.getEv(), 2022);
        ASSERT_EQ(csaladi.getLeiras(), String("Antik_faraok_tortenete"));
    END

    TEST(Dokumentum, film_kiir)
        Dokumentum film("Piramis", 195, 1997, "Antik faraok tortenete");
        std::stringstream ss;
        film.film_kiir(ss);
        EXPECT_EQ(ss.str(), "Dokumentum Piramis 195 1997 Antik faraok tortenete\n");
    END

    TEST(Dokumentum, operator==)
        Dokumentum film1("Piramis", 195, 1997, 12);
        Dokumentum film2("Piramis", 195, 1997, 12);
        Dokumentum film3("Avatar", 162, 2009, 16);
        EXPECT_TRUE(film1 == film2);
        EXPECT_FALSE(film1 == film3);
    END

//Tesztek a Filmtar osztályra

    TEST(Filmtar, konstruktor_getter)
        Filmtar tar;
        EXPECT_EQ(0, static_cast<int>(tar.getMeret()));
        EXPECT_EQ(0, static_cast<int>(tar.getMax_meret()));
        Filmtar tarolo(150);
        EXPECT_EQ(0, static_cast<int>(tar.getMeret()));
        EXPECT_EQ(150, static_cast<int>(tarolo.getMax_meret()));
    END

    TEST(Filmtar, cpy_konstruktor)
        Filmtar tarolo(2);
        Film* proba1 = new Film("Proba", 120, 1999);

        tarolo.felvetel(proba1);

        Filmtar masolas(tarolo);
        EXPECT_EQ(1, static_cast<int>(masolas.getMeret()));
        EXPECT_EQ(2, static_cast<int>(masolas.getMax_meret()));
    END

    TEST(Filmtar, indexeles)
        Filmtar tarolo(3);

        Film* proba0 = new Film("Proba", 121, 1998);
        Csaladi* proba1 = new Csaladi("Nagyfiuk", 135, 2015, 12);
        Dokumentum* proba2 = new Dokumentum("Allatok", 55, 2021, "Elet a vadonban");

        tarolo.felvetel(proba0);
        tarolo.felvetel(proba1);
        tarolo.felvetel(proba2);

        EXPECT_EQ(String("Proba"), tarolo[0]->getNev());
        EXPECT_EQ(121, tarolo[0]->getHossz());
        EXPECT_EQ(1998, tarolo[0]->getEv());

        Csaladi* csaladi_elem = dynamic_cast<Csaladi*>(tarolo[1]);
        if (csaladi_elem)
        {
            EXPECT_EQ(12, csaladi_elem->getKorhatar());
        }
        else
        {
            std::cerr << "Ervenyes indexu elemet adjon meg!" << std::endl;
        }

        Dokumentum* dokumentum_elem = dynamic_cast<Dokumentum*>(tarolo[2]);
        if (dokumentum_elem)
        {
            EXPECT_EQ(String("Elet a vadonban"), dokumentum_elem->getLeiras());
        }
        else
        {
            std::cerr << "Ervenyes indexu elemet adjon meg!" << std::endl;
        }

        std::cout << "Hibakezeles miatt jelenik meg a kovetkezo:\n";
        try
        {
            tarolo[4];
        }
        catch (const char* hiba)
        {
            ;
        }
    END

    TEST(Filmtar, tarolo_tele)
        Filmtar tarolo(3);

        std::cout << "Hibakezeles miatt jelenik meg a kovetkezo:\n";
        try
        {
            tarolo.felvetel(new Film("Proba", 111, 1879));
            tarolo.felvetel(new Csaladi("Proba", 111, 1879, 12));
            tarolo.felvetel(new Dokumentum("Proba", 111, 1879, "Proba szoveg"));
            tarolo.felvetel(new Film("Tul sok", 111, 1879));
        }
        catch (const char* hiba)
        {
            ;
        }
    END

    TEST(Filmtar, felvetel_operator == )
        Filmtar tarolo1(5);
        Filmtar tarolo2(5);
        EXPECT_TRUE(tarolo1 == tarolo2);

        Filmtar tarolo3(6);
        EXPECT_FALSE(tarolo1 == tarolo3);

        Filmtar tarolo4(5);
        Filmtar tarolo5(5);

        Csaladi* proba1 = new Csaladi("Nagyfiuk", 135, 2015, 12);
        Dokumentum* proba2 = new Dokumentum("Allatok", 55, 2021, "Elet_a_vadonban");
        tarolo4.felvetel(proba1);
        tarolo4.felvetel(proba2);

        Csaladi* proba3 = new Csaladi("Nagyfiuk", 135, 2015, 12);
        Dokumentum* proba4 = new Dokumentum("Allatok", 55, 2021, "Elet_a_vadonban");
        tarolo5.felvetel(proba3);
        tarolo5.felvetel(proba4);

        EXPECT_TRUE(tarolo4 == tarolo5);
        EXPECT_FALSE(tarolo1 == tarolo4);
    END

    TEST(Filmtar, eltavolitas_index)
        Filmtar tarolo(3);

        tarolo.felvetel(new Film("Proba", 111, 1879));
        tarolo.felvetel(new Csaladi("Proba", 111, 1879, 12));
        tarolo.felvetel(new Dokumentum("Proba", 111, 1879, "Proba szoveg"));

        EXPECT_EQ(3, static_cast<int>(tarolo.getMeret()));

        tarolo.eltavolitas(2);

        EXPECT_EQ(2, static_cast<int>(tarolo.getMeret()));

        std::cout << "Hibakezeles miatt jelenik meg a kovetkezo:\n";
        try
        {
            tarolo.eltavolitas(2);
        }
        catch (const char* hiba)
        {
            ;
        }

        Filmtar tarolo2(3);

        tarolo2.felvetel(new Film("Proba1", 111, 1879));
        tarolo2.felvetel(new Csaladi("Proba2", 111, 1879, 12));
        tarolo2.felvetel(new Dokumentum("Proba3", 111, 1879, "Proba szoveg"));

        tarolo2.eltavolitas(1);

        Dokumentum* dokumentum_elem = dynamic_cast<Dokumentum*>(tarolo2[1]);
        if (dokumentum_elem)
        {
            EXPECT_EQ(String("Proba szoveg"), dokumentum_elem->getLeiras());
        }
        else
        {
            std::cerr << "Ervenyes indexu elemet adjon meg!" << std::endl;
        }

        EXPECT_EQ(111, tarolo[0]->getHossz());
    END

    TEST(Filmtar, eltavolitas_nev)
        Filmtar tarolo(3);

        tarolo.felvetel(new Film("Proba1", 111, 1879));
        tarolo.felvetel(new Csaladi("Proba2", 111, 1879, 12));
        tarolo.felvetel(new Dokumentum("Proba3", 111, 1879, "Proba szoveg"));

        EXPECT_EQ(3, static_cast<int>(tarolo.getMeret()));

        tarolo.eltavolitas("Proba1");

        EXPECT_EQ(2, static_cast<int>(tarolo.getMeret()));

        std::cout << "Hibakezeles miatt jelenik meg a kovetkezo:\n";
        try
        {
            tarolo.eltavolitas("Proba1");
        }
        catch (const char* hiba)
        {
            ;
        }

        Filmtar tarolo2(3);

        tarolo2.felvetel(new Film("Proba1", 111, 1879));
        tarolo2.felvetel(new Csaladi("Proba2", 111, 1879, 12));
        tarolo2.felvetel(new Dokumentum("Proba3", 111, 1879, "Proba szoveg"));

        tarolo2.eltavolitas("Proba2");

        Dokumentum* dokumentum_elem = dynamic_cast<Dokumentum*>(tarolo2[1]);
        if (dokumentum_elem)
        {
            EXPECT_EQ(String("Proba szoveg"), dokumentum_elem->getLeiras());
        }
        else
        {
            std::cerr << "Ervenyes indexu elemet adjon meg!" << std::endl;
        }

        EXPECT_EQ(111, tarolo[0]->getHossz());
    END

    TEST(Filmtar, kiiras)
        Filmtar tarolo(3);

        tarolo.felvetel(new Film("Proba1", 111, 1879));
        tarolo.felvetel(new Csaladi("Proba2", 211, 1999, 16));
        tarolo.felvetel(new Dokumentum("Proba3", 101, 1179, "Proba szoveg"));

        std::stringstream ss;
        tarolo.kiir(ss);

        //std::string használata, mivel a gtest_lite nem tudja ebben a formátumban kezelni a sajat string osztályt
        EXPECT_EQ(std::string("Film Proba1 111 1879\nCsaladi Proba2 211 1999 16\nDokumentum Proba3 101 1179 Proba szoveg\n"), ss.str());

        //Második elem eltávolítása
        tarolo.eltavolitas("Proba2");

        std::stringstream ss2;
        tarolo.kiir(ss2);

        //Középső elem kiesik
        EXPECT_EQ(std::string("Film Proba1 111 1879\nDokumentum Proba3 101 1179 Proba szoveg\n"), ss2.str());

        //Harmadik elem felvétele
        Csaladi* felvetel_proba = new Csaladi("Proba2", 211, 1999, 16);
        tarolo.felvetel(felvetel_proba);

        std::stringstream ss3;
        tarolo.kiir(ss3);

        //Új elem a lista végére illeszkedik
        EXPECT_EQ(std::string("Film Proba1 111 1879\nDokumentum Proba3 101 1179 Proba szoveg\nCsaladi Proba2 211 1999 16\n"), ss3.str());
    END

    TEST(Filmtar, kereses)
        Filmtar tarolo(3);

        tarolo.felvetel(new Film("Proba1", 111, 1879));
        tarolo.felvetel(new Csaladi("Proba2", 211, 1999, 16));
        tarolo.felvetel(new Dokumentum("Proba3", 101, 1179, "Proba szoveg"));

        Csaladi* csaladi_elem = dynamic_cast<Csaladi*>(tarolo.kereses("Proba2"));
        if (csaladi_elem)
        {
            EXPECT_EQ(16, csaladi_elem->getKorhatar());
        }

        Dokumentum* dokumentum_elem = dynamic_cast<Dokumentum*>(tarolo.kereses("Proba3"));
        if (dokumentum_elem)
        {
            EXPECT_EQ(String("Proba szoveg"), dokumentum_elem->getLeiras());
        }

        std::cout << "Hibakezeles miatt jelenik meg a kovetkezo:\n";
        try
        {
            tarolo.kereses("Proba5");
        }
        catch (const char* hiba)
        {
            ;
        }
    END

    TEST(Filmtar, modositasok)
        Filmtar tarolo(4);

        Film* proba0 = new Film("Proba", 121, 1998);
        Csaladi* proba1 = new Csaladi("Nagyfiuk", 135, 2015, 12);
        Dokumentum* proba2 = new Dokumentum("Allatok", 55, 2021, "Elet a vadonban");
        Film* proba3 = new Film("Nincs", 10, 1999);

        tarolo.felvetel(proba0);
        tarolo.felvetel(proba1);
        tarolo.felvetel(proba2);

        tarolo.modosit(proba1, "Valtozas");
        tarolo.modosit(proba0, 122);
        tarolo.modosit_overload(proba2, 2023);

        tarolo.modosit(proba1, 16);
        tarolo.modosit(proba2, "Vadallatok vilaga");

        EXPECT_EQ(String("Valtozas"), proba1->getNev());
        EXPECT_EQ(122, proba0->getHossz());
        EXPECT_EQ(2023, proba2->getEv());

        EXPECT_EQ(16, proba1->getKorhatar());
        EXPECT_EQ(String("Vadallatok vilaga"), proba2->getLeiras());

        std::cout << "Hibakezeles miatt jelenik meg a kovetkezo:\n";
        try
        {
            tarolo.modosit(proba3, "Hoppa");
        }
        catch (const char* hiba)
        {
            ;
        }

        //Törölni kell az adott objektumot mivel dinamikusan lett foglalva
        //És nem lett felhasználva a tárolóban, ahol végül lefutna a destruktor
        delete proba3;

        std::stringstream ss;
        tarolo.kiir(ss);

        EXPECT_EQ(std::string("Film Proba 122 1998\nCsaladi Valtozas 135 2015 16\nDokumentum Allatok 55 2023 Vadallatok vilaga\n"), ss.str());
    END

    TEST(Filmtar, fajlba_kiiras)
        Filmtar tarolo(5);

        Film* proba0 = new Film("Titanic", 255, 1999);
        Csaladi* proba1 = new Csaladi("Nagyfiuk", 165, 2010, 12);
        Dokumentum* proba2 = new Dokumentum("Asvanyok", 111, 2019, "Hazank_kincsei");

        tarolo.felvetel(proba0);
        tarolo.felvetel(proba1);
        tarolo.felvetel(proba2);

        tarolo.kiir_fajl("teszt.txt");
        EXPECT_TRUE(tarolo.kiir_fajl("teszt.txt"));
    END

    TEST(Filmtar, fajlbol_beolvasas)
        Filmtar tarolo("teszt.txt", 10);

        EXPECT_EQ(255,tarolo[0]->getHossz());

        Csaladi* csaladi_elem = dynamic_cast<Csaladi*>(tarolo[1]);
        if (csaladi_elem)
        {
            EXPECT_EQ(165, csaladi_elem->getHossz());
            EXPECT_EQ(12, csaladi_elem->getKorhatar());
        }

        Dokumentum* dokumentum_elem = dynamic_cast<Dokumentum*>(tarolo[2]);
        if (dokumentum_elem)
        {
            EXPECT_EQ(2019, dokumentum_elem->getEv());
            EXPECT_EQ(String("Hazank_kincsei"), dokumentum_elem->getLeiras());
        }
    END

    TEST(Filmtar, rendezes_ev)
        Filmtar tarolo(10);

        Film* film1 = new Film("Titanic", 255, 2010);
        Csaladi* film2 = new Csaladi("Nagyfiuk", 165, 1996, 12);
        Dokumentum* film3 = new Dokumentum("Asvanyok", 111, 2019, "Hazank_kincsei");
        Film* film4 = new Film("Transfromers", 230, 2013);
        Csaladi* film5 = new Csaladi("Kapitany", 145, 2001, 16);
        Dokumentum* film6 = new Dokumentum("Faraok", 60, 2024, "Titkok_kamraja");

        tarolo.felvetel(film1);
        tarolo.felvetel(film2);
        tarolo.felvetel(film3);
        tarolo.felvetel(film4);
        tarolo.felvetel(film5);
        tarolo.felvetel(film6);

        //Rendezés előtt
        EXPECT_EQ(String("Titanic"), tarolo[0]->getNev());
        EXPECT_EQ(String("Nagyfiuk"), tarolo[1]->getNev());
        EXPECT_EQ(String("Asvanyok"), tarolo[2]->getNev());
        EXPECT_EQ(String("Transfromers"), tarolo[3]->getNev());
        EXPECT_EQ(String("Kapitany"), tarolo[4]->getNev());
        EXPECT_EQ(String("Faraok"), tarolo[5]->getNev());

        tarolo.rendezes(ev_alapjan);
        //Rendezés után

        //2024
        EXPECT_EQ(String("Faraok"), tarolo[0]->getNev());
        //2019
        EXPECT_EQ(String("Asvanyok"), tarolo[1]->getNev());
        //2013
        EXPECT_EQ(String("Transfromers"), tarolo[2]->getNev());
        //2010
        EXPECT_EQ(String("Titanic"), tarolo[3]->getNev());
        //2001
        EXPECT_EQ(String("Kapitany"), tarolo[4]->getNev());
        //1996
        EXPECT_EQ(String("Nagyfiuk"), tarolo[5]->getNev());
    END

    TEST(Filmtar, rendezes_hossz)
        Filmtar tarolo(10);

        Film* film1 = new Film("Titanic", 255, 2010);
        Csaladi* film2 = new Csaladi("Nagyfiuk", 165, 1996, 12);
        Dokumentum* film3 = new Dokumentum("Asvanyok", 111, 2019, "Hazank_kincsei");
        Film* film4 = new Film("Transfromers", 230, 2013);
        Csaladi* film5 = new Csaladi("Kapitany", 145, 2001, 16);
        Dokumentum* film6 = new Dokumentum("Faraok", 60, 2024, "Titkok_kamraja");

        tarolo.felvetel(film1);
        tarolo.felvetel(film2);
        tarolo.felvetel(film3);
        tarolo.felvetel(film4);
        tarolo.felvetel(film5);
        tarolo.felvetel(film6);

        //Rendezés előtt
        EXPECT_EQ(String("Titanic"), tarolo[0]->getNev());
        EXPECT_EQ(String("Nagyfiuk"), tarolo[1]->getNev());
        EXPECT_EQ(String("Asvanyok"), tarolo[2]->getNev());
        EXPECT_EQ(String("Transfromers"), tarolo[3]->getNev());
        EXPECT_EQ(String("Kapitany"), tarolo[4]->getNev());
        EXPECT_EQ(String("Faraok"), tarolo[5]->getNev());

        tarolo.rendezes(hossz_alapjan);
        //Rendezés után

        //60
        EXPECT_EQ(String("Faraok"), tarolo[0]->getNev());
        //111
        EXPECT_EQ(String("Asvanyok"), tarolo[1]->getNev());
        //145
        EXPECT_EQ(String("Kapitany"), tarolo[2]->getNev());
        //165
        EXPECT_EQ(String("Nagyfiuk"), tarolo[3]->getNev());
        //230
        EXPECT_EQ(String("Transfromers"), tarolo[4]->getNev());
        //255
        EXPECT_EQ(String("Titanic"), tarolo[5]->getNev());
    END
}

///FŐPROGRAM
int main()
{
    //Konstruktor, ami fájlból olvassa be az adatokat
    Filmtar tarolo("filmtar.txt", 100);

    int menupont;

    //Menürendszer kialakítva az egyes funkciók eléréséhez
    do
    {
        logo();
        fomenu();
        cin >> menupont;
        system("cls");

        switch (menupont)
        {
        case 1:
            {
                // Új film hozzáadása
                std::string tipus;

                String nev;
                int hossz;
                int ev;

                int korhatar;
                String leiras;

                cout << "Add meg a film tipusat (film/csaladi/dokumentum): ";
                cin >> tipus;

                if(tipus != "film" && tipus != "csaladi" && tipus != "dokumentum")
                {
                    cout << "Ervenyes tipust adjon meg!\n\n";
                    break;
                }

                cout << "Add meg a film nevet: ";
                cin >> nev;

                cout << "Add meg a film hosszat (percekben): ";
                cin >> hossz;

                cout << "Add meg a film megjelenesi evet: ";
                cin >> ev;

                if (tipus == "csaladi")
                {
                    cout << "Add meg a korhatart: ";
                    cin >> korhatar;
                    tarolo.felvetel(new Csaladi(nev, hossz, ev, korhatar));
                    cout << "Sikeres felvetel!\n\n";
                }
                else if (tipus == "dokumentum")
                {
                    cout << "Add meg a leirast (also vonallal elvalasztva): ";
                    cin >> leiras;
                    tarolo.felvetel(new Dokumentum(nev, hossz, ev, leiras));
                    cout << "Sikeres felvetel!\n\n";
                }
                else
                {
                    tarolo.felvetel(new Film(nev, hossz, ev));
                    cout << "Sikeres felvetel!\n\n";
                }
            }
            break;
        case 2:
            {
            // Film törlése
            String filmnev;

            cout << "Add meg a film nevet, amelyet torolni szeretnel: ";
            cin >> filmnev;

            bool sikeres = tarolo.benne_van(filmnev);
            tarolo.eltavolitas(filmnev);

            if(sikeres)
                cout << "Sikeres torles!\n\n";
            }
            break;
        case 3:
            {
                // Keresés film neve alapján
                String filmnev;

                cout << "Add meg a keresett film nevet: ";
                cin >> filmnev;

                Film* talalat = tarolo.kereses(filmnev.c_str());
                if (talalat != nullptr)
                {
                    cout << "A keresett film adatai:" << endl;
                    talalat->film_kiir(cout);
                }
                else
                {
                    std::cerr << "Nincs ilyen film a filmtarban!\n" << endl;
                }
            }
            break;
        case 4:
            {
                //Módosítások
                String filmnev;
                cout << "Add meg a film nevet, amelyen modositani szeretnel: ";
                cin >> filmnev;

                Film* film = tarolo.kereses(filmnev.c_str());
                if(film == nullptr)
                {
                    break;
                }

                int valasztas;
                do
                {
                    cout << "Modositasi lehetosegek:\n";
                    cout << "1. Nev modositasa\n";
                    cout << "2. Hossz modositasa\n";
                    cout << "3. Kiadasi ev modositasa\n";
                    if (dynamic_cast<Csaladi*>(film))
                    {
                        cout << "4. Korhatar modositasa\n";
                    }
                    if (dynamic_cast<Dokumentum*>(film))
                    {
                        cout << "4. Leiras modositasa\n";
                    }
                    cout << "0. Visszalepes\n";
                    cout << "Valasszon egy opciot: ";
                    cin >> valasztas;

                    switch (valasztas)
                    {
                    case 1:
                    {
                        cout << "Adja meg az uj nevet: ";
                        String uj_nev;
                        cin.ignore();
                        cin >> uj_nev;
                        tarolo.modosit(film, uj_nev);
                        cout << "Sikeresen modositva\n\n";
                        break;
                    }
                    case 2:
                    {
                        cout << "Adja meg az uj hosszusagot: ";
                        int uj_hossz;
                        cin >> uj_hossz;
                        tarolo.modosit(film, uj_hossz);
                        cout << "Sikeresen modositva\n\n";
                        break;
                    }
                    case 3:
                    {
                        cout << "Adja meg az uj kiadasi evet: ";
                        int uj_ev;
                        cin >> uj_ev;
                        tarolo.modosit_overload(film, uj_ev);
                        cout << "Sikeresen modositva\n\n";
                        break;
                    }
                    case 4:
                    {
                        if (Csaladi* csaladi = dynamic_cast<Csaladi*>(film))
                        {
                            cout << "Adja meg az uj korhatart: ";
                            int uj_korhatar;
                            cin >> uj_korhatar;
                            tarolo.modosit(csaladi, uj_korhatar);
                            cout << "Sikeresen modositva\n\n";
                        }
                        else if (Dokumentum* dokumentum = dynamic_cast<Dokumentum*>(film))
                        {
                            cout << "Adja meg az uj leirast (also vonallal elvalasztva): ";
                            String uj_leiras;
                            cin.ignore();
                            cin >> uj_leiras;
                            tarolo.modosit(dokumentum, uj_leiras);
                            cout << "Sikeresen modositva\n\n";
                        }
                        break;
                    }
                    case 0:
                        system("cls");
                        break;
                    default:
                        cout << ("Ervenytelen valasztas. Probalja ujra.\n\n");
                    }
                }
                while (valasztas != 0);
            }
        case 5:
            {
                //Filmtár kiírása
                almenu4();
                tarolo.kiir(cout);
            }
            break;
        case 6:
            {
                //Rendezések
                logo();
                almenu5();
                cin >> menupont;
                system("cls");

                switch(menupont)
                {
                case 1:
                    tarolo.rendezes(ev_alapjan);
                    cout << "Rendezve!\n\n";
                    break;
                case 2:
                    tarolo.rendezes(hossz_alapjan);
                    cout << "Rendezve!\n\n";
                    break;
                case 0:
                    break;
                default:
                    cout << "Ervenytelen valasztas. Probalja ujra.\n\n";
                    break;
                }
                menupont = -1;
            }
            break;
        case 7:
            {
                //TESZTEK
                teszt();
            }
            break;
        case 0:
            // Kilépés a programból
            cout << "Kilepes...\n";
            break;
        default:
            cout << "Ervenytelen valasztas. Probalja ujra.\n\n";
            break;
        }
    }
    while (menupont != 0);

    //Azért fut le itt, hogy mindenképpen lássa a jporta a tesztek lefutását
    teszt();

    //Mentés a filmtar.txt fáljba
    bool kiiras = tarolo.kiir_fajl("filmtar.txt");
    if(kiiras)
    {
        cout << "\nSikeres mentes!\n";
    }
    else
    {
        cout << "\nSikertelen mentes!\n";
    }

    return 0;
}
