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
	statusMemorije();
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
			for (int i = 0; t < ListaInstrukcija.size()-1; t++, i++)
				text.push_back(ListaInstrukcija[t + 1]);
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
		this->memorija.insert({ a.argument1,temp });
		a.~Instrukcija();
	}
	for (int i = 0; i < bss.size(); i++)
	{
		line = bss[i];
		Instrukcija a(line);
		this->memorija.insert({ a.argument1,0});
		a.~Instrukcija();
	}
}

void IS::Procesor::Izvrsavanje()
{

	
}

void IS::Procesor::IzvrsavanjeInstrukcije(Instrukcija a)
{
	if (!(strcmp(a.naziv.c_str(), "ADD")))
	{
		if (!(a.argument1.empty()) && !(a.argument2.empty()))
		{
			pokazivac(a);
			if (Registri.contains(a.argument1))
			{
				if (Registri.contains(a.argument2))
				{
					auto t1 = Registri.find(a.argument1);
					auto t2 = Registri.find(a.argument2);
					t1->second = t1->second + t2->second;
				}
				else if (memorija.contains(a.argument2))
				{
					auto t1 = Registri.find(a.argument1);
					auto t2 = memorija.find(a.argument2);
					t1->second = t1->second + t2->second;
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
				if (memorija.contains(a.argument1))
				{
					auto t1 = Registri.find(a.argument2);
					auto t2 = memorija.find(a.argument1);
					t1->second = t1->second + t2->second;
				}
				else
				{
					long long temp = stoll(a.argument1, nullptr, 10);
					auto t1 = Registri.find(a.argument2);
					t1->second = t1->second + temp;
				}
			}
			else if (memorija.contains(a.argument1))
			{
				if (memorija.contains(a.argument2))
				{
					auto t1 = memorija.find(a.argument1);
					auto t2 = memorija.find(a.argument2);
					t1->second = t1->second + t2->second;
				}
				else
				{
					long long temp = stoll(a.argument2, nullptr, 10);
					auto t1 = memorija.find(a.argument1);
					t1->second = t1->second + temp;
				}
			}
			else if (memorija.contains(a.argument2))
			{
				if (memorija.contains(a.argument1))
				{
					auto t1 = memorija.find(a.argument2);
					auto t2 = memorija.find(a.argument1);
					t1->second = t1->second + t2->second;
				}
				else
				{
					long long temp = stoll(a.argument1, nullptr, 10);
					auto t1 = memorija.find(a.argument2);
					t1->second = t1->second + temp;
				}
			}
		}
		else
		{
			std::cout << "Greska u kodu!" << std::endl;
			std::exit(-1);
		}
	}
	if (!(strcmp(a.naziv.c_str(), "SUB")))
	{
		if (!(a.argument1.empty()) && !(a.argument2.empty()))
		{
			pokazivac(a);
			if (Registri.contains(a.argument1))
			{
				if (Registri.contains(a.argument2))
				{
					auto t1 = Registri.find(a.argument1);
					auto t2 = Registri.find(a.argument2);
					t1->second = t1->second - t2->second;
				}
				else if (memorija.contains(a.argument2))
				{
					auto t1 = Registri.find(a.argument1);
					auto t2 = memorija.find(a.argument2);
					t1->second = t1->second - t2->second;
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
				if (memorija.contains(a.argument1))
				{
					auto t1 = Registri.find(a.argument2);
					auto t2 = memorija.find(a.argument1);
					t1->second = t1->second - t2->second;
				}
				else
				{
					long long temp = stoll(a.argument1, nullptr, 10);
					auto t1 = Registri.find(a.argument2);
					t1->second = t1->second - temp;
				}
			}
			else if (memorija.contains(a.argument1))
			{
				if (memorija.contains(a.argument2))
				{
					auto t1 = memorija.find(a.argument1);
					auto t2 = memorija.find(a.argument2);
					t1->second = t1->second - t2->second;
				}
				else
				{
					long long temp = stoll(a.argument2, nullptr, 10);
					auto t1 = memorija.find(a.argument1);
					t1->second = t1->second - temp;
				}
			}
			else if (memorija.contains(a.argument2))
			{
				if (memorija.contains(a.argument1))
				{
					auto t1 = memorija.find(a.argument2);
					auto t2 = memorija.find(a.argument1);
					t1->second = t1->second - t2->second;
				}
				else
				{
					long long temp = stoll(a.argument1, nullptr, 10);
					auto t1 = memorija.find(a.argument2);
					t1->second = t1->second - temp;
				}
			}
		}
		else
		{
			std::cout << "Greska u kodu!" << std::endl;
			std::exit(-1);
		}
	}
	if (!(strcmp(a.naziv.c_str(), "AND")))
	{
		if (!(a.argument1.empty()) && !(a.argument2.empty()))
		{
			pokazivac(a);
			if (Registri.contains(a.argument1))
			{
				if (Registri.contains(a.argument2))
				{
					auto t1 = Registri.find(a.argument1);
					auto t2 = Registri.find(a.argument2);
					t1->second = t1->second & t2->second;
				}
				else if (memorija.contains(a.argument2))
				{
					auto t1 = Registri.find(a.argument1);
					auto t2 = memorija.find(a.argument2);
					t1->second = t1->second & t2->second;
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
				if (memorija.contains(a.argument1))
				{
					auto t1 = Registri.find(a.argument2);
					auto t2 = memorija.find(a.argument1);
					t1->second = t1->second & t2->second;
				}
				else
				{
					long long temp = stoll(a.argument1, nullptr, 10);
					auto t1 = Registri.find(a.argument2);
					t1->second = t1->second & temp;
				}
			}
			else if (memorija.contains(a.argument1))
			{
				if (memorija.contains(a.argument2))
				{
					auto t1 = memorija.find(a.argument1);
					auto t2 = memorija.find(a.argument2);
					t1->second = t1->second & t2->second;
				}
				else
				{
					long long temp = stoll(a.argument2, nullptr, 10);
					auto t1 = memorija.find(a.argument1);
					t1->second = t1->second & temp;
				}
			}
			else if (memorija.contains(a.argument2))
			{
				if (memorija.contains(a.argument1))
				{
					auto t1 = memorija.find(a.argument2);
					auto t2 = memorija.find(a.argument1);
					t1->second = t1->second & t2->second;
				}
				else
				{
					long long temp = stoll(a.argument1, nullptr, 10);
					auto t1 = memorija.find(a.argument2);
					t1->second = t1->second & temp;
				}
			}
		}
		else
		{
			std::cout << "Greska u kodu!" << std::endl;
			std::exit(-1);
		}
	}
	if (!(strcmp(a.naziv.c_str(), "OR")))
	{
		if (!(a.argument1.empty()) && !(a.argument2.empty()))
		{
			pokazivac(a);
			if (Registri.contains(a.argument1))
			{
				if (Registri.contains(a.argument2))
				{
					auto t1 = Registri.find(a.argument1);
					auto t2 = Registri.find(a.argument2);
					t1->second = t1->second | t2->second;
				}
				else if (memorija.contains(a.argument2))
				{
					auto t1 = Registri.find(a.argument1);
					auto t2 = memorija.find(a.argument2);
					t1->second = t1->second | t2->second;
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
				if (memorija.contains(a.argument1))
				{
					auto t1 = Registri.find(a.argument2);
					auto t2 = memorija.find(a.argument1);
					t1->second = t1->second | t2->second;
				}
				else
				{
					long long temp = stoll(a.argument1, nullptr, 10);
					auto t1 = Registri.find(a.argument2);
					t1->second = t1->second | temp;
				}
			}
			else if (memorija.contains(a.argument1))
			{
				if (memorija.contains(a.argument2))
				{
					auto t1 = memorija.find(a.argument1);
					auto t2 = memorija.find(a.argument2);
					t1->second = t1->second | t2->second;
				}
				else
				{
					long long temp = stoll(a.argument2, nullptr, 10);
					auto t1 = memorija.find(a.argument1);
					t1->second = t1->second | temp;
				}
			}
			else if (memorija.contains(a.argument2))
			{
				if (memorija.contains(a.argument1))
				{
					auto t1 = memorija.find(a.argument2);
					auto t2 = memorija.find(a.argument1);
					t1->second = t1->second | t2->second;
				}
				else
				{
					long long temp = stoll(a.argument1, nullptr, 10);
					auto t1 = memorija.find(a.argument2);
					t1->second = t1->second | temp;
				}
			}
		}
		else
		{
			std::cout << "Greska u kodu!" << std::endl;
			std::exit(-1);
		}
	}
}

void IS::Procesor::pravljenjeRegistara()
{
	this->Registri.insert({ "EAX", (long)0 });
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
	for (auto x : memorija)
		std::cout << x.first << " " << x.second << std::endl;
}

int IS::Procesor::provjeraSintakse()
{
	return 0;
}

void IS::Procesor::pronadjiLabele()
{
	
}

void IS::Procesor::pokazivac(Instrukcija a)
{
	if (a.argument1.find('[') >= 0)
	{
		a.argument1.erase(std::remove(a.argument1.begin(), a.argument1.end(), '['), a.argument1.end());
		a.argument1.erase(std::remove(a.argument1.begin(), a.argument1.end(), ']'), a.argument1.end());
		if (Registri.contains(a.argument1))
		{
			auto t1 = Registri.find(a.argument1);
			std::string temp = std::to_string(t1->second);
			a.argument1 = temp;
		}
		else if (memorija.contains(a.argument1))
		{
			auto t1 = memorija.find(a.argument1);
			std::string temp = std::to_string(t1->second);
			a.argument1 = temp;
		}
	}
	else if (a.argument2.find('[') >= 0)
	{
		a.argument2.erase(std::remove(a.argument2.begin(), a.argument2.end(), '['), a.argument2.end());
		a.argument2.erase(std::remove(a.argument2.begin(), a.argument2.end(), ']'), a.argument2.end());
		if (Registri.contains(a.argument2))
		{
			auto t1 = Registri.find(a.argument2);
			std::string temp = std::to_string(t1->second);
			a.argument2 = temp;
		}
		else if (memorija.contains(a.argument2))
		{
			auto t1 = memorija.find(a.argument2);
			std::string temp = std::to_string(t1->second);
			a.argument2 = temp;
		}
	}
}


