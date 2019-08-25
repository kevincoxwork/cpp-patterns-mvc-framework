/*!	\console-error.hpp/
	\author Kevin Cox
	\date 2019-02-24
	\version 1.0.0
	\note Last edited for Project 2
	\brief Handles the delaration for custom error class by Garth Santor
*/
#pragma once
#include <Windows.h>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
//=======================================================
// Error exception class and utilities
//=======================================================
#pragma region XError

/* ErrorDescription */
std::string ErrorDescription(DWORD dwMessageID);

/* Console error exception class. */
class XError {
public:
	using id_type = decltype(GetLastError());
	using file_type = char const *;
	using string_type = std::string;
private:
	id_type code_;
	int	line_;
	file_type file_;
public:
	XError(int line, file_type file);
	auto code() const->id_type;
	auto line() const -> int;
	auto file() const->file_type;

	string_type msg() const;
};

/* Console error exception throw helper macro. */
#define THROW_IF_CONSOLE_ERROR(res) if(!res) throw XError(__LINE__,__FILE__)
#define THROW_CONSOLE_ERROR() throw XError(__LINE__,__FILE__)

#pragma endregion