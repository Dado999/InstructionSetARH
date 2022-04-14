#include <iostream>
#include <unordered_map>
#include <string>
#include "Procesor.h"
#include "Instrukcija.h"
using namespace IS;

int main(int argc, char* argv[])
{
	Procesor a;
	std::cout << "Provjera sintakse koda : ";
	if (a.provjeraSintakse())
		std::cout << "Kod ispravan, zapocinje izvrsi : " << std::endl;
	else {
		std::cout << "Greska u kodu!";
		exit(-1);
	}
	a.izvrsi();
}