#include <cox/patterns/subject.hpp>

/*!	\Subject.cpp/
	\author Kevin Cox
	\date 2019-04-17
	\version 1.0.0
	\note Last edited for Project 3
	\brief represents the subject attribute of the observer pattern.
*/

void Subject::notify() {
	for (auto observer : observers)
		observer->update();
}