/*!	\number Identification.cpp
	\author Kevin Cox
	\date 2019-01-19
	\version 1.0.0
	\note  Last edited for project 1
	\brief Implementation of math.hpp methods.
*/

#include <cox\mathematics\numberidentification.hpp>

using namespace std;

bool isPerfectNumber(uint64_t number) {
	uint64_t sum = 0;

	for (int x = 1; x <= number - 1; x++) {
		if (number % x == 0)
			sum += x;
	}

	if (sum == number)
		return true;

	return false;
}

bool isDeficientNumber(uint64_t number) {
	uint64_t sum = 0;

	for (int x = 1; x <= number - 1; x++) {
		if (number % x == 0)
			sum += x;
	}

	if (sum < number)
		return true;

	return false;
}

bool isAbundantNumber(uint64_t number) {
	uint64_t sum = 0;

	for (int x = 1; x <= number - 1; x++) {
		if (number % x == 0)
			sum += x;
	}

	if (sum > number)
		return true;

	return false;
}