#pragma once
#include <cox/mvc/MVCApp.hpp>
#include "GomokuController.hpp"

//views
#include "GomokuBoardView.hpp"
#include "GomokuMovesView.hpp"
#include "GomokuScoreboardView.hpp"
#include "GomokuPlayerView.hpp"

/*!	\GomokuMVCApplication.hpp/
	\author Kevin Cox
	\date 2019-04-17
	\version 1.0.0
	\note Last edited for Project 3
	\brief Is the "main" for the project. All events are generated here
*/

class GomokuMVCApplication : public MVCApp {
	//constnats
	const int TOTAL_CONSOLE_WINDOW_SIZE_X = 50;
	const int TOTAL_CONSOLE_WINDOW_SIZE_Y = 29;

	bool execution = true;

	std::shared_ptr<GomokuController> gomokuController;
	std::shared_ptr<Console> consoleUtil;

	std::shared_ptr<View> gbv;
	std::shared_ptr<View> gsbv;
	std::shared_ptr<View> gmv;
	std::shared_ptr<View> gpv;

	std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> orderedBoundingBoxs;

	int execute();
	bool proc(Command::ptr command) override;
}GomokuMVCApplication;