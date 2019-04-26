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
    double sorensen;
    double score;

    // Constructors
    explicit Rank() {}
    explicit Rank(const std::string& seqID,
                  const std::string& substr,
                  const int lScore,
                  const double sScore) :
    id (seqID),
    substring(substr),
    levenshtein(lScore),
    sorensen(sScore),
    score(lScore - sScore) {
    }

    // Sorting
    bool operator > (const Rank& r) const {
        return (score > r.score);
    }
    bool operator < (const Rank& r) const {
        return (score < r.score);
    }
};