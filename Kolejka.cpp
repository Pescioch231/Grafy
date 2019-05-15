#include "pch.h"
#include "Kolejka.h"

Kolejka::Kolejka(int rozmiar)
{
	this->rozmiar = rozmiar;
	korzen = new Wierzcholek[rozmiar];
	aktualny_rozmiar = 0;
}

Kolejka::~Kolejka()
{
	delete[] korzen;
	rozmiar = 0;
	aktualny_rozmiar = 0;
}

void Kolejka::Dodaj(Wierzcholek wierzcholek)
{
	if (rozmiar > aktualny_rozmiar)
	{
		*(korzen + aktualny_rozmiar) = wierzcholek;
		aktualny_rozmiar++;
		this->Napraw_w_gore(aktualny_rozmiar - 1);
	}
}

Wierzcholek Kolejka::pierwszy()
{
	return *korzen;
}

void Kolejka::Usun()
{
	if (aktualny_rozmiar != 0)
	{
		if (aktualny_rozmiar - 1 == 0)
			korzen = nullptr;
		else
			*(korzen) = *(korzen + aktualny_rozmiar - 1);
		aktualny_rozmiar--;
		Napraw_w_dol(0);
	}
}

void Kolejka::Napraw_w_gore(int index)
{
	while (index > 0)
	{
		int rodzic = (index - 1) / 2;
		if ((korzen + rodzic)->koszt_dojscia > (korzen + index)->koszt_dojscia)
		{
			Wierzcholek pomoc = *(korzen + index);
			*(korzen + index) = *(korzen + rodzic);
			*(korzen + rodzic) = pomoc;
			index = rodzic;
		}
		else
		{
			return;
		}

	}
}

bool Kolejka::Czy_pusty()
{
	if (aktualny_rozmiar > 1)
		return false;
	else
		return true;
}

void Kolejka::Napraw_w_dol(int index)
{
	int prawy, lewy = 2 * index + 1;
	while (index < aktualny_rozmiar)
	{
		prawy = lewy + 1;
		int min = index;
		if (lewy < aktualny_rozmiar and (*(korzen + 1)).koszt_dojscia < (*(korzen + index)).koszt_dojscia)
			min = lewy;
		if (prawy < aktualny_rozmiar and (*(korzen + prawy)).koszt_dojscia < (*(korzen + min)).koszt_dojscia)
			min = prawy;
		if (min != index)
		{
			Wierzcholek pomoc = *(korzen + index);
			*(korzen + index) = *(korzen + min);
			*(korzen + min) = pomoc;
			index = min;
			lewy = 2 * index + 1;
		}
		else
		{
			return;
		}
	}
}

void Kolejka::Zmien_sasiada(int wierzcholek, int wartosc, int nowy)
{
	for (int a = 0; a < aktualny_rozmiar; a++)
	{
		if ((*(korzen + a)).numer_wierzcholka == wierzcholek)
		{
			if ((*(korzen + a)).koszt_dojscia > wartosc)
			{
				(*(korzen + a)).koszt_dojscia = wartosc;
				(*(korzen + a)).poprzednik = nowy;
				Napraw_w_gore(a);
				Napraw_w_dol(a);
			}
			return;
		}
	}
}