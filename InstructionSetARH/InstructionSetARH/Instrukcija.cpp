#include "Instrukcija.h"
#include<vector>
#include<string>
#include<stdexcept>
#include <iostream>



IS::Instrukcija::Instrukcija(std::string argument1, std::string argument2, std::string naziv)
{
	this->argument1 = argument1;
	this->argument2 = argument2;
	this->naziv = naziv;
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
		token1 = a.substr(0, pos); // store the substring   
		argumenti.push_back(token1);
		a.erase(0, pos + delim.length());  /* erase() function store the current positon and move to next token. */
		if (pos == std::string::npos)
			break;
	}
	argumenti[0] = naziv;
	argumenti[1] = argument1;
	try {
		argumenti[2] = argument2;
	}
	catch (std::invalid_argument& ex) {
		std::cout << ex.what() << std::endl;
	}
}

IS::Instrukcija::~Instrukcija()
{

}
