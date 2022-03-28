#pragma once
#include "Instrukcija.h"
#include<unordered_map>
#include<fstream>
#include<vector>

namespace IS
{
	class Procesor
	{
	private:
		std::unordered_map<std::string, long long> Labele;
		std::unordered_map<std::string, long long> Memorija;
		std::unordered_map<std::string, int> Registri;
		std::vector<std::string> ListaInstrukcija;
		inline static int line_counter=0;
	public:
		Procesor();
		~Procesor();
		void pravljenjeRegistara();
		void pronadjiLabele();
		void getInstructions();
		void statusRegistara();
		void statusMemorije();
		int provjeraSintakse();
		void Izvrsavanje();
		void IzvrsavanjeInstrukcije(Instrukcija);
		void pokazivac(Instrukcija);
	};
}
