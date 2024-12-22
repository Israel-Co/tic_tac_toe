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

const std::vector<std::string>& Board::operator[](int row) const
{
	return board[row];
}

//std::string Board::getCellContent(int row, int col) const ==========================================
//{
//	return board.at(row).at(col);
//}

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
			// os << board.getCellContent(row, col) << " "; =========================
			os << std::setw(width) << board[row][col];
		}
		// std::cout << std::endl; ==================================================
		os << std::endl;
	}
	return os;
}
