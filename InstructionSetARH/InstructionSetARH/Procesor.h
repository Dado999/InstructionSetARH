#pragma once
#include "Instrukcija.h"
#include "Memorija.h"
#include<unordered_map>
#include<fstream>
#include<vector>

namespace IS
{
	class Procesor
	{
	private:
		std::unordered_map<std::string, int> Labele;
		std::unordered_map<std::string, int> Registri;
		std::vector<std::string> data;
		std::vector<std::string> bss;
		std::vector<std::string> text;
		std::vector<std::string> ListaInstrukcija;
		std::vector<IS::Memorija> Memorija;
		int line_counter=0;
		int adresa = 0;
		int cmp;
	public:
		Procesor();
		~Procesor();
		void dobaviInstrukcije();
		void ucitajPodatke();
		void izvrsi();
		void izvrsiInstrukciju(Instrukcija);
		void izvrsiInstrukcijuPomocna(Instrukcija&, char);
		void izvrsiInstrukcijuPomocnaSkokovi(Instrukcija);
		void pravljenjeRegistara();
		void ispisiStanjeRegistara();
		void ispisiStanjeMemorije();
		int provjeraSintakse();
		int provjeraMemorije(std::string&);
		void pronadjiLabele();
		void dohvatiAdresu(Instrukcija&);
		void dohvatiAdresuPomocna(std::string& a);
	};
}