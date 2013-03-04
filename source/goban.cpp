#include "goban.hpp"
	
goban::goban()
{
	debprintf("  Goban constructor works!\n");

	this->_fields.clear();
	this->_size = 0;
	this->_round = WHITE;
} // goban

goban::~goban()
{
	debprintf("  Goban destructor works!\n");
} // ~goban

void goban::Initialize(int gobanSize) 
{
	debprintf("   Initializing goban %d\n", gobanSize);

	// Setting gobanSize
	this->_size = gobanSize;
	field::SetSize(gobanSize);
	pawn::SetSize(gobanSize);
	field::SetHistory(&(this->_history));
	
	for (int i = 0; i < this->GetSize(); ++i) {
		for (int j = 0; j < this->GetSize(); ++j) {
			field tmp(i,j);	
			this->_fields.push_back(tmp);
		}
	}
	this->FillFieldNeighbours();
} // Initialize

void goban::FillFieldNeighbours()
{
	for (vector <field>::iterator it = _fields.begin(); it != _fields.end(); ++it)
	{
		int row = it->GetRow();
		int column = it->GetColumn();
		field* up = this->FindField(row - 1, column);
		field* right = this->FindField(row, column + 1);
		field* down = this->FindField(row + 1, column);
		field* left = this->FindField(row, column - 1);
		if (row == 0 && column == 1) {
			debprintf("%d %d %d %d %d", this->FindField(row, column), up, right, down, left);
		}
		it->SetNeighbours(up, right, down, left);
	}
		
} // FillFieldNeighbours

void goban::DrawAll()
{
	debprintf("   Drawing all fields\n");

	for (vector <field>::iterator it = _fields.begin(); it != _fields.end(); ++it) {
		it->Draw();
	}

	this->DrawScores();
} // DrawAll

void goban::DrawScores()
{
	debprintf("   Drawing scores\n");

	move(DEFAULT_ROW_OFFSET, DEFAULT_COLUMN_OFFSET);
	
	if (this->GetRound() == WHITE) attron(A_REVERSE);
	printw("WHITE %d", this->_players[WHITE].GetScore());
	attroff(A_REVERSE);
	
	printw(" | ");
	
	if (this->GetRound() == BLACK) attron(A_REVERSE);
	printw("%d BLACK", this->_players[BLACK].GetScore());
	attroff(A_REVERSE);

} // DrawScores

int goban::GetSize()
{
	return this->_size;
} // GetSize

color goban::GetRound() 
{
	return this->_round;
} // GetRound

int goban::GetScore(color player)
{
	return this->_players[player].GetScore();
} // GetScore

field* goban::FindField(int row, int column) 
{
	for (vector <field>::iterator it = _fields.begin(); it != _fields.end(); ++it) {
		if (it->GetRow() == row && it->GetColumn() == column) {
			return &(*it);
		}
	} 

	return NULL;  
} // FindField

void goban::SettlePawn(int row, int column)
{
	debprintf("   Trying to settle pawn on %d %d color %c\n", row, column, (this->_round == WHITE) ? 'W' : 'B');

	pawn *newPawn;
	if (this->_round == WHITE) {
		newPawn = new pawn_white(row, column);
	} else {
 		newPawn = new pawn_black(row, column);
	}	

	if (this->FindField(row, column)->Settle(newPawn)) {

		event newEvent(this->_round, row, column);
		this->_history.AddEvent(newEvent);
		debprintf("   Pawn added to history\n");
		
		this->_players[this->_round].AddScore(this->FindField(row, column)->CarryOnBeating());
		debprintf("   Points added to score\n");

		this->ChangeRound();
	} else {
		delete newPawn;
	}
} // SettlePawn
	
void goban::CountFinalPoints()
{
	vector <field*> visited; //odwiedzone pola
	visited.clear();
	pair <color, int> tmp;

	for (vector <field>::iterator it = _fields.begin(); it != _fields.end(); ++it) {
		bool beenVisited = false;
		for (vector <field*>:: iterator it2 = visited.begin(); it2 != visited.end(); ++it2) {
			if (&(*it) == *it2) {
				beenVisited = true; 
				break;
			}
		}

		if(!beenVisited) {
			
			tmp = it->CountPoints(visited);
			debprintf("Conut points %d %d returns %d %d\n", it->GetRow(), it->GetColumn(), tmp.first, tmp.second);
			for (int i = 0; i < 3; i++) {
				if (tmp.first == i) this->_players[i].AddScore(tmp.second);
			}
		}
	} 
} // CountFinalPoints

void goban::ChangeRound()
{
	this->_round = !this->_round;
	this->DrawScores();
	debprintf("   Round changed\n");
} // ChangeRound
