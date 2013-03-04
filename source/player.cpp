#include "player.hpp"

player::player()
{
	this->_score = 0;
} // player

int player::GetScore()
{
	return this->_score;
}

int player::AddScore(int points)
{
	this->_score += points;
	return this->_score;
}