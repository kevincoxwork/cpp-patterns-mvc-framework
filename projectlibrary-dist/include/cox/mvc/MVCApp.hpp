#pragma once
#include <cox/mvc/controller.hpp>
#include <cox/patterns/command-target.hpp>
#include <cox/console-utilities/consoleApp.hpp>

/*!	\MVCApp.hpp/
	\author Kevin Cox
	\date 2019-04-17
	\version 1.0.0
	\note Last edited for Project 3
	\brief uses the console app library and is the "main" for an mvc
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

class MVCApp : public ConsoleApp, public CommandTarget {
public:
	bool proc(Command::ptr command) override;
};