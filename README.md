# FMWS (Fuzzy Matching With Seeds)

### What is it?

A command-line interface that takes in a [FASTA](https://en.wikipedia.org/wiki/FASTA) file and a sequence, then finds the best matching substrings of each sequence in the FASTA file using [fuzzy matching](https://en.wikipedia.org/wiki/Fuzzy_matching_(computer-assisted_translation)) and using [Levenshtein distance](https://en.wikipedia.org/wiki/Levenshtein_distance) and [Sørensen–Dice coefficient](https://en.wikipedia.org/wiki/S%C3%B8rensen%E2%80%93Dice_coefficient) as metrics.

### Why?

Fuzzy matching is the process of finding and matching an approximate pattern across strings. The concept started back in 1920, with the many-valued logic proposed by Jan Łukasiewicz, and then followed the evolution of translation memory tools leading up to the 1990's.

Now, fuzzy matching is used in all sorts of applications, including computer assisted translation (CAT) and spell checking. In bioinformatics, fuzzy matching is used for approximate string matching on large DNA sequences. This is what our FMWS tool is meant to facilitate.

### Motivation

This project was created for Northern Arizona University's CS 499 class in Bioinformatics (Spring 2019 term). The primary driving force was proposing our own idea and implementation as well as having the flexibility to do as we please. We also proposed this idea to give us the opportunity to personalize our solution.

### Main Logic

1. Parse command-line arguments
2. Read in FASTA file
3. Extract k-mers from sequence
4. Compare each k-mer to the given substring (parallelized)
5. Store the best substring of each sequence
6. Sort rankings
7. Output smallest distances, in order

###  Use Cases

Different use cases for fuzzy matching range from searching for a list based on relevance to providing recommendations to replace potentially misspelled search words. 

When running our program with three different FASTA sequences, a substring of ACTCACCACTGT, and an Intel i7-4700HQ, these were our outcomes.

Sequence (length)  | Levenshtein | Sorensen | Time(Parallelized vs Non-parallelized) |
------------------ | ----------- | -------- | -------------------------------------- |
E.Coli (4641652)  | 1  | 0.909091  | 2.01 sec vs 5.83 sec  |
Bacillus Anthracis (5227293)  | 1  | 0.909091  | 2.19 sec vs 6.46 sec  |
Bacillus Cereus (5411809)  | 1  | 0.909091  | 2.27 sec vs 6.60 sec  |

### Set-up instructions

We use the following libraries: CMake, GoogleTest. 

GoogleTest has to be compiled and cannot be easily installed. Because of this, we include a 1.7.0 release of GoogleTest in the code base, for the sake of convenience. No installation has to be done. 

Thus, CMake is required. CMake is installed by default in most Linux distros, though we require version 3.4.


__Install dependencies__

Debian-based systems:

```sh
sudo apt install cmake
```

RedHat-based systems:
```sh
dnf install cmake
```

__Set CXX compiler__

A CXX compiler must be set somewhere in your environment. It's often easiest to add it to your terminal.

```sh
vim ~/.bashrc
export CXX=clang++  # Insert at bottom
:wq
```

__Make__

We use CMake to build our code. It produces a unit test executable (tester) and a command-line executable (run)

```sh
cd FMWS/build
cmake ..
make  # add -jX where X is twice the number of cores of your CPU
```

__Use__

To run the unit tests, call tester like below.

```sh
cd FMWS/build
./tester
```

To use the tool, call run like below.

```sh
cd FMWS/build
./run "Path to FASTA file" "some sequence"
```
