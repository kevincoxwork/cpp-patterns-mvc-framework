#include <cox/mvc/controller.hpp>

/*!	\Controller.hpp/
	\author Kevin Cox
	\date 2019-04-17
	\version 1.0.0
	\note Last edited for Project 3
	\brief Holds the models and views
	Is the "dispatcher" for commands
*/

using namespace std;

bool Controller::pushCommandToCommandTargets(Command::ptr command) {
	//see if the command works for the views
	bool result = false;

	//see if the command works for the mvcapp
	result = mvcApp->proc(command);

	if (result)
		return true;

	for (size_t i = 0; i < views.size(); i++)
	{
		result = views[i]->proc(command);

		if (result)
			return true;
	}

	return false;
}

void Controller::attachAllViews() {
	for (size_t i = 0; i < views.size(); i++)
	{
		(*model).attach(views[i]);
	}
	notifyAllViews();
}

void Controller::detachAllViews() {
	for (size_t i = 0; i < views.size(); i++)
	{
		(*model).detach(views[i]);
	}
	notifyAllViews();
}

void Controller::notifyAllViews() {
	for (size_t i = 0; i < views.size(); i++)
	{
		(*model).notify();
	}
}

void Controller::addView(std::shared_ptr<View> view) {
	this->views.push_back(view);
	this->attachAllViews();
}
void Controller::removeView(std::shared_ptr<View> view) {
	this->views.erase(std::find(views.begin(), views.end(), view));
}

void Controller::closeApplication(bool& execution) {
	Command::ptr closeApplicationCommandPointer = Command::ptr(new CloseApplicationCommand());
	this->pushCommandToCommandTargets(closeApplicationCommandPointer);
}

void Controller::startApplication() {
	Command::ptr startApplicationCommandPointer = Command::ptr(new StartApplicationCommand());
	this->pushCommandToCommandTargets(startApplicationCommandPointer);
}