#include "MenuView.hpp"

/*!	\MenuView.cpp/
	\author Kevin Cox
	\date 2019-04-17
	\version 1.0.0
	\note Last edited for Project 3
	\brief is the representation of the menu
*/

using namespace std;

MenuView::MenuView(Model& model, std::pair<int, int> startingPoint, std::pair<int, int> endingPoint, std::shared_ptr<Console> console) : model_(model), console_(console) {
	this->startingPoint_ = startingPoint;
	this->endingPoint_ = endingPoint;

	//create static view items
	//grey background
	for (int i = startingPoint_.second; i <= endingPoint_.second; i++)
	{
		console_->drawHorizontalLine(pair<int, int>{startingPoint_.first, i}, pair<int, int>{endingPoint_.first, i}, Console::Colors::Gray);
	}

	//large button outline
	console_->drawHorizontalLine(pair<int, int>{startingPoint_.first, startingPoint_.second}, pair<int, int>{endingPoint_.first, startingPoint_.second}, Console::Colors::Black);
	console_->drawHorizontalLine(pair<int, int>{startingPoint_.first, endingPoint_.second}, pair<int, int>{endingPoint_.first, endingPoint_.second}, Console::Colors::Black);

	console_->drawVertialLine(pair<int, int>{startingPoint_.first, startingPoint_.second}, pair<int, int>{endingPoint_.first, endingPoint_.second}, Console::Colors::Black);
	console_->drawVertialLine(pair<int, int>{endingPoint_.first - 1, startingPoint_.second}, pair<int, int>{endingPoint_.first - 1, endingPoint_.second}, Console::Colors::Black);

	//draw static button
	const string textToWrite = "Quit Application";

	console_->drawText(pair<int, int>{((endingPoint_.first - startingPoint_.first - (int)textToWrite.size()) / 2), ((endingPoint_.second - startingPoint_.second) / 2 + startingPoint_.second)}, textToWrite, console_->Black, console_->Gray);
}
void MenuView::update() {
	//use the ref model to update our view

	/*PaintingModel* pmodel = (PaintingModel*)&model_;

	cout << " " << pmodel->getActiveColor();*/
};

bool MenuView::proc(Command::ptr command) {
	//test to see if the command should be executed here

	return false;
}