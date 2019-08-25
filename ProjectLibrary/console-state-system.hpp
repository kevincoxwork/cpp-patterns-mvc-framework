/*!	\console-state-system.hpp/
	\author Kevin Cox
	\date 2019-02-24
	\version 1.0.0
	\note Last edited for Project 2
	\brief Handles the delaration for console related state methods. Custom object
*/

#pragma once
#include <string>
#include <Windows.h>
#include <iostream>
#include <vector>

namespace consoleAPI {
	class ConsoleState {
	private:
		std::vector<char>			originalTitle;
		HANDLE                      hConsoleInput, hConsoleOutput;
		CONSOLE_SCREEN_BUFFER_INFO	originalCSBI;
		CONSOLE_CURSOR_INFO			originalCCI;
		std::vector<CHAR_INFO>      originalBuffer;
		COORD						originalBufferCoord;
		DWORD						originalConsoleMode;
		WORD						currentConsoleWidth = 0;

		//

	public:
		ConsoleState();

		ConsoleState(std::vector<char>& originalTitle_P, HANDLE& handleConsoleInput, HANDLE& handleConsoleOutput, CONSOLE_SCREEN_BUFFER_INFO& originalCSBI_P,
			CONSOLE_CURSOR_INFO& originalCCI_P, std::vector<CHAR_INFO>& originalBuffer_P, COORD& originalBufferCoord_P, DWORD& originalConsoleMode_P, WORD& currentConsoleWidth_P);

		//getters
		std::vector<char> getOriginalTitle();
		HANDLE getOriginalConsoleInputHandle();
		HANDLE getOriginalConsoleOutputHandle();
		CONSOLE_SCREEN_BUFFER_INFO getOriginalConsoleScreenBufferInfo();
		CONSOLE_CURSOR_INFO getOriginalConsoleCursorInfo();
		std::vector<CHAR_INFO> getOriginalBuffer();
		COORD getOriginalBufferCoord();
		DWORD getOriginalConsoleMode();

		//setters
		void setCurrentConsoleWidth(WORD currentConsoleWidth_P);
		void setConsoleMode(DWORD consoleMode);

		void setTitle(std::vector<char> title);
		void setOriginalConsoleInputHandle(HANDLE input);
		void setOriginalConsoleOutputHandle(HANDLE output);
		void setOriginalConsoleScreenBufferInfo(CONSOLE_SCREEN_BUFFER_INFO csbi);
		void setOriginalConsoleCursorInfo(CONSOLE_CURSOR_INFO ccinfo);
		void setOriginalBuffer(std::vector<CHAR_INFO> buffer);

		void setOriginalBufferCoord(COORD bufferCoord);
	};
	class ConsoleStateHolder {
	public:
		static ConsoleState originalState;
		static ConsoleState currentState;
	};
}