///////////////////////////////////////////////////////////////////////////////
/// @file Driver.hpp
/// @brief Holds main logic of code base
///////////////////////////////////////////////////////////////////////////////

#include <algorithm>
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
    std::vector<Rank> globalRanks(sequences.size() * 2);  // 2 scores per sequence

    // Go through each sequence
    Index i;
    #pragma omp parallel for schedule(dynamic) private(i)
    for (i = 0; i < sequences.size(); ++i) {
        std::vector<Rank> localRanks;
        // For now get all substrings at once
        // TODO(Someone): Only generate a certain amount at a time
        const auto substrings = GetSubstrings(0,
                                              substringLength,
                                              sequences.at(i).DNA.length() - 2*substringLength,
                                              sequences.at(i).DNA);
        for (const auto& substr : substrings) {
            // Calculate distance
            localRanks.push_back(Rank(sequences.at(i).id, substr, LevenshteinDistance(substr, substring)));
        }
        // Sort in ascending order
        std::sort(localRanks.begin(), localRanks.end());
        // Take the best two
        globalRanks.at(2*i) = localRanks.at(0);
        globalRanks.at(2*i+1) = localRanks.at(1);
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
