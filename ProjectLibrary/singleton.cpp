/*!	\singleton.cpp
	\author Kevin Cox
	\date 2019-01-19
	\version 1.0.0
	\note  Last edited for Project 1
	\brief Implementation of singleton.hpp methods.
*/

#include <cox\patterns\singleton.hpp>
#include <iostream>
#include <exception>
using namespace std;

/*!	Process entry point.
	Calls the SingletonPattern singleton's wmain.
*/
int wmain(int argc, wchar_t* argv[]) try {
#ifdef _DEBUG
	// Enable CRT memory leak checking.
	int dbgFlags = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
	dbgFlags |= _CRTDBG_CHECK_ALWAYS_DF;
	dbgFlags |= _CRTDBG_DELAY_FREE_MEM_DF;
	dbgFlags |= _CRTDBG_LEAK_CHECK_DF;
	_CrtSetDbgFlag(dbgFlags);
#endif
	return SingletonPattern::thisApp_sm->wmain(argc, argv);
}
catch (char const * msg) {
	wcerr << L"exception string: " << msg << endl;
}
catch (exception const& e) {
	wcerr << L"std::exception: " << e.what() << endl;
}
catch (...) {
	wcerr << L"Error: an exception has been caught...\n";
	return EXIT_FAILURE;
}

/*!	SingletonPattern singleton instance pointer.
*/
SingletonPattern* SingletonPattern::thisApp_sm = nullptr;

/*!	main configures the application.
*/
int SingletonPattern::wmain(int argc, wchar_t* argv[]) {
	args_m.assign(argv, argv + argc);
	return execute();
}

/*!	Singleton initialization and confirmation.
	Throws a logic_error if multiple instances are created.
*/
SingletonPattern::SingletonPattern() {
	if (thisApp_sm)
		throw std::logic_error("Error: Singleton Pattern has already been initialized!");
	thisApp_sm = this;
}

/*!	execute the application.
	Override this method in the derived class.
*/
int SingletonPattern::execute() {
	wcout << "Singleton Pattern Framework - Kevin Cox\n";
	return EXIT_SUCCESS;
}