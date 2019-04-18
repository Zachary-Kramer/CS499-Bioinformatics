#include "gtest/gtest.h"
#include "omp.h"
#include "Driver.hpp"

///////////////////////////////////////////////////////////////////////////////
/// @brief E. coli benchmark
///////////////////////////////////////////////////////////////////////////////
TEST(Benchmark, EColi) {
    // TODO(Claudia): Change to E. Coli
    const std::string filePath = "../test/data/11-Small.fasta";
    const std::string substring = "ACTCACCACTGT";

    // omp_get_wtime() is very accuracte and measures in seconds
    double start = omp_get_wtime();
    FuzzyMatch::Run(filePath, substring, false);
    double end = omp_get_wtime();
    std::cout << end - start << " seconds" << std::endl;
}

