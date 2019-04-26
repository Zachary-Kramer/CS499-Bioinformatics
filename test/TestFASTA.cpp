#include "gtest/gtest.h"
#include "FASTA.hpp"


///////////////////////////////////////////////////////////////////////////////
/// @brief Read in a small, simple FASTA file
///////////////////////////////////////////////////////////////////////////////
TEST(FASTA, Small) {
    const auto sequences = ReadFASTA("../test/data/Random.fasta");
    ASSERT_EQ("GAACGTCCTTAACTCTGGCAGG", sequences.at(0).DNA.substr(0, 22));
}
