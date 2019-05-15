#include "pch.h"
#include "Graf_macierz.h"

Graf_macierz::Graf_macierz()
{
	tablica_grafu = nullptr;
	il_krawedz = 0;
	il_wierzcholek = 0;
}

Graf_macierz::~Graf_macierz()
{
	Usun_macierz();
}

void Graf_macierz::Usun_macierz()
{
	for (int i = 0; i < il_wierzcholek; i++)
		delete[] tablica_grafu[i];
	delete[] tablica_grafu;
	tablica_grafu = nullptr;
}

void Graf_macierz::Czytaj_z_pliku()
{
	fstream plik;
	int poczatek = 0, koniec = 0, waga = 0;
	plik.open("Wejscie.txt", ios::in);
	if (plik.good())
	{
		if (tablica_grafu != nullptr)
			Usun_macierz();
		plik >> il_krawedz >> il_wierzcholek >> start;
		tablica_grafu = new int*[il_wierzcholek];
		int i, j;
		for (i = 0; i < il_wierzcholek; i++)
			tablica_grafu[i] = new int[il_wierzcholek];

		for (i = 0; i < il_wierzcholek; i++)
		{
			for (j = 0; j < il_wierzcholek; j++)
				tablica_grafu[i][j] = 0;
		}

		for (i = 0; i < il_krawedz; i++)
		{
			plik >> poczatek >> koniec >> waga;
			tablica_grafu[poczatek][koniec] = waga;
			tablica_grafu[koniec][poczatek] = waga;
		}
		plik.close();
	}
	else
		cout << "Plik nie zosta³ otworzony" << endl;
}

void Graf_macierz::Generator(int ile_wierz, int gestosc, int max, int min)
{
	if (tablica_grafu != nullptr)
		Usun_macierz();
	tablica_grafu = new int*[ile_wierz];
	il_wierzcholek = ile_wierz;
	il_krawedz = (gestosc*ile_wierz*(ile_wierz - 1)) / 200;
	bool* Czy_uzyty = new bool[ile_wierz];
	for (int i = 0; i < ile_wierz; i++)
	{
		tablica_grafu[i] = new int[ile_wierz];
		for (int j = 0; j < ile_wierz; j++)
			tablica_grafu[i][j] = 0;
		Czy_uzyty[i] = false;
	}
	int pierwszy = 0;
	Czy_uzyty[pierwszy] = true;
	int drugi;
	int waga_kraw;
	int ile_kraw = 0;
	while (ile_kraw < ile_wierz - 1)
	{
		drugi = Losowy_wierzch(Czy_uzyty);
		waga_kraw = (rand() % max - min + 1) + min;
		tablica_grafu[pierwszy][drugi] = waga_kraw;
		tablica_grafu[drugi][pierwszy] = waga_kraw;
		Czy_uzyty[drugi] = true;
		ile_kraw++;
		pierwszy = drugi;
	}

	waga_kraw = (rand() % max - min + 1) + min;
	tablica_grafu[pierwszy][0] = waga_kraw;
	tablica_grafu[0][pierwszy] = waga_kraw;
	ile_kraw++;

	while (ile_kraw < il_krawedz)
	{
		pierwszy = rand() % ile_wierz;
		drugi = rand() % ile_wierz;
		waga_kraw = (rand() % max - min + 1) + min;

		if (pierwszy != drugi and tablica_grafu[pierwszy][drugi] == 0)
		{
			tablica_grafu[pierwszy][drugi] = waga_kraw;
			tablica_grafu[drugi][pierwszy] = waga_kraw;
			ile_kraw++;
		}
	}

	start = rand() % ile_wierz;
}

int Graf_macierz::Losowy_wierzch(bool *Czy_uzyty)
{
	int los;
	do {
		los = (rand() % il_wierzcholek - 1) + 1;
	} while (Czy_uzyty[los]);
	return los;
}

void Graf_macierz::Drukuj_graf()
{
	cout << "\t";
	int i, j;
	for (i = 0; i < il_wierzcholek; i++)
		cout << i << "\t";
	cout << endl;

	for (i = 0; i < il_wierzcholek; i++)
	{
		cout << i << "\t";
		for (j = 0; j < il_wierzcholek; j++)
			cout << tablica_grafu[i][j] << "\t";
		cout << endl;
	}
	cout << endl;
}

void Graf_macierz::Zapisz_graf_do_pliku()
{
	fstream plik;
	plik.open("Wejscie.txt", ios::out);
	if (plik.good())
	{
		plik << il_krawedz << "\t" << il_wierzcholek << "\t" << start << endl;
		for (int i = 0; i < il_wierzcholek; i++)
			for (int j = i + 1; j < il_wierzcholek; j++)
			{
				if (tablica_grafu[i][j] != 0)
					plik << i << "\t" << j << "\t" << tablica_grafu[i][j] << endl;
			}
		plik.close();
	}
	else
		cout << "Plik nie zosta³ otworzony" << endl;
}

void Graf_macierz::Dijkstra(bool Czy_wypisac)
{
	fstream plik;
	plik.open("Wyjscie.txt", ios::out);
	if (plik.good())
	{
		if (il_wierzcholek != 0)
		{
			if (Czy_wypisac == true)
				plik << "Wierzcholek startowy: " << start << endl;

			Wierzcholek* wierzcholki = Algorytm::Dijkstra(tablica_grafu, nullptr, il_wierzcholek, start);

			if (wierzcholki != nullptr)
			{
				int droga[50];
				int i;
				for (int a = 0; a < il_wierzcholek; a++)
				{
					Wierzcholek wierzcholek = wierzcholki[a];
					if (Czy_wypisac == true)
						plik << "Cel:" << a << " koszt: " << wierzcholek.koszt_dojscia << " droga: ";
					droga[0] = wierzcholek.numer_wierzcholka;
					i = 1;
					while (wierzcholek.poprzednik != -1)
					{
						droga[i] = wierzcholek.poprzednik;
						wierzcholek = wierzcholki[wierzcholek.poprzednik];
						i++;
					}
					Odwroc_tablice(droga, i);
					for (int j = 0; j < i; j++)
					{
						if (Czy_wypisac == true)
							plik << droga[j] << " ";
					}
					if (Czy_wypisac == true)
						plik << endl;
				}
				delete[] wierzcholki;
			}
		}
	}
	else
		cout << "Plik nie zosta³ otworzony" << endl;
}

void Graf_macierz::Zamien_indeksy(int tablica[], int numer1, int numer2)
{
	int pomoc = tablica[numer1];
	tablica[numer1] = tablica[numer2];
	tablica[numer2] = pomoc;
}

void Graf_macierz::Odwroc_tablice(int tab[], int rozmiar)
{
	int i = 0;
	int j = rozmiar - 1;
	while (i < j)
	{
		Zamien_indeksy(tab, i, j);
		i++;
		j = j - 1;
	}
}