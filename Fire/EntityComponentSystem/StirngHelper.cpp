#include "StirngHelper.h"



size_t StringHelper::FindClosingBrace(const std::string& data, size_t start)
{
	size_t openingBrace = data.find('{', start);

	size_t close = openingBrace + 1;

	int openCount = 1;

	while (openCount != 0)
	{
		if (data[close] == '{')
			openCount++;
		else if (data[close] == '}')
			openCount--;

		if (openCount == 0)
			return close;

		++close;
	}

	return close;
}

size_t StringHelper::FindOpeningBrace(const std::string& data, size_t start)
{
	return data.find('{', start);
}

size_t StringHelper::FindIndex(const std::string& data, size_t start)
{
	size_t closeBrace = data.find('}',start);

	size_t open = data.find('[', start);
	size_t close = data.find(']', start);

	if (closeBrace <= open)
		return std::string::npos;

	std::string strIndex = data.substr(open + 1, close - 1);

	size_t index = std::stoull(strIndex);

	return index;
}

std::string StringHelper::EraseNamespace(const std::string& name)
{
	size_t spaceStart = name.find_last_of(':', name.size());

	if (spaceStart == std::string::npos)
		return name;

	return name.substr( spaceStart+1, name.size()-spaceStart);
}

std::string StringHelper::GetTypeName(const std::string& data, size_t start)
{
	size_t openIndex = FindOpeningBrace(data, start);

	std::string typeName = data.substr(start, openIndex - 1 - start);

	return typeName;
}
