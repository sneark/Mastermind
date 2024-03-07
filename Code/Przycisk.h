#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Obiekt.h"
using namespace sf;

class Przycisk : public Obiekt
{
private:
	RectangleShape shape;
	void draw(RenderTarget& target, RenderStates state) const override;
public:
	Przycisk(float x, float y, float width, float height,Color idleColor, Color hoverColor, Color activeColor);
	Przycisk() = delete;
	~Przycisk() = default;
	
	const bool isPressed() const;
	void update(Vector2f mousePos, Color kolor) override;

	float zwrocPozycjex();
	float zwrocPozycjey();

	int sprawdzkolor(Color wynik[4], Color dosprawdzenia[4]);
	int sprawdzmiejsce(Color wynik[4], Color dosprawdzenia[4]);
	void ustawTeksture(Texture& tekstura);
};

