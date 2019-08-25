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
	GomokuGameModel* model = (GomokuGameModel*)&model_;
	if (model->player1BoxSelected) {
		std::string s;
		s.push_back(keyPressed_);

		std::string currentName = model->player1ID;
		model->updatePlayer1Name(currentName + s);
	}
	else if (model->player2BoxSelected) {
		std::string s;
		s.push_back(keyPressed_);

		std::string currentName = model->player2ID;
		model->updatePlayer2Name(currentName + s);
	}
	else if (keyPressed_ == 'r')
	{
		model->resetBoard();
	}
}