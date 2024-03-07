#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
class Napis : public Drawable
{
public:
	Napis(Font* font, std::string text, int rozmiar, Color kolor);
	~Napis() = default;
	float zwrocPozycjex();
	float zwrocPozycjey();
	void ustawPozycje(float x, float y);
private:
	void draw(RenderTarget& target, RenderStates state) const override;
	Font* font;
	Text text;
};

