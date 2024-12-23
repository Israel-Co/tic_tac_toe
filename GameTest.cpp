#include "GameTest.h"

void GameTest::oWinTest()
{
	std::cout << "============ O Win Test ============" << std::endl;
	Game game(4, 4);
	game.play(Game::gameMode::AUTO, { 1, 4, 2, 7, 3, 10, 6, 13 });
}

void GameTest::enterToFullCellTest()
{
	std::cout << std::endl << "============ Enter To Full Cell Test ============" << std::endl;
	Game game(4, 4);
	game.play(Game::gameMode::AUTO, { 1, 4, 2, 7, 3, 10, 10, 6, 13 });
}

void GameTest::tieTest()
{
	std::cout << std::endl << "============ Tie Test ============" << std::endl;
	Game game(4, 4);
	game.play(Game::gameMode::AUTO, { 1, 3, 2, 4, 7, 5, 8, 6, 9, 11, 10, 12, 15, 13, 16, 14 });
}

void GameTest::throwTest()
{
	std::cout << std::endl << "============ ThrowTest ============" << std::endl;
	try
	{
		Game game(4, 8);
	}
	catch (...)
	{
		return;
	}

	exit(-1);
}

void GameTest::outOfRnageTest() 
{
	std::cout << std::endl << "============ Out Of Rnage Test ============" << std::endl;
	Game game(4, 4);
	game.play(Game::gameMode::AUTO, { 1, 4, 2, 7, 3, 20, 10, 6, 13 });
}
