#pragma once
#include "Kula.h"
class KuleZapelniane : public Kula
{
private:
	int idKuli;
public:
	KuleZapelniane(float x, float y, int id);
	~KuleZapelniane() = default;
	void zmienKolor(Color kolor);
	Color zwrocKolor();
	int zwrocID();
};

