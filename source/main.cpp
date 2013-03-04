#include "main.hpp"
#include "go.hpp"

#include "AllTests.hpp" // UNIT TESTS
FILE *fd; // DEBUG.LOG


int main(int argc, char *argv[])
{
	if (argc == 2 && !strcmp(argv[1], "--debug")) {
		//	unlink("debug.log");
	   	fd = fopen("debug.log", "a"); 
	   	debprintf("-----------------------------------------\n");
	   	debprintf("---------------NEW SESSION---------------\n");
	   	debprintf("-----------------------------------------\n");
		RunAllTests(); // UNIT TESTS
	} else {
		fd = NULL;
	}
    initscr(); 	// ncursesLib init
    noecho();  	//  
    // timeout(0); // do not wait for getch()

	go go;
	go.Start();

	getch();
    endwin();

	return 0;
} // main