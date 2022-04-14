#include "Memorija.h"
#include <iostream>

IS::Memorija::Memorija(std::string naziv,long long vrijednost)
{
	this->naziv = naziv;
	this->vrijednost = vrijednost;
}

IS::Memorija::Memorija(std::string a, long long b, int c) : Memorija(a,b)
{
	adresa = c;
}

IS::Memorija::Memorija(const Memorija& a)
{
	naziv = a.naziv;
	vrijednost = a.vrijednost;
	adresa = a.adresa;
}