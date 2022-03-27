#include "Instrukcija.h"
#include<vector>
#include<string>
#include<algorithm>
#include<stdexcept>
#include <iostream>



IS::Instrukcija::Instrukcija(std::string argument1, std::string argument2, std::string naziv)
{ 
	this->naziv = naziv;
	this->argument1 = argument1;
	this->argument2 = argument2;
}

IS::Instrukcija::Instrukcija()
{
	std::cout << "hi" << std::endl;
}

IS::Instrukcija::Instrukcija(std::string a)
{
	std::vector<std::string> argumenti;
	std::string delim = " ";
	size_t pos = 0;
	std::string token1;

	while ((pos = a.find(delim)))
	{
		token1 = a.substr(0, pos);
		argumenti.push_back(token1);
		a.erase(0, pos + delim.length());
		if (pos == std::string::npos)
			break;
	}
	naziv = argumenti[0];
	argument1 = argumenti[1];
	if (argumenti.size() < 3)
		argument2="";
	else
		argument2 = argumenti[2];
}

IS::Instrukcija::~Instrukcija(){}

void IS::Instrukcija::pokazivac()
{
	if (argument1.find('[') >= 0)
	{
		argument1.erase(std::remove(argument1.begin(), argument1.end(), '['), argument1.end());
		argument1.erase(std::remove(argument1.begin(), argument1.end(), ']'), argument1.end());
	}
	else if (argument2.find('[') >= 0)
	{
		argument2.erase(std::remove(argument2.begin(), argument2.end(), '['), argument2.end());
		argument2.erase(std::remove(argument2.begin(), argument2.end(), ']'), argument2.end());
	}
}


