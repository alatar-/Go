#include "event.hpp"

event::event(color argRound, int row, int column)
{
	this->_round = argRound;
	this->_row = row;
	this->_column = column;
} // event::event()

int event::GetRow()
{
	return this->_row;
}

int event::GetColumn()
{
	return this->_column;
}