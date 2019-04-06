#include "gtest/gtest.h"
#include "Levenshtein.hpp"


///////////////////////////////////////////////////////////////////////////////
/// @brief Small equal-sized sequences
///////////////////////////////////////////////////////////////////////////////
TEST(Levenshtein, SmallEqual) {
    const std::string seqA = "ACTGACTCGACG";
    const std::string seqB = "ACTCACCACTGT";
    ASSERT_EQ(LevenshteinDistance(seqA, seqB), 5);
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Small different-sized sequences
///////////////////////////////////////////////////////////////////////////////
TEST(Levenshtein, SmallDifferent) {
    const std::string seqA = "ACTCAG";
    const std::string seqB = "ACTCACCACTGT";
    ASSERT_EQ(LevenshteinDistance(seqA, seqB), 6);
}
