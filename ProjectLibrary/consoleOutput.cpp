/*!	\ConsoleOutput.cpp/
	\author Kevin Cox
	\date 2019-02-24
	\version 1.0.0
	\note Last edited for Project 2
	\brief Handles the implementation for all console output related methods
*/

#include <cox/console-utilities/console.hpp>
#include "consoleOutput-system.hpp"

using namespace std;

void Console::setConsoleSize(int length, int width) {
	//set buffer to 0
	SMALL_RECT sr{ 0 };
	consoleAPI::setScreenBufferPosition(consoleAPI::ConsoleStateHolder::originalState.getOriginalConsoleOutputHandle(), sr);

	//set buffer size to screensize
	COORD bufferSize;
	bufferSize.X = length;
	bufferSize.Y = width;
	consoleAPI::setScreenBufferSize(consoleAPI::ConsoleStateHolder::originalState.getOriginalConsoleOutputHandle(), bufferSize);

	CONSOLE_SCREEN_BUFFER_INFO sbi = consoleAPI::getConsoleScreenBufferInfo(consoleAPI::ConsoleStateHolder::originalState.getOriginalConsoleOutputHandle());

	sr.Top = sr.Left = 0;
	length = min((SHORT)length, sbi.dwMaximumWindowSize.X);
	width = min((SHORT)width, sbi.dwMaximumWindowSize.Y);
	sr.Right = length - 1;
	sr.Bottom = width - 1;

	consoleAPI::setScreenBufferPosition(consoleAPI::ConsoleStateHolder::originalState.getOriginalConsoleOutputHandle(), sr);

	consoleAPI::ConsoleStateHolder::originalState.setCurrentConsoleWidth(sr.Right - sr.Left + 1);

	//set the tracker for the current width
}

void Console::setConsoleTitle(std::string title) {
	consoleAPI::setConsoleTitle(title);
}

void Console::setConsoleBackgroundColor(Colors color) {
	WORD backgroundColor = consoleAPI::getBackgroundWORDColor(color);
	consoleAPI::setBackgroundColor(consoleAPI::ConsoleStateHolder::originalState.getOriginalConsoleOutputHandle(), backgroundColor, consoleAPI::ConsoleStateHolder::originalState.getOriginalConsoleScreenBufferInfo());
}

void Console::drawPixal(int x, int y, Colors color) {
	WORD backgroundColor = consoleAPI::getBackgroundWORDColor(color);
	consoleAPI::setPixal(x, y, backgroundColor, consoleAPI::ConsoleStateHolder::originalState.getOriginalConsoleOutputHandle());
}
void Console::setGlobalFontSize(int size) {
	consoleAPI::setConsoleFontSize(consoleAPI::ConsoleStateHolder::originalState.getOriginalConsoleOutputHandle(), size);
}

void Console::drawHorizontalLine(std::pair<int, int> point1, std::pair<int, int> point2, Colors color) {
	size_t distance = point2.first - point1.first;
	WORD backgroundColor = consoleAPI::getBackgroundWORDColor(color);
	consoleAPI::drawHorizontalLine(point1.first, point1.second, backgroundColor, consoleAPI::ConsoleStateHolder::originalState.getOriginalConsoleOutputHandle(), distance);
}

void Console::drawVertialLine(std::pair<int, int> point1, std::pair<int, int> point2, Colors color) {
	WORD backgroundColor = consoleAPI::getBackgroundWORDColor(color);

	for (size_t i = (size_t)point1.second; i < (size_t)point2.second; i++)
	{
		consoleAPI::setPixal(point1.first, (int)i, backgroundColor, consoleAPI::ConsoleStateHolder::originalState.getOriginalConsoleOutputHandle());
	}
}

void Console::drawText(pair<int, int> location, string text, Colors color, Colors colorBack) {
	consoleAPI::drawText(consoleAPI::ConsoleStateHolder::originalState.getOriginalConsoleOutputHandle(), text, location.first, location.second);
	WORD forgroundColor = consoleAPI::getForgroundWORDColor(color);
	WORD backgroundColor = consoleAPI::getBackgroundWORDColor(colorBack);

	//consoleAPI::drawHorizontalLine(location.first, location.second, forgroundColor, consoleAPI::ConsoleStateHolder::originalState.getOriginalConsoleOutputHandle(), (size_t)text.size());
	consoleAPI::drawHorizontalLine(location.first, location.second, backgroundColor, consoleAPI::ConsoleStateHolder::originalState.getOriginalConsoleOutputHandle(), (size_t)text.size());
}