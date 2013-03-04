#include "history.hpp"

void history::AddEvent(event eventArg)
{
	this->_history.push_back(eventArg);
} // history::AddEvent()

event history::GetEvent(int index)
{
	vector <event> :: reverse_iterator it = this->_history.rbegin();
	while(index--)
	{
		it++;
	}
	return *it;
} // history::GetEvent()

int history::GetSize()
{
	return this->_history.size();
}