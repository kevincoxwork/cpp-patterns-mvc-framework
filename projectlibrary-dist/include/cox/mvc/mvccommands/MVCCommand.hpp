#pragma once
#include <cox/patterns/command.hpp>

/*!	\MVCCommand.hpp/
	\author Kevin Cox
	\date 2019-04-17
	\version 1.0.0
	\note Last edited for Project 3
	\brief uses the base command and includes a mouse click location. we don't want every command to have this so we make a new object
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

class MVCCommand : public Command {
	//this command will be used in mvc apps and will include the current mouse postion and window focus so we can determine where to distribute the command
public:
	std::pair<int, int> mouseClickLocation = { -1, -1 };
};