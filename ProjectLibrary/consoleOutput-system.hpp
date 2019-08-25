#pragma once
/*!	\consoleOutput-system.cpp
	\author Kevin Cox
	\date 2019-02-18
	\version 1.0.0
	\note Last edited for Project 2
	\brief Declaration of "system level" console output related methods. Class interacts with the console-level api.
*/
#include "console-error.hpp"
#include "console-state-system.hpp"

namespace consoleAPI {
	//custom colors
#define BACKGROUND_CYAN   (WORD) 0x0030
#define BACKGROUND_BROWN  (WORD) 0x0060
#define BACKGROUND_GREY (WORD) 0x0080

#define FOREGROUND_CYAN   (WORD) 0x0003
#define FOREGROUND_BROWN  (WORD) 0x0006
#define FOREGROUND_GREY (WORD) 0x0008

	std::vector<char> getConsoleTitle();
	HANDLE getSTDHandle(DWORD handle);

	CONSOLE_SCREEN_BUFFER_INFO getConsoleScreenBufferInfo(HANDLE hConsoleOutput);
	std::vector<CHAR_INFO> getConsoleOutputData(HANDLE hConsoleOutput, CONSOLE_SCREEN_BUFFER_INFO& originalCSBI, COORD& originalBufferCoord);

	CONSOLE_CURSOR_INFO getConsoleCursorInfo(HANDLE hConsoleOutput);

	void setConsoleTitle(std::string title);
	void setScreenBufferPosition(HANDLE hConsoleOutput, SMALL_RECT sr);

	void setScreenBufferSize(HANDLE hConsoleOutput, COORD dwSize);

	void setConsoleOutputData(HANDLE hConsoleOutput, std::vector<CHAR_INFO> originalBuffer, CONSOLE_SCREEN_BUFFER_INFO originalCSBI, COORD originalBufferCoord);

	void setConsoleCursorInfo(HANDLE hConsoleOutput, CONSOLE_CURSOR_INFO originalCCI);
	void setConsoleCursorPosition(HANDLE hConsoleOutput, CONSOLE_SCREEN_BUFFER_INFO originalCSBI);

	void setBackgroundColor(HANDLE hConsoleOutput, WORD color, CONSOLE_SCREEN_BUFFER_INFO csbi);

	void setPixal(int x, int y, WORD color, HANDLE hConsoleOutput);

	bool setConsoleMode(HANDLE hConsoleInput, DWORD consoleMode);

	WORD getForgroundWORDColor(int color);
	WORD getBackgroundWORDColor(int color);

	void setConsoleFontSize(HANDLE hConsoleOutput, int size);
	void drawHorizontalLine(int x, int y, WORD color, HANDLE hConsoleOutput, size_t length);
	void drawText(HANDLE hConsoleOutput, std::string text, int x, int y);
}