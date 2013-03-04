#ifndef MAIN_HPP
#define MAIN_HPP

#include <iostream>
#include <cstdio>
#include <list>
#include <vector>
#include <cstring>
#include <algorithm>
#include <map>
#include <queue>

using namespace std;

#include <ncurses.h>

// DEBUG SECTION...
extern FILE *fd;
#define debprintf(...) \
	if (fd) { \
		fprintf(fd, __VA_ARGS__); \
		fflush(fd); \
	}
// DEBUG END

// DISPLAY SETTINGS
#define DEFAULT_COLUMN_OFFSET 0
//
#define DEFAULT_ROW_OFFSET 1
//
#define GOBAN_ROW_OFFSET 2
//
#define MESSAGES_ROW_TO_GOBAN_OFFSET 2
// counted from goban back


enum color
{
	NONE,
	BLACK,
	WHITE
};

inline color operator !(color colorArg)
{
	switch (colorArg) {
		case WHITE:
			return BLACK;
		case BLACK:
			return WHITE;
		default:
			return NONE;
	}
} // operator !




#endif // MAIN_HPP