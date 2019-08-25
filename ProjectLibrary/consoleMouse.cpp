/*!	\consoleMouse.cpp/
	\author Kevin Cox
	\date 2019-02-24
	\version 1.0.0
	\note Last edited for Project 2
	\brief Handles the implementation for all mouse input related methods
*/

#include <cox/console-utilities/console.hpp>
#include "consoleMouse-system.hpp"

using namespace std;

pair<int, int> Console::getMouseLocation() {
	COORD coord = consoleAPI::getMouseLocation(consoleAPI::ConsoleStateHolder::originalState.getOriginalConsoleInputHandle());
	pair<int, int> formattedPair(coord.X, coord.Y);
	return formattedPair;
}

Console::MouseClickTypes Console::getNextMouseClickType() {
	return MouseClickTypes(consoleAPI::getNextMouseEvent(consoleAPI::ConsoleStateHolder::originalState.getOriginalConsoleInputHandle()));
}

pair<int, int> Console::getNextSpecifiedMouseEvent(MouseClickTypes mouseEvent) {
	pair<int, int> location{ 0,0 };

	return location;
}