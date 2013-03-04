#include "pawn_black.hpp"

pawn_black::pawn_black(int cordX, int cordY) : pawn(cordX, cordY)
{
	this->_color = BLACK;
} // pawn_black

// void pawn_black::Draw()
// {
// 	debprintf("      Drawing pawn BLACK at %d %d\n", this->GetRow(), this->GetColumn());
// 	mvprintw(DEFAULT_ROW_OFFSET + GOBAN_ROW_OFFSET + this->GetRow(), DEFAULT_COLUMN_OFFSET + this->GetColumn(), "B");
// } // Draw

char pawn_black::GetImage()
{
	return 'B';
}
