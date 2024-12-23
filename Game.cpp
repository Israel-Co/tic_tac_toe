#include "game.h"

Game::Game(int boardSize, int lenSequence)
	: board(boardSize), m_lenSequence(lenSequence), m_status(gameStatus::GAME_ON),
	currentPlayer(players.size() - 1)
{
	if (lenSequence > boardSize)
	{
		throw "The length of the sequence cannot be bigeer than the boeard size\n";
	}
}

void Game::play()
{
	int cellNumber;
	while (m_status == gameStatus::GAME_ON)
	{
		std::cout << board << std::endl;
		currentPlayer = nextPlayer();
		std::cout << "Enter cell number" << std::endl;
		std::cin >> cellNumber;
		while (!makeMove(cellNumber, players[currentPlayer]))
		{
			std::cout << "The cell is full or out of the range. Enter new cell number" << std::endl;
			std::cin >> cellNumber;
		}
		setStatus(cellNumber, players[currentPlayer]);
	}

	switch (m_status)
	{
	case Game::gameStatus::WIN:
		std::cout << std::endl << board;
		std::cout << std::endl << "----- " << players[currentPlayer] << " is the winner -----" << std::endl;
		break;
	case Game::gameStatus::GAME_OVER:
		std::cout << std::endl << board << std::endl;
		std::cout << "----- GAME OVER, the board is full -----" << std::endl;
		break;
	default:
		break;
	}
}

bool Game::makeMove(int cellNumber, std::string playerSymbol)
{
	return board.updateCellContent(cellNumber, playerSymbol);
}

bool Game::horizontalSequence(int cellNumber, std::string playerSymbol) const
{
	int counter = 0;
	std::vector<int> horizontalSequenceCells;
	int newCell = cellNumber;
	int row, col;
	for (int i = 1; i <= m_lenSequence && board.inSameRow(cellNumber, newCell); i++)
	{
		horizontalSequenceCells.insert(horizontalSequenceCells.begin(), newCell);
		newCell = cellNumber - i;
	}
	newCell = cellNumber + 1;
	for (int i = 2; i <= m_lenSequence && board.inSameRow(cellNumber, newCell); i++)
	{
		horizontalSequenceCells.push_back(newCell);
		newCell = cellNumber + i;
	}

	for (auto cell : horizontalSequenceCells)
	{
		row = board.getRow(cell);
		col = board.getCol(cell);
		if (board[row][col] != playerSymbol)
		{
			counter = 0;
		}
		else
		{
			++counter;
		}

		if (counter >= m_lenSequence)
		{
			return true;
		}
	}
	return false;
}

bool Game::verticalSequence(int cellNumber, std::string playerSymbol) const
{
	int counter = 0;
	std::vector<int> verticalSequenceCells;
	int newCell = cellNumber;
	int row, col;

	for (int i = 1; i <= m_lenSequence && board.inSameCol(cellNumber, newCell); i++)
	{
		verticalSequenceCells.insert(verticalSequenceCells.begin(), newCell);
		newCell = cellNumber - i * board.rowNumber();
	}
	newCell = cellNumber + board.rowNumber();
	for (int i = 2; i <= m_lenSequence && board.inSameCol(cellNumber, newCell); i++)
	{
		verticalSequenceCells.push_back(newCell);
		newCell = cellNumber + i * board.rowNumber();
	}

	for (auto cell : verticalSequenceCells)
	{
		row = board.getRow(cell);
		col = board.getCol(cell);
		if (board[row][col] != playerSymbol)
		{
			counter = 0;
		}
		else
		{
			++counter;
		}

		if (counter >= m_lenSequence)
		{
			return true;
		}
	}
	return false;
}

bool Game::descendingDiagonalSequence(int cellNumber, std::string playerSymbol) const
{
	int counter = 0;
	int row = board.getRow(cellNumber);
	int col = board.getCol(cellNumber);
	int fromRow = row, fromCol = col;
	int toRow = row, toCol = col;
  
	for (size_t i = 0; i <= m_lenSequence; i++)
	{
		if (!board.isCellInRange(row - i, col - i))
		{
			fromRow = row - i + 1;
			fromCol = col - i + 1;
			break;
		}
	}

	for (size_t i = 0; i <= m_lenSequence; i++)
	{
		if (!board.isCellInRange(row + i, col + i))
		{
			toRow = row + i - 1;
			toCol = col + i - 1;
			break;
		}
	}

	for (int row = fromRow, col = fromCol; row <= toRow && col <= toCol && counter < m_lenSequence; row++, col++)
	{
		if (board[row][col] != playerSymbol)
		{
			counter = 0;
		}
		else
		{
			counter++;
		}
	}

	return counter >= m_lenSequence;
}

bool Game::risingDiagonalSequence(int cellNumber, std::string playerSymbol) const
{
	int counter = 0;
	int row = board.getRow(cellNumber);
	int col = board.getCol(cellNumber);
	int fromRow = row, fromCol = col;
	int toRow = row, toCol = col;

	for (size_t i = 0; i <= m_lenSequence; i++)
	{
		if (!board.isCellInRange(row + i, col - i))
		{
			fromRow = row + i - 1;
			fromCol = col - i + 1;
			break;
		}
	}

	for (size_t i = 0; i <= m_lenSequence; i++)
	{
		if (!board.isCellInRange(row - i, col + i))
		{
			toRow = row - i + 1;
			toCol = col + i - 1;
			break;
		}
	}

	for (int row = fromRow, col = fromCol; row >= toRow && col <= toCol && counter < m_lenSequence; row--, col++)
	{
		if (board[row][col] != playerSymbol)
		{
			counter = 0;
		}
		else
		{
			counter++;
		}
	}

	return counter >= m_lenSequence;
}

bool Game::win(int cellNumber, std::string playerSymbol) const
{
	return horizontalSequence(cellNumber, playerSymbol) || verticalSequence(cellNumber, playerSymbol) ||
		descendingDiagonalSequence(cellNumber, playerSymbol) || risingDiagonalSequence(cellNumber, playerSymbol);
}

void Game::setStatus(int cellNumber, std::string playerSymbol)
{
	if (win(cellNumber, playerSymbol))
	{
		m_status = gameStatus::WIN;
	}
	else if (board.isFull())
	{
		m_status = gameStatus::GAME_OVER;
	}
	else
	{
		m_status = gameStatus::GAME_ON;
	}
}

int Game::nextPlayer()
{
	return (currentPlayer + 1) % players.size();
}
