#include "Procesor.h"
#include<iostream>
#include<vector>
#include<cctype>
#include<fstream>

IS::Procesor::Procesor()
{
	pravljenjeRegistara();
}

IS::Procesor::~Procesor()
{
}

void IS::Procesor::getInstructions()
{
	std::ifstream Fajl("a.txt");
	for (std::string line; getline(Fajl, line);)
		this->ListaInstrukcija.push_back(line);
}

void IS::Procesor::Izvrsavanje()
{
	getInstructions();
	int t = this->provjeraSintakse();
	if (t) 
	{
		for (std::string line = ListaInstrukcija[line_counter]; line_counter < ListaInstrukcija.size(); line_counter++)
		{
			if (!strcmp("BREAKPOINT", line.c_str())) {
				char c;
				std::cout << "Za next step unesi N, a za prelazak na sledeci BREAKPOINT unesi B." << std::endl;
				std::cin >> c;
				while (c == 'N')
				{
					line = ListaInstrukcija[++line_counter];
					if (!strcmp(line.c_str(), "BREAKPOINT"))
					{
						line_counter--;
						continue;
					}
					Instrukcija a(line);
					IzvrsavanjeInstrukcije(a);
					this->statusRegistara();
					this->statusMemorije();
					std::cout << "Za next step unesi N, a za prelazak na sledeci BREAKPOINT unesi B." << std::endl;
					std::cin >> c;
				}
				if (c == 'B')
				{
					line_counter++;
					while (strcmp(ListaInstrukcija[line_counter].c_str(), "BREAKPOINT") && line_counter + 1 < ListaInstrukcija.size())
						line_counter++;
					line_counter--;
				}

			}
			else
			{
				Instrukcija a(line);
				IzvrsavanjeInstrukcije(a);
			}
		}

		std::cout << "Izvrsavanje zavrseno!" << std::endl;
		statusMemorije();
		statusRegistara();
	}
	else
		std::cout << "Greska u kodu!" << std::endl;
}

void IS::Procesor::IzvrsavanjeInstrukcije(Instrukcija a)
{
	if (!(strcmp(a.naziv.c_str(), "ADD")))
	{
		if (!(a.argument1.empty()) && !(a.argument2.empty()))
		{
			if (Registri.contains(a.argument1))
			{
				if (Registri.contains(a.argument2))
				{
					auto t1 = Registri.find(a.argument1);
					auto t2 = Registri.find(a.argument2);
					t1->second = t1->second + t2->second;
				}
			}
		}


	}
}

void IS::Procesor::pravljenjeRegistara()
{
	this->Registri.insert({ "EAX", (long)3 });
	this->Registri.insert({ "EBX", (long)5 });
	this->Registri.insert({ "ECX", (long)0 });
	this->Registri.insert({ "EDX", (long)0 });
}

void IS::Procesor::statusRegistara()
{
	for (auto x : Registri)
		std::cout << x.first << " " << x.second << std::endl;
}

void IS::Procesor::statusMemorije()
{
	for (auto x : Memorija)
		std::cout << x.first << " " << x.second << std::endl;
}

int IS::Procesor::provjeraSintakse()
{
	return 0;
}

void IS::Procesor::pronadjiLabele()
{
	std::ifstream Fajl("a.txt");
	for (std::string line; getline(Fajl, line);)
		this->ListaInstrukcija.push_back(line);
	for (int i=0; i< ListaInstrukcija.size();i++)
	{
		if (ListaInstrukcija[i].find(":") >= 0)
		{
			std::string temp = "";
			temp = ListaInstrukcija[i].substr(0, ListaInstrukcija[i].size() - 1);
			Labele.insert({ temp,i });
		}
	}
}




