#pragma once
#include "Instrukcija.h"
#include "Memorija.h"
#include<unordered_map>
#include<fstream>
#include<vector>

namespace IS
{
	class Procesor : public Memorija
	{
	private:
		std::unordered_map<std::string, long long> Labele;
		std::unordered_map<std::string, int> Registri;
		std::vector<std::string> data;
		std::vector<std::string> bss;
		std::vector<std::string> text;
		std::vector<std::string> ListaInstrukcija;
		inline static int line_counter=0;
	public:
		Procesor();
		~Procesor();
		void pravljenjeRegistara();
		void pronadjiLabele();
		void getInstructions();
		void ucitavanjePodataka();
		void Izvrsavanje();
		void IzvrsavanjeInstrukcije(Instrukcija);
		void statusRegistara();
		void statusMemorije();
		int provjeraSintakse();
		void pokazivac(Instrukcija);
	};
}
