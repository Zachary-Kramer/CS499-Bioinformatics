#include "gtest/gtest.h"
#include "omp.h"
#include "Driver.hpp"
#include "Levenshtein.hpp"

///////////////////////////////////////////////////////////////////////////////
/// @brief E. coli benchmark
///////////////////////////////////////////////////////////////////////////////
TEST(Benchmark, EColi) {
    // TODO(Claudia): Change to E. Coli
    const std::string filePath = "../test/data/E-Coli.fna";
    const std::string substring = "ACTCACCACTGT";

    // omp_get_wtime() is very accuracte and measures in seconds
    double start = omp_get_wtime();
    FuzzyMatch::Run(filePath, substring, true);
    double end = omp_get_wtime();
    std::cout << end - start << " seconds" << std::endl;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Bacillus Anthracis benchmark
///////////////////////////////////////////////////////////////////////////////
TEST(Benchmark, BacAnth) {
    const std::string filePath = "../test/data/Bac_Anth.fasta";
    const std::string substring = "ACTCACCACTGT";

    // omp_get_wtime() is very accuracte and measures in seconds
    double start = omp_get_wtime();
    FuzzyMatch::Run(filePath, substring, true);
    double end = omp_get_wtime();
    std::cout << end - start << " seconds" << std::endl;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Bacillus Cereus benchmark
///////////////////////////////////////////////////////////////////////////////
TEST(Benchmark, BacCer) {
    const std::string filePath = "../test/data/Bac_Cer.fasta";
    const std::string substring = "ACTCACCACTGT";

    // omp_get_wtime() is very accuracte and measures in seconds
    double start = omp_get_wtime();
    FuzzyMatch::Run(filePath, substring, true);
    double end = omp_get_wtime();
    std::cout << end - start << " seconds" << std::endl;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Homo Sapien benchmark
///////////////////////////////////////////////////////////////////////////////
TEST(Benchmark, HomoSap) {
    const std::string filePath = "../test/data/homo_sap.fasta";
    const std::string substring = "ACTCACCACTGT";

    // omp_get_wtime() is very accuracte and measures in seconds
    double start = omp_get_wtime();
    FuzzyMatch::Run(filePath, substring, true);
    double end = omp_get_wtime();
    std::cout << end - start << " seconds" << std::endl;
}