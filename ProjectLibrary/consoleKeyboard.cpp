/*!	\consoleKeyboard.cpp/
	\author Kevin Cox
	\date 2019-02-24
	\version 1.0.0
	\note Last edited for Project 2
	\brief Handles the implementation for keyboard input related methods
*/
#include <cox/console-utilities/console.hpp>
#include "consoleKeyboard-system.hpp"

void Console::setCursorVisability(bool visability) {
	int visabilityInt = 0;
	if (visability) {
		visabilityInt = 1;
	}
	consoleAPI::setCursorVisability(consoleAPI::ConsoleStateHolder::originalState.getOriginalConsoleOutputHandle(), consoleAPI::ConsoleStateHolder::originalState.getOriginalConsoleCursorInfo(), visabilityInt);
}

bool Console::keyPressed(char keyPress) {
	char pressed = consoleAPI::keyPressed(consoleAPI::ConsoleStateHolder::originalState.getOriginalConsoleInputHandle());

	if (pressed == keyPress) {
		return true;
	}
	return false;
}

char Console::getNextKeyPress() {
	return consoleAPI::keyPressed(consoleAPI::ConsoleStateHolder::originalState.getOriginalConsoleInputHandle());
}