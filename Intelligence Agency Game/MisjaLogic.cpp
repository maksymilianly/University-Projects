#include "MisjaLogic.h"
#include <random>



std::string MisjaLogic::randomMiasto(std::vector<std::string> miasta)
{
	if (miasta.empty()) { return ""; }
	static std::random_device rd;
	static std::mt19937 engine(rd());
	std::uniform_int_distribution<size_t> dist(0, miasta.size() - 1);
	return miasta[dist(engine)];
}


void MisjaLogic::genMisja(std::vector<int>& dane)
{

}