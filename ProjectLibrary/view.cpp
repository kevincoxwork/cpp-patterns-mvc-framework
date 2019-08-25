#include <cox/mvc/view.hpp>

using namespace std;

/*!	\View.cpp/
	\author Kevin Cox
	\date 2019-04-17
	\version 1.0.0
	\note Last edited for Project 3
	\brief represents the visual elements of a model. will update on model notifiy
*/

bool View::proc(Command::ptr command) {
	//default proc.
	//should not return true as we can't handle the command
	return false;
}

bool View::isHit(pair<int, int> pointHit) {
	//use the internal x and y to determine if hit
	if ((pointHit.first >= startingPoint_.first && pointHit.first <= endingPoint_.first) && (pointHit.second >= startingPoint_.second && pointHit.second <= endingPoint_.second))
		return true;
	return false;
}