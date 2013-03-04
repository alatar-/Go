#include "pawn_white.hpp"

pawn_white::pawn_white(int cordX, int cordY) : pawn(cordX, cordY)
{
	this->_color = WHITE;
} // pawn_white

// void pawn_white::Draw()
// {
// 	debprintf("      Drawing pawn WHITE at %d %d\n", this->GetRow(), this->GetColumn());
// 	mvprintw(DEFAULT_ROW_OFFSET + GOBAN_ROW_OFFSET + this->GetRow(), DEFAULT_COLUMN_OFFSET + this->GetColumn(), "W" );
// } // Draw

char pawn_white::GetImage()
{
	return 'W';
}
