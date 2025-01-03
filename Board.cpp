#include "Board.h"

Board::Board(int boardSize) : m_boardSize(boardSize), board(boardSize)
{
	for (size_t i = 0; i < boardSize; i++)
	{
		board[i].resize(boardSize);
	}

	int cellNumber = 0;

	for (size_t i = 0; i < m_boardSize; i++)
	{
		for (size_t j = 0; j < m_boardSize; j++)
		{
			cellNumber = i * m_boardSize + j + 1;
			board[i][j] = std::to_string(cellNumber);
			emptyCells.insert(cellNumber);
		}
	}
}

int Board::rowNumber() const
{
	return m_boardSize;
}

int Board::colNumber() const
{
	return m_boardSize;
}

bool Board::updateCellContent(int cellNumber, std::string playerSymbol)
{
	if (isEmptyCell(cellNumber) && isCellInRange(cellNumber))
	{
		int row = getRow(cellNumber);
		int col = getCol(cellNumber);
		board[row][col] = playerSymbol;
		emptyCells.erase(cellNumber);

		return true;
	}
	return false;
}

bool Board::isFull() const
{
	return emptyCells.empty();
}

bool Board::inSameRow(int currentCell, int otherCell) const
{
	return isCellInRange(otherCell) && getRow(currentCell) ==  getRow(otherCell);
}

bool Board::inSameCol(int currentCell, int otherCell) const
{
	return isCellInRange(otherCell) && getCol(currentCell) == getCol(otherCell);
}

bool Board::inSameDiagonal(int currentCell, int otherCell) const
{
	return isCellInRange(otherCell) && 
		std::abs(getCol(currentCell) - getCol(otherCell)) == std::abs(getRow(currentCell) - getRow(otherCell));
}

bool Board::isCellInRange(int row, int col) const
{
	return row >= 0 && row < m_boardSize && col >= 0 && col < m_boardSize;;
}

const std::vector<std::string>& Board::operator[](int row) const
{
	return board[row];
}

int Board::getRow(int cellNumber) const
{
	int col = cellNumber % m_boardSize;
	int row = row = cellNumber / m_boardSize;

	// if cellNumber % m_boardSize == 0, that means that it's the last cell in the row
	if (!col)
	{
		row = cellNumber / m_boardSize - 1;
	}

	return row;
}

int Board::getCol(int cellNumber) const
{
	int col = cellNumber % m_boardSize;

	// if cellNumber % m_boardSize == 0, that means that it's the last cell in the row
	if (!col)
	{
		col = m_boardSize - 1;
		return col;
	};

	return col - 1;
}

bool Board::isEmptyCell(int cellNumber) const
{
	return emptyCells.find(cellNumber) != emptyCells.end();
}

bool Board::isCellInRange(int cellNumber) const
{
	return cellNumber > 0 && cellNumber <= m_boardSize * m_boardSize;
}

std::ostream& operator<<(std::ostream& os, const Board& board)
{
	int maxCellNumber = board.rowNumber() * board.colNumber();
	int width = std::to_wstring(maxCellNumber).length() + 1;
	for (size_t row = 0; row < board.rowNumber(); row++)
	{
		for (size_t col = 0; col < board.colNumber(); col++)
		{
			os << std::setw(width) << board[row][col];
		}
		os << std::endl;
	}
	return os;
}
