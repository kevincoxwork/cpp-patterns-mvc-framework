#include "GomokuController.hpp"

using namespace std;

/*!	\GomokuController.hpp/
	\author Kevin Cox
	\date 2019-04-17
	\version 1.0.0
	\note Last edited for Project 3
	\brief Controller for gomoku game
*/

GomokuController::GomokuController(shared_ptr<CommandTarget> holder) {
	this->mvcApp = holder;
	this->model = shared_ptr<Model>(new GomokuGameModel());
}

void GomokuController::processMouseClick(Console::MouseClickTypes click, std::pair<int, int> point, std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> orderedBoundingBoxs) {
	Command::ptr mouseClick = Command::ptr(new MouseClickCommand(*model, point, orderedBoundingBoxs));
	this->pushCommandToCommandTargets(mouseClick);
}

void GomokuController::processKeyPressed(char keyhit) {
	Command::ptr keyPress = Command::ptr(new KeyPressCommand(*model, keyhit));
	this->pushCommandToCommandTargets(keyPress);
}