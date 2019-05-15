#include "pch.h"
#include "Wierzcholek.h"

bool Wierzcholek::operator()(const Wierzcholek &pierwszy, const Wierzcholek &drugi)
{
	if (pierwszy.koszt_dojscia > drugi.koszt_dojscia)
		return true;
	else
		return false;
}

Wierzcholek::Wierzcholek()
{
	poprzednik = 0;
	numer_wierzcholka = 0;
	koszt_dojscia = 0;
}

Wierzcholek::Wierzcholek(int poc, int kon, int wag)
{
	poprzednik = poc;
	numer_wierzcholka = kon;
	koszt_dojscia = wag;
}

Wierzcholek::~Wierzcholek()
{
	poprzednik = 0;
	numer_wierzcholka = 0;
	koszt_dojscia = 0;
}













