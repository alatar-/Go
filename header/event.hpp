#ifndef EVENT_HPP
#define EVENT_HPP
#include "main.hpp"
#include "pawn.hpp"

class event
{
private:
	color _round;
	int _row;
	int _column;
public:
	event(color,int,int);
	int GetRow();
	int GetColumn();
}; // class event

#endif // EVENT_HPP