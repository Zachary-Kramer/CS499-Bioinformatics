#include "gtest/gtest.h"
#include "SorensenDice.hpp"


///////////////////////////////////////////////////////////////////////////////
/// @brief Small equal-sized sequences
///////////////////////////////////////////////////////////////////////////////
TEST(SorensenDice, SmallEqual) {
    const std::string seqA = "ACTGACTCGACG";
    const std::string seqB = "ACTCACCACTGT";
    ASSERT_EQ(SorensenDice(seqA, seqB), 0.25);
}