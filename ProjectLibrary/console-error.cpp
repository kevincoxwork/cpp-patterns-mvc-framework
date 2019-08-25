/*!	\console-error.cpp/
	\author Kevin Cox
	\date 2019-02-24
	\version 1.0.0
	\note Last edited for Project 2
	\brief Handles the implementation for custom error class by Garth Santor
*/

#include <Windows.h>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

#include "console-error.hpp"

using namespace std;

//=======================================================
// Error exception class and utilities
//=======================================================
#pragma region XError

/* ErrorDescription */
string ErrorDescription(DWORD dwMessageID) {
	char* msg;
	auto c = FormatMessageA(
		/* flags */			FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_MAX_WIDTH_MASK,
		/* source*/			NULL,
		/* message ID */	dwMessageID,
		/* language */		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		/* buffer */		(LPSTR)&msg,
		/* size */			0,
		/* args */			NULL
	);

	string strMsg = (c == 0)
		? "unknown"
		: msg;
	LocalFree(msg);
	return strMsg;
}

/* Console error exception class. */

XError::XError(int line, file_type file) : code_(GetLastError()), line_(line), file_(file) {}
auto XError::code() const -> id_type { return code_; }
auto XError::line() const -> int { return line_; }
auto XError::file() const -> file_type { return file_; }

XError::string_type XError::msg() const {
	ostringstream oss;
	oss << "Error: " << code() << "\n";
	oss << ErrorDescription(code()) << "\n";
	oss << "In: " << file() << "\n";
	oss << "Line: " << line() << "\n";
	return oss.str();
}

/* Console error exception throw helper macro. */
#define THROW_IF_CONSOLE_ERROR(res) if(!res) throw XError(__LINE__,__FILE__)
#define THROW_CONSOLE_ERROR() throw XError(__LINE__,__FILE__)

#pragma endregion