#ifndef HISTORY_HPP
#define HISTORY_HPP
#include "main.hpp"
#include "pawn.hpp"
#include "event.hpp"

class history 
{
private:
	vector <event> _history;
public:
	void AddEvent(event);
	event GetEvent(int);
	int GetSize();

}; // class history

#endif // HISTORY_HPP