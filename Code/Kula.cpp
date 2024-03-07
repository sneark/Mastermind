#include "Kula.h"
Kula::Kula(float radius) {
	shape.setRadius(radius);
	shape.setFillColor(Color::White);
	shape.setOrigin(radius, radius);
}

Kula::Kula(){
}

void Kula::draw(RenderTarget& target, RenderStates state) const {
	target.draw(this->shape, state);
}

Color Kula::wezKolor() {
	return this->shape.getFillColor();
}

const bool Kula ::isPressed() const {
	if (buttonState == 2) {
		return true;
	}
	else
		return false;
}

void Kula::update(Vector2f mousePos, Color kolor)
{
	buttonState = 0;
	if (shape.getGlobalBounds().contains(mousePos)) {
		buttonState = 1;
		if (Mouse::isButtonPressed(Mouse::Left)) {
			buttonState = 2;
		}
	}

	switch (buttonState) {
	case 0:
		shape.setFillColor(kolor);
		break;
	case 1:
		shape.setFillColor(kolor - Color{0,0,0,100});
		break;
	case 2:
		shape.setFillColor(kolor);
		break;
	default:
		shape.setFillColor(Color::Red);
		break;
	}
}

Vector2f Kula::wezPozycje() {
	sf::Vector2f pozycjakuli = shape.getPosition();
	return pozycjakuli;
}

bool Kula::sprawdzMyszke(Vector2f mousePos) {
	if (shape.getGlobalBounds().contains(mousePos))
	{
		return true;
	}
	return false;
}

void Kula::ustawKolor(Color kolor) {
	shape.setFillColor(kolor);;
}

void Kula::ustawPozycje(float x, float y, int moveX, int moveY)
{
	shape.setPosition(x+moveX, y+moveY);
}

void Kula::ustawTeksture(Texture& tekstura)
{
	this->shape.setTexture(&tekstura);
}
