#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <unordered_set>

class Board
{
private:
	int m_boardSize;
	std::vector<std::vector<std::string>> board;
	std::unordered_set<int> emptyCells;

public:
	Board(int boardSize);

	int rowNumber() const;
	int colNumber() const;

	const std::vector<std::string>& operator[](int row) const;
	// std::string getCellContent(int row, int col) const;
	int getRow(int cellNumber) const;
	int getCol(int cellNumber) const;
	bool updateCellContent(int cellNumber, std::string playerSymbol);
	bool isFull() const;

	friend std::ostream& operator<<(std::ostream& os, const Board& obj);
private:

	bool isEmptyCell(int cellNumber) const;
	bool isCellInRange(int cellNumber) const;
};