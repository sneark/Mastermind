#include "Game.h"

RenderWindow* Game::window;
Przycisk przycisk(410, 680, 150, 50, Color{ 180,180,180 }, Color{ 100,100,100 }, Color::Green);
Przycisk nowagra(150, 400, 150, 50, Color{ 180,180,180 }, Color{ 100,100,100 }, Color::Green);

Game::Game(float x, float y, std::string title)
{
    window = new RenderWindow(VideoMode((unsigned int)x, (unsigned int)y), title);
    window->setFramerateLimit(60);
    Image icon;
    if (icon.loadFromFile("Textures\\icon.png")) {
        window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    }
    srand(time(NULL));
}

Game::~Game() {
    delete window;
    wskaznik = nullptr;
    delete wskaznik;
}

void Game::Run()
{
    ustawTeksture();

    czcionka.loadFromFile("Textures\\Themilan.ttf");

    stworzKule();

    Napis sprawdz(&czcionka, "Sprawdz", 36, Color::White);
    sprawdz_x = przycisk.zwrocPozycjex() - sprawdz.zwrocPozycjex();
    sprawdz_y = przycisk.zwrocPozycjey() - sprawdz.zwrocPozycjey();
    sprawdz.ustawPozycje(sprawdz_x, sprawdz_y - 10);

    Napis tytul(&czcionka, "Master Mind", 48, Color::White);
    tytul.ustawPozycje(85, 135);

    while (window->isOpen())
    {
        Event event;
        window->clear(Color{ 173, 134, 134 });
        window->draw(this->tlo);
        for (int i = 0; i < 36; i++)
            window->draw(kulezapelniane[i]);
        for (int j = 0; j < 36; j++)
            window->draw(kulepodpowiedzi[j]);
        for (int j = 0; j < 8; j++)
            window->draw(kulewyboru[j]);
        for (int j = 0; j < 4; j++){
            window->draw(kulewyniku[j]);
        }
        window->draw(przycisk);
        window->draw(sprawdz);
        window->draw(tytul);

        while (window->pollEvent(event)) {
            Vector2f mousePos = (Vector2f)Mouse::getPosition(*window);
            wskaznik = &przycisk;
            wskaznik->update(mousePos,gainedcolor);
            wskaznik = &nowagra;
            wskaznik->update(mousePos,gainedcolor);
            for (int i = 0; i < 8; i++) {
                wskaznik = &kulewyboru[i];
                wskaznik->update(mousePos, kolory[i]);
            }

            if (event.type == Event::MouseButtonPressed) {

                for (int i = 0; i < 8; i++) {
                    wskaznik = &kulewyboru[i];
                    if (wskaznik->isPressed() == true) gainedcolor = kulewyboru[i].wezKolor();
                }

                ustawWybranyKolor(mousePos);
                sprawdzenieWyniku();      

                if (nowagra.isPressed() == true && czyWygrana != 2) {
                    nowaGra();
                }
            }
            if (event.type == Event::Closed) {
                window->close();
                break;
            }
            if (event.type == Event::Resized)
            {
                FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window->setView(sf::View(visibleArea));
            }
        }

        if(czyWygrana != 2) wyswietlWynik();

        window->display();
    }
}

const void Game::stworzKule() 
{
    int kuleX{}, kuleY{};
    //kule wyboru
    kuleX = { 4 };
    kuleY = { 2 };
    int l = 0;
    for (int i = 0; i < kuleY; i++) {
        for (int j = 0; j < kuleX; j++) {
            kulewyboru.emplace_back(25.0f);
            kulewyboru[l].ustawPozycje((j + 1) * (kuleX + 50), (i + 2) * (kuleY + 50), 90, 450);
            kulewyboru[l].ustawKolor(kolory[l]);
            kulewyboru[l].ustawTeksture(teksturaKula);
            l++;
        }
    }
    //kule zape³niane
    int licznikID = 0;
    kuleX = { 4 };
    kuleY = { 9 };
    for (int i = 0; i < kuleY; i++) {
        for (int j = 0; j < kuleX; j++) {
            kulezapelniane.emplace_back((j + 1) * (kuleX + 50), (i + 2) * (kuleY + 50), licznikID);
            kulezapelniane[licznikID].ustawTeksture(teksturaKula);
            licznikID++;
        }
    }
    //kule podpowiedzi
    kuleX = { 4 };
    kuleY = { 9 };
    l = 0;
    for (int i = 0; i < kuleY; i++) {
        for (int j = 0; j < kuleX; j++) {
            kulepodpowiedzi.emplace_back(13.0f);
            kulepodpowiedzi[l].ustawPozycje((j + 1) * (kuleX + 25), (i + 2) * (kuleY + 50), 600, 50);
            kulepodpowiedzi[l].ustawKolor(Color{ 189, 187, 187 });
            l++;
        }
    }

    //kule wyniku
    kuleX = { 4 };
    kuleY = { 1 };
    l = 0;
    for (int i = 0; i < kuleY; i++) {
        for (int j = 0; j < kuleX; j++) {
            losowanie[l] = (std::rand() % 8);
            wynik[l] = kolory[losowanie[l]];
            kulewyniku.emplace_back(25.0f);
            kulewyniku[l].ustawPozycje((j + 1) * (kuleX + 50), (i + 2) * (kuleY + 50), 350, -15 );
            kulewyniku[j].ustawKolor(gainedcolor);
            kulewyniku[l].ustawTeksture(teksturaKula);
            l++;
        }
    }
}

void Game::ustawTeksture()
{
    if (!this->teksturatla.loadFromFile("Textures\\tlo.png"))
        cout << "BLAD LADOWANIA TEKSTURY TLA" << endl;
    if (!this->teksturaSprawdz.loadFromFile("Textures\\przycisk.png"))
        cout << "BLAD LADOWANIA TEKSTURY PRZYCISKU" << endl;
    if (!this->teksturaKula.loadFromFile("Textures\\kula2.png"))
        cout << "BLAD LADOWANIA TEKSTURY KUL" << endl;

    this->tlo.setTexture(this->teksturatla);
    przycisk.ustawTeksture(teksturaSprawdz);
    nowagra.ustawTeksture(teksturaSprawdz);
}

void Game::ustawWybranyKolor(Vector2f mousePos)
{
    if (start >= 0 && this->czyWygrana == 2) {
        for (int ustaw = start; ustaw >= koniec; ustaw--) {
            id = kulezapelniane[ustaw].zwrocID();
            if (kulezapelniane[ustaw].sprawdzMyszke(mousePos) == true) {
                if (id == start) {
                    wynikDoSprawdzenia[0] = gainedcolor;
                }
                else if (id == start - 1) {
                    wynikDoSprawdzenia[1] = gainedcolor;
                }
                else if (id == start - 2) {
                    wynikDoSprawdzenia[2] = gainedcolor;
                }
                else if (id == start - 3) {
                    wynikDoSprawdzenia[3] = gainedcolor;
                }
                kulezapelniane[id].zmienKolor(gainedcolor);
            }
        }
    }
}

void Game::sprawdzenieWyniku() {
    int czysprawdzany = 0;
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 8; i++) {
            if (wynikDoSprawdzenia[j] == kolory[i]) czysprawdzany++;
        }
    }
    if (przycisk.isPressed() == true && czyWygrana == 2 && czysprawdzany > 0) {
        int kolory = przycisk.sprawdzkolor(wynik, wynikDoSprawdzenia);
        int pomocnicza;
        int miejsca = przycisk.sprawdzmiejsce(wynik, wynikDoSprawdzenia);
        pomocnicza = miejsca;
        int rzad = 0;
        for (int i = kolejna; i >= 0; i--) {
            if (rzad < 4) {
                if (miejsca >= 4) {
                    czyWygrana = 0;
                }
                if (miejsca > 0) {
                    kulepodpowiedzi[i].ustawKolor(Color::Black);
                    miejsca--;
                    rzad++;
                }
                else if (kolory - pomocnicza > 0) {
                    kulepodpowiedzi[i].ustawKolor(Color::White);
                    kolory--;
                    rzad++;
                }
                else {
                    kulepodpowiedzi[i].ustawKolor(Color{ 189, 187, 187 });
                    rzad++;
                }
            }
            else {
                kolejna -= 4;
                break;
            }
        }
        wynikDoSprawdzenia[0] = Color::Black;
        wynikDoSprawdzenia[1] = Color::Black;
        wynikDoSprawdzenia[2] = Color::Black;
        wynikDoSprawdzenia[3] = Color::Black;
        start -= 4;
        koniec -= 4;

        if (koniec == -4 && pomocnicza < 4) {
            czyWygrana = 1;
        }
    }
}

const void Game::wyswietlWynik()
{
    Napis nowa_gra(&czcionka, "NOWA GRA", 32, Color::White);
    sprawdz_x = nowagra.zwrocPozycjex() - nowa_gra.zwrocPozycjex();
    sprawdz_y = nowagra.zwrocPozycjey() - nowa_gra.zwrocPozycjey();
    nowa_gra.ustawPozycje(sprawdz_x, sprawdz_y - 10);

    Napis wygrana(&czcionka, "WYGRALES", 48, Color::Green);
    wygrana.ustawPozycje(120, 300);

    Napis przegrana(&czcionka, "PRZEGRALES", 48, Color::Red);
    przegrana.ustawPozycje(100, 300);

    window->draw(nowagra);
    for (int i = 0; i < 4; i++) {
        kulewyniku[i].ustawKolor(wynik[i]);
    }
    if (this->czyWygrana == 0)
    {
        window->draw(wygrana);
        window->draw(nowa_gra);
    }
    else if (this->czyWygrana == 1) {
        window->draw(przegrana);
        window->draw(nowa_gra);
    }
}

void Game::nowaGra()
{
    gainedcolor = Color{ 189, 187, 187 };
    czyWygrana = 2;
    id = 0;
    kolejna = 35;
    start = 35;
    koniec = 32;
    for (int i = 0; i < 4; i++) {
        losowanie[i] = (std::rand() % 8);
        wynik[i] = kolory[losowanie[i]];
        kulewyniku[i].ustawKolor(gainedcolor);
    }
    for (int i = 0; i <= 35; i++) {
        kulezapelniane[i].ustawKolor(gainedcolor);
        kulepodpowiedzi[i].ustawKolor(gainedcolor);
    }
}

