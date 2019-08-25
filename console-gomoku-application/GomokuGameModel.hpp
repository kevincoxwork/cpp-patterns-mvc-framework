#pragma once
#include <cox/mvc/model.hpp>
#include <cox/console-utilities/console.hpp>
#include <vector>
#include <map>
#include <algorithm>

/*!	\GomokuGameModel.hpp/
	\author Kevin Cox
	\date 2019-04-17
	\version 1.0.0
	\note Last edited for Project 3
	\brief Contains the bl for the gomokugame
*/

class GomokuGameTile {
public:
	GomokuGameTile();
	GomokuGameTile(std::pair<int, int> location, Console::Colors color, bool legal, std::pair<char, int> gameVal);
	std::pair<int, int> location_;
	std::pair<char, int> gameVal_;
	Console::Colors color_;
	bool claimed_;
	bool legal_;
};

class GomokuGameModel : public Model {
public:
	//ctor
	GomokuGameModel();
	GomokuGameModel(int x, int y);

	//vars
	std::pair<std::pair<int, int>, std::pair<int, int>> gameBoundsBox;
	std::pair<std::pair<int, int>, std::pair<int, int>> playerBoundsBox;
	std::pair<std::pair<int, int>, std::pair<int, int>> movesBoundsBox;
	std::pair<std::pair<int, int>, std::pair<int, int>> playerNameBox;

	//scroll info

	std::vector<std::pair<std::pair<int, int>, std::pair<std::string, Console::Colors>>> scrollDrawInfo;
	std::vector<std::pair<std::pair<int, int>, std::pair<std::string, Console::Colors>>> scrollBarComponents;

	std::pair<std::pair<int, int>, std::pair<int, int>> playerOneNameBounds;
	std::pair<std::pair<int, int>, std::pair<int, int>> playerTwoNamesBounds;
	bool player1BoxSelected;
	bool player2BoxSelected;

	int scrollTop;
	int scrollBot;

	std::vector<std::pair<std::string, Console::Colors>> moveHistroy;

	std::vector<GomokuGameTile> boardTiles;

	std::vector<std::pair<int, int>> redMoves;
	std::vector<std::pair<int, int>> blackMoves;

	std::string movesViewText = "";

	std::string player1ID = "Player 1";
	std::string player2ID = "Player 2";

	bool blacksTurn;
	int blackScore;
	int redScore;

	// public external methods
	void updatePoint(std::pair<int, int> point);
	void resetBoard();
	void setAllBounds(std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> orderedBoundingBoxes);
	void mouseClick(std::pair<int, int> point);

	void updatePlayer1Name(std::string name);
	void updatePlayer2Name(std::string name);
private:
	//private internal use methods
	bool determineIfWin();
	bool horizontalCheck(std::vector<std::pair<int, int>>& moves, int& score);
	bool verticalCheck(std::vector<std::pair<int, int>>& moves, int& score);
	bool diagonalCheck(std::vector<std::pair<int, int>>& moves, int& score);
	void addMoveHistory(std::pair<std::string, Console::Colors> point);
	void scrollUp();
	void scrollDown();
};