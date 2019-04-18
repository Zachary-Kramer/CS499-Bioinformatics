///////////////////////////////////////////////////////////////////////////////
/// @file Driver.cpp
/// @brief Serves as the command-line interface
///////////////////////////////////////////////////////////////////////////////

#include "Driver.hpp"


int main(int argc, char* argv[]) {
    // Parse command-line arguments
    if (argc != 3) {
        throw std::invalid_argument("Must be called with: <FASTA path> <substring>");
    }
    const std::string filePath(argv[1]);
    const std::string substring(argv[2]);

    // Run program
    FuzzyMatch::Run(filePath, substring);

    return 0;
}
