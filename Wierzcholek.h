#pragma once

class Wierzcholek {
public:
	int poprzednik;
	int numer_wierzcholka;
	int koszt_dojscia;

	Wierzcholek();
	Wierzcholek(int poc, int kon, int wag);
	~Wierzcholek();
	bool operator()(const Wierzcholek &pierwszy, const Wierzcholek &drugi);
};