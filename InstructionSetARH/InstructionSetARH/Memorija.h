#pragma once
#include<unordered_map>
#include<fstream>
#include<vector>

namespace IS
{
	class Memorija
	{
	public:
		std::unordered_map<std::string, long long> memorija;
		Memorija() = default;
	};
}