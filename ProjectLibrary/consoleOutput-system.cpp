/*!	\consoleOutput-system.cpp
	\author Kevin Cox
	\date 2019-02-18
	\version 1.0.0
	\note Last edited for Project 2
	\brief Declaration of "system level" console output related methods. Class interacts with the console-level api.
*/
#include "consoleOutput-system.hpp"

using namespace std;

//getters
vector<char> consoleAPI::getConsoleTitle() {
	vector<char> originalTitle(64 * 1024);
	originalTitle.resize(size_t(GetConsoleTitleA(originalTitle.data(), (DWORD)originalTitle.size())) + 1);
	originalTitle.shrink_to_fit();
	return originalTitle;
}
HANDLE consoleAPI::getSTDHandle(DWORD handle) {
	return GetStdHandle(handle);
}

CONSOLE_SCREEN_BUFFER_INFO consoleAPI::getConsoleScreenBufferInfo(HANDLE hConsoleOutput) {
	CONSOLE_SCREEN_BUFFER_INFO	originalCSBI;
	THROW_IF_CONSOLE_ERROR(GetConsoleScreenBufferInfo(hConsoleOutput, &originalCSBI));
	return originalCSBI;
}
vector<CHAR_INFO> consoleAPI::getConsoleOutputData(HANDLE hConsoleOutput, CONSOLE_SCREEN_BUFFER_INFO& originalCSBI, COORD& originalBufferCoord) {
	vector<CHAR_INFO> originalBuffer;
	originalBuffer.resize(size_t(originalCSBI.dwSize.X)*originalCSBI.dwSize.Y);
	originalBufferCoord = COORD{ 0 };
	SMALL_RECT bufferRect{ 0 };
	bufferRect.Right = originalCSBI.dwSize.X - 1;
	bufferRect.Bottom = originalCSBI.dwSize.Y - 1;
	THROW_IF_CONSOLE_ERROR(ReadConsoleOutputA(hConsoleOutput, originalBuffer.data(), originalCSBI.dwSize, originalBufferCoord, &bufferRect));
	return originalBuffer;
}

CONSOLE_CURSOR_INFO consoleAPI::getConsoleCursorInfo(HANDLE hConsoleOutput) {
	CONSOLE_CURSOR_INFO	originalCCI;
	THROW_IF_CONSOLE_ERROR(GetConsoleCursorInfo(hConsoleOutput, &originalCCI));
	return originalCCI;
}

//setters
void consoleAPI::setConsoleTitle(string title) {
	THROW_IF_CONSOLE_ERROR(SetConsoleTitleA(title.c_str()));
}

void consoleAPI::setScreenBufferPosition(HANDLE hConsoleOutput, SMALL_RECT sr) {
	THROW_IF_CONSOLE_ERROR(SetConsoleWindowInfo(hConsoleOutput, TRUE, &sr));
}

void consoleAPI::setScreenBufferSize(HANDLE hConsoleOutput, COORD dwSize) {
	THROW_IF_CONSOLE_ERROR(SetConsoleScreenBufferSize(hConsoleOutput, dwSize));
}

void consoleAPI::setConsoleOutputData(HANDLE hConsoleOutput, vector<CHAR_INFO> originalBuffer, CONSOLE_SCREEN_BUFFER_INFO originalCSBI, COORD originalBufferCoord) {
	// Restore the desktop contents
	SMALL_RECT bufferRect{ 0 };
	bufferRect.Right = originalCSBI.dwSize.X - 1;
	bufferRect.Bottom = originalCSBI.dwSize.Y - 1;
	THROW_IF_CONSOLE_ERROR(WriteConsoleOutputA(hConsoleOutput, originalBuffer.data(), originalCSBI.dwSize, originalBufferCoord, &bufferRect));
}

void consoleAPI::setConsoleCursorInfo(HANDLE hConsoleOutput, CONSOLE_CURSOR_INFO originalCCI) {
	THROW_IF_CONSOLE_ERROR(SetConsoleCursorInfo(hConsoleOutput, &originalCCI));
}

void consoleAPI::setConsoleCursorPosition(HANDLE hConsoleOutput, CONSOLE_SCREEN_BUFFER_INFO originalCSBI) {
	THROW_IF_CONSOLE_ERROR(SetConsoleCursorPosition(hConsoleOutput, originalCSBI.dwCursorPosition));
}

void consoleAPI::setBackgroundColor(HANDLE hConsoleOutput, WORD color, CONSOLE_SCREEN_BUFFER_INFO csbi) {
	DWORD charsWritten;
	DWORD consoleSize = csbi.dwSize.X * csbi.dwSize.Y;
	COORD cursorHomeCoord{ 0, 0 };
	THROW_IF_CONSOLE_ERROR(FillConsoleOutputCharacterA(hConsoleOutput, ' ', consoleSize, cursorHomeCoord, &charsWritten));
	THROW_IF_CONSOLE_ERROR(FillConsoleOutputAttribute(hConsoleOutput, color, consoleSize, cursorHomeCoord, &charsWritten));
}

void consoleAPI::setPixal(int x, int y, WORD color, HANDLE hConsoleOutput) {
	COORD loc;
	loc.X = x;
	loc.Y = y;
	DWORD nCharsWritten;
	WriteConsoleOutputAttribute(hConsoleOutput, &color, (DWORD)1, loc, &nCharsWritten);
}

bool consoleAPI::setConsoleMode(HANDLE hConsoleInput, DWORD consoleMode) {
	return SetConsoleMode(hConsoleInput, consoleMode);
}

WORD consoleAPI::getForgroundWORDColor(int color) {
	if (color == 0) {
		return FOREGROUND_RED;
	}
	else if (color == 1) {
		return FOREGROUND_GREEN;
	}
	else if (color == 2) {
		return FOREGROUND_BLUE;
	}
	else if (color == 3) {
		return FOREGROUND_RED | FOREGROUND_GREEN;
	}
	else if (color == 4) {
		return FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
	}
	else if (color == 5) {
		return 0;
	}
	else if (color == 6) {
		return FOREGROUND_CYAN;
	}
	else if (color == 7) {
		return FOREGROUND_BROWN;
	}
	else if (color == 8) {
		return FOREGROUND_GREY;
	}
	else if (color == 9) {
		return FOREGROUND_BLUE | FOREGROUND_RED;
	}
	THROW_CONSOLE_ERROR();
	return 0;
}
WORD consoleAPI::getBackgroundWORDColor(int color) {
	if (color == 0) {
		return BACKGROUND_RED;
	}
	else if (color == 1) {
		return BACKGROUND_GREEN;
	}
	else if (color == 2) {
		return BACKGROUND_BLUE;
	}
	else if (color == 3) {
		return BACKGROUND_RED | BACKGROUND_GREEN;
	}
	else if (color == 4) {
		return BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
	}
	else if (color == 5) {
		return 0;
	}
	else if (color == 6) {
		return BACKGROUND_CYAN;
	}
	else if (color == 7) {
		return BACKGROUND_BROWN;
	}
	else if (color == 8) {
		return BACKGROUND_GREY;
	}
	else if (color == 9) {
		return BACKGROUND_BLUE | BACKGROUND_RED;
	}

	THROW_CONSOLE_ERROR();
	return 0;
}

void consoleAPI::setConsoleFontSize(HANDLE hConsoleOutput, int size) {
	CONSOLE_FONT_INFO lpConsoleCurrentFont;
	THROW_IF_CONSOLE_ERROR(GetCurrentConsoleFont(hConsoleOutput, FALSE, &lpConsoleCurrentFont));
	lpConsoleCurrentFont.dwFontSize.X = size;
	lpConsoleCurrentFont.dwFontSize.Y = size * 2;

	SetCurrentConsoleFontEx(hConsoleOutput, FALSE, (PCONSOLE_FONT_INFOEX)&lpConsoleCurrentFont);
}

void consoleAPI::drawHorizontalLine(int x, int y, WORD color, HANDLE hConsoleOutput, size_t length) {
	//must push colors to an array where the element at the index is the color to use
	//using one color or a constant color will cause errors
	vector<WORD> arr;
	for (size_t i = 0; i < length; i++)
	{
		arr.push_back(color);
	}

	COORD loc;
	loc.X = x;
	loc.Y = y;
	DWORD nCharsWritten;
	WriteConsoleOutputAttribute(hConsoleOutput, arr.data(), (DWORD)length, loc, &nCharsWritten);
}

void consoleAPI::drawText(HANDLE hConsoleOutput, string text, int x, int y) {
	COORD loc;
	loc.X = x;
	loc.Y = y;
	DWORD nCharsWritten;
	THROW_IF_CONSOLE_ERROR(WriteConsoleOutputCharacterA(hConsoleOutput, text.c_str(), (DWORD)text.size(), loc, &nCharsWritten));
}
//SMALL_RECT consoleAPI::getBackgroundColorAt(HANDLE hConsoleOutput, vector<CHAR_INFO> originalBuffer, CONSOLE_SCREEN_BUFFER_INFO originalCSBI, COORD originalBufferCoord) {
//
//	 SMALL_RECT bufferRect{ 0 };
//	 bufferRect.Right = originalCSBI.dwSize.X - 1;
//	 bufferRect.Bottom = originalCSBI.dwSize.Y - 1;
//	 THROW_IF_CONSOLE_ERROR(ReadConsoleOutputA(hConsoleOutput, originalBuffer.data(), originalCSBI.dwSize, originalBufferCoord, &bufferRect));
//	 return bufferRect;
//}