/*!	\console-state-system.cpp/
	\author Kevin Cox
	\date 2019-02-24
	\version 1.0.0
	\note Last edited for Project 2
	\brief Handles the implementation for console related state methods. Custom object
*/

#include "console-state-system.hpp"

using namespace std;

consoleAPI::ConsoleState consoleAPI::ConsoleStateHolder::currentState = consoleAPI::ConsoleState();
consoleAPI::ConsoleState consoleAPI::ConsoleStateHolder::originalState = consoleAPI::ConsoleState();

consoleAPI::ConsoleState::ConsoleState() {
	//assign nothing - this is for the inital starup
}

consoleAPI::ConsoleState::ConsoleState(vector<char>& originalTitle_P, HANDLE& handleConsoleInput, HANDLE& handleConsoleOutput, CONSOLE_SCREEN_BUFFER_INFO& originalCSBI_P,
	CONSOLE_CURSOR_INFO& originalCCI_P, vector<CHAR_INFO>& originalBuffer_P, COORD& originalBufferCoord_P, DWORD& originalConsoleMode_P, WORD& currentConsoleWidth_P) {
	originalTitle = originalTitle_P;
	hConsoleInput = handleConsoleInput;
	hConsoleOutput = handleConsoleOutput;
	originalCSBI = originalCSBI_P;
	originalCCI = originalCCI_P;
	originalBuffer = originalBuffer_P;
	originalBufferCoord = originalBufferCoord_P;
	originalConsoleMode = originalConsoleMode_P;
	currentConsoleWidth = currentConsoleWidth_P;
}

//getters
vector<char> consoleAPI::ConsoleState::getOriginalTitle() {
	return originalTitle;
}
HANDLE consoleAPI::ConsoleState::getOriginalConsoleInputHandle() {
	return hConsoleInput;
}
HANDLE consoleAPI::ConsoleState::getOriginalConsoleOutputHandle() {
	return hConsoleOutput;
}
CONSOLE_SCREEN_BUFFER_INFO consoleAPI::ConsoleState::getOriginalConsoleScreenBufferInfo() {
	return originalCSBI;
}
CONSOLE_CURSOR_INFO consoleAPI::ConsoleState::getOriginalConsoleCursorInfo() {
	return originalCCI;
}
vector<CHAR_INFO> consoleAPI::ConsoleState::getOriginalBuffer() {
	return originalBuffer;
}
COORD consoleAPI::ConsoleState::getOriginalBufferCoord() {
	return originalBufferCoord;
}
DWORD consoleAPI::ConsoleState::getOriginalConsoleMode() {
	return originalConsoleMode;
}

void consoleAPI::ConsoleState::setConsoleMode(DWORD consoleMode_P) {
	originalConsoleMode = consoleMode_P;
}

void consoleAPI::ConsoleState::setCurrentConsoleWidth(WORD currentConsoleWidth_P) {
	currentConsoleWidth = currentConsoleWidth_P;
}

void consoleAPI::ConsoleState::setTitle(std::vector<char> title) {
	originalTitle = title;
}
void consoleAPI::ConsoleState::setOriginalConsoleInputHandle(HANDLE input) {
	hConsoleInput = input;
}
void consoleAPI::ConsoleState::setOriginalConsoleOutputHandle(HANDLE output) {
	hConsoleOutput = output;
}
void consoleAPI::ConsoleState::setOriginalConsoleScreenBufferInfo(CONSOLE_SCREEN_BUFFER_INFO csbi) {
	originalCSBI = csbi;
}
void consoleAPI::ConsoleState::setOriginalConsoleCursorInfo(CONSOLE_CURSOR_INFO ccinfo) {
	originalCCI = ccinfo;
}
void consoleAPI::ConsoleState::setOriginalBuffer(std::vector<CHAR_INFO> buffer) {
	originalBuffer = buffer;
}
void consoleAPI::ConsoleState::setOriginalBufferCoord(COORD bufferCoord) {
	originalBufferCoord = bufferCoord;
}