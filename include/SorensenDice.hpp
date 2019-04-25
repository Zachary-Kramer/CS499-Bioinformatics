///////////////////////////////////////////////////////////////////////////////
/// @file NewDistance.hpp
/// @brief Calculate 
///////////////////////////////////////////////////////////////////////////////

#pragma once


#include <algorithm>
#include <numeric>
#include <vector>
#include "Types.hpp"
#include <string.h>


///////////////////////////////////////////////////////////////////////////////
/// @brief Calculate 
///////////////////////////////////////////////////////////////////////////////
static double SorensenDice(const std::string& string1, const std::string& string2)
{
	if (string1.empty() || string2.empty())
		return 0;

	if (string1 == string2)
		return 1;

	int length1 = string1.size();
	int length2 = string2.size();

	if (length1 < 2 || length2 < 2)
		return 0;

	double bigrams = 0;
	int i = 0;
	int j = 0;

	while (i < length1 && j < length2)
	{
		auto a = string1.substr(i, 2);
		auto b = string2.substr(j, 2);
		int similarity = a.compare(b);

		if (similarity == 0)
			bigrams += 1;

		++i;
		++j;
	}

	return (2 * bigrams) / (length1 + length2);
}
