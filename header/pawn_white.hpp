#ifndef PAWN_WHITE_HPP
#define PAWN_WHITE_HPP

#include "main.hpp"
#include "pawn.hpp"

class pawn_white : public pawn
{
private:
	// color _color;
public:
	pawn_white(int, int);
	char GetImage();
}; // class pawn_white

#endif // PAWN_WHITE_HPP