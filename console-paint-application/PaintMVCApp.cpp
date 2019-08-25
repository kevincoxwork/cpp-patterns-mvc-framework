#include "PaintMVCApp.hpp"

using namespace std;

/*!	\PaintMVCApp.cpp/
	\author Kevin Cox
	\date 2019-04-17
	\version 1.0.0
	\note Last edited for Project 3
	\brief is the main mvc app.
*/

int PaintMVCApp::execute() {
	//should be placed in the proc with a startup command
	paintController = shared_ptr<PaintController>(new PaintController((shared_ptr<CommandTarget>(this))));

	paintController->startApplication();

	while (this->execution)
	{
		//pass relivent information to the controller to process
		Console::MouseClickTypes clickType = consoleUtil->getNextMouseClickType();
		if (clickType != -100) {
			//process the click. something other than moving
			pair<int, int> clickLocation = consoleUtil->getMouseLocation();
			paintController->processMouseClick(clickType, clickLocation, orderedBoundingBoxs);
		}
		else if (consoleUtil->keyPressed('c')) {
			paintController->processKeyPressed('c');
		}
	}

	return EXIT_SUCCESS;
}

bool PaintMVCApp::proc(Command::ptr command) {
	if (this->getCommandClassname(command) == "CloseApplicationCommand") {
	}
	else if (this->getCommandClassname(command) == "StartApplicationCommand") {
		consoleUtil = shared_ptr<Console>(new Console);

		consoleUtil->setConsoleTitle("Paint Application - Kevin Cox 2019");
		consoleUtil->setConsoleBackgroundColor(Console::Gray);

		consoleUtil->setConsoleSize(this->TOTAL_CONSOLE_WINDOW_SIZE_X, this->TOTAL_CONSOLE_WINDOW_SIZE_Y);

		orderedBoundingBoxs.push_back(pair<pair<int, int>, pair<int, int>> {make_pair(pair<int, int>{0, 0}, pair<int, int>{40, 5})});
		orderedBoundingBoxs.push_back(pair<pair<int, int>, pair<int, int>> {make_pair(pair<int, int>{0, 6}, pair<int, int>{40, 46})});
		//orderedBoundingBoxs.push_back(pair<pair<int, int>, pair<int, int>> {make_pair(pair<int, int>{0, 46}, pair<int, int>{40, 55})});

		//build the views

		pv = std::shared_ptr<View>(new PaletteView(*paintController->model, orderedBoundingBoxs[0].first, orderedBoundingBoxs[0].second, std::shared_ptr<Console>(consoleUtil)));
		cv = std::shared_ptr<View>(new CanvasView(*paintController->model, orderedBoundingBoxs[1].first, orderedBoundingBoxs[1].second, std::shared_ptr<Console>(consoleUtil)));
		//MenuView mv(*paintController.model, orderedBoundingBoxs[2].first, orderedBoundingBoxs[2].second, std::shared_ptr<Console>(consoleUtil));

		//add views to controller
		paintController->addView(pv);
		paintController->addView(cv);
		//paintController.addView(std::shared_ptr<View>(&mv));

		paintController->notifyAllViews();

		consoleUtil->setCursorVisability(false);
		return true;
	}
	return false;
}