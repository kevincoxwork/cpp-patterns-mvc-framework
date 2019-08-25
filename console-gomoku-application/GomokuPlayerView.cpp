#include "GomokuPlayerView.hpp"

using namespace std;

/*!	\GomokuPlayerView.cpp/
	\author Kevin Cox
	\date 2019-04-17
	\version 1.0.0
	\note Last edited for Project 3
	\brief Is the representation of the player names
*/

GomokuPlayerView::GomokuPlayerView(Model& model, std::pair<int, int> startingPoint, std::pair<int, int> endingPoint, std::shared_ptr<Console> console) : model_(model), console_(console) {
	startingPoint_ = startingPoint;
	endingPoint_ = endingPoint;

	//game board border
	console_->drawHorizontalLine(pair<int, int>{startingPoint_.first, startingPoint_.second}, pair<int, int>{endingPoint_.first, startingPoint_.second}, console_->Magenta);
	console_->drawHorizontalLine(pair<int, int>{startingPoint_.first, endingPoint_.second}, pair<int, int>{endingPoint_.first + 1, endingPoint_.second}, console_->Magenta);

	console_->drawVertialLine(pair<int, int>{startingPoint_.first, startingPoint_.second}, pair<int, int>{startingPoint_.first, endingPoint_.second}, console_->Magenta);
	console_->drawVertialLine(pair<int, int>{endingPoint_.first, startingPoint_.second}, pair<int, int>{endingPoint_.first, endingPoint_.second}, console_->Magenta);
}

void GomokuPlayerView::update() {
	//use the model to redraw the board
	GomokuGameModel* gmodel = (GomokuGameModel*)&model_;

	console_->drawText(pair<int, int>{gmodel->playerOneNameBounds.first.first, gmodel->playerOneNameBounds.first.second - 1}, "Name 1:", Console::Black, Console::Gray);
	console_->drawText(pair<int, int>{gmodel->playerTwoNamesBounds.first.first, gmodel->playerTwoNamesBounds.first.second - 1}, "Name 2:", Console::Black, Console::Gray);

	for (int i = gmodel->playerOneNameBounds.first.first; i < gmodel->playerOneNameBounds.second.first; i++)
	{
		console_->drawPixal(i, gmodel->playerOneNameBounds.first.second, Console::Cyan);
	}
	if (gmodel->player1ID == "")
		console_->drawText(std::pair<int, int>{gmodel->playerOneNameBounds.first.first, gmodel->playerOneNameBounds.first.second}, "          ", Console::Black, Console::Cyan);
	else {
		console_->drawText(std::pair<int, int>{gmodel->playerOneNameBounds.first.first, gmodel->playerOneNameBounds.first.second}, gmodel->player1ID, Console::Black, Console::Cyan);
	}

	for (int i = gmodel->playerTwoNamesBounds.first.first; i < gmodel->playerTwoNamesBounds.second.first; i++)
	{
		console_->drawPixal(i, gmodel->playerTwoNamesBounds.first.second, Console::Cyan);
	}

	if (gmodel->player2ID == "")
		console_->drawText(std::pair<int, int>{gmodel->playerTwoNamesBounds.first.first, gmodel->playerTwoNamesBounds.first.second}, "          ", Console::Black, Console::Cyan);
	else {
		console_->drawText(std::pair<int, int>{gmodel->playerTwoNamesBounds.first.first, gmodel->playerTwoNamesBounds.first.second}, gmodel->player2ID, Console::Black, Console::Cyan);
	}
}

bool GomokuPlayerView::proc(Command::ptr command) {
	if (this->getCommandClassname(command) == "MouseClickCommand") {
		//we know this command is an updatePointCommand
		//cast to UpdateCommand
		shared_ptr<MVCCommand> derived = dynamic_pointer_cast<MVCCommand>(command);
		//check if we are in the right clicking
		if (this->isHit(derived->mouseClickLocation)) {
			command->execute();
			return true;
		}
	}
	else if (this->getCommandClassname(command) == "KeyPressCommand") {
		command->execute();
		return true;
	}
	return false;
}