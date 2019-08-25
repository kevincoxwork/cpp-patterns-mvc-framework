#pragma once
#include <cox/mvc/MVCApp.hpp>
#include "PaintController.hpp"

//views
#include "CanvasView.hpp"
#include "MenuView.hpp"
#include "PaletteView.hpp"

/*!	\PaintMVCApp.hpp/
	\author Kevin Cox
	\date 2019-04-17
	\version 1.0.0
	\note Last edited for Project 3
	\brief is the main mvc app.
*/

class PaintMVCApp : public MVCApp {
	std::shared_ptr<Console> consoleUtil;
	std::shared_ptr<PaintController> paintController;

	//views
	std::shared_ptr<View> pv;
	std::shared_ptr<View> cv;

	std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> orderedBoundingBoxs;

	//constnats
	const int TOTAL_CONSOLE_WINDOW_SIZE_X = 40;
	const int TOTAL_CONSOLE_WINDOW_SIZE_Y = 46;

	bool execution = true;

	int execute();
	bool proc(Command::ptr command) override;
}PaintMVCApp
;