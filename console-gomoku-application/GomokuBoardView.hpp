#pragma once
#include <cox/mvc/view.hpp>
#include "GomokuGameModel.hpp"
#include <cox/console-utilities/console.hpp>
#include <iostream>
#include <string>

/*!	\GomokuBoardView.hpp/
	\author Kevin Cox
	\date 2019-04-17
	\version 1.0.0
	\note Last edited for Project 3
	\brief Is the representation of the actual game
*/

class GomokuBoardView : public View {
	Model& model_;
	std::shared_ptr<Console> console_;

public:
	GomokuBoardView(Model& model, std::pair<int, int> startingPoint, std::pair<int, int> endingPoint, std::shared_ptr<Console> console);
	void update() override;
	bool proc(Command::ptr command);
};