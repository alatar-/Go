#ifndef FIELD_HPP
#define FIELD_HPP

#include "main.hpp"
#include "pawn_white.hpp"
#include "pawn_black.hpp"
#include "history.hpp"

enum directions
{
	UP = 0,
	RIGHT = 1,
	DOWN = 2,
	LEFT = 3
};

class field_exception
{
private:
	int _message;

public:
	field_exception(int);
	int GetMessage();

}; //class field_exception

class field
{
private:
	static int _size;
	static history *_history;
	int _row;
	int _column;
	field* _neighbour[4];
	pawn* _pawn;

public:
	field (int, int);
	void SetNeighbours(field*, field*, field*, field*);
	static void SetSize(int);
	static void SetHistory(history*);

	void Draw();
	
	int GetRow();
	int GetColumn();

	bool Settle(pawn*);
	void AffirmPosition(pawn*) throw(field_exception);
	bool Ko();
	bool Suicide();
	
	bool CheckIfBeatsOpponent();
	bool CheckIfIsSuicide();
	int NeighbourhoodCheck(color,int = 0);

	int CarryOnBeating();
	int Beat();
	
	void UpdateBreaths(int);
	pair <color, int> CountPoints(vector <field*>&);
};


#endif // FIELD_HPP