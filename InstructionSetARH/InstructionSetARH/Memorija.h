#pragma once
#include<unordered_map>
#include<fstream>
#include<vector>

namespace IS
{
	class Memorija
	{
	public:
		std::string naziv;
		long long vrijednost;
		int adresa;
		Memorija(std::string,long long);
		Memorija(std::string,long long,int);
		Memorija(const Memorija&);
		Memorija() = default;
	};
}