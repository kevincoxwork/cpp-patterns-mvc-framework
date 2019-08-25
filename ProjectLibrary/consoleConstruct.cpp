/*!	\consoleConstruct.cpp/
	\author Kevin Cox
	\date 2019-02-24
	\version 1.0.0
	\note Last edited for Project 2
	\brief Handles the implementation for destructor and constructor
*/

#include <cox/console-utilities/console.hpp>
#include "consoleOutput-system.hpp"
#include "consoleKeyboard-system.hpp"
#include "console-state-system.hpp"

using namespace std;

Console::Console() {
	//new console window
	//save all the relivent information into the

	//temp information to store and pass to object
	vector<char>				originalTitle;
	HANDLE hConsoleInput, hConsoleOutput;
	CONSOLE_SCREEN_BUFFER_INFO	originalCSBI;
	CONSOLE_CURSOR_INFO			originalCCI;
	vector<CHAR_INFO>			originalBuffer;
	COORD						originalBufferCoord;
	DWORD						originalConsoleMode;
	WORD						currentConsoleWidth = 0;

	//get all the current information from the existing console
	originalTitle = consoleAPI::getConsoleTitle();
	hConsoleInput = consoleAPI::getSTDHandle(STD_INPUT_HANDLE);
	hConsoleOutput = consoleAPI::getSTDHandle(STD_OUTPUT_HANDLE);
	originalCSBI = consoleAPI::getConsoleScreenBufferInfo(hConsoleOutput);
	originalCCI = consoleAPI::getConsoleCursorInfo(hConsoleOutput);
	originalBuffer = consoleAPI::getConsoleOutputData(hConsoleOutput, originalCSBI, originalBufferCoord);

	//save this in our state objects
	consoleAPI::ConsoleStateHolder::originalState = consoleAPI::ConsoleState(originalTitle, hConsoleInput, hConsoleOutput, originalCSBI, originalCCI, originalBuffer, originalBufferCoord, originalConsoleMode, currentConsoleWidth);
	consoleAPI::ConsoleStateHolder::originalState = consoleAPI::ConsoleStateHolder::originalState;

	//change the consoleMode to allow for mouse and keyboard input
	originalConsoleMode = ENABLE_WINDOW_INPUT | ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT;
	originalConsoleMode |= ENABLE_EXTENDED_FLAGS;

	consoleAPI::ConsoleStateHolder::originalState.setConsoleMode(originalConsoleMode);
	consoleAPI::setCtrlCHandler();

	if (!consoleAPI::setConsoleMode(consoleAPI::ConsoleStateHolder::originalState.getOriginalConsoleInputHandle(), consoleAPI::ConsoleStateHolder::originalState.getOriginalConsoleMode())) {
		THROW_CONSOLE_ERROR();
	}
}

void Console::dispose() {
	//restore the console back to normal
	consoleAPI::dispose();
}

Console::~Console() {
	this->dispose();
}