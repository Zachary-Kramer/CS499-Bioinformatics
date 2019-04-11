///////////////////////////////////////////////////////////////////////////////
/// @file Driver.cpp
/// @brief Serves as the command-line interface
///////////////////////////////////////////////////////////////////////////////

#include "FASTA.hpp"
#include "Levenshtein.hpp"
#include "Rank.hpp"
#include "Sequence.hpp"
#include "Types.hpp"


int main(int argc, char* argv[]) {
    // Parse command-line arguments
    if (argc != 3) {
        throw std::invalid_argument("3 arguments are required");
    }
    const std::string filePath(argv[1]);
    const std::string substring(argv[2]);
    const Index substringLength = substring.length();

    // Prepare to store rankings
    std::vector<Rank> globalRanks;

    // Read in FASTA file
    const auto sequences = ReadFASTA(filePath);

    // Go through each sequence
    for (const auto& seq : sequences) {
        std::vector<Rank> localRanks;
        // For now get all substrings at once
        const auto substrings = GetSubstrings(0, substringLength, seq.DNA.length() - 2*substringLength, seq.DNA);
        for (const auto& substr : substrings) {
            // Calculate distance
            localRanks.push_back(Rank(seq.id, substr, LevenshteinDistance(substr, substring)));
        }
        // Sort in descending order
        std::sort(localRanks.begin(), localRanks.end(), std::greater());
        // Take the best two
        globalRanks.push_back(localRanks.at(0));
        globalRanks.push_back(localRanks.at(1));
    }

    std::sort(globalRanks.begin(), globalRanks.end(), std::greater());
    for (const auto& rank : globalRanks) {
        std::cout << rank.id << ": " << rank.substring << " | " << rank.levenshtein << std::endl;
    }

    return 0;
}
