#include "pch.h"
#include "Wezel.h"

Wezel::Wezel(Wezel *Nast, int wierz, int wag)
{
	Nastepny = Nast;
	wierzcholek = wierz;
	waga = wag;
}