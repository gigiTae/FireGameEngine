#include "StirngHelper.h"



size_t StringHelper::FindClosingBrace(const std::string& data, size_t start)
{
	size_t openingBrace = data.find('{', start);
	
	size_t close = openingBrace+1;

	int openCount = 1;

	while (openCount != 0)
	{
		if (data[close] == '{')
			openCount++;
		else if (data[close] == '}')
			openCount--;

		++close;
	} 

	return close;
}

size_t StringHelper::FindOpeningBrace(const std::string& data, size_t start)
{
	return data.find('{', start);
}
