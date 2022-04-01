#include <iostream>
#include <unordered_map>
#include <string>
#include "Procesor.h"
#include "Instrukcija.h"
#include "Memorija.h"
using namespace IS;

int main()
{
	Procesor a;
	std::cout << "Provjera sintakse koda : ";
	if (a.provjeraSintakse())
		std::cout << "Kod ispravan, zapocinje izvrsavanje : " << std::endl;
	else {
		std::cout << "Greska u kodu!";
		exit(-1);
	}
	a.Izvrsavanje();
}

