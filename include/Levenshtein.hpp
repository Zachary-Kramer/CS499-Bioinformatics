///////////////////////////////////////////////////////////////////////////////
/// @file Levenshtein.hpp
/// @brief Calculate Levenshtein distance
///////////////////////////////////////////////////////////////////////////////

#pragma once


#include <algorithm>
#include <numeric>
#include <vector>
#include "Types.hpp"


///////////////////////////////////////////////////////////////////////////////
/// @brief Calculate Levenshtein distance on two sequences
///////////////////////////////////////////////////////////////////////////////
inline int LevenshteinDistance(
    const std::string& seqA,
    const std::string& seqB) {
    // Get size of matrix
    const Index rows = seqA.size();
    const Index cols = seqB.size();

    // Create A x B scoring matrix
    std::vector<std::vector<int>> d(rows+1, std::vector<int>(cols+1));
    // First row is 0, 1, ..., cols
    for (Index i = 0; i <= cols; ++i) {
        d.at(0).at(i) = i;
    }
    // First col is 0, 1, ..., rows
    for (Index i = 1; i <= rows; ++i) {
        d.at(i).at(0) = i;
    }

    Index tracker;
    for (Index j = 1; j <= cols; ++j) {
        for (Index i = 1; i <= rows; ++i) {
            tracker = (seqA.at(i-1) == seqB.at(j-1)) ? 0 : 1;
            Index temp = std::min(d.at(i-1).at(j) + 1, d.at(i).at(j-1) + 1);
            d.at(i).at(j) = std::min(temp, d.at(i-1).at(j-1) + tracker);
        }
    }

    return d.at(rows).at(cols);
}
