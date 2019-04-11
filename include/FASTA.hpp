///////////////////////////////////////////////////////////////////////////////
/// @file FASTA.hpp
/// @brief Handle reading in FASTA files into sequences
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "Types.hpp"
#include "Sequence.hpp"



///////////////////////////////////////////////////////////////////////////////
/// @brief Read in a simple FASTA file and return a vector of sequences
/// @note
/// C++11 and higher doesn't return a copy of the data here, it performs
/// a move operation. This is important when dealing with the human genome.
///////////////////////////////////////////////////////////////////////////////
inline std::vector<Sequence> ReadFASTA(const std::string& filePath) {
    // Open file
    std::ifstream fasta(filePath);
    if (!fasta.good()) {
        throw std::invalid_argument("FASTA file path invalid");
    }

    // Prepare to store sequences
    std::vector<Sequence> sequences;

    // Read file
    std::string line, id, sequence;
    while (std::getline(fasta, line)) {
        // Allow empty lines
        if (line.empty()) {
            continue;
        }

        // Mark of new sequence
        if (line.at(0) == '>') {
            // If we just read a sequence, save it
            if (!sequence.empty()) {
                sequences.push_back(Sequence(id, sequence));
            }
            // Extract ID
            id = line.substr(1);
            sequence.clear();
        } else {
            // Sequences are often multi-line
            sequence += line;
        }
    }

    // Save final sequence, terminated by EOF
    if (!sequence.empty()) {
        sequences.push_back(Sequence(id, sequence));
    }

    return sequences;
}
