#include "game.hpp"

game::game()
{
	debprintf(" Game contructor works!\n");

	this->_screenRow = 0;
	this->_screenColumn = 0;
	this->_event.clear();
	this->_gameFinished = 0;

	// Event handlers
	this->_event.insert(make_pair(65, &game::MoveUp));
	this->_event.insert(make_pair(66, &game::MoveDown));
	this->_event.insert(make_pair(68, &game::MoveLeft));
	this->_event.insert(make_pair(67, &game::MoveRight));
	this->_event.insert(make_pair(10, &game::SettlePawn));
	this->_event.insert(make_pair('e', &game::Exit));
	this->_event.insert(make_pair('E', &game::Exit));
	this->_event.insert(make_pair('q', &game::Exit));
	this->_event.insert(make_pair('Q', &game::Exit));
	this->_event.insert(make_pair('r', &game::Rest));
	this->_event.insert(make_pair('R', &game::Rest));
	this->_event.insert(make_pair('t', &game::Truce));
	this->_event.insert(make_pair('T', &game::Truce));
}

void game::Start()
{
	debprintf(" Game start\n");
	clear(); // screen
	int tmpKey; 

	move(DEFAULT_ROW_OFFSET, DEFAULT_COLUMN_OFFSET);
	printw("Welcome in Go!!\n");
	printw("Choose goban size:\n");
	printw("-11 (1)\n");
	printw("-15 (2)\n");
	printw("-19 (3)\n");

	do {
		tmpKey = getch();
	} while (tmpKey != '1' && tmpKey != '2' && tmpKey != '3');

	clear();
    this->_goban.Initialize((tmpKey == '1') ? 11 : ((tmpKey == '2') ? 15 : 19));
    // this->_goban.Initialize(7);

	this->_goban.DrawAll();
	move(DEFAULT_ROW_OFFSET + GOBAN_ROW_OFFSET + this->_screenRow, DEFAULT_COLUMN_OFFSET + this->_screenColumn);

	while (!this->_gameFinished) {

		tmpKey = getch();
		// debprintf(" Key read: %d\n", tmpKey);

		if (this->_event.find(tmpKey) != this->_event.end()) {
			mvprintw(DEFAULT_ROW_OFFSET + GOBAN_ROW_OFFSET + MESSAGES_ROW_TO_GOBAN_OFFSET + this->_goban.GetSize(), DEFAULT_COLUMN_OFFSET, "                                        "); // cleaning old messages
			void (game::*funkcja)() = this->_event[tmpKey];
			(this->*(this->_event[tmpKey]))();
			//(this->*funkcja)(); // shortest version??
			move(DEFAULT_ROW_OFFSET + GOBAN_ROW_OFFSET + this->_screenRow, DEFAULT_COLUMN_OFFSET + this->_screenColumn);
		}
	}

	this->_goban.CountFinalPoints();
	this->DrawWinner();
} // Start

void game::DrawWinner()
{
	// this->_goban.Zlicz();
	clear();
	move(DEFAULT_ROW_OFFSET + 5, DEFAULT_COLUMN_OFFSET);
	if (this->_goban.GetScore(WHITE) == this->_goban.GetScore(BLACK)) {
		printw("Both players earned %d points. Draw!", this->_goban.GetScore(BLACK));
	} else {
		printw("Winner is player %s. Congratulations!", (this->_goban.GetScore(BLACK) > this->_goban.GetScore(WHITE)) ? "BLACK" : "WHITE");
	}

	mvprintw(DEFAULT_ROW_OFFSET + GOBAN_ROW_OFFSET + MESSAGES_ROW_TO_GOBAN_OFFSET + this->_goban.GetSize(), DEFAULT_COLUMN_OFFSET, "Do you want play again? (Y/N)"); 

	int tmpKey;
	do {
		tmpKey = getch();
	} while (tmpKey != 'Y' && tmpKey != 'y' && tmpKey != 'N' && tmpKey != 'n');

	if (tmpKey == 'N' || tmpKey == 'n') {
		this->Exit();
	} 
} // DrawWinner

//////////////////////////////////////////////////////////////////
// Event handlers:
void game::Exit()
{
	debprintf("  Q or E key pressed\n");
	
	mvprintw(DEFAULT_ROW_OFFSET + GOBAN_ROW_OFFSET + MESSAGES_ROW_TO_GOBAN_OFFSET + this->_goban.GetSize(), DEFAULT_COLUMN_OFFSET, "Do you really want to exit? (Y/N)"); 

	int tmpKey;
	do {
		tmpKey = getch();
	} while (tmpKey != 'Y' && tmpKey != 'y' && tmpKey != 'N' && tmpKey != 'n');

	if (tmpKey == 'Y' || tmpKey == 'y') {
		endwin();
		if (fd) fclose(fd); 
		unlink("debug.log");
		_exit(0);
	} else {
		mvprintw(DEFAULT_ROW_OFFSET + GOBAN_ROW_OFFSET + MESSAGES_ROW_TO_GOBAN_OFFSET + this->_goban.GetSize(), DEFAULT_COLUMN_OFFSET, "                                                                                            "); // cleaning old messages
	}
}

void game::MoveUp()
{
	debprintf("  Up pressed\n");
	if (this->_screenRow) this->_screenRow--;
	move(DEFAULT_ROW_OFFSET + GOBAN_ROW_OFFSET + this->_screenRow, DEFAULT_COLUMN_OFFSET + this->_screenColumn);
}
void game::MoveDown()
{
	debprintf("  Down pressed\n");
	if (this->_screenRow + 1 < this->_goban.GetSize()) this->_screenRow++;
	move(DEFAULT_ROW_OFFSET + GOBAN_ROW_OFFSET + this->_screenRow, DEFAULT_COLUMN_OFFSET + this->_screenColumn);
}
void game::MoveRight()
{
	debprintf("  Right pressed\n");
	if (this->_screenColumn + 1 < this->_goban.GetSize()) this->_screenColumn++;
	move(DEFAULT_ROW_OFFSET + GOBAN_ROW_OFFSET + this->_screenRow, DEFAULT_COLUMN_OFFSET + this->_screenColumn);
}
void game::MoveLeft()
{
	debprintf("  Left pressed\n");
	if (this->_screenColumn) this->_screenColumn--;
	move(DEFAULT_ROW_OFFSET + GOBAN_ROW_OFFSET + this->_screenRow, DEFAULT_COLUMN_OFFSET + this->_screenColumn);
}
void game::SettlePawn()
{
	debprintf("  Enter pressed\n");
	_goban.SettlePawn(this->_screenRow, this->_screenColumn);
	move(DEFAULT_ROW_OFFSET + GOBAN_ROW_OFFSET + this->_screenRow, DEFAULT_COLUMN_OFFSET + this->_screenColumn);
}

void game::Rest()
{
	debprintf("  Player %s need a rest.\n", (this->_goban.GetRound() == WHITE) ? "WHITE" : "BLACK");
	
	mvprintw(DEFAULT_ROW_OFFSET + GOBAN_ROW_OFFSET + MESSAGES_ROW_TO_GOBAN_OFFSET + this->_goban.GetSize(), DEFAULT_COLUMN_OFFSET, "Player %s need a rest.", (this->_goban.GetRound() == WHITE) ? "WHITE" : "BLACK"); 
	this->_goban.ChangeRound();
}

void game::Truce()
{
	debprintf("  Player %s wants a truce.\n", (this->_goban.GetRound() == WHITE) ? "WHITE" : "BLACK");

	mvprintw(DEFAULT_ROW_OFFSET + GOBAN_ROW_OFFSET + MESSAGES_ROW_TO_GOBAN_OFFSET + this->_goban.GetSize(), DEFAULT_COLUMN_OFFSET, "Player %s proposes truce. Do you accept? (Y/N)", (this->_goban.GetRound() == WHITE) ? "WHITE" : "BLACK"); 

	int tmpKey;
	do {
		tmpKey = getch();
	} while (tmpKey != 'Y' && tmpKey != 'y' && tmpKey != 'N' && tmpKey != 'n');

	if (tmpKey == 'Y' || tmpKey == 'y') {
		this->_gameFinished = true;
	} else {
		mvprintw(DEFAULT_ROW_OFFSET + GOBAN_ROW_OFFSET + MESSAGES_ROW_TO_GOBAN_OFFSET + this->_goban.GetSize(), DEFAULT_COLUMN_OFFSET, "                                                                                   "); // cleaning old messages
	}
}