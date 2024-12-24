#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Board.h"


class Game
{
private:

	enum class gameStatus { GAME_ON, WIN, GAME_OVER };

	std::vector<std::string> players{ "X", "O" };

	Board board;
	int m_lenSequence;
	int currentPlayer;
	gameStatus m_status;

public:
	enum class gameMode { PLAYER, AUTO };

	Game(int boardSize, int lenSequence);

	void play(gameMode mode, std::vector<int> moves);

private:
	bool makeMove(int cellNumber, std::string playerSymbol);
	bool horizontalSequence(int cellNumber, std::string playerSymbol) const;
	bool verticalSequence(int cellNumber, std::string playerSymbol) const;
	bool descendingDiagonalSequence(int cellNumber, std::string playerSymbol) const;
	bool risingDiagonalSequence(int cellNumber, std::string playerSymbol) const;
	bool win(int cellNumber, std::string playerSymbol) const;
	void setStatus(int cellNumber, std::string playerSymbol);
	int nextPlayer();
};
