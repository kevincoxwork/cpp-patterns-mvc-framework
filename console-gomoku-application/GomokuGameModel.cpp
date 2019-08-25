#include "GomokuGameModel.hpp"

using namespace std;

/*!	\GomokuGameModel.hpp/
	\author Kevin Cox
	\date 2019-04-17
	\version 1.0.0
	\note Last edited for Project 3
	\brief Contains the bl for the gomokugame
*/

GomokuGameTile::GomokuGameTile() {
}

GomokuGameTile::GomokuGameTile(std::pair<int, int> location, Console::Colors color, bool legal, std::pair<char, int> gameVal) : location_(location), color_(color), legal_(legal), claimed_(false), gameVal_(gameVal) {
}

GomokuGameModel::GomokuGameModel(int x, int y) : blacksTurn(true), redScore(0), blackScore(0) {
	resetBoard();
}

GomokuGameModel::GomokuGameModel() : blacksTurn(true), redScore(0), blackScore(0) {
	//default color is red
	resetBoard();

	playerOneNameBounds = pair<pair<int, int>, pair<int, int>>{ make_pair(pair<int, int>{31, 13}, pair<int, int>{48, 13}) };
	playerTwoNamesBounds = pair<pair<int, int>, pair<int, int>>{ make_pair(pair<int, int>{31, 15}, pair<int, int>{48, 15}) };
}

void GomokuGameModel::resetBoard() {
	blacksTurn = true;
	movesViewText = "Turn: " + player1ID;
	player1ID = "Player 1";
	player2ID = "Player 2";
	blackMoves.clear();
	redMoves.clear();

	blackScore = 0;
	redScore = 0;

	boardTiles.clear();
	moveHistroy.clear();

	for (int y = 1; y < 28; y++)
	{
		char xCharVal = 'A';
		for (int x = 1; x < 28; x++)
		{
			int remainderX = x % 2;
			int remainderY = y % 2;

			if ((x != 1 && remainderX == 0) || remainderY == 0) {
				boardTiles.push_back(GomokuGameTile(pair<int, int>{x, y}, Console::Blue, true, pair<char, char>{xCharVal, y}));
				xCharVal++;
			}
			else {
				boardTiles.push_back(GomokuGameTile(pair<int, int>{x, y}, Console::White, false, pair<char, char>{' ', -1}));
			}
		}
	}
	notify();
}

void GomokuGameModel::addMoveHistory(std::pair<std::string, Console::Colors> point) {
	moveHistroy.push_back(point);

	//update the scrollbar location
	scrollDrawInfo.clear();

	if (scrollBarComponents.empty()) {
		scrollBarComponents.push_back(pair<pair<int, int>, std::pair<std::string, Console::Colors>> {make_pair(pair<int, int>{movesBoundsBox.second.first - 1, movesBoundsBox.first.second + 1}, (pair<string, Console::Colors>{"^", Console::Gray}))});

		for (int i = movesBoundsBox.first.second + 2; i < movesBoundsBox.second.second - 1; i++)
		{
			scrollBarComponents.push_back(pair<pair<int, int>, std::pair<std::string, Console::Colors>> {make_pair(pair<int, int>{movesBoundsBox.second.first - 1, i}, (pair<string, Console::Colors>{"|", Console::Gray}))});
		}

		scrollBarComponents.push_back(pair<pair<int, int>, std::pair<std::string, Console::Colors>> {make_pair(pair<int, int>{movesBoundsBox.second.first - 1, movesBoundsBox.second.second - 1 }, (pair<string, Console::Colors>{"v", Console::Gray}))});
	}

	//render the active moves

	if (moveHistroy.size() >= 8) {
		scrollTop = abs(7 - (int)moveHistroy.size());
		for (size_t i = moveHistroy.size() - 1; i > moveHistroy.size() - 8; i--)
		{
			scrollDrawInfo.push_back(pair<pair<int, int>, std::pair<std::string, Console::Colors>> {make_pair(pair<int, int>{movesBoundsBox.first.first + 1, movesBoundsBox.first.second + std::abs((int)i - (int)moveHistroy.size()) + 1  }, moveHistroy[i])});
		}
	}
	else {
		scrollTop = 0;
		for (size_t i = moveHistroy.size() - 1; i < -1; i--)
		{
			scrollDrawInfo.push_back(pair<pair<int, int>, std::pair<std::string, Console::Colors>> {make_pair(pair<int, int>{movesBoundsBox.first.first + 1, movesBoundsBox.first.second + std::abs((int)i) + 2 }, moveHistroy[i])});
		}
	}
	scrollBot = (int)moveHistroy.size();
}

void GomokuGameModel::updatePoint(pair<int, int> point) {
	for (size_t i = 0; i < boardTiles.size(); i++)
	{
		//find the point
		if (boardTiles[i].location_ == point && boardTiles[i].legal_ && !boardTiles[i].claimed_) {
			if (blacksTurn) {
				string s;
				s.push_back(boardTiles[i].gameVal_.first);
				addMoveHistory(std::pair<string, Console::Colors>(s + " " + to_string(boardTiles[i].gameVal_.second), Console::Black));
				blackMoves.push_back(point);
				boardTiles[i].color_ = Console::Black;
				movesViewText = "Turn: " + player2ID;
			}
			else {
				string s;
				s.push_back(boardTiles[i].gameVal_.first);
				addMoveHistory(std::pair<string, Console::Colors>(s + " " + to_string(boardTiles[i].gameVal_.second), Console::Red));
				redMoves.push_back(point);
				boardTiles[i].color_ = Console::Red;
				movesViewText = "Turn: " + player1ID;
			}
			boardTiles[i].claimed_ = true;

			if (determineIfWin()) {
				resetBoard();
			}
			else {
				blacksTurn = !blacksTurn;
			}

			notify();
			break;
		}
	}
}

void GomokuGameModel::updatePlayer1Name(std::string name) {
	
	if (name.size() <= 13) {
		notify();
		player1ID = name;
	}
}
void GomokuGameModel::updatePlayer2Name(std::string name) {
	if (name.size() <= 13) {
		player2ID = name;
		notify();
	}
}

void GomokuGameModel::scrollDown() {
	if (scrollTop != 0) {
		//take the current selected and start drawing from that

		scrollDrawInfo.clear();

		scrollBot--;
		scrollTop--;

		for (int i = scrollTop; i < scrollBot; i++)
		{
			scrollDrawInfo.push_back(pair<pair<int, int>, std::pair<std::string, Console::Colors>> {make_pair(pair<int, int>{movesBoundsBox.first.first + 1, movesBoundsBox.second.second - std::abs((int)i) - 2}, moveHistroy[i])});
		}

		notify();
	}
}

void GomokuGameModel::scrollUp() {
	//if we arnt at the top

	if (scrollBot != moveHistroy.size()) {
		//take the current selected and start drawing from that
		scrollDrawInfo.clear();

		scrollBot++;
		scrollTop++;

		for (int i = scrollTop; i < scrollBot; i++)
		{
			scrollDrawInfo.push_back(pair<pair<int, int>, std::pair<std::string, Console::Colors>> {make_pair(pair<int, int>{movesBoundsBox.first.first + 1, movesBoundsBox.second.second - std::abs((int)i) - 1}, moveHistroy[i])});
		}

		notify();
	}
}

void GomokuGameModel::mouseClick(std::pair<int, int> point) {
	//determine where the click occoured
	if (this->isHit(this->gameBoundsBox, point)) {
		pair<int, int> newPoint = { point.first - gameBoundsBox.first.first, point.second - gameBoundsBox.first.second };
		player1BoxSelected = false;
		player2BoxSelected = false;
		this->updatePoint(newPoint);
	}
	else if (this->isHit(this->playerBoundsBox, point)) {
		//subtract the offset of the box and the point
		//pair<int, int> newPoint = { point.first - playerBoundsBox.first.first, point.second - playerBoundsBox.first.second };

		//then update the point on the canvas
		//this->updatePoint(newPoint);
	}
	else if (this->isHit(this->movesBoundsBox, point)) {
		//pair<int, int> newPoint = { point.first - movesBoundsBox.first.first, point.second - movesBoundsBox.first.second };

		if (point.first == movesBoundsBox.second.first - 1 && point.second == movesBoundsBox.first.second + 1) {
			scrollUp();
		}
		else if (point.first == movesBoundsBox.second.first - 1 && point.second == movesBoundsBox.second.second - 1) {
			scrollDown();
		}
		player1BoxSelected = false;
		player2BoxSelected = false;

		//if we click anywhere in these bounds we want to close the application
	}
	else if (this->isHit(this->playerOneNameBounds, point)) {
		player1BoxSelected = true;
		player2BoxSelected = false;

		updatePlayer1Name("");
	}
	else if (this->isHit(this->playerTwoNamesBounds, point)) {
		player1BoxSelected = false;
		player2BoxSelected = true;

		updatePlayer2Name("");
	}
}

void GomokuGameModel::setAllBounds(std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> orderedBoundingBoxes) {
	this->gameBoundsBox = orderedBoundingBoxes[0];
	this->playerBoundsBox = orderedBoundingBoxes[1];
	this->movesBoundsBox = orderedBoundingBoxes[2];
	this->playerNameBox = orderedBoundingBoxes[3];
	this->playerOneNameBounds = orderedBoundingBoxes[4];
	this->playerTwoNamesBounds = orderedBoundingBoxes[5];
}

bool GomokuGameModel::horizontalCheck(vector<pair<int, int>>& moves, int& score) {
	int counter = 0;
	for (size_t i = 1; i < moves.size(); i++)
	{
		if (moves[i - 1].first - moves[i].first == -1 && moves[i - 1].second == moves[i].second) {
			counter++;
		}
		else {
			counter = 0;
		}
	}

	if (counter + 1 > score) {
		score = counter + 1;
	}

	if (counter >= 4)
		return true;
	else
		return false;
}
//check if a color has won vertically
bool GomokuGameModel::verticalCheck(vector<pair<int, int>>& moves, int& score) {
	int counter = 0;
	for (size_t i = 1; i < moves.size(); i++)
	{
		if (moves[i - 1].second - moves[i].second == -1 && moves[i - 1].first == moves[i].first) {
			counter++;
		}
		else {
			counter = 0;
		}
	}

	if (counter + 1 > score) {
		score = counter + 1;
	}

	if (counter >= 4)
		return true;
	else
		return false;
}
//check to see if a color has won diagonally. Has 2 variations
bool GomokuGameModel::diagonalCheck(vector<pair<int, int>>& moves, int& score) {
	//decending
	int counter = 0;
	for (size_t i = 1; i < moves.size(); i++)
	{
		if (moves[i - 1].first - moves[i].first == -1 && moves[i - 1].second - moves[i].second == -1) {
			counter++;
		}
		else {
			counter = 0;
		}
	}
	if (moves.size() == 1)
		score = 1;
	else if (counter + 1 > score) {
		score = counter + 1;
	}

	if (counter >= 4)
		return true;

	//ascending
	counter = 0;
	for (size_t i = 1; i < moves.size(); i++)
	{
		if (moves[i - 1].first - moves[i].first == -1 && moves[i - 1].second - moves[i].second == 1) {
			counter++;
		}
		else {
			counter = 0;
		}
	}

	if (counter + 1 > score) {
		score = counter + 1;
	}
	if (counter >= 4)
		return true;
	else
		return false;
}
//check if we have a winner
bool GomokuGameModel::determineIfWin() {
	bool redWin = false;
	bool blackWin = false;

	//winning calcs

	//sort the data in order by x
	sort(blackMoves.begin(), blackMoves.end());
	sort(redMoves.begin(), redMoves.end());

	//black first

	if (blackMoves.size() == 1)
		blackScore = 1;
	else if (blackMoves.size() != 0) {
		//black horizontal
		blackWin = horizontalCheck(blackMoves, blackScore);

		if (!blackWin) {
			//vertical
			//use temp vector sorted on y
			vector<pair<int, int>> blackMovesVert = blackMoves;

			sort(blackMovesVert.begin(), blackMovesVert.end(), [](auto &left, auto &right) {
				return left.second < right.second;
			});
			blackWin = verticalCheck(blackMovesVert, blackScore);
		}
		if (!blackWin) {
			blackWin = diagonalCheck(blackMoves, blackScore);
		}
	}

	if (redMoves.size() == 1) {
		redScore = 1;
	}
	else if (redMoves.size() != 0) {
		//red horizontal
		redWin = horizontalCheck(redMoves, redScore);

		if (!redWin) {
			//vertical
			//use temp vector sorted on y
			vector<pair<int, int>> redMovesVert = redMoves;

			sort(redMovesVert.begin(), redMovesVert.end(), [](auto &left, auto &right) {
				return left.second < right.second;
			});
			redWin = verticalCheck(redMovesVert, redScore);
		}
		if (!redWin) {
			//red diagonal
			redWin = diagonalCheck(redMoves, redScore);
		}
	}

	//winning display info
	if (blackWin || redWin) {
		//display winning message
		if (blackWin) {
			movesViewText = player1ID + " Wins!";
		}
		if (redWin) {
			movesViewText = player2ID + " Wins!";
		}

		for (size_t i = 0; i < boardTiles.size(); i++)
		{
			if (boardTiles[i].legal_) {
				boardTiles[i].color_ = Console::Red;
			}
		}
		notify();
		Sleep(500);

		for (size_t i = 0; i < boardTiles.size(); i++)
		{
			if (boardTiles[i].legal_) {
				boardTiles[i].color_ = Console::Green;
			}
		}
		notify();
		Sleep(500);

		for (size_t i = 0; i < boardTiles.size(); i++)
		{
			if (boardTiles[i].legal_) {
				boardTiles[i].color_ = Console::Blue;
			}
		}
		notify();
		Sleep(500);

		for (size_t i = 0; i < boardTiles.size(); i++)
		{
			if (boardTiles[i].legal_) {
				boardTiles[i].color_ = Console::Yellow;
			}
		}
		notify();
		Sleep(500);

		for (size_t i = 0; i < boardTiles.size(); i++)
		{
			if (boardTiles[i].legal_) {
				boardTiles[i].color_ = Console::Cyan;
			}
		}
		notify();
		Sleep(500);

		for (size_t i = 0; i < boardTiles.size(); i++)
		{
			if (boardTiles[i].legal_) {
				boardTiles[i].color_ = Console::Magenta;
			}
		}
		notify();
		Sleep(500);
		return true;
	}
	return false;
}