#pragma once
#include <SFML/Graphics.hpp>
#include "Obiekt.h"
using namespace sf;
using namespace std;

class Kula : public Obiekt
{
protected:
	CircleShape shape;
	const float ballRadius{ 25.0f };
	void draw(RenderTarget& target, RenderStates state) const override;
public:
	Kula(float radius);
	Kula();
	~Kula() = default;

	void update(Vector2f mousePos, Color kolor) override;
	const bool isPressed() const override;
	void ustawTeksture(Texture& tekstura);

	Vector2f wezPozycje();
	Color wezKolor();
	bool sprawdzMyszke(Vector2f mousePos);
	void ustawKolor(Color kolor);
	void ustawPozycje(float x, float y, int moveX, int moveY);
};

