#include "PaintController.hpp"

using namespace std;

/*!	\PaintController.hpp/
	\author Kevin Cox
	\date 2019-04-17
	\version 1.0.0
	\note Last edited for Project 3
	\brief Controller for paint mvc app
*/

PaintController::PaintController(shared_ptr<CommandTarget> holder) {
	this->mvcApp = holder;
	this->model = shared_ptr<Model>(new PaintingModel());
}

void PaintController::processMouseClick(Console::MouseClickTypes click, std::pair<int, int> point, std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> orderedBoundingBoxs) {
	Command::ptr mouseClick = Command::ptr(new MouseClickCommand(*model, point, orderedBoundingBoxs));
	this->pushCommandToCommandTargets(mouseClick);
}

void PaintController::processKeyPressed(char keyhit) {
	Command::ptr keyPress = Command::ptr(new KeyPressCommand(*model, keyhit));
	this->pushCommandToCommandTargets(keyPress);
}