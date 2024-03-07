#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
class Obiekt : public Drawable
{
protected:
	Color idleColor = Color{ 100,100,100};
	Color hoverColor = Color{ 170,170,170};
	Color activeColor = Color::Green;
	int buttonState;
public:
	Obiekt();
	virtual ~Obiekt();

	virtual const bool isPressed() const = 0;
	virtual void update(Vector2f,Color) = 0;
};

