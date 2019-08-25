#pragma once
#include <cox/patterns/command.hpp>
#include <string>

/*!	\CommandTarget.hpp/
	\author Kevin Cox
	\date 2019-04-17
	\version 1.0.0
	\note Last edited for Project 3
	\brief objects the derive from this object will become target of commands
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

class CommandTarget {
public:
	virtual bool proc(Command::ptr command) = 0;
	std::string getCommandClassname(Command::ptr command);
};