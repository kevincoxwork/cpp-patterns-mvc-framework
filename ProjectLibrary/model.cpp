#include <cox/mvc/model.hpp>

/*!	\Model.hpp/
	\author Kevin Cox
	\date 2019-04-17
	\version 1.0.0
	\note Last edited for Project 3
	\brief Is the internal represenation of an item. Contains the bl
*/

bool Model::isHit(std::pair<std::pair<int, int>, std::pair<int, int>> boundingBox, std::pair<int, int> point) {
	if ((point.first >= boundingBox.first.first && point.first <= boundingBox.second.first) && (point.second >= boundingBox.first.second && point.second <= boundingBox.second.second))
		return true;
	return false;
}