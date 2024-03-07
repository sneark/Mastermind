#include "KuleZapelniane.h"
KuleZapelniane::KuleZapelniane(float x, float y, int id) {
	this->idKuli = id;
	shape.setPosition(x+350, y+50);
	shape.setRadius(this->ballRadius);
	shape.setFillColor(Color{ 189, 187, 187 });
	shape.setOrigin(this->ballRadius, this->ballRadius);
}

void KuleZapelniane::zmienKolor(Color kolor) {
	shape.setFillColor(kolor);
}

Color KuleZapelniane::zwrocKolor() {
	return shape.getFillColor();
}

int KuleZapelniane::zwrocID() {
	return idKuli;
}