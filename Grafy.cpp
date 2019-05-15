#include "pch.h"
#include "Graf_macierz.h"
#include "Graf_lista.h"
#include <iostream>

void Tester(int gestosc)
{
	fstream plik;
	plik.open("Dane.txt", ios::out | ios::app);
	if (plik.good() == true)
	{
		double srednia_macierz[5];
		double srednia_lista[5];
		const int ilosc_pomiarow = 8;
		double Pomiary_macierzy[ilosc_pomiarow];
		double Pomiary_listy[ilosc_pomiarow];
		int Ilosci[] = { 10, 50, 100, 500, 1000 };
		double licznik, srednia;
		clock_t start1, stop1, start2, stop2;
		double czas;

		Graf_macierz graf1;
		Graf_lista graf2;
		for (int i = 0; i < 5; i++)  //ilosc wierzcholkow
		{
				for (int z = 0; z < ilosc_pomiarow; z++)   //ilosc pomiarow
				{
					graf1.Generator(Ilosci[i], gestosc, 100, 0);
					start1 = clock();
					graf1.Dijkstra(0);
					stop1 = clock();
					czas = (double)(stop1 - start1) / CLOCKS_PER_SEC;
					Pomiary_macierzy[z] = czas;

					graf2.Generator(Ilosci[i], gestosc, 100, 0);
					start2 = clock();
					graf2.Dijkstra(0);
					stop2 = clock();
					czas = (double)(stop2 - start2) / CLOCKS_PER_SEC;
					Pomiary_listy[z] = czas;
				}
				licznik = 0;
				for (int k = 0; k < ilosc_pomiarow; k++)
					licznik += Pomiary_macierzy[k];
				srednia = licznik / ilosc_pomiarow;
				srednia_macierz[i] = srednia;
				licznik = 0;
				for (int k = 0; k < ilosc_pomiarow; k++)
					licznik += Pomiary_listy[k];
				srednia = licznik / ilosc_pomiarow;
				srednia_lista[i] = srednia;
		}
		plik << "Macierz, gestosc: " << gestosc << endl;
		for (int t = 0; t < 5; t++)
		{
			plik << srednia_macierz[t] << "\t";
		}
		plik << endl;
		plik << "Lista, gestosc: " << gestosc << endl;
		for (int t = 0; t < 5; t++)
		{
			plik << srednia_lista[t] << "\t";
		}
		plik << endl << endl;
	}
	else
		cout << "BLAD: nie mozna otworzyc pliku." << endl;
}

int main()
{
	srand(time(NULL));
	Graf_macierz grafik;
	grafik.Generator(10, 70, 10, 0);
	grafik.Drukuj_graf();
	grafik.Zapisz_graf_do_pliku();
	grafik.Czytaj_z_pliku();
	//grafik.Drukuj_graf();
	grafik.Dijkstra(1);
	cout << endl << endl << endl << endl << endl;
	Graf_lista grafik2;
	grafik2.Generator(10, 70, 10, 0);
	grafik2.Drukuj_graf();
	grafik2.Zapisz_graf_do_pliku();
	grafik2.Czytaj_z_pliku();
	//grafik2.Drukuj_graf();
	grafik2.Dijkstra(1);
	int gestosc = 100;
	//Tester(gestosc);


	return 0;
}
