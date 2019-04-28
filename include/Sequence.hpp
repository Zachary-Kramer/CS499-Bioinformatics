///////////////////////////////////////////////////////////////////////////////
/// @file Sequence.hpp
/// @brief Provides functionality for manipulating DNA sequences
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include <vector>
#include "Types.hpp"


// Just pairs together the DNA sequence and its ID, more explicit than std::pair
struct Sequence {
    std::string DNA;
    std::string id;

    explicit Sequence(const std::string& seqID, const std::string& seq) :
    DNA(seq), id(seqID) {}
};


///////////////////////////////////////////////////////////////////////////////
/// @brief Extract substrings from given string AKA make k-mers
///////////////////////////////////////////////////////////////////////////////
inline std::vector<std::string> GetSubstrings(
    const Index start,
    const Index length,
    Index& amount,  // This is modified to tell the user how much was actually generated
    const std::string& sequence) {
    const Index sequenceSize = sequence.size();

    
    // How many substrings can we generate?
    const Index maxSubstr = (sequenceSize - start) - 2*length;

    // If user requested too many substrings, truncate it.
    amount = (amount > maxSubstr) ? maxSubstr : amount;

    // Extract substrings
    // Initialize vector here to ensure contiguous memory
    std::vector<std::string> substrings(amount);
    Index i = 0;
    for (Index j = start; j < amount+start; ++j) {
        substrings.at(i++) = sequence.substr(j, length);
    }

    return substrings;
}

