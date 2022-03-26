#include "Procesor.h"
#include<iostream>
#include<vector>
#include <cctype>
#include<fstream>

IS::Procesor::Procesor()
{
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
	for (std::string line=ListaInstrukcija[line_counter] ; line_counter < ListaInstrukcija.size() ; line_counter++)
	{
		if (!strcmp("BREAKPOINT", line.c_str())) {
			char c;
			std::cout << "Za next step unesi N, a za prelazak na sledeci BREAKPOINT unesi B." << std::endl;
			std::cin >> c;
			while (c == 'N')
			{
				line=ListaInstrukcija[++line_counter];
				if (!strcmp(line, "BREAKPOINT"))
				{
					line_counter--;
					continue;
				}
				Instrukcija a(line);
				a.IzvrsiInstrukiju();
				this->statusRegistara();
				this->statusMemorije();
				std::cout << "Za next step unesi N, a za prelazak na sledeci BREAKPOINT unesi B." << std::endl;
				std::cin >> c;
			}
			if (c == 'B')
			{
				line_counter++;
				while (strcmp(line = ListaInstrukcija[line_counter], "BREAKPOINT") && line_counter + 1 < ListaInstrukcija.size())
					line_counter++;
				line_counter--;
			}

		}
		else
		{
			Instrukcija a(line);
			a.IzvrsiInstrukiju();
		}
	}
	std::cout << "Izvrsavanje zavrseno!" << std::endl;
	statusMemorije();
	statusRegistara();
}

void IS::Procesor::pravljenjeRegistara()
{
	this->Registri.insert({ "EAX", (long) 0 });
	this->Registri.insert({ "EBX", (long)0 });
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




