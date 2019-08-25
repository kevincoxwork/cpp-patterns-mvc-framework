#pragma once
#include <cox/mvc/view.hpp>
#include <cox/mvc/mvccommands/CloseApplicationCommand.hpp>
#include <cox/mvc/mvccommands/StartApplicationCommand.hpp>
#include <memory>
#include <vector>

/*!	\Controller.hpp/
	\author Kevin Cox
	\date 2019-04-17
	\version 1.0.0
	\note Last edited for Project 3
	\brief Holds the models and views
	Is the "dispatcher" for commands
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

class Controller {
public:
	//has a model and a view
	std::shared_ptr<Model> model;
	std::vector<std::shared_ptr<View>> views;
	std::shared_ptr<CommandTarget> mvcApp;

public:
	bool pushCommandToCommandTargets(Command::ptr command);
	void addView(std::shared_ptr<View> view);
	void removeView(std::shared_ptr<View> view);
	void notifyAllViews();

	void closeApplication(bool& execution);
	void startApplication();

	//redo
	//undo

	void attachAllViews();
	void detachAllViews();
};