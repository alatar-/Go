#ifndef PAWN_HPP
#define PAWN_HPP

#include "main.hpp"

class pawn 
{
private:
	static int _size;
	int _breaths;
	// virtual color _color;
public:
	color _color;
	pawn(int, int);
	void BreathsInitialize(int, int);
	static void SetSize(int);

	virtual char GetImage(); 

	void UpdateBreaths(int);
	void ReduceBreaths(int = 1);
	void AddBreaths(int = 1);

	int GetBreaths();
	color GetColor();
}; // class pawn

#endif // PAWN_HPP