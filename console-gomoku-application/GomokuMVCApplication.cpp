#include "GomokuMVCApplication.hpp"

using namespace std;

/*!	\GomokuMVCApplication.cpp/
	\author Kevin Cox
	\date 2019-04-17
	\version 1.0.0
	\note Last edited for Project 3
	\brief Is the "main" for the project. All events are generated here
*/

int GomokuMVCApplication::execute() {
	gomokuController = shared_ptr<GomokuController>(new GomokuController((shared_ptr<CommandTarget>(this))));

	gomokuController->startApplication();
	gomokuController->processMouseClick(Console::LeftClick, { 0,0 }, orderedBoundingBoxs);

	while (this->execution)
	{
		//pass relivent information to the controller to process
		Console::MouseClickTypes clickType = consoleUtil->getNextMouseClickType();
		char c = consoleUtil->getNextKeyPress();
		if (clickType != -100) {
			//process the click. something other than moving
			pair<int, int> clickLocation = consoleUtil->getMouseLocation();
			gomokuController->processMouseClick(clickType, clickLocation, orderedBoundingBoxs);
		}
		else if (c != '\0') {
			gomokuController->processKeyPressed(c);
		}
	}

	return EXIT_SUCCESS;
}

bool GomokuMVCApplication::proc(Command::ptr command) {
	//maybe have a setup command?????

	if (this->getCommandClassname(command) == "CloseApplicationCommand") {
	}
	else if (this->getCommandClassname(command) == "StartApplicationCommand") {
		consoleUtil = shared_ptr<Console>(new Console);

		//should be placed in the proc with a startup command
		consoleUtil->setConsoleTitle("Gomoku Application - Kevin Cox 2019");
		consoleUtil->setConsoleSize(this->TOTAL_CONSOLE_WINDOW_SIZE_X, this->TOTAL_CONSOLE_WINDOW_SIZE_Y);
		consoleUtil->setConsoleBackgroundColor(consoleUtil->Gray);

		orderedBoundingBoxs.push_back(pair<pair<int, int>, pair<int, int>> {make_pair(pair<int, int>{0, 0}, pair<int, int>{30, 29})});
		orderedBoundingBoxs.push_back(pair<pair<int, int>, pair<int, int>> {make_pair(pair<int, int>{29, 20}, pair<int, int>{49, 28})});
		orderedBoundingBoxs.push_back(pair<pair<int, int>, pair<int, int>> {make_pair(pair<int, int>{29, 0}, pair<int, int>{49, 10})});
		orderedBoundingBoxs.push_back(pair<pair<int, int>, pair<int, int>> {make_pair(pair<int, int>{29, 11}, pair<int, int>{49, 19})});

		orderedBoundingBoxs.push_back(pair<pair<int, int>, pair<int, int>> {make_pair(pair<int, int>{31, 13}, pair<int, int>{48, 13})});
		orderedBoundingBoxs.push_back(pair<pair<int, int>, pair<int, int>> {make_pair(pair<int, int>{31, 15}, pair<int, int>{48, 15})});

		//build the views
		gbv = shared_ptr<View>(new GomokuBoardView(*gomokuController->model, orderedBoundingBoxs[0].first, orderedBoundingBoxs[0].second, std::shared_ptr<Console>(consoleUtil)));
		gsbv = shared_ptr<View>(new GomokuScoreboardView(*gomokuController->model, orderedBoundingBoxs[1].first, orderedBoundingBoxs[1].second, std::shared_ptr<Console>(consoleUtil)));
		gmv = shared_ptr<View>(new GomokuMovesView(*gomokuController->model, orderedBoundingBoxs[2].first, orderedBoundingBoxs[2].second, std::shared_ptr<Console>(consoleUtil)));
		gpv = shared_ptr<View>(new GomokuPlayerView(*gomokuController->model, orderedBoundingBoxs[3].first, orderedBoundingBoxs[3].second, std::shared_ptr<Console>(consoleUtil)));

		//add views to controller
		gomokuController->addView(gbv);
		gomokuController->addView(gsbv);
		gomokuController->addView(gmv);
		gomokuController->addView(gpv);

		consoleUtil->setCursorVisability(false);
	}

	return false;
}