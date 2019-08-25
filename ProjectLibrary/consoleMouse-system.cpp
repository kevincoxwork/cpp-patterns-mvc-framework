/*!	\consoleMouse-system.cpp/
	\author Kevin Cox
	\date 2019-02-24
	\version 1.0.0
	\note Last edited for Project 2
	\brief Handles the implementation for system api level mouse related methods
*/
#include "consoleMouse-system.hpp"
using namespace std;

COORD consoleAPI::getMouseLocation(HANDLE hConsoleInput) {
	vector<INPUT_RECORD> inBuffer(128);
	DWORD numEvents;
	if (!ReadConsoleInput(hConsoleInput, inBuffer.data(), (DWORD)inBuffer.size(), &numEvents)) {
		cerr << "Failed to read console input\n";
	}

	for (size_t iEvent = 0; iEvent < numEvents; ++iEvent) {
		switch (inBuffer[iEvent].EventType) {
		case MOUSE_EVENT:
			return inBuffer[iEvent].Event.MouseEvent.dwMousePosition;
		}
	}
	return COORD{ -1,-1 };
}

int consoleAPI::getNextMouseEvent(HANDLE hConsoleInput) {
	// read input buffer repeatedly
	vector<INPUT_RECORD> inBuffer(128);
	//while (true) {
	DWORD numEvents;
	if (!ReadConsoleInput(hConsoleInput, inBuffer.data(), (DWORD)inBuffer.size(), &numEvents)) {
		cerr << "Failed to read console input\n";
		//break;
	}

	for (size_t iEvent = 0; iEvent < numEvents; ++iEvent) {
		switch (inBuffer[iEvent].EventType) {
		case MOUSE_EVENT:
			int value = consoleAPI::mouseEventRationalized(inBuffer[iEvent].Event.MouseEvent);
			//-1 is just mouse movement - we want a "click" event
			if (value != -1) {
				return value;
			}
		}
	}
	//}

	return -100;
}

int consoleAPI::mouseEventRationalized(MOUSE_EVENT_RECORD const& mer) {
#if !defined(MOUSE_HWHEELED)
#define MOUSE_HWHEELED 0x0008
#endif

	switch (mer.dwEventFlags) {
	case 0:	// button pressed or released
	{
		auto mask = mer.dwButtonState;
		if (mask&FROM_LEFT_1ST_BUTTON_PRESSED)
			return 0;
		if (mask&RIGHTMOST_BUTTON_PRESSED)
			return 1;
		if (!mask)
			return 5;
	}

	case DOUBLE_CLICK:
		return 2;

	case MOUSE_HWHEELED:
		return 3;

	case MOUSE_WHEELED:
		return 4;

	default:
		return -1;
	}
}

int consoleAPI::getNextSpecifiedMouseEvent(HANDLE hConsoleInput, DWORD mouseEvent) {
	return 1;
}