#pragma once
#include <cox/patterns/subject.hpp>

/*!	\Model.hpp/
	\author Kevin Cox
	\date 2019-04-17
	\version 1.0.0
	\note Last edited for Project 3
	\brief Is the internal represenation of an item. Contains the bl
*/

#if defined(_DEBUG) && defined(_DLL)
#pragma comment (lib, "projectlibrary-dist-mt-gd.lib")
#elif defined(_DEBUG) && !defined(_DLL)
#pragma comment (lib, "projectlibrary-dist-mt-sgd.lib")
#elif !defined(_DEBUG) && defined(_DLL)
#pragma comment (lib, "projectlibrary-dist-mt.lib")
#elif !defined(_DEBUG) && !defined(_DLL)
#pragma comment (lib, "projectlibrary-dist-mt-s.lib")
#endif

class Model : public Subject {
public:
	virtual ~Model() {};
	bool isHit(std::pair<std::pair<int, int>, std::pair<int, int>> boundingBox, std::pair<int, int> point);
};