/*!	\numEval.cpp/
	\author Kevin Cox
	\date 2019-01-19
	\version 1.0.0
	\note Last edited for Project 1
	\brief Used to evaluate the singleton and math methods found in the "ProjectLibrary" project.
*/

#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <math.h>
#include <cox/patterns/singleton.hpp>
#include <cox/mathematics/numberidentification.hpp>

using namespace std;

class NumericEvaluator : public SingletonPattern {
	int execute() override {
		//showing that we have access to the number identifcation lib

		vector<uint64_t> perfectNumberExamples{ 6, 28, 496, 8128, 33550336, 12, 1, 2, 3, 4, 5 };
		vector<uint64_t> deficientNumberExamples{ 1, 2, 3, 4, 5, 7, 8, 9, 10, 11, 13, 14, 15, 16, 17, 19, 21, 22, 23, 25, 26, 27, 29, 31, 32, 33, 34, 35, 37, 38, 39, 41, 43, 44, 45, 46, 47, 49, 50, 6, 28, 496, 8128,12 };
		vector<uint64_t> abundantNumberExamples{ 12, 18, 20, 24, 30, 36, 40, 42, 48, 54, 56, 60, 66, 70, 72, 78, 80, 84, 88, 90, 96, 100, 102, 104, 108, 112, 114, 120, 1,2,3,4,5,6, 28,496 };

		cout << "IsPerfect Number Function Examples" << endl;

		for (size_t i = 0; i < perfectNumberExamples.size(); i++)
		{
			if (isPerfectNumber(perfectNumberExamples[i]))
				cout << perfectNumberExamples[i] << " is a perfect number" << endl;
			else
				cout << perfectNumberExamples[i] << " is not a perfect number" << endl;
		}

		cout << "\n\nIsDeficient Number Function Examples" << endl;

		for (size_t i = 0; i < deficientNumberExamples.size(); i++)
		{
			if (isDeficientNumber(deficientNumberExamples[i]))
				cout << deficientNumberExamples[i] << " is a deficient number" << endl;
			else
				cout << deficientNumberExamples[i] << " is not a deficient number" << endl;
		}

		cout << "\n\nIsAbundant Number Function Examples" << endl;

		for (size_t i = 0; i < abundantNumberExamples.size(); i++)
		{
			if (isAbundantNumber(abundantNumberExamples[i]))
				cout << abundantNumberExamples[i] << " is an abundant number" << endl;
			else
				cout << abundantNumberExamples[i] << " is not an abundant number" << endl;
		}

		return EXIT_SUCCESS;
	}
}numEval /*, numEval2 */;