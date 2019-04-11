///////////////////////////////////////////////////////////////////////////////
/// @file Rank.hpp
/// @brief Defines how we rank the best substrings
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include <string>


struct Rank {
    std::string id;
    std::string substring;
    int levenshtein;
    
    // Constructor
    explicit Rank(const std::string& seqID, const std::string& substr, const int lScore) :
    id (seqID), substring(substr), levenshtein(lScore) {
    }

    // Sorting
    bool operator > (const Rank& r) const {
        return (levenshtein > r.levenshtein);
    }
    bool operator < (const Rank& r) const {
        return (levenshtein < r.levenshtein);
    }
};