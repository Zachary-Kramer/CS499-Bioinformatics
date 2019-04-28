///////////////////////////////////////////////////////////////////////////////
/// @file Driver.hpp
/// @brief Holds main logic of code base
///////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <string>
#include <vector>
#include <thread>
#include <limits>
#include "FASTA.hpp"
#include "Levenshtein.hpp"
#include "SorensenDice.hpp"
#include "Rank.hpp"
#include "Sequence.hpp"
#include "Types.hpp"

constexpr bool ENABLE_PARALLELIZATION = true;

namespace FuzzyMatch {

///////////////////////////////////////////////////////////////////////////////
/// @brief Run the program, called from CLI
///////////////////////////////////////////////////////////////////////////////
inline void Run(const std::string& filePath,
                const std::string& substring,
                const bool verbose = (true)) {
    const Index substringLength = substring.length();
    const Index maxMemory = 5e7;  // 50 MB

    // Read in FASTA file
    const auto sequences = ReadFASTA(filePath);

    // Prepare to store rankings
    std::vector<Rank> globalRanks(sequences.size());

    // If we can assign a sequence to each thread, parallelize at the sequence-level.
    // Otherwise, parallelize individual sequences. There is a greater overhead of
    // parallelizing individual sequences because the CPU threads get re-assinged
    // very quickly.
    const unsigned concurrentThreadsSupported = std::thread::hardware_concurrency();
    const bool parallelizeKMers = (sequences.size() < concurrentThreadsSupported) ? true : false;

    // How many k-mers can we fit into the max memory amount?
    // Non-const because it is modified on the last iteration
    Index numKmers = maxMemory / substringLength;

    // Go through each sequence
    Index i;
    #pragma omp parallel for schedule(dynamic) private(i) \
    if (!parallelizeKMers && ENABLE_PARALLELIZATION)
    for (i = 0; i < sequences.size(); ++i) {
        // Calculate how many k-mers to calculate at a time
        // For now get all substrings at once
        const Index numIters = (sequences.at(i).DNA.length() - 2*substringLength) / numKmers;
        // Prepare to store ranks
        std::vector<Rank> localRanks(numKmers);
        // Only generate a certain amount at a time
        const std::string id = sequences.at(i).id;
        for (Index j = 0; j <= numIters; ++j) {
            const auto substrings = \
            GetSubstrings(j * numKmers, substringLength, numKmers, sequences.at(i).DNA);

            // Now calculate the Levenshtein distance for each k-mer, parallelized
            #pragma omp parallel for schedule(dynamic) \
            private(j) firstprivate(id) \
            if (parallelizeKMers && ENABLE_PARALLELIZATION)
            for (Index k = 0; k < numKmers; ++k) {
                // Calculate distance
                localRanks.at(k) = \
                Rank(id,
                     substrings.at(k),
                     LevenshteinDistance(substrings.at(k), substring),
                     SorensenDice(substrings.at(j), substring));
            }
        }

        // Save best substring + score
        globalRanks.at(i) = *std::min(localRanks.begin(), localRanks.end());
        }

        // Output best scores
        std::sort(globalRanks.begin(), globalRanks.end());
        if (verbose) {
            for (const auto& rank : globalRanks) {
                std::cout << rank.id << ": " << rank.substring << " | " << \
                "Distance: " << rank.score << " | " << \
                "Levenshtein: " << rank.levenshtein << " | " << \
                "Sorensen: " << rank.sorensen << std::endl;
            }
        }
    }
    }  // namespace FuzzyMatch
