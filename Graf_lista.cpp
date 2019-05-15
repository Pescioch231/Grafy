#include "pch.h"
#include "Graf_lista.h"

Graf_lista::Graf_lista()
{
	lista_grafu = nullptr;
	il_wierzcholkow = 0;
	il_krawedzi = 0;
}

Graf_lista::~Graf_lista()
{
	Usun_liste();
}

void Graf_lista::Usun_liste()
{
	if (lista_grafu != nullptr)
	{
		Wezel* pomoc1, *pomoc2;
		for (int i = 0; i < il_wierzcholkow; i++)
		{
			pomoc1 = lista_grafu[i];
			while (pomoc1 != nullptr)
			{
				pomoc2 = pomoc1;
				pomoc1 = pomoc1->Nastepny;
				delete pomoc2;
			}
		}
		delete[] lista_grafu;
		lista_grafu = nullptr;
	}
}

void Graf_lista::Dodaj_wezel(int poczatek, int koniec, int waga)
{
	Wezel* nowy = new Wezel(lista_grafu[poczatek], koniec, waga);
	lista_grafu[poczatek] = nowy;
}

bool Graf_lista::Czy_istnieje_krawedz(int poczatek, int koniec)
{
	Wezel* zmienna = lista_grafu[poczatek];
	while (zmienna != nullptr)
	{
		if (zmienna->wierzcholek == koniec)
			return true;
		zmienna = zmienna->Nastepny;
	}
	return false;
}

int Graf_lista::Waga_krawedzi(int poczatek, int koniec)
{
	if (Czy_istnieje_krawedz(poczatek, koniec))
	{
		Wezel* zmienna = lista_grafu[poczatek];
		while (zmienna->wierzcholek != koniec)
		{
			zmienna = zmienna->Nastepny;
		}
		return zmienna->waga;
	}
	else
		cout << "Nie istnieje taka krawedz!" << endl;
	return 0;
}

int Graf_lista::Losowy_wierzcholek(bool* Czy_uzyty)
{
	int los;
	do {
		los = (rand() % il_wierzcholkow - 1) + 1;
	} while (Czy_uzyty[los]);
	return los;
}

void Graf_lista::Czytaj_z_pliku()
{
	fstream plik;
	int poczatek = 0, koniec = 0, waga = 0;
	plik.open("Wejscie.txt", ios::in);
	if (plik.good())
	{
		if (lista_grafu != nullptr)
			Usun_liste();
		plik >> il_krawedzi >> il_wierzcholkow >> start;
		lista_grafu = new Wezel* [il_wierzcholkow];
		for (int i = 0; i < il_wierzcholkow; i++)
			lista_grafu[i] = nullptr;

		int poczatek, koniec, wartosc;
		for (int i = 0; i < il_krawedzi; i++)
		{
			plik >> poczatek >> koniec >> wartosc;
			Dodaj_wezel(poczatek, koniec, wartosc);
			Dodaj_wezel(koniec, poczatek, wartosc);
		}
		plik.close();
	}
	else
		cout << "Plik nie zosta³ otworzony" << endl;
}

void Graf_lista::Generator(int ile_wierz, int gestosc, int max, int min)
{
	if (lista_grafu != nullptr)
		Usun_liste();
	lista_grafu = new Wezel* [ile_wierz];
	il_wierzcholkow = ile_wierz;
	il_krawedzi = (gestosc*ile_wierz*(ile_wierz - 1)) / 200;
	bool* Czy_uzyty = new bool[ile_wierz];
	for (int i = 0; i < ile_wierz; i++)
	{
		lista_grafu[i] = nullptr;
		Czy_uzyty[i] = false;
	}
	int pierwszy = 0;
	Czy_uzyty[pierwszy] = true;
	int drugi;
	int waga_kraw;
	int ile_kraw = 0;
	while (ile_kraw < ile_wierz - 1)
	{
		drugi = Losowy_wierzcholek(Czy_uzyty);
		waga_kraw = (rand() % max - min + 1) + min;
		Dodaj_wezel(pierwszy, drugi, waga_kraw);
		Dodaj_wezel(drugi, pierwszy, waga_kraw);
		Czy_uzyty[drugi] = true;
		ile_kraw++;
		pierwszy = drugi;
	}

	waga_kraw = (rand() % max - min + 1) + min;
	Dodaj_wezel(pierwszy, 0, waga_kraw);
	Dodaj_wezel(0, pierwszy, waga_kraw);
	ile_kraw++;

	while (ile_kraw < il_krawedzi)
	{
		pierwszy = rand() % ile_wierz;
		drugi = rand() % ile_wierz;
		waga_kraw = (rand() % max - min + 1) + min;

		if (pierwszy != drugi and !Czy_istnieje_krawedz(pierwszy, drugi))
		{
			Dodaj_wezel(pierwszy, drugi, waga_kraw);
			Dodaj_wezel(drugi, pierwszy, waga_kraw);
			ile_kraw++;
		}
	}

	start = rand() % ile_wierz;
}

void Graf_lista::Zapisz_graf_do_pliku()
{
	fstream plik;
	plik.open("Wejscie.txt", ios::out);
	if (plik.good())
	{
		plik << il_krawedzi << "\t" << il_wierzcholkow << "\t" << start << endl;
		int i, j;
		for (i = 0; i < il_wierzcholkow; i++)
		{
			for (j = i + 1; j < il_wierzcholkow; j++)
				if (Czy_istnieje_krawedz(i, j))
				{
					plik << i << "\t" << j << "\t" << Waga_krawedzi(i, j) << endl;
				}
		}
		plik.close();
	}
	else
		cout << "Plik nie zosta³ otworzony" << endl;
}

void Graf_lista::Drukuj_graf()
{
	Wezel* pomocnik;
	for (int i = 0; i < il_wierzcholkow; i++)
	{
		pomocnik = lista_grafu[i];
		cout << i << "\t";
		while (pomocnik != nullptr)
		{
			cout << pomocnik->wierzcholek << "-" << pomocnik->waga << "\t";
			pomocnik = pomocnik->Nastepny;
		}
		cout << endl;
	}
	cout << endl;
}

void Graf_lista::Dijkstra(bool Czy_wypisac)
{
	fstream plik;
	plik.open("Wyjscie2.txt", ios::out);
	if (plik.good())
	{
		if (il_wierzcholkow != 0)
		{
			if (Czy_wypisac == true)
				plik << "Wierzcholek startowy: " << start << endl;
			Wierzcholek* wierzcholki = Algorytm::Dijkstra(nullptr, lista_grafu, il_wierzcholkow, start);
			if (wierzcholki != nullptr)
			{
				int droga[50];
				int i;
				for (int a = 0; a < il_wierzcholkow; a++)
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

void Graf_lista::Zamien_indeksy(int tablica[], int numer1, int numer2)
{
	int pomoc = tablica[numer1];
	tablica[numer1] = tablica[numer2];
	tablica[numer2] = pomoc;
}

void Graf_lista::Odwroc_tablice(int tab[], int rozmiar)
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





