#pragma once
#include <cox/mvc/mvccommands/MVCCommand.hpp>
#include <cox/console-utilities/console.hpp>
#include "GomokuGameModel.hpp"

/*!	\MouseClickCommand.hpp/
	\author Kevin Cox
	\date 2019-04-17
	\version 1.0.0
	\note Last edited for Project 3
	\brief MouseClickCommand - represents a mouse click action
*/

class MouseClickCommand : public MVCCommand {
	Model& model_;
	Console::Colors color_;
	std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> orderedBoundingBoxes_;

public:
	MouseClickCommand(Model& model, std::pair<int, int> point, std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> orderedBoundingBoxes);
	void execute() override;
};