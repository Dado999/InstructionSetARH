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
	if (argumenti.size() == 1) {
		if(argumenti[0].find('*'))
			argumenti[0].erase(std::remove(argumenti[0].begin(), argumenti[0].end(), '*'), argumenti[0].end());
		naziv = argumenti[0];
		argument1 = "";
		argument2 = "";
	}
	else if (argumenti.size() == 2)
	{
		if (argumenti[0].find('*'))
			argumenti[0].erase(std::remove(argumenti[0].begin(), argumenti[0].end(), '*'), argumenti[0].end());
		naziv = argumenti[0];
		argument1 = argumenti[1];
		argument2 = "";
	}
	else
	{
		if (argumenti[0].find('*'))
			argumenti[0].erase(std::remove(argumenti[0].begin(), argumenti[0].end(), '*'), argumenti[0].end());
		naziv = argumenti[0];
		argument1 = argumenti[1];
		argument2 = argumenti[2];
	}
}

IS::Instrukcija::~Instrukcija(){}