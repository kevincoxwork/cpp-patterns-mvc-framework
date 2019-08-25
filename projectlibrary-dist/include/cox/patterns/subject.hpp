#pragma once
#include <set>
#include <memory>
#include <cox/patterns/observer.hpp>

/*!	\Subject.hpp/
	\author Kevin Cox
	\date 2019-04-17
	\version 1.0.0
	\note Last edited for Project 3
	\brief represents the subject attribute of the observer pattern.
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

class Subject {
	std::set< std::shared_ptr<Observer>> observers;
public:
	void attach(std::shared_ptr<Observer> p) { observers.insert(p); }
	void detach(std::shared_ptr<Observer> p) { observers.erase(p); }
	void notify();
};