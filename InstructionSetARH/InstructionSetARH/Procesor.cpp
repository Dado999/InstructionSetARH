#include "Procesor.h"
#include<iostream>
#include<vector>
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
		if (!strcmp("BREAKPOINT_START", line.c_str())) {
			continue;
			while (!(strcmp(line.c_str(), "BREAKPOINT_END")) && line_counter + 1 < ListaInstrukcija.size())
			{
				//Instrukcija instrukcija(line);
			}
		}
	}
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




