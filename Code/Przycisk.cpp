#include "Przycisk.h"
#include <iostream>

void Przycisk::draw(RenderTarget& target, RenderStates state) const {
	target.draw(this->shape, state);
}

Przycisk::Przycisk(float x, float y, float width, float height,Color idleColor, Color hoverColor, Color activeColor) {

	this->buttonState = 0;
	this->shape.setSize(Vector2f(width, height));
	this->shape.setPosition(x, y);
	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;
	this->shape.setFillColor(this->idleColor);

}


const bool Przycisk::isPressed() const {
	if (this->buttonState == 2) {
		return true;
	}
	else
		return false;
}

void Przycisk::update(Vector2f mousePos, Color kolor) {
	this->buttonState = 0;
	if (this->shape.getGlobalBounds().contains(mousePos)) {
		this->buttonState = 1;
		if (Mouse::isButtonPressed(Mouse::Left)) {
			this->buttonState = 2;
		}
	}

	switch (this->buttonState) {
	case 0:
		this->shape.setFillColor(this->idleColor);
		break;
	case 1:
		this->shape.setFillColor(this->hoverColor);
		break;
	case 2:
		this->shape.setFillColor(Color{0,255,0});
		break;
	default:
		this->shape.setFillColor(Color::Red);
		break;
	}
}

float Przycisk::zwrocPozycjex() {
	float x = this->shape.getPosition().x + this->shape.getGlobalBounds().width / 2.f;
	return x;
}

float Przycisk::zwrocPozycjey() {
	float y = this->shape.getPosition().y + this->shape.getGlobalBounds().height / 2.f;
	return y;
}

int Przycisk::sprawdzkolor(Color wynik[4], Color dosprawdzenia[4]) {
	int licznik = 0;
	int tymczasowa[4] = {5,5,5,5};
	bool warunek = false;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (dosprawdzenia[i] == wynik[j] && tymczasowa[j] != j) {
				tymczasowa[j] = j;
				licznik++;
				break;
			}
		}
	}
	return licznik;
}

int Przycisk::sprawdzmiejsce(Color wynik[4], Color dosprawdzenia[4]) {
	int licznik = 0;
	int odwrotnie = 3;
	for (int j = 0; j < 4; j++) {
		if (dosprawdzenia[j] == wynik[odwrotnie]) {
			licznik++;
			odwrotnie--;
		}
		else odwrotnie--;
	}
	return licznik;
}

void Przycisk::ustawTeksture(Texture& tekstura)
{
	this->shape.setTexture(&tekstura);
}
