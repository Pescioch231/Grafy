#pragma once
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "Kolejka.h"
#include "Algorytm.h"
using namespace std;



class Graf_macierz {
	int il_wierzcholek;
	int il_krawedz;
	int start;

	int** tablica_grafu;

public:
	Graf_macierz();
	~Graf_macierz();
	void Czytaj_z_pliku();
	void Generator(int ile_wierz, int gestosc, int max, int min);
	void Zapisz_graf_do_pliku();
	void Drukuj_graf();
	void Dijkstra(bool Czy_wypisac);

private:
	void Usun_macierz();
	int Losowy_wierzch(bool* Czy_uzyty);
	void Zamien_indeksy(int tablica[], int numer1, int numer2);
	void Odwroc_tablice(int tab[], int rozmiar);
};