#ifndef GOBAN_HPP
#define GOBAN_HPP

#include "main.hpp"
#include "field.hpp"
#include "history.hpp"
#include "player.hpp"

class goban
{
private:
	int _size;
	color _round;	
	vector <field> _fields;
	history _history;
	player _players[3];
public:
	goban();
	~goban();
	void Initialize(int);
	void FillFieldNeighbours();

	void DrawAll();
	void DrawScores();

	int GetSize();
	color GetRound();
	int GetScore(color);
	field* FindField(int,int);

	void SettlePawn(int, int);

	void CountFinalPoints();
	void ChangeRound();
}; // class goban

#endif // GOBAN_HPP