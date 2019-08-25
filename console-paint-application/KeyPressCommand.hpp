#pragma once
#include <cox/mvc/mvccommands/MVCCommand.hpp>
#include <cox/console-utilities/console.hpp>
#include "PaintingModel.hpp"

/*!	\KeyPressCommand.hpp/
	\author Kevin Cox
	\date 2019-04-17
	\version 1.0.0
	\note Last edited for Project 3
	\brief KeyPressCommand - represents a key action
*/

class KeyPressCommand : public MVCCommand {
	Model& model_;
	char keyPressed_;

public:
	KeyPressCommand(Model& model, char keyPressed);
	void execute() override;
};