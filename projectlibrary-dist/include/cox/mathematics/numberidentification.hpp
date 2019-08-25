#pragma once

/*!	\numberidentification.hpp
	\author Kevin Cox
	\date 2019-01-19
	\version 1.0.0
	\note Last edited for project 1
	\brief Delcaration of math related functions for the "projectLibrary"
*/
#include <cstdint>

#if defined(_DEBUG) && defined(_DLL)
#pragma comment (lib, "projectlibrary-dist-mt-gd.lib")
#elif defined(_DEBUG) && !defined(_DLL)
#pragma comment (lib, "projectlibrary-dist-mt-sgd.lib")
#elif !defined(_DEBUG) && defined(_DLL)
#pragma comment (lib, "projectlibrary-dist-mt.lib")
#elif !defined(_DEBUG) && !defined(_DLL)
#pragma comment (lib, "projectlibrary-dist-mt-s.lib")
#endif
//methods make static to access at any time.

//https://en.wikipedia.org/wiki/Perfect_number
//sum of divisors of n (excluding itself) is equal to n
bool isPerfectNumber(std::uint64_t number);

//https://en.wikipedia.org/wiki/Deficient_number
//sum of divisors of n (excluding itself) is > n
bool isDeficientNumber(std::uint64_t number);

//https://en.wikipedia.org/wiki/Abundant_number
//sum of divisors of n (excluding itself) is < n
bool isAbundantNumber(std::uint64_t number);