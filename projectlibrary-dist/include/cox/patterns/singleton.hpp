#pragma once

/*!	\singleton.hpp
	\author Kevin Cox
	\date 2019-01-19
	\version 1.0.0
	\note Last edited for Project 1
	\brief Declaration of "singleton pattern" related methods as well as quality of life cpp actions.
*/

#if defined(_DEBUG) && defined(_DLL)
#pragma comment (lib, "projectlibrary-dist-mt-gd.lib")
#elif defined(_DEBUG) && !defined(_DLL)
#pragma comment (lib, "projectlibrary-dist-mt-sgd.lib")
#elif !defined(_DEBUG) && defined(_DLL)
#pragma comment (lib, "projectlibrary-dist-mt.lib")
#elif !defined(_DEBUG) && !defined(_DLL)
#pragma comment (lib, "projectlibrary-dist-mt-s.lib")
#endif

// Setup DBG environment
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#pragma comment(linker,"/ENTRY:wmainCRTStartup")

// Create a dbg version of new that provides more information
#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#else
#define DBG_NEW new
#endif

// Remaining includes
#include <string>
#include <vector>

/*!	\brief	SingletonPattern is the base-class of the framework.
*/
class SingletonPattern {
	using Args = std::vector<std::wstring>;
	static SingletonPattern* thisApp_sm;
	friend int wmain(int argc, wchar_t* argv[]);
	int wmain(int argc, wchar_t* argv[]);
	Args args_m;
protected:
	SingletonPattern();
	virtual ~SingletonPattern() {}
	virtual int execute();

	/*!	Access th ecommand-line arguments container.
	*/
	Args const& get_args() const { return args_m; }
};