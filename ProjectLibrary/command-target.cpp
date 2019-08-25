#include <cox/patterns/command-target.hpp>

using namespace std;

/*!	\CommandTarget.cpp/
	\author Kevin Cox
	\date 2019-04-17
	\version 1.0.0
	\note Last edited for Project 3
	\brief objects the derive from this object will become target of commands
*/

std::string CommandTarget::getCommandClassname(Command::ptr command) {
	string className = typeid(*command).name();
	//removes the "class " + class name from the typeid call
	return className.substr(6, (int)className.size());
}