///////////////////////////////////////////////////////////////////////////////
/// @file SorensenDice.hpp
/// @brief Calculate Sorensen Dice coefficient
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include <algorithm>
#include <numeric>
#include <vector>
#include "Types.hpp"


///////////////////////////////////////////////////////////////////////////////
/// @brief Calculate Sorensen Dice distance
///////////////////////////////////////////////////////////////////////////////
inline double SorensenDice(const std::string& seqA, const std::string& seqB) {
    // Empty strings are invalid
    if (seqA.empty() || seqB.empty()) {
        return 0;
    }

    // Equal strings have a score of 1
    if (seqA == seqB) {
        return 1;
    }

    // Get sequence sizes
    const Index seqASize = seqA.size();
    const Index seqBSize = seqB.size();

    // Single characters are invalid due to bigrams
    if (seqASize < 2 || seqBSize < 2) {
        return 0;
    }

    double bigrams = 0;
    Index i = 0;
    Index j = 0;
    while (i < seqASize && j < seqBSize) {
        // If bigrams are equal, increase the count
        if (seqA.substr(i, 2).compare(seqB.substr(j, 2)) == 0) {
            ++bigrams;
        }
        ++i;
        ++j;
    }

    // Formula
    return (2.0 * bigrams) / static_cast<double>(seqASize-1 + seqBSize-1);
}
