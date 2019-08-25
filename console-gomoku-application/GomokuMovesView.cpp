#include "GomokuMovesView.hpp"

using namespace std;

/*!	\GomokuMovesView.cpp/
	\author Kevin Cox
	\date 2019-04-17
	\version 1.0.0
	\note Last edited for Project 3
	\brief Is the representation of the moves played
*/

GomokuMovesView::GomokuMovesView(Model& model, std::pair<int, int> startingPoint, std::pair<int, int> endingPoint, std::shared_ptr<Console> console) : model_(model), console_(console) {
	startingPoint_ = startingPoint;
	endingPoint_ = endingPoint;

	//draw static components

	//game board border
	console_->drawHorizontalLine(pair<int, int>{startingPoint_.first, startingPoint_.second}, pair<int, int>{endingPoint_.first, startingPoint_.second}, console_->Cyan);
	console_->drawHorizontalLine(pair<int, int>{startingPoint_.first, endingPoint_.second}, pair<int, int>{endingPoint_.first + 1, endingPoint_.second}, console_->Cyan);

	console_->drawVertialLine(pair<int, int>{startingPoint_.first, startingPoint_.second}, pair<int, int>{startingPoint_.first, endingPoint_.second}, console_->Cyan);
	console_->drawVertialLine(pair<int, int>{endingPoint_.first, startingPoint_.second}, pair<int, int>{endingPoint_.first, endingPoint_.second}, console_->Cyan);
}

void GomokuMovesView::update() {
	//use the model to redraw the board

	GomokuGameModel* gmodel = (GomokuGameModel*)&model_;

	for (size_t i = 0; i < gmodel->scrollBarComponents.size(); i++) {
		console_->drawText(gmodel->scrollBarComponents[i].first, gmodel->scrollBarComponents[i].second.first, Console::Black, Console::Gray);
	}

	for (size_t i = 0; i < gmodel->scrollDrawInfo.size(); i++)
	{
		console_->drawText(gmodel->scrollDrawInfo[i].first, "     ", Console::Black, Console::Gray);
		console_->drawText(gmodel->scrollDrawInfo[i].first, gmodel->scrollDrawInfo[i].second.first, Console::Black, Console::Gray);
		console_->drawPixal(gmodel->scrollDrawInfo[i].first.first + 5, gmodel->scrollDrawInfo[i].first.second, gmodel->scrollDrawInfo[i].second.second);
	}
}

bool GomokuMovesView::proc(Command::ptr command) {
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
	return false;
}