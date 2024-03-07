#include "Napis.h"
Napis::Napis(Font* font, std::string text, int rozmiar, Color kolor) {
	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(kolor);
	this->text.setCharacterSize(rozmiar);
}

void Napis::draw(RenderTarget& target, RenderStates state) const {
	target.draw(this->text, state);
}

float Napis::zwrocPozycjex() {
	float x = this->text.getGlobalBounds().width / 2.f;
	return x;
}

float Napis::zwrocPozycjey() {
	float y = this->text.getGlobalBounds().height / 2.f;
	return y;
}
void Napis::ustawPozycje(float x, float y) {
	this->text.setPosition(x, y);
}