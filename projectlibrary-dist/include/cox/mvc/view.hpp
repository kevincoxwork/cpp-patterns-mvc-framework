#pragma once
#include <cox/patterns/observer.hpp>
#include <cox/mvc/model.hpp>
#include <cox/patterns/command-target.hpp>
#include <cox/mvc/mvccommands/MVCCommand.hpp>

/*!	\View.hpp/
	\author Kevin Cox
	\date 2019-04-17
	\version 1.0.0
	\note Last edited for Project 3
	\brief represents the visual elements of a model. will update on model notifiy
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

class View : public Observer, public CommandTarget {
protected:
	std::pair<int, int> startingPoint_;
	std::pair<int, int> endingPoint_;
public:
	//View();
	//View(std::pair<int, int> startingPoint, std::pair<int, int> endingPoint);
	bool proc(Command::ptr command) override;
	bool isHit(std::pair<int, int> pointHit);
};