///////////////////////////////////////////////////////////////////////////////
/// @file Sequence.hpp
/// @brief Provides functionality for manipulating DNA sequences
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include <vector>
#include "Types.hpp"


///////////////////////////////////////////////////////////////////////////////
/// @brief Extract substrings from given string AKA make k-mers
///////////////////////////////////////////////////////////////////////////////
inline std::vector<std::string> GetSubstrings(
    const Index start,
    const Index length,
    const Index amount,
    const std::string& sequence) {
    const Index sequenceSize = sequence.size();

    // How many substrings can we generate?
    const Index maxSubstr = (sequenceSize - start) - 2*length;
    if (amount > maxSubstr) {
        throw std::invalid_argument("Too many substrings were requested");
    }

    // Extract substrings
    // Initialize vector here to ensure contiguous memory
    std::vector<std::string> substrings(amount);
    Index i = 0;
    for (Index j = start; j < amount; ++j) {
        substrings.at(i++) = sequence.substr(j, length);
    }

    return substrings;
}

