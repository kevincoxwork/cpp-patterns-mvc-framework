/*!	\ConsoleOutput.hpp/
	\author Kevin Cox
	\date 2019-04-17
	\version 1.0.0
	\note Last edited for Project 3
	\brief Outer public facade implementation for console related methods
*/
#pragma once
#include <string>
#include <Windows.h>
#include <iostream>
#include <vector>

//Remove these problematic statemnts
#undef min
#undef max

#if defined(_DEBUG) && defined(_DLL)
#pragma comment (lib, "projectlibrary-dist-mt-gd.lib")
#elif defined(_DEBUG) && !defined(_DLL)
#pragma comment (lib, "projectlibrary-dist-mt-sgd.lib")
#elif !defined(_DEBUG) && defined(_DLL)
#pragma comment (lib, "projectlibrary-dist-mt.lib")
#elif !defined(_DEBUG) && !defined(_DLL)
#pragma comment (lib, "projectlibrary-dist-mt-s.lib")
#endif

class Console {
public:

	Console();
	~Console();
	//Different mouse click types that we might encounter
	enum MouseClickTypes
	{
		LeftClick,
		RightClick,
		DoubleClick,
		HorizonalWheel,
		VerticalWheel,
		LeftMouseUp
	};
	//color constants
	enum Colors
	{
		Red,
		Green,
		Blue,
		Yellow,
		White,
		Black,
		Cyan,
		Brown,
		Gray,
		Magenta
	};

	//life methods
	void dispose();

	//Console Output Methods
	void setConsoleSize(int length, int width);
	void setConsoleTitle(std::string title);
	void setConsoleBackgroundColor(Colors color);

	void drawPixal(int x, int y, Colors color);
	void drawText(std::pair<int, int> location, std::string text, Colors color, Colors colorBack);

	void drawHorizontalLine(std::pair<int, int> point1, std::pair<int, int> point2, Colors color);
	void drawVertialLine(std::pair<int, int> point1, std::pair<int, int> point2, Colors color);

	//void drawCollection();
	void setGlobalFontSize(int size);

	//Console Keyboard Methods
	bool keyPressed(char keyPress);
	char getNextKeyPress();

	//Console Mouse Methods
	std::pair<int, int> getMouseLocation();
	MouseClickTypes getNextMouseClickType();
	std::pair<int, int> getNextSpecifiedMouseEvent(MouseClickTypes mouseEvent);
	void setCursorVisability(bool visability);
};