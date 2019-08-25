/*!	\console-Keyboard-system.cpp/
	\author Kevin Cox
	\date 2019-02-24
	\version 1.0.0
	\note Last edited for Project 2
	\brief Handles the implementation for system api level keyboard related methods
*/

#include "consoleKeyboard-system.hpp"

using namespace std;

void consoleAPI::setCursorVisability(HANDLE hConsoleOuput, CONSOLE_CURSOR_INFO originalCCI, int visability) {
	auto newCCI = originalCCI;
	newCCI.bVisible = FALSE;
	THROW_IF_CONSOLE_ERROR(SetConsoleCursorInfo(hConsoleOuput, &newCCI));
}

bool consoleAPI::setCtrlCHandler() {
	return SetConsoleCtrlHandler((PHANDLER_ROUTINE)DefaultCtrlHandler, TRUE);
}
void consoleAPI::dispose() {
	//restore past console window from the saved state information
	//call all the set methods and use the data from the state object
	//must set buffer position to 0 before changing screen size

	consoleAPI::setScreenBufferPosition(consoleAPI::ConsoleStateHolder::originalState.getOriginalConsoleOutputHandle(), SMALL_RECT{ 0 });
	consoleAPI::setScreenBufferSize(consoleAPI::ConsoleStateHolder::originalState.getOriginalConsoleOutputHandle(), consoleAPI::ConsoleStateHolder::originalState.getOriginalConsoleScreenBufferInfo().dwSize);
	consoleAPI::setScreenBufferPosition(consoleAPI::ConsoleStateHolder::originalState.getOriginalConsoleOutputHandle(), consoleAPI::ConsoleStateHolder::originalState.getOriginalConsoleScreenBufferInfo().srWindow);

	consoleAPI::setConsoleOutputData(consoleAPI::ConsoleStateHolder::originalState.getOriginalConsoleOutputHandle(), consoleAPI::ConsoleStateHolder::originalState.getOriginalBuffer(), consoleAPI::ConsoleStateHolder::originalState.getOriginalConsoleScreenBufferInfo(), consoleAPI::ConsoleStateHolder::originalState.getOriginalBufferCoord());

	consoleAPI::setConsoleCursorInfo(consoleAPI::ConsoleStateHolder::originalState.getOriginalConsoleOutputHandle(), consoleAPI::ConsoleStateHolder::originalState.getOriginalConsoleCursorInfo());
	consoleAPI::setConsoleCursorPosition(consoleAPI::ConsoleStateHolder::originalState.getOriginalConsoleOutputHandle(), consoleAPI::ConsoleStateHolder::originalState.getOriginalConsoleScreenBufferInfo());

	exit(EXIT_SUCCESS);
}

BOOL consoleAPI::DefaultCtrlHandler(DWORD ctrlType) {
	switch (ctrlType) {
	case CTRL_C_EVENT:
		dispose();

		return TRUE;
	}

	return FALSE;
}

char consoleAPI::keyPressed(HANDLE hConsoleInput) {
	// read input buffer repeatedly
	vector<INPUT_RECORD> inBuffer(128);
	DWORD numEvents;
	if (!ReadConsoleInput(hConsoleInput, inBuffer.data(), (DWORD)inBuffer.size(), &numEvents)) {
		cerr << "Failed to read console input\n";
	}

	for (size_t iEvent = 0; iEvent < numEvents; ++iEvent) {
		switch (inBuffer[iEvent].EventType) {
		case KEY_EVENT:
			return consoleAPI::keyRationalized(inBuffer[iEvent].Event.KeyEvent);
		}
	}
	//return null char if no key was pressed
	return '\0';
}

char consoleAPI::keyRationalized(KEY_EVENT_RECORD const& ker) {
	if (isgraph(ker.uChar.AsciiChar))
		return ker.uChar.AsciiChar;
	return '\0';
}