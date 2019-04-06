#include "gtest/gtest.h"
#include "Sequence.hpp"


///////////////////////////////////////////////////////////////////////////////
/// @brief Generate a few small k-mers
///////////////////////////////////////////////////////////////////////////////
TEST(Sequence, Substr) {
    // Get substrings
    const std::string seq = "ACTGACTCGACG";
    const auto substrings = GetSubstrings(0, 3, 5, seq);

    // Compare results
    std::vector<std::string> substringsRef = {
        "ACT", "CTG", "TGA", "GAC", "ACT"
    };
    for (Index i = 0; i < 5; ++i) {
        ASSERT_EQ(substrings.at(i), substringsRef.at(i));
    }
}