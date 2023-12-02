#pragma once
#include <string>

namespace StringHelper
{
	size_t FindClosingBrace(const std::string& data, size_t start);
	
	size_t FindOpeningBrace(const std::string& data, size_t start);

	size_t FindIndex(const std::string& data, size_t start);

}