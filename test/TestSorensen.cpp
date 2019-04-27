#include "gtest/gtest.h"
#include "SorensenDice.hpp"


///////////////////////////////////////////////////////////////////////////////
/// @brief Small equal-sized sequences
///////////////////////////////////////////////////////////////////////////////
TEST(SorensenDice, SmallEqual) {
    const std::string seqA = "algorithms are fun";
    const std::string seqB = "logarithms are not";
    ASSERT_NEAR(SorensenDice(seqA, seqB), 0.588235294, 0.0000001);
}