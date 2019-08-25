#include "GomokuScoreboardView.hpp"

using namespace std;

/*!	\GomokuScoreboardView.hpp/
	\author Kevin Cox
	\date 2019-04-17
	\version 1.0.0
	\note Last edited for Project 3
	\brief Is the representation of the current score
*/

GomokuScoreboardView::GomokuScoreboardView(Model& model, std::pair<int, int> startingPoint, std::pair<int, int> endingPoint, std::shared_ptr<Console> console) : model_(model), console_(console) {
	startingPoint_ = startingPoint;
	endingPoint_ = endingPoint;

	//draw static components

	//game board border
	console_->drawHorizontalLine(pair<int, int>{startingPoint_.first, startingPoint_.second}, pair<int, int>{endingPoint_.first, startingPoint_.second}, console_->Yellow);
	console_->drawHorizontalLine(pair<int, int>{startingPoint_.first, endingPoint_.second}, pair<int, int>{endingPoint_.first + 1, endingPoint_.second}, console_->Yellow);

	console_->drawVertialLine(pair<int, int>{startingPoint_.first, startingPoint_.second}, pair<int, int>{startingPoint_.first, endingPoint_.second}, console_->Yellow);
	console_->drawVertialLine(pair<int, int>{endingPoint_.first, startingPoint_.second}, pair<int, int>{endingPoint_.first, endingPoint_.second}, console_->Yellow);
}

void GomokuScoreboardView::update() {
	//use the model to redraw the board
	GomokuGameModel* gmodel = (GomokuGameModel*)&model_;

	//draw static button

	 
	console_->drawText(pair<int, int>{startingPoint_.first + 1, startingPoint_.second + 1 }, "                   ", console_->Black, console_->Gray);
	console_->drawText(pair<int, int>{((endingPoint_.first - startingPoint_.first - (int)gmodel->movesViewText.size()) / 2 + startingPoint_.first + 1), startingPoint_.second + 1}, gmodel->movesViewText, console_->Black, console_->Gray);

	//update the score
	string blackScore = "Score Black: " + to_string(gmodel->blackScore);
	string redScore = "Score Red: " + to_string(gmodel->redScore);
	string totalPlayed = "Turn: " + to_string(gmodel->moveHistroy.size());


	console_->drawText(pair<int, int>{((endingPoint_.first - startingPoint_.first - (int)blackScore.size()) / 2 + startingPoint_.first), startingPoint_.second + 3}, blackScore, console_->Black, console_->Gray);
	console_->drawText(pair<int, int>{((endingPoint_.first - startingPoint_.first - (int)redScore.size()) / 2 + startingPoint_.first), startingPoint_.second + 5}, redScore, console_->Black, console_->Gray);

	console_->drawText(pair<int, int>{((endingPoint_.first - startingPoint_.first - (int)totalPlayed.size()) / 2 + startingPoint_.first), startingPoint_.second + 7}, totalPlayed, console_->Black, console_->Gray);
}

bool GomokuScoreboardView::proc(Command::ptr command) {
	return false;
}