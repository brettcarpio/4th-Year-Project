#include "GrammarSystem.h"

GrammarSystem::GrammarSystem()
{
}

GrammarSystem::~GrammarSystem()
{
}

std::string GrammarSystem::ConvertToLowercase(std::string code)
{
	std::string result;
	for (char& c : code) {
		if (isupper(c))
			c = tolower(c);
		result += c;
	}
	std::cout << result << std::endl;
	return result;
}
