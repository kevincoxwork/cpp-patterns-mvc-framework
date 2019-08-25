#include "CanvasView.hpp"

using namespace std;

/*!	\CanvasView.cpp/
	\author Kevin Cox
	\date 2019-04-17
	\version 1.0.0
	\note Last edited for Project 3
	\brief is the representation of the canvas
*/

CanvasView::CanvasView(Model& model, std::pair<int, int> startingPoint, std::pair<int, int> endingPoint, std::shared_ptr<Console> console) : model_(model), console_(console) {
	this->startingPoint_ = startingPoint;
	this->endingPoint_ = endingPoint;
}
void CanvasView::update() {
	//use the ref model to update our view
	PaintingModel* pmodel = (PaintingModel*)&model_;

	//redraw the screen
	for (int y = this->startingPoint_.second; y < this->endingPoint_.second; y++)
	{
		for (int x = this->startingPoint_.first; x < this->endingPoint_.first; x++)
		{
			this->console_->drawPixal(x, y, pmodel->getColorAtPoint(pair<int, int>{(x - startingPoint_.first), (y - startingPoint_.second)}));
		}
	}
};

bool CanvasView::proc(Command::ptr command) {
	//test to see if the command should be executed here

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
	}
	return false;
}