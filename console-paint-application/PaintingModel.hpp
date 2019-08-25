#pragma once
#include <cox/mvc/model.hpp>
#include <cox/console-utilities/console.hpp>
#include <vector>
#include <map>

/*!	\PaintingModel.hpp/
	\author Kevin Cox
	\date 2019-04-17
	\version 1.0.0
	\note Last edited for Project 3
	\brief Contains the bl and the data for the canvas and palette.
*/

class Tile {
public:
	Tile(int x, int y, Console::Colors color);
	int x_;
	int y_;
	Console::Colors color_;
};

class PaintingModel : public Model {
	//bounds
	std::pair<std::pair<int, int>, std::pair<int, int>> paletteBoundsBox;
	std::pair<std::pair<int, int>, std::pair<int, int>> canvasBoundsBox;
	std::pair<std::pair<int, int>, std::pair<int, int>> menuBoundsBox;

	std::map<std::pair<int, int>, Console::Colors> palettePoints;

	//std::map<std::pair<int, int>, Console::Colors> paintPoints;

	std::vector<Tile> paintPoints;
	Console::Colors activeColor;
	int canvasSizeX_;
	int canvasSizeY_;
public:
	PaintingModel();
	PaintingModel(Console::Colors color, int x, int y);

	//also pass a vector of bounding boxes and use this to determine where the relitive components are
	void mouseClick(std::pair<int, int> point);

	void updatePoint(std::pair<int, int> point);

	void clearCanvas();
	void generatePalette();

	//getters
	Console::Colors getActiveColor();
	Console::Colors getColorAtPoint(std::pair<int, int> point);

	std::map<std::pair<int, int>, Console::Colors> getPalettePoints();

	//int getCanvasSizeX();
	//int getCanvasSizeY();

	//setters
	void setActiveColor(Console::Colors color);
	void setActiveColorFromPalettePoint(std::pair<int, int> point);

	void setAllBounds(std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> orderedBoundingBoxes);

	void setPaletteBoundsBox(std::pair<std::pair<int, int>, std::pair<int, int>> box);
	void setCanvasBoundsBox(std::pair<std::pair<int, int>, std::pair<int, int>> box);
	void setMenuBoundsBox(std::pair<std::pair<int, int>, std::pair<int, int>> box);
};