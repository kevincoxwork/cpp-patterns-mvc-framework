#include "PaletteView.hpp"

using namespace std;

/*!	\PaletteView.cpp/
	\author Kevin Cox
	\date 2019-04-17
	\version 1.0.0
	\note Last edited for Project 3
	\brief is the representation of the palette
*/

PaletteView::PaletteView(Model& model, std::pair<int, int> startingPoint, std::pair<int, int> endingPoint, std::shared_ptr<Console> console) : model_(model), console_(console) {
	this->startingPoint_ = startingPoint;
	this->endingPoint_ = endingPoint;

	//draw static console components here

	//grey background
	for (int i = startingPoint_.second; i <= endingPoint_.second; i++)
	{
		console_->drawHorizontalLine(pair<int, int>{startingPoint_.first, i}, pair<int, int>{endingPoint_.first, i}, Console::Colors::Gray);
	}

	PaintingModel* pmodel = (PaintingModel*)&model_;

	//get a copy of palette points
	std::map<std::pair<int, int>, Console::Colors> pp = pmodel->getPalettePoints();

	//draw the updated palette
	for (auto it = pp.begin(); it != pp.end(); it++)
	{
		console_->drawPixal(it->first.first, it->first.second, it->second);
	}
}
void PaletteView::update() {
	//use the ref model to update our view
	PaintingModel* pmodel = (PaintingModel*)&model_;

	const string colorStringNames[] = {
		"Red",
		"Green",
		"Blue",
		"Yellow",
		"White",
		"Black",
		"Cyan",
		"Brown",
		"Gray",
		"Magenta",
		"                           " };

	//center and draw text
	console_->drawText(pair<int, int>{((endingPoint_.first - startingPoint_.first - (int)colorStringNames[10].size()) / 2), endingPoint_.second}, colorStringNames[10], pmodel->getActiveColor(), console_->Gray);

	console_->drawText(pair<int, int>{((endingPoint_.first - startingPoint_.first - (int)colorStringNames[pmodel->getActiveColor()].size()) / 2), endingPoint_.second}, colorStringNames[pmodel->getActiveColor()], pmodel->getActiveColor(), console_->Gray);
};

bool  PaletteView::proc(Command::ptr command) {
	//test to see if the command should be executed here

	if (this->getCommandClassname(command) == "MouseClickCommand") {
		//we know this command is an updatePointCommand
		//cast to UpdateCommand

		shared_ptr<MVCCommand> derived = dynamic_pointer_cast<MVCCommand>(command);
		//check if we are in the right clicking area
		if (this->isHit(derived->mouseClickLocation)) {
			command->execute();
			return true;
		}
	}
	return false;
}