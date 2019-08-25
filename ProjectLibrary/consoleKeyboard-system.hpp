/*!	\console-Keyboard-system.hpp/
	\author Kevin Cox
	\date 2019-02-24
	\version 1.0.0
	\note Last edited for Project 2
	\brief Handles the delaration for system api level keyboard related methods
*/
#pragma once
#include "console-error.hpp"
#include "consoleOutput-system.hpp"
#include "console-state-system.hpp"
namespace consoleAPI {
	void setCursorVisability(HANDLE hConsoleOuput, CONSOLE_CURSOR_INFO originalCCI, int visability);

	bool setCtrlCHandler();

	BOOL DefaultCtrlHandler(DWORD ctrlType);

	void dispose();

	char keyPressed(HANDLE hConsoleInput);

	char keyRationalized(KEY_EVENT_RECORD const& ker);
}