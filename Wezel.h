#pragma once

class Wezel {
public:
	Wezel* Nastepny;
	int wierzcholek;
	int waga;

	Wezel(Wezel* Nast, int wierz, int wag);
};
