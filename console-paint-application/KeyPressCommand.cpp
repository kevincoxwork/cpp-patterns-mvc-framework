#include "KeyPressCommand.hpp"

/*!	\KeyPressCommand.cpp/
	\author Kevin Cox
	\date 2019-04-17
	\version 1.0.0
	\note Last edited for Project 3
	\brief KeyPressCommand - represents a key action
*/

KeyPressCommand::KeyPressCommand(Model& model, char keyPressed) : model_(model), keyPressed_(keyPressed) {
}

void KeyPressCommand::execute() {
	PaintingModel* model = (PaintingModel*)&model_;

	model->clearCanvas();
}