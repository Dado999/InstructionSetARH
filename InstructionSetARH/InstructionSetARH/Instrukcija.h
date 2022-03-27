#pragma once
#include<string>

namespace IS
{
	class Instrukcija
	{
	private:
		std::string argument1;
		std::string argument2;
		std::string naziv;
	public:
		Instrukcija(std::string argument1, std::string argument2, std::string naziv);
		Instrukcija();
		Instrukcija(std::string);
		void pokazivac();
		~Instrukcija();
		friend class Procesor;
	}; 
}