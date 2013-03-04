#ifndef GAME_HPP
#define GAME_HPP

#include "main.hpp"
#include "goban.hpp"

class game 
{
private:
	int _screenRow;
	int _screenColumn;
	map <int, void (game::*)()> _event;
	goban _goban;
	bool _gameFinished;

public:
	game();

	void Start();
	void Exit();
	void DrawWinner();

	void MoveUp();
	void MoveDown();
	void MoveRight();
	void MoveLeft();
	
	void SettlePawn();
	void Rest();
	void Truce();
}; // class game

#endif // GAME_HPP