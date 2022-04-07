#include "Procesor.h"
#include<iostream>
#include<string>
#include<vector>
#include<cctype>
#include<fstream>

IS::Procesor::Procesor()
{
	pravljenjeRegistara();
	getInstructions();
	ucitavanjePodataka();
	pronadjiLabele();
}

IS::Procesor::~Procesor()
{
}

void IS::Procesor::getInstructions()
{
	std::ifstream Fajl("a.txt");
	for (std::string line; getline(Fajl, line);)
		this->ListaInstrukcija.push_back(line);
	static int d, b, t;
	for (int i = 0; i < ListaInstrukcija.size(); i++)
	{
		if (!strcmp(ListaInstrukcija[i].c_str(), ".data")) 
		{
			d = i;
			break;
		}
	}
	for (int i = 0; i < ListaInstrukcija.size(); i++)
	{
		if (!strcmp(ListaInstrukcija[i].c_str(), ".bss"))
		{
			b = i;
			break;
		}
	}
	for (int i = 0; i < ListaInstrukcija.size(); i++)
	{
		if (!strcmp(ListaInstrukcija[i].c_str(), ".text")) 
		{
			t = i;
			break;
		}
	}
	try {
		if (d < b && b < t)
		{
			for (int i = 0; d < b-1; d++, i++)
				data.push_back(ListaInstrukcija[d + 1]);
			for (int i = 0; b < t-1; b++, i++)
				bss.push_back(ListaInstrukcija[b + 1]);
			for (int i = 0; t < ListaInstrukcija.size() - 1; t++, i++) {
				text.push_back(ListaInstrukcija[t + 1]);
			}
		}
		else
			throw;
	}
	catch(std::exception ex)
	{
		std::cout << "Greska u kodu!";
	}

}

void IS::Procesor::ucitavanjePodataka()
{
	std::string line;
	for (int i=0;i<data.size();i++)
	{
		line = data[i];
		Instrukcija a(line);
		long long temp = std::stoll(a.argument2, nullptr, 10);
		IS::Memorija b(a.argument1, temp, this->adresa++);
		this->Memorija.push_back(b);
	}
	for (int i = 0; i < bss.size(); i++)
	{
		line = bss[i];
		Instrukcija a(line);
		IS::Memorija b(a.argument1, 0,this->adresa++);
		this->Memorija.push_back(b);
		a.~Instrukcija();
	}
}

void IS::Procesor::Izvrsavanje()
{
	char c;
	bool debug = false;
	std::cout << "Unesi 1 za izvrsavanje sa debagovanjem ili 2 za izvrsavanje bez debagovanja : ";
	std::cin >> c;
	if (c == '1')
		debug = true;
	std::cout << "Status memorije i registara prije izvrsavanja :" << std::endl;
	statusRegistara();
	statusMemorije();
	for (; line_counter < text.size() && debug==true; line_counter++)
	{
		Instrukcija a(text[line_counter]);
		IzvrsavanjeInstrukcije(a);
		std::cout << "Instrukcija izvrsena! Status registara i memorije: " << std::endl;
		statusRegistara();
		statusMemorije();
		std::cout << "Za sledecu instrukciju unesi 1, za nastavak bez debagovanja unesi 2 a za skok na sledecu breakpoint tacku unesi 3:";
		std::cin >> c;
		if (c == '2') {
			debug = false;
			--line_counter;
			continue;
		}
		else if (c == '3')
		{
			int br = 1;
			line_counter++;
			for (; line_counter < text.size() && text[line_counter].find('*') == std::string::npos; line_counter++, br++)
			{
				Instrukcija a(text[line_counter]);
				IzvrsavanjeInstrukcije(a);
				if (line_counter >= text.size()) {
					debug = false;
					continue;
				}
			}
			std::cout << "Status registara i memorije na breakpoint tacki" << std::endl;
			statusRegistara();
			statusMemorije();
			line_counter--;
		}
		else if (c != '1')
			std::cout << "Pogresan unos, nastavlja se izvrsavanje sa debagovanjem";
	}
	while (++line_counter < text.size())
	{
		Instrukcija a(text[line_counter]);
		IzvrsavanjeInstrukcije(a);
	}
	std::cout << "Izvrsavanje zavrseno! Finalno stanje registara i memorije: " << std::endl;
	statusRegistara();
	statusMemorije();
}

void IS::Procesor::IzvrsavanjeInstrukcije(Instrukcija a)
{
	if (!(strcmp(a.naziv.c_str(), "\tADD")))
	{
			pokazivac(a);
			int t1 = provjeraMemorije(a.argument1);
			int t2 = provjeraMemorije(a.argument2);
			if (Registri.contains(a.argument1))
			{
				if (Registri.contains(a.argument2))
				{
					auto t1 = Registri.find(a.argument1);
					auto t2 = Registri.find(a.argument2);
					t1->second = t1->second + t2->second;
				}
				else if (t2>=0)
				{
					auto t1 = Registri.find(a.argument1);
					t1->second = t1->second + this->Memorija[t2].vrijednost;
				}
				else
				{
					long long temp = stoll(a.argument2, nullptr, 10);
					auto t1 = Registri.find(a.argument1);
					t1->second = t1->second + temp;
				}
			}
			else if (Registri.contains(a.argument2))
			{
				if (t1>=0)
				{
					auto t2 = Registri.find(a.argument2);
					this->Memorija[t1].vrijednost = this->Memorija[t1].vrijednost + t2->second;
				}
				else
				{
					std::cout << "Greska u " << line_counter << " liniji koda!" << std::endl;
					std::exit(-1);
				}
			}
			else if (t1>=0)
			{
				if (t2>=0) {
					this->Memorija[t1].vrijednost = this->Memorija[t1].vrijednost + this->Memorija[t1].vrijednost;
				}
				else
				{
					long long temp = stoll(a.argument2, nullptr, 10);
					this->Memorija[t1].vrijednost = this->Memorija[t1].vrijednost + temp;
				}
			}
			else
			{
				std::cout << "Greska u " << line_counter << " liniji koda!" << std::endl;
				std::exit(-1);
			}
	}
	else if (!(strcmp(a.naziv.c_str(), "\tSUB")))
	{
		pokazivac(a);
		int t1 = provjeraMemorije(a.argument1);
		int t2 = provjeraMemorije(a.argument2);
		if (Registri.contains(a.argument1))
		{
			if (Registri.contains(a.argument2))
			{
				auto t1 = Registri.find(a.argument1);
				auto t2 = Registri.find(a.argument2);
				t1->second = t1->second - t2->second;
			}
			else if (t2>=0)
			{
				auto t1 = Registri.find(a.argument1);
				t1->second = t1->second - this->Memorija[t2].vrijednost;
			}
			else
			{
				long long temp = stoll(a.argument2, nullptr, 10);
				auto t1 = Registri.find(a.argument1);
				t1->second = t1->second - temp;
			}
		}
		else if (Registri.contains(a.argument2))
		{
			if (t1>=0)
			{
				auto t2 = Registri.find(a.argument2);
				this->Memorija[t1].vrijednost = this->Memorija[t1].vrijednost - t2->second;
			}
			else
			{
				std::cout << "Greska u " << line_counter << " liniji koda!" << std::endl;
				std::exit(-1);
			}
		}
		else if (t1>=0)
		{
			if (t2>=0) {
				this->Memorija[t1].vrijednost = this->Memorija[t1].vrijednost - this->Memorija[t2].vrijednost;
			}
			else
			{
				long long temp = stoll(a.argument2, nullptr, 10);
				this->Memorija[t1].vrijednost = this->Memorija[t1].vrijednost + temp;
			}
		}
		else
		{
			std::cout << "Greska u " << line_counter << " liniji koda!" << std::endl;
			std::exit(-1);
		}
	}
	else if (!(strcmp(a.naziv.c_str(), "\tAND")))
	{
		pokazivac(a);
		int t1 = provjeraMemorije(a.argument1);
		int t2 = provjeraMemorije(a.argument2);
		if (Registri.contains(a.argument1))
		{
			if (Registri.contains(a.argument2))
			{
				auto t1 = Registri.find(a.argument1);
				auto t2 = Registri.find(a.argument2);
				t1->second = t1->second & t2->second;
			}
			else if (t2>=0)
			{
				auto t1 = Registri.find(a.argument1);
				t1->second = t1->second & this->Memorija[t2].vrijednost;
			}
			else
			{
				long long temp = stoll(a.argument2, nullptr, 10);
				auto t1 = Registri.find(a.argument1);
				t1->second = t1->second & temp;
			}
		}
		else if (Registri.contains(a.argument2))
		{
			if (t1>=0)
			{
				auto t2 = Registri.find(a.argument2);
				this->Memorija[t1].vrijednost = this->Memorija[t1].vrijednost & t2->second;
			}
			else
			{
				std::cout << "Greska u " << line_counter << " liniji koda!" << std::endl;
				std::exit(-1);
			}
		}
		else if (t1>=0)
		{
			if (t2>=0) {
				this->Memorija[t1].vrijednost = this->Memorija[t1].vrijednost & this->Memorija[t2].vrijednost;
			}
			else
			{
				long long temp = stoll(a.argument2, nullptr, 10);
				this->Memorija[t1].vrijednost = this->Memorija[t1].vrijednost & temp;
			}
		}
		else
		{
			std::cout << "Greska u " << line_counter << " liniji koda!" << std::endl;
			std::exit(-1);
		}
	}
	else if (!(strcmp(a.naziv.c_str(), "\tOR")))
	{
		pokazivac(a);
		int t1 = provjeraMemorije(a.argument1);
		int t2 = provjeraMemorije(a.argument2);
		if (Registri.contains(a.argument1))
		{
			if (Registri.contains(a.argument2))
			{
				auto t1 = Registri.find(a.argument1);
				auto t2 = Registri.find(a.argument2);
				t1->second = t1->second | t2->second;
			}
			else if (t2>=0)
			{
				auto t1 = Registri.find(a.argument1);
				t1->second = t1->second | this->Memorija[t2].vrijednost;
			}
			else
			{
				long long temp = stoll(a.argument2, nullptr, 10);
				auto t1 = Registri.find(a.argument1);
				t1->second = t1->second | temp;
			}
		}
		else if (Registri.contains(a.argument2))
		{
			if (t1>=0)
			{
				auto t2 = Registri.find(a.argument2);
				this->Memorija[t1].vrijednost = this->Memorija[t1].vrijednost | t2->second;
			}
			else
			{
				std::cout << "Greska u " << line_counter << " liniji koda!" << std::endl;
				std::exit(-1);
			}
		}
		else if (t1>=0)
		{
			if (t2>=0) {
				this->Memorija[t1].vrijednost = this->Memorija[t1].vrijednost | this->Memorija[t2].vrijednost;
			}
			else
			{
				long long temp = stoll(a.argument2, nullptr, 10);
				this->Memorija[t1].vrijednost = this->Memorija[t1].vrijednost | temp;
			}
		}
		else
		{
			std::cout << "Greska u " << line_counter << " liniji koda!" << std::endl;
			std::exit(-1);
		}
	}
	else if (!(strcmp(a.naziv.c_str(), "\tNOT")))
	{
		int t1 = provjeraMemorije(a.argument1);
		if (Registri.contains(a.argument1))
		{
			auto t1 = Registri.find(a.argument1);
			t1->second = ~t1->second;
		}
		else if (t1>=0)
		{
			this->Memorija[t1].vrijednost = ~this->Memorija[t1].vrijednost;
		}
		else
		{
			std::cout << "Greska u " << line_counter << " liniji koda!" << std::endl;
			std::exit(-1);
		}
	}
	else if (!(strcmp(a.naziv.c_str(), "\tMOV")))
	{
	pokazivac(a);
	int t1 = provjeraMemorije(a.argument1);
	int t2 = provjeraMemorije(a.argument2);
	if (Registri.contains(a.argument1))
	{
		if (Registri.contains(a.argument2))
		{
			auto t1 = Registri.find(a.argument1);
			auto t2 = Registri.find(a.argument2);
			t1->second = t2->second;
		}
		else if (t2>=0)
		{
			auto t1 = Registri.find(a.argument1);
			t1->second = this->Memorija[t2].vrijednost;
		}
		else
		{
			long long temp = stoll(a.argument2, nullptr, 10);
			auto t1 = Registri.find(a.argument1);
			t1->second = temp;
		}
	}
	else if (Registri.contains(a.argument2))
	{
		if (t1>=0)
		{
			auto t2 = Registri.find(a.argument2);
			this->Memorija[t1].vrijednost = t2->second;
		}
		else
		{
			std::cout << "Greska u " << line_counter << " liniji koda!" << std::endl;
			std::exit(-1);
		}
	}
	else if (t1>=0)
	{
		if (t2>=0) 
			this->Memorija[t1].vrijednost = this->Memorija[t2].vrijednost;
		else
		{
			long long temp = stoll(a.argument2, nullptr, 10);
			this->Memorija[t1].vrijednost = temp;
		}
	}
	else
	{
		std::cout << "Greska u " << line_counter << " liniji koda!" << std::endl;
		std::exit(-1);
	}
	}
	else if (!(strcmp(a.naziv.c_str(), "\tJMP")))
	{
	   if (Labele.contains("\t"+a.argument1))
	   {
	       auto t1 = Labele.find("\t"+a.argument1);
	   	   line_counter = t1->second;
	   }
	   else {
	   	   int temp = std::stoi(a.argument1, nullptr, 10);
	   	   line_counter = --temp;
	   }
	}
	else if (!(strcmp(a.naziv.c_str(), "\tIN")))
	{
		int t1 = provjeraMemorije(a.argument1);
		if (Registri.contains(a.argument1))
		{
		    auto t1 = Registri.find(a.argument1);
			std::cout << "Unesi novu vrijednost " << t1->first << " registra: ";
			long long temp;
			std::cin >> temp;
			t1->second = temp;
		}
		else if (t1>=0)
		{
			std::cout << "Unesi novu vrijednost " << this->Memorija[t1].naziv << ":";
			long long temp;
			std::cin >> temp;
			this->Memorija[t1].vrijednost = temp;
		}
		else
		{
			std::cout << "Greska u " << line_counter << " liniji koda!" << std::endl;
			std::exit(-1);
		}
	}
	else if (!(strcmp(a.naziv.c_str(), "\tOUT")))
	{
		int t1 = provjeraMemorije(a.argument1);
		if (Registri.contains(a.argument1))
		{
			auto t1 = Registri.find(a.argument1);
			std::cout << "Ispis iz registra " << t1->first << ": " << t1->second << std::endl;
		}
		if (t1>=0)
		{
			std::cout << "Ispis iz memorije " << this->Memorija[t1].naziv << ": " << this->Memorija[t1].vrijednost << std::endl;
		}
		else
		{
			std::cout << "Greska u " << line_counter << " liniji koda!" << std::endl;
			std::exit(-1);
		}
	}
	else if (!(strcmp(a.naziv.c_str(), "\tCMP")))
	{
		int t1 = provjeraMemorije(a.argument1);
		int t2 = provjeraMemorije(a.argument2);
		pokazivac(a);
		if (Registri.contains(a.argument1))
		{
			if (Registri.contains(a.argument2))
			{
				auto t1 = Registri.find(a.argument1);
				auto t2 = Registri.find(a.argument2);
				if (t1->second > t2->second) cmp = 1;
				else if (t1->second == t2->second) cmp = 0;
				else if (t1->second < t2->second) cmp = -1;
			}
			else if (t2>=0)
			{
				auto t1 = Registri.find(a.argument1);
				if (t1->second > this->Memorija[t2].vrijednost) cmp = 1;
				else if (t1->second == this->Memorija[t2].vrijednost) cmp = 0;
				else if (t1->second < this->Memorija[t2].vrijednost) cmp = -1;
			}
			else
			{
				auto t1 = Registri.find(a.argument1);
				long long temp = stoll(a.argument2, nullptr, 10);
				if (t1->second > temp) cmp = 1;
				else if (t1->second == temp) cmp = 0;
				else if (t1->second < temp) cmp = -1;
			}
		}
		else if (Registri.contains(a.argument2))
		{
			if (t1>=0)
			{
				auto t2 = Registri.find(a.argument2);
				if (this->Memorija[t1].vrijednost > t2->second) cmp = 1;
				else if (this->Memorija[t1].vrijednost == t2->second) cmp = 0;
				else if (this->Memorija[t1].vrijednost < t2->second) cmp = -1;
			}
			else
			{
				long long temp = stoll(a.argument1, nullptr, 10);
				auto t1 = Registri.find(a.argument2);
				if (temp > t1->second) cmp = 1;
				else if (temp == t1->second) cmp = 0;
				else if (temp < t1->second) cmp = -1;
			}
		}
		else if (t1>=0)
		{
			if (t2>=0)
			{
				if (this->Memorija[t1].vrijednost > this->Memorija[t2].vrijednost) cmp = 1;
				else if (this->Memorija[t1].vrijednost == this->Memorija[t2].vrijednost) cmp = 0;
				else if (this->Memorija[t1].vrijednost < this->Memorija[t2].vrijednost) cmp = -1;
			}
			else
			{
				long long temp = stoll(a.argument2, nullptr, 10);
				if (this->Memorija[t1].vrijednost > temp) cmp = 1;
				else if (this->Memorija[t1].vrijednost == temp) cmp = 0;
				else if (this->Memorija[t1].vrijednost < temp) cmp = -1;
			}
		}
		else if (t2>=0)
		{
			long long temp = stoll(a.argument1, nullptr, 10);
			if (this->Memorija[t2].vrijednost > temp) cmp = 1;
			else if (this->Memorija[t2].vrijednost == temp) cmp = 0;
			else if (this->Memorija[t2].vrijednost < temp) cmp = -1;
		}
		else
		{
			long long temp1 = stoll(a.argument1, nullptr, 10);
			long long temp2 = stoll(a.argument2, nullptr, 10);
			if (temp1 > temp2) cmp = 1;
			else if (temp1 == temp2) cmp = 0;
			else if (temp1 < temp2) cmp = -1;
		}
	}
	else if (!(strcmp(a.naziv.c_str(), "\tJE")))
	{
		if (!cmp)
		{
			if (Labele.contains(a.argument1)) {
				auto t1 = Labele.find(a.argument1);
				line_counter = t1->second;
			}
			else
			{
				int t1 = stoi(a.argument1, nullptr, 10);
				line_counter = --t1;
			}
		}
		else
			std::cout << "Skok neuspjesan!" << std::endl;
	}
	else if (!(strcmp(a.naziv.c_str(), "\tJNE")))
	{
		if (cmp)
		{
			if (Labele.contains(a.argument1)) {
				auto t1 = Labele.find(a.argument1);
				line_counter = t1->second;
			}
			else
			{
				int t1 = stoi(a.argument1, nullptr, 10);
				line_counter = --t1;
			}
		}
		else
			std::cout << "Skok neuspijesan!" << std::endl;
	}
	else if (!(strcmp(a.naziv.c_str(), "\tJGE")))
	{
		if (cmp>=0)
		{
			if (Labele.contains(a.argument1)) {
				auto t1 = Labele.find(a.argument1);
				line_counter = t1->second;
			}
			else
			{
				int t1 = stoi(a.argument1, nullptr, 10);
				line_counter = --t1;
			}
		}
		else
			std::cout << "Skok neuspjesan!" << std::endl;
	}
	else if (!(strcmp(a.naziv.c_str(), "\tJNE")))
	{
		if (cmp<0)
		{
			if (Labele.contains(a.argument1)) {
				auto t1 = Labele.find(a.argument1);
				line_counter = t1->second;
			}
			else
			{
				int t1 = stoi(a.argument1, nullptr, 10);
				line_counter = --t1;
			}
		}
		else
			std::cout << "Skok neuspjesan!" << std::endl;
	}
	else if (!(a.naziv.empty()) && (a.argument1.empty()) && (a.argument2.empty()))
	{
		return;
	} 
	else {
	std::cout << "Nepoznata komanda! u liniji " << line_counter << "!" << std::endl;
		exit(-1);
	}
}

void IS::Procesor::pravljenjeRegistara()
{
	this->Registri.insert({ "RAX", (long)0 });
	this->Registri.insert({ "RBX", (long)0 });
	this->Registri.insert({ "RCX", (long)0 });
	this->Registri.insert({ "RDX", (long)0 });
}

void IS::Procesor::statusRegistara()
{
	std::cout << "=====Registri=====" << std::endl;
	for (auto x : Registri)
		std::cout << x.first << " " << x.second << std::endl;
}

void IS::Procesor::statusMemorije()
{
	std::cout << "=====Memorija=====" << std::endl;
	for (auto x : this->Memorija)
		std::cout << x.naziv << " " << x.vrijednost << std::endl;
}

int IS::Procesor::provjeraSintakse()
{
	for (std::string x : data)
	{
		Instrukcija a(x);
		if (a.naziv.empty() || a.argument1.empty() || a.argument2.empty())
			return 0;
	}
	for (std::string x : bss)
	{
		Instrukcija a(x);
		if (a.naziv.empty() || a.argument1.empty())
			return 0;
	}
	for (int i = 0; i < text.size(); i++)
	{
		if (Labele.contains(text[i]))
			continue;
		Instrukcija a(text[i]);
		if (a.naziv.empty() || a.argument1.empty())
			return 0;
	}
	return 1;
}

int IS::Procesor::provjeraMemorije(std::string& a)
{
	for (int i=0;i<this->Memorija.size();i++)
	{
		if (this->Memorija[i].naziv == a)
			return i;
	}
	return -1;
}

void IS::Procesor::pronadjiLabele()
{
	for (int i = 0; i < text.size(); i++)
	{
		if ((text[i].find(':') != std::string::npos))
		{
			text[i].erase(std::remove(text[i].begin(), text[i].end(), ':'), text[i].end());
			Labele.insert({ text[i] , i });
		}
	}
}

void IS::Procesor::pokazivac(Instrukcija& a)
{
	if (a.argument1.find('[') >= 0 && a.argument1.find('[') != std::string::npos)
	{
		a.argument1.erase(std::remove(a.argument1.begin(), a.argument1.end(), '['), a.argument1.end());
		a.argument1.erase(std::remove(a.argument1.begin(), a.argument1.end(), ']'), a.argument1.end());
		if (Registri.contains(a.argument1))
		{
			auto t1 = Registri.find(a.argument1);
				if (this->Memorija[t1->second].adresa >= 0 && t1->second < this->Memorija.size()) {
					a.argument1 = this->Memorija[t1->second].naziv;
					return;
				}
			std::cout << "Nepoznata memorijska lokacija!" << std::endl;
			exit(-1);
		}
		else
		{
			int temp = stoi(a.argument1);
			if (this->Memorija[temp].adresa >= 0 && temp < this->Memorija.size()) {
				a.argument1 = this->Memorija[temp].naziv;
				return;
			}
			std::cout << "Nepoznata memorijska lokacija!" << std::endl;
			exit(-1);
		}
	}
	else if (a.argument2.find('[') >= 0 && a.argument2.find('[') != std::string::npos)
	{
		a.argument2.erase(std::remove(a.argument2.begin(), a.argument2.end(), '['), a.argument2.end());
		a.argument2.erase(std::remove(a.argument2.begin(), a.argument2.end(), ']'), a.argument2.end());
		if (Registri.contains(a.argument2))
		{
			auto t1 = Registri.find(a.argument2);
			if (this->Memorija[t1->second].adresa >= 0 && t1->second < this->Memorija.size()) {
				a.argument2 = this->Memorija[t1->second].naziv;
				return;
			}
			std::cout << "Nepoznata memorijska lokacija!" << std::endl;
			exit(-1);
		}
		else
		{
			int temp = stoi(a.argument2);
			if (this->Memorija[temp].adresa >= 0 && temp < this->Memorija.size()) {
				a.argument2 = this->Memorija[temp].naziv;
				return;
			}
			std::cout << "Nepoznata memorijska lokacija!" << std::endl;
			exit(-1);
		}
	}
	else if (Labele.contains(a.naziv))
		return;
}


