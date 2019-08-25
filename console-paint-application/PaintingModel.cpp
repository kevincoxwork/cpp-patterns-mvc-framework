#include "PaintingModel.hpp"

using namespace std;

/*!	\PaintingModel.cpp/
	\author Kevin Cox
	\date 2019-04-17
	\version 1.0.0
	\note Last edited for Project 3
	\brief Contains the bl and the data for the canvas and palette.
*/

Tile::Tile(int x, int y, Console::Colors color) : x_(x), y_(y), color_(color) {
}

PaintingModel::PaintingModel(Console::Colors color, int x, int y) : activeColor(color), canvasSizeX_(x), canvasSizeY_(y) {
	clearCanvas();
	generatePalette();
}

PaintingModel::PaintingModel() : activeColor(Console::Blue), canvasSizeX_(40), canvasSizeY_(46) {
	//default color is red
	clearCanvas();
	generatePalette();
}

void PaintingModel::generatePalette() {
	const Console::Colors colors[] = { Console::Red, Console::Green, Console::Blue, Console::Cyan, Console::Yellow, Console::Magenta };

	for (int i = 0; i < 6; i++)
	{
		this->palettePoints.insert(make_pair(make_pair(this->paletteBoundsBox.first.first + i * 4 + 8, (this->paletteBoundsBox.second.second - this->paletteBoundsBox.first.second) / 2), colors[i]));
		this->palettePoints.insert(make_pair(make_pair(this->paletteBoundsBox.first.first + i * 4 + 1 + 8, (this->paletteBoundsBox.second.second - this->paletteBoundsBox.first.second) / 2), colors[i]));
		this->palettePoints.insert(make_pair(make_pair(this->paletteBoundsBox.first.first + i * 4 + 2 + 8, (this->paletteBoundsBox.second.second - this->paletteBoundsBox.first.second) / 2), colors[i]));
	}
	notify();
}

void PaintingModel::clearCanvas() {
	if (paintPoints.size() != 0) {
		paintPoints.clear();
	}

	for (int y = 0; y < canvasSizeY_; y++)
	{
		for (int x = 0; x < canvasSizeX_; x++)
		{
			//paintPoints.insert(make_pair(make_pair(x, y), Console::Colors::White));
			paintPoints.push_back(Tile(x, y, Console::Colors::White));
		}
	}
	notify();
}

void PaintingModel::updatePoint(pair<int, int> point) {
	int point2 = canvasSizeX_ * point.second + point.first;
	//get active color
	paintPoints[point2].color_ = this->getActiveColor();

	//update the view
	notify();
}
void PaintingModel::setActiveColor(Console::Colors color) {
	this->activeColor = color;
	//update the view
	notify();
}
Console::Colors PaintingModel::getActiveColor() {
	return this->activeColor;
}

Console::Colors PaintingModel::getColorAtPoint(std::pair<int, int> point) {
	//do some math
	int point2 = canvasSizeX_ * point.second + point.first;

	return paintPoints[point2].color_;
}

void PaintingModel::setActiveColorFromPalettePoint(std::pair<int, int> point) {
	if (this->palettePoints.find(point) != this->palettePoints.end()) {
		//we have the key
		//set and notify
		this->activeColor = palettePoints[point];

		notify();
	}
}

void PaintingModel::mouseClick(std::pair<int, int> point) {
	//determine where the click occoured
	if (this->isHit(this->paletteBoundsBox, point)) {
		pair<int, int> newPoint = { point.first - paletteBoundsBox.first.first, point.second - paletteBoundsBox.first.second };
		this->setActiveColorFromPalettePoint(newPoint);
	}
	else if (this->isHit(this->canvasBoundsBox, point)) {
		//subtract the offset of the box and the point
		pair<int, int> newPoint = { point.first - canvasBoundsBox.first.first, point.second - canvasBoundsBox.first.second };

		//then update the point on the canvas
		this->updatePoint(newPoint);
	}
	else if (this->isHit(this->menuBoundsBox, point)) {
		pair<int, int> newPoint = { point.first - menuBoundsBox.first.first, point.second - menuBoundsBox.first.second };

		//if we click anywhere in these bounds we want to close the application
	}
}

void PaintingModel::setPaletteBoundsBox(std::pair<std::pair<int, int>, std::pair<int, int>> box) {
	this->paletteBoundsBox = box;
}
void PaintingModel::setCanvasBoundsBox(std::pair<std::pair<int, int>, std::pair<int, int>> box) {
	this->canvasBoundsBox = box;
}
void PaintingModel::setMenuBoundsBox(std::pair<std::pair<int, int>, std::pair<int, int>> box) {
	this->menuBoundsBox = box;
}

void PaintingModel::setAllBounds(std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> orderedBoundingBoxes) {
	if (orderedBoundingBoxes.size() == 1) {
		this->paletteBoundsBox = orderedBoundingBoxes[0];
	}
	else if (orderedBoundingBoxes.size() == 2) {
		this->paletteBoundsBox = orderedBoundingBoxes[0];
		this->canvasBoundsBox = orderedBoundingBoxes[1];
	}
	else if (orderedBoundingBoxes.size() == 3) {
		this->paletteBoundsBox = orderedBoundingBoxes[0];
		this->canvasBoundsBox = orderedBoundingBoxes[1];
		this->menuBoundsBox = orderedBoundingBoxes[2];
	}
}

std::map<std::pair<int, int>, Console::Colors> PaintingModel::getPalettePoints() {
	return this->palettePoints;
}