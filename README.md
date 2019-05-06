# FMWS (Fuzzy Matching With Seeds)

ReadMe in-development.


### What is it?

A command-line interface that takes in a FASTA file and a sequence, then finds the best matching substrings of each sequence in the FASTA file using fuzzy-matching.

### Why?

Fuzzy matching is the process of finding and matching an approximate pattern across strings. The concept started back in 1920, with the many-valued logic proposed by Jan Łukasiewicz, and then followed the evolution of translation memory tools leading up to the 90's.

Now, fuzzy matching is used in all sorts of applications, including computer assisted translation (CAT) and spell checking. In bioinformatics, fuzzy matching is used for approximate string matching on large DNA sequences. This is what our FMWS tool is meant to facilitate.

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
