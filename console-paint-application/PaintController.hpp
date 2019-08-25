#pragma once
#include <cox/mvc/controller.hpp>
#include <memory>
#include "PaintingModel.hpp"
#include "MouseClickCommand.hpp"
#include "KeyPressCommand.hpp"

/*!	\PaintController.hpp/
	\author Kevin Cox
	\date 2019-04-17
	\version 1.0.0
	\note Last edited for Project 3
	\brief Controller for paint mvc app
*/

class PaintController : public Controller {
public:
	PaintController(std::shared_ptr<CommandTarget> holder);

	void processMouseClick(Console::MouseClickTypes click, std::pair<int, int> point, std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> orderedBoundingBoxs);
	void processKeyPressed(char keyhit);
};