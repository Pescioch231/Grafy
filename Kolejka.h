#pragma once
#include <iostream>
#include "Wierzcholek.h"

class Kolejka {

	Wierzcholek* korzen;
	int rozmiar;
	int aktualny_rozmiar;

	void Napraw_w_gore (int index);
	void Napraw_w_dol(int index);

public:
	Kolejka(int rozmiar);
	~Kolejka();

	Wierzcholek pierwszy();
	void Dodaj(Wierzcholek krawedz);
	void Usun();
	bool Czy_pusty();
	void Zmien_sasiada(int wierzcholek, int wartosc, int nowy);
};































