#pragma once
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "Wezel.h"
#include "Kolejka.h"
#include "Algorytm.h"
using namespace std;

class Graf_lista {
	Wezel** lista_grafu;
	int start;
	int il_wierzcholkow;
	int il_krawedzi;

	int Losowy_wierzcholek(bool* Czy_uzyty);
	void Dodaj_wezel(int poczatek, int koniec, int waga);
	void Usun_liste();
	bool Czy_istnieje_krawedz(int poczatek, int koniec);
	int Waga_krawedzi(int poczatek, int koniec);
	void Zamien_indeksy(int tablica[], int numer1, int numer2);
	void Odwroc_tablice(int tab[], int rozmiar);

public:
	Graf_lista();
	~Graf_lista();
	void Czytaj_z_pliku();
	void Generator(int ile_wierz, int gestosc, int max, int min);
	void Zapisz_graf_do_pliku();
	void Drukuj_graf();
	void Dijkstra(bool Czy_wypisac);
};