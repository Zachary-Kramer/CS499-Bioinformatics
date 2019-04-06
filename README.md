# CS499-Bioinformatics

ReadMe in-development.


### What is it?

A command-line interface that takes in a FASTA file and a sequence, then finds the best matching substrings of each sequence in the FASTA file using fuzzy-matching.


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
cd CS499-Bioinformatics/build
cmake ..
make  # add -jX where X is twice the number of cores of your CPU
```

__Use__

To run the unit tests, call tester like below.

```sh
cd CS499-Bioinformatics/build
./tester
```

To use the tool, call run like below.

```sh
cd CS499-Bioinformatics/build
./run "Path to FASTA file" "some sequence"
```
