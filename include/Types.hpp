///////////////////////////////////////////////////////////////////////////////
/// @file Types.hpp
/// @brief Defines various custom data types for ease-of-use
///////////////////////////////////////////////////////////////////////////////

#include <utility>   // For std::size_t
#include <iostream>  // For printing
#include <iomanip>   // For messing with precision
#include <string>    // For std::string


// Define a standard type to represent indices
// -------------------------------------------
// std::size_t is designed for this, make it our standard
// It is essentially an unsigned int, which is the type used in sizeof() and
// similar functions. It can store the maximum size of any type.
// https://en.cppreference.com/w/cpp/types/size_t
// Is extremely important to *not* use int because of the human genome
using Index = std::size_t;
