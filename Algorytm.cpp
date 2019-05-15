#include "pch.h"
#include "Algorytm.h"
using namespace std;

Algorytm::Algorytm()
{}

Wierzcholek* Algorytm::Dijkstra(int** macierz, Wezel** lista, int il_wierzcholkow, int start)
{
	Kolejka wydatki(il_wierzcholkow);
	Wierzcholek* wierzcholki = new Wierzcholek[il_wierzcholkow];
	

	if (macierz != nullptr or lista != nullptr)
	{
	
		for (int i = 0; i < il_wierzcholkow; i++)
		{
			if (i == start)
				wydatki.Dodaj(Wierzcholek(-1, i, 0));
			else
				wydatki.Dodaj(Wierzcholek(-1, i, NIESKONCZONOSC));
			
		}

		for (int i = 0; i < il_wierzcholkow; i++)
		{
			
			Wierzcholek wierzcholek = wydatki.pierwszy();
			wydatki.Usun();
			if (lista != nullptr)
			{
				Wezel *element = lista[wierzcholek.numer_wierzcholka];
				while (element != nullptr)
				{
					wydatki.Zmien_sasiada(element->wierzcholek, wierzcholek.koszt_dojscia + element->waga, wierzcholek.numer_wierzcholka);
					element = element->Nastepny;
				}
			}
			else if (macierz != nullptr)
			{
				for (int a = 0; a < il_wierzcholkow; a++)
				{
					if (macierz[wierzcholek.numer_wierzcholka][a] == 0) continue;
					wydatki.Zmien_sasiada(a, wierzcholek.koszt_dojscia + macierz[wierzcholek.numer_wierzcholka][a], wierzcholek.numer_wierzcholka);
				}
			}
			wierzcholki[wierzcholek.numer_wierzcholka] = wierzcholek;
		}
	}
	return wierzcholki;
}