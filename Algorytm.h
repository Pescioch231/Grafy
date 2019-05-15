#pragma once
#include "Kolejka.h"
#include "Graf_lista.h"
#include <iostream>

class Algorytm {
	Algorytm();
	static const int NIESKONCZONOSC = 2147483647;

public:
	static Wierzcholek* Dijkstra(int **macierz, Wezel** lista, int il_wierzcholkow, int start);
};