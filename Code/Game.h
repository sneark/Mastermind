#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Kula.h"
#include "KuleZapelniane.h"
#include "Przycisk.h"
#include "Napis.h"
#include "Obiekt.h"
#include <iostream>

using namespace sf;

class Game{
	private:
		Obiekt* wskaznik;

		Sprite tlo;
		Texture teksturatla;
		Texture teksturaSprawdz;
		Texture teksturaKula;

		vector<KuleZapelniane> kulezapelniane;
		vector<Kula> kulewyboru;
		vector<Kula> kulewyniku;
		vector<Kula> kulepodpowiedzi;

		static RenderWindow* window;
		Font czcionka;
		Color wynik[4];
		Color wynikDoSprawdzenia[4];
		Color gainedcolor = Color{ 189, 187, 187 };
		const Color kolory[8] = { Color::Green,Color::Blue,Color::Cyan,Color::Magenta,Color::Red,Color::Yellow,Color{0,100,0 },Color{255,140,0} };

		int czyWygrana = 2;
		int kolejna = 35;
		int start = 35;
		int koniec = 32;
		int id;
		int losowanie[4];
		float sprawdz_x;
		float sprawdz_y;

		const void stworzKule();
		void ustawTeksture();
		void ustawWybranyKolor(Vector2f mousePos);
		void sprawdzenieWyniku();
		const void wyswietlWynik();
		void nowaGra();
	public:
		Game(float x, float y, std::string title);
		Game() = delete;
		~Game();
		void Run();
};

