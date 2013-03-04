#include "field.hpp"

////////////////////////////////////////////////////////////////
// Init static elements:

int field::_size;
history* field::_history;

////////////////////////////////////////////////////////////////
// Exception methods:

field_exception::field_exception(int type)
{
	this->_message = type;
} // field_exception::field_exception
 
int field_exception::GetMessage()
{
	return this->_message;
} // field_exception::GetMessage

////////////////////////////////////////////////////////////////
//

field::field(int cordX, int cordY)
{
	this->_row =  cordX;
	this->_column = cordY;
	this-> _pawn = NULL;
	for( int i = 0; i < 4; ++i)
		_neighbour[i] = NULL;
} // field

void field::SetNeighbours(field* up, field* right, field* down, field* left)
{
	this->_neighbour[UP] = up;
	this->_neighbour[RIGHT] = right;
	this->_neighbour[DOWN] = down;
	this->_neighbour[LEFT] = left;
} // SetNeighbours

void field::SetSize(int size)
{
	field::_size = size;
} // SetSize

void field::SetHistory(history *hist)
{
	field::_history = hist;
	// history &field::_history;// = himst;
} // SetHistory

////////////////////////////////////////////////////////////////
// Getters

int field::GetRow()
{
	return this->_row;
} // GetRow

int field::GetColumn()
{
	return this->_column;
} // GetColumn

////////////////////////////////////////////////////////////////
// 

void field::Draw()
{
	debprintf("      Drawing %c at %d %d\n", (this->_pawn == NULL) ? '-' : this->_pawn->GetImage(), this->GetRow(), this->GetColumn());

	mvprintw(DEFAULT_ROW_OFFSET + GOBAN_ROW_OFFSET + this->_row, DEFAULT_COLUMN_OFFSET + this->_column, "%c", (this->_pawn == NULL) ? '-' : this->_pawn->GetImage());
} // field::Draw()

bool field::Settle(pawn *newPawn)
{
 	try
	{
		debprintf("      Trying execute AffirmPosition\n");
		this->AffirmPosition(newPawn);
	}
	catch(field_exception error)
	{
		debprintf("      Affirm position returns exception %d\n", error.GetMessage());
		
		if (error.GetMessage() == 1) {
			mvprintw(DEFAULT_ROW_OFFSET + GOBAN_ROW_OFFSET + MESSAGES_ROW_TO_GOBAN_OFFSET + this->_size, DEFAULT_COLUMN_OFFSET, "Field is already occupied!\n");
		} else if (error.GetMessage() == 2) {
			mvprintw(DEFAULT_ROW_OFFSET + GOBAN_ROW_OFFSET + MESSAGES_ROW_TO_GOBAN_OFFSET + this->_size, DEFAULT_COLUMN_OFFSET, "Ko! Choose another field!\n");
		} else if (error.GetMessage() == 3) {
			mvprintw(DEFAULT_ROW_OFFSET + GOBAN_ROW_OFFSET + MESSAGES_ROW_TO_GOBAN_OFFSET + this->_size, DEFAULT_COLUMN_OFFSET, "Suicide! Choose another field!\n");
		}

		return false;
	}

	debprintf("      Affirm position returns OK!\n");

	this->_pawn = newPawn;
	this->Draw();
	return true;
} // Settle

void field::AffirmPosition(pawn* newPawn) throw(field_exception)
{
	if (this->_pawn != NULL) {
 		debprintf("       Field occupied!\n");
		field_exception error = field_exception(1);
	 	throw error;
 	}	

 	this->_pawn = newPawn;
 	this->UpdateBreaths(-1);

 	debprintf("      Checking Ko...\n");
	if (this->Ko())	{
		this->UpdateBreaths(1);
		this->_pawn = NULL;
		field_exception err = field_exception(2);
	 	throw err;
	}
 	debprintf("      Checking Suicide...\n");
	if(this->Suicide())
	{
 		debprintf("      Suicide returns true...\n");
 		this->UpdateBreaths(1);
		this->_pawn = NULL;
		field_exception err = field_exception(3);
	 	throw err;
	}

} // AffirmPosition

bool field::Ko()
{
	if(this->_history->GetSize() > 4)
	{	
		event tmp = this->_history->GetEvent(1);
		if(tmp.GetRow() == this->GetRow() && tmp.GetColumn() == this->GetColumn())
		{
			return true;
		}
	}
	return false;
} // Ko

bool field::Suicide()
{
	debprintf("       Suicide checking %d %d color %d\n", this->GetRow(), this->GetColumn(), this->_pawn->GetColor());

	if (CheckIfBeatsOpponent()) {// check if pawn beats opponent stones, pawn can be added
		//this->CarryOnBeating();
		return false; // to nie jest samobojstwo
	}
	if (!CheckIfIsSuicide()) {
		return false;
	}
	return true;
} // Suicide


bool field::CheckIfBeatsOpponent()
{
	debprintf("       CheckIfBeatsOpponent\n");

	int sum = 5; //zakladamy ze nie bije
	for (int i = 0; i < 4; i++) {
		if (this->_neighbour[i] != NULL && 
			this->_neighbour[i]->_pawn != NULL && 
			this->_neighbour[i]->_pawn->GetColor() == !this->_pawn->GetColor()) {

			sum =  min(sum, this->_neighbour[i]->NeighbourhoodCheck(!this->_pawn->GetColor(), 1));
		}
	}

	if (sum == 0) { // jesli jsednak bije
		debprintf("       CheckIfBeatsOpponent returns TRUE!\n");
		return true;
	} else {
		debprintf("       CheckIfBeatsOpponent returns FALSE!\n");
		return false;
	}
} // CheckIfBeatsOpponent

bool field::CheckIfIsSuicide()
{
	debprintf("       CheckIfIsSuicide\n");

	if (this->NeighbourhoodCheck(this->_pawn->GetColor(), 1) == 0) { // bedzie zbity!
		debprintf("       CheckIfIsSuicide returns TRUE!\n");
		return true;
	} else {
		debprintf("       CheckIfIsSuicide returns FALSE!\n");
		return false;
	}
} // CheckIfSuicide

int field::NeighbourhoodCheck(color colorArg, int clear) //returns breaths of stone (group of stones)
{
	if (clear) {
		debprintf("        NeighbourhoodCheck for %d %d color %d\n", this->GetRow(), this->GetColumn(), this->_pawn->GetColor());
	}

	static vector <field*> visited;
	if (clear) visited.clear();
	visited.push_back(this); 

	if (this->_pawn->GetBreaths() == 0)
	{
		int lmax = 0;
		debprintf("        %d %d has 0 breaths, check neighbours\n", this->GetRow(), this->GetColumn());
		for(int i = 0; i < 4; ++i)
		{
			debprintf("         Checking neighbour nr %d\n", i);
			if (this->_neighbour[i] != NULL && 
				this->_neighbour[i]->_pawn != NULL &&
				this->_neighbour[i]->_pawn->GetColor() == colorArg) { //jeśli istnieje i ma ten sam kolor
				
				bool beenVisited = false;
				for (vector <field*>:: iterator it = visited.begin(); it != visited.end(); ++it) {
					if (*it == this->_neighbour[i]) {
						beenVisited = true; 
						break;
					}
				} // oraz nie był odwiedzony

				if (!beenVisited) {
					int tmp = this->_neighbour[i]->NeighbourhoodCheck(colorArg);
					debprintf("        neigbour %d %d returned %d\n", this->_neighbour[i]->GetRow(), this->_neighbour[i]->GetColumn(), tmp);

					// lmax = max(lmax, this->_neighbour[i]->NeighbourhoodCheck(searchedColor));
					lmax = max(lmax, tmp);

				}
			}
		}
		debprintf("        neighbour max is and returns %d\n", lmax);
		return lmax;
	} else {
		debprintf("        %d %d has %d breaths so returns it\n", this->GetRow(), this->GetColumn(), this->_pawn->GetBreaths());
		return this->_pawn->GetBreaths();
	}
} // NeighbourhoodCheck()


int field::CarryOnBeating()
{
	debprintf("       CarryOnBeating\n");
	int beatenStones = 0;
	for (int i = 0; i < 4; i++) {
		if (this->_neighbour[i] != NULL && 
			this->_neighbour[i]->_pawn != NULL && 
			this->_neighbour[i]->_pawn->GetColor() == !this->_pawn->GetColor() &&
			this->_neighbour[i]->NeighbourhoodCheck(!this->_pawn->GetColor(), 1) == 0) {

			debprintf("Condition satisfied - will be beaten\n");
			beatenStones += this->_neighbour[i]->Beat();
		}
	}
	return beatenStones;
} // CarryOnBeating

int field::Beat()
{
	int beatenStones = 1;

	color tmp_color = this->_pawn->GetColor();
	debprintf("       BeatOpponent\n");
	this->UpdateBreaths(1);
	delete this->_pawn;
	this->_pawn = NULL;
	this->Draw();

	debprintf("       Redraw and proceed to destroy neighbours\n");
	for (int i = 0; i < 4; i++) {
		if (this->_neighbour[i] != NULL && 
			this->_neighbour[i]->_pawn != NULL && 
			this->_neighbour[i]->_pawn->GetColor() == tmp_color) {
				beatenStones += this->_neighbour[i]->Beat();
		}
	}

	return beatenStones;
} // Beat

void field::UpdateBreaths(int flag)
{	
	debprintf("       Reducing/Adding breaths of %d %d neighbours\n", this->GetRow(), this->GetColumn());

	for (int i = 0; i < 4; ++i) {

		if (this->_neighbour[i] != NULL && 
			this->_neighbour[i]->_pawn != NULL)	{

			_neighbour[i]->_pawn->UpdateBreaths(flag);
			this->_pawn->UpdateBreaths(flag);
		}
	}
} // UpdateBreaths

pair <color, int> field::CountPoints(vector <field*> &visited) //wektor juz odwiedzonych
{
	bool foundSearchedColor = false; //nie znalazlem jeszcze koloru
	field* tmp;				//wskaznik na pole

	pair <color, int> out; 	//jakaś tymczasowa para do zwrotu
	out.first = NONE;		//nie wiem czego szukam
	out.second = 0;			//mam takich elementow 0

	if (this->_pawn != NULL) return out; // jesli to nie puste pole to nas nie interesuje

	queue <field*> search;		//kolejka pol po ktorych bedziemy chodzic
	search.push(this);			//wrzucamy biezace pole do kolejki
	while(!search.empty())		//dopoki kolejka nie jest pusta
	{

		tmp = search.front();	//bierzemy front z kolejki
		search.pop();
		if (tmp->GetRow() == 0 && tmp->GetColumn() == 1) {
			debprintf("%d %d %d %d %d", tmp, tmp->_neighbour[0],tmp->_neighbour[1],tmp->_neighbour[2],tmp->_neighbour[3]);
		}
		debprintf("Obrabiamy %d %d\n", tmp->GetRow(), tmp->GetColumn());

		debprintf("1\n");
		// jeśli nie był odwiedzony
		bool beenVisited = false;
		for (vector <field*>:: iterator it = visited.begin(); it != visited.end(); ++it) {
			if (*it == tmp) {
				beenVisited = true; 
				break;
			}
		} //jesli dane pole zostalo juz odwiedzone to koniec przebiegu
		if (beenVisited) continue;
		debprintf("2\n");

		visited.push_back(tmp); //else zaznaczamy ze je odwiedzilismy i dodajemy out.second
		out.second++;

		debprintf("3\n");

		for(int i = 0 ; i < 4; ++i)
		{
			if (tmp->_neighbour[i] == NULL) continue;
			if (tmp->GetRow() == 0 && tmp->GetColumn() == 1) {
				debprintf("%d %d %d %d %d", tmp, tmp->_neighbour[0],tmp->_neighbour[1],tmp->_neighbour[2],tmp->_neighbour[3]);
			}
			debprintf("Obrabiamy neighboura %d %d color %d pawn %d\n", tmp->_neighbour[i]->GetRow(), tmp->_neighbour[i]->GetColumn(), tmp->_neighbour[i]->_pawn, (tmp->_neighbour[i]->_pawn != NULL) ? tmp->_neighbour[i]->_pawn->GetColor() : 10 );
			debprintf("4\n");

			if (!foundSearchedColor &&
				tmp->_neighbour[i]->_pawn != NULL) {

				foundSearchedColor = true;
				debprintf("5 %d\n", out.first);
				debprintf("5.2 %d\n", tmp->_neighbour[i]->_pawn->GetColor());
				out.first = tmp->_neighbour[i]->_pawn->GetColor();
				debprintf("5.5\n");
			}
			debprintf("6\n");
			if (tmp->_neighbour[i]->_pawn != NULL) {
				debprintf("7\n");
				if (tmp->_neighbour[i]->_pawn->GetColor() == !out.first) {
					debprintf("8\n");
					out.first = NONE;
				}				
			} else {
				debprintf("10\n");
				search.push(tmp->_neighbour[i]);		
			} 
		}
	}	
	return out;
}