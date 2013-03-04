#ifndef PAWN_BLACK_HPP
#define PAWN_BLACK_HPP

#include "main.hpp"
#include "pawn.hpp"

class pawn_black : public pawn
{
private:
	// color _color;
public:
	pawn_black(int, int);
	char GetImage();
}; // class pawn_black

#endif // PAWN_BLACK_HPP