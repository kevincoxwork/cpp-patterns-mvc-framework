/*!	\consoleMouse-system.hpp/
	\author Kevin Cox
	\date 2019-02-24
	\version 1.0.0
	\note Last edited for Project 2
	\brief Handles the delaration for system api level mouse related methods
*/
#pragma once
#include "console-error.hpp"
#include "console-state-system.hpp"

namespace consoleAPI {
	COORD getMouseLocation(HANDLE hConsoleInput);

	int getNextMouseEvent(HANDLE hConsoleInput);
	int getNextSpecifiedMouseEvent(HANDLE hConsoleInput, DWORD mouseEvent);

	int mouseEventRationalized(MOUSE_EVENT_RECORD const& mer);
}