#include "GomokuBoardView.hpp"

using namespace std;

/*!	\GomokuBoardView.cpp/
	\author Kevin Cox
	\date 2019-04-17
	\version 1.0.0
	\note Last edited for Project 3
	\brief Is the representation of the actual game
*/

GomokuBoardView::GomokuBoardView(Model& model, std::pair<int, int> startingPoint, std::pair<int, int> endingPoint, std::shared_ptr<Console> console) : model_(model), console_(console) {
	startingPoint_ = startingPoint;
	endingPoint_ = endingPoint;

	//draw static components

	//game board border
	console_->drawHorizontalLine(pair<int, int>{0, 0}, pair<int, int>{28, 0}, console_->Green);
	console_->drawHorizontalLine(pair<int, int>{0, 28}, pair<int, int>{29, 28}, console_->Green);

	console_->drawVertialLine(pair<int, int>{0, 0}, pair<int, int>{0, 28}, console_->Green);
	console_->drawVertialLine(pair<int, int>{28, 0}, pair<int, int>{28, 28}, console_->Green);
}

void GomokuBoardView::update() {
	//use the model to redraw the board
	GomokuGameModel* gmodel = (GomokuGameModel*)&model_;

	for (size_t i = 0; i < gmodel->boardTiles.size(); i++)
	{
		console_->drawPixal(gmodel->boardTiles[i].location_.first, gmodel->boardTiles[i].location_.second, gmodel->boardTiles[i].color_);
	}
}

bool GomokuBoardView::proc(Command::ptr command) {
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