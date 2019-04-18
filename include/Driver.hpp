///////////////////////////////////////////////////////////////////////////////
/// @file Driver.hpp
/// @brief Holds main logic of code base
///////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <string>
#include <vector>
#include "FASTA.hpp"
#include "Levenshtein.hpp"
#include "Rank.hpp"
#include "Sequence.hpp"
#include "Types.hpp"


namespace FuzzyMatch {

///////////////////////////////////////////////////////////////////////////////
/// @brief Run the program, called from CLI
///////////////////////////////////////////////////////////////////////////////
inline void Run(const std::string& filePath,
                const std::string& substring,
                const bool verbose = (true)) {
    const Index substringLength = substring.length();

    // Read in FASTA file
    const auto sequences = ReadFASTA(filePath);

    // Prepare to store rankings
    std::vector<Rank> globalRanks(sequences.size());

    // If we are dealing with more than 4 sequences, parallelize
    // at the sequence level. Otherwise parallelize at the k-mer level.
    bool parallelizeKMers = (sequences.size() < 4) ? true : false;

    // Go through each sequence
    Index i;
    #pragma omp parallel for schedule(dynamic) private(i) \
    if (!parallelizeKMers)
    for (i = 0; i < sequences.size(); ++i) {
        // Calculate how many k-mers to calculate at a time
        // For now get all substrings at once
        const Index numKMers = sequences.at(i).DNA.length() - 2*substringLength;

        // Prepare to store ranks
        std::vector<Rank> localRanks(numKMers);

        // TODO(Someone): Only generate a certain amount at a time
        const auto substrings = GetSubstrings(0,
                                              substringLength,
                                              numKMers,
                                              sequences.at(i).DNA);

        // Now calculate the Levenshtein distance for each k-mer
        Index j;
        const std::string id = sequences.at(i).id;
        // Create a fake rank
        Rank bestRank;
        bestRank.levenshtein = 100000000;
        // Parallelize
        #pragma omp parallel for schedule(dynamic) \
        private(j) firstprivate(id) \
        if (parallelizeKMers)
        for (j = 0; j < substrings.size(); ++j) {
            // Calculate distance
            const Rank rank(id, substrings.at(j), LevenshteinDistance(substrings.at(j), substring));
            if (rank < bestRank) bestRank = rank;
        }
        // Save best substring + score
        globalRanks.at(i) = bestRank;
    }

    // Output best scores
    std::sort(globalRanks.begin(), globalRanks.end());
    if (verbose) {
        for (const auto& rank : globalRanks) {
            std::cout << rank.id << ": " << rank.substring << " | " << rank.levenshtein << std::endl;
        }
    }
}
}  // namespace FuzzyMatch
