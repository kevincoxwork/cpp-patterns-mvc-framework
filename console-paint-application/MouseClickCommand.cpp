#include "MouseClickCommand.hpp"

/*!	\MouseClickCommand.hpp/
	\author Kevin Cox
	\date 2019-04-17
	\version 1.0.0
	\note Last edited for Project 3
	\brief MouseClickCommand - represents a mouse click action
*/

MouseClickCommand::MouseClickCommand(Model& model, std::pair<int, int> point, std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> orderedBoundingBoxes) : model_(model), orderedBoundingBoxes_(orderedBoundingBoxes) {
	this->mouseClickLocation = point;
}
void MouseClickCommand::execute() {
	PaintingModel* model = (PaintingModel*)&model_;

	//update the model with the current bounds
	model->setAllBounds(orderedBoundingBoxes_);

	model->mouseClick(this->mouseClickLocation);
}