#include "pawn.hpp"

int pawn::_size;

pawn::pawn(int row, int column)
{
	this->BreathsInitialize(row, column);

	debprintf("     Pawn constructor works %d %d breaths %d\n", row, column, this->_breaths);
} // pawn

void pawn::BreathsInitialize(int row, int column)
{
	if ((row) > 0 && 
		(row) < (this->_size)-1 &&
		(column) > 0 &&
		(column) < (this->_size)-1)
	{
		this->_breaths = 4;
	}
	else if (	((row) == 0 && 
			 	(column) == 0) ||
				((row) == 0 && 
				(column) == (this->_size)-1) ||
				((row) == (this->_size)-1 && 
				(column) == 0) ||
				((row) == (this->_size)-1 && 
				(column) == (this->_size)-1)	)
	{
		this->_breaths = 2;
	}
	else
	{
		this->_breaths = 3;
	}
} // BreathsInitialize

void pawn::SetSize(int size)
{
	pawn::_size = size;
} // SetSize

char pawn::GetImage() 
{ 
	return '-';
} // GetImage

void pawn::UpdateBreaths(int breaths)
{
	this->_breaths += breaths;
	debprintf("        Adding/Reducing %d breaths of pawn color %c so he has %d\n", breaths, (this->GetColor() == WHITE) ? 'W' : 'S' , this->_breaths);
} // UpdateBreaths

void pawn::AddBreaths(int breaths)
{
	this->_breaths += breaths;
} // AddBreaths

void pawn::ReduceBreaths(int breaths)
{
	this -> _breaths -= breaths;
} // ReduceBreaths

int pawn::GetBreaths()
{
	return this->_breaths;
} // GetBreaths

color pawn::GetColor()
{
	return this->_color;
} // GetColor

