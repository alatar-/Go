#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "main.hpp"

class player
{
private:
	int _score;
public:
	player(); 
	
	int GetScore();
	int AddScore(int);
}; // class player

#endif // PLAYER_HPP