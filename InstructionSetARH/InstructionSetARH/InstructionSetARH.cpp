#include <iostream>
#include <unordered_map>
#include <string>
#include "Procesor.h"
#include "Instrukcija.h"
using namespace IS;

int main()
{
	Procesor a;
	Instrukcija b("ADD EAX EBX");
	a.IzvrsavanjeInstrukcije(b);
}

