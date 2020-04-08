#include "coloring.h"


static int fg = WHITE;
static int bg = BLACK;
static int started = 0;
static int pair    = 8;

//static WINDOW battle;

void initapppairs()
{
	init_pair(BLACK,   BLACK,   bg);
	init_pair(RED,     RED,     bg);
	init_pair(GREEN,   GREEN,   bg);
	init_pair(YELLOW,  YELLOW,  bg);
	init_pair(BLUE,    BLUE,    bg);
	init_pair(MAGENTA, MAGENTA, bg);
	init_pair(CYAN,    CYAN,    bg);
	init_pair(WHITE,   WHITE,   bg);
}

void checkstart()
{
	if(!started)
	{
		initscr();
		cbreak();
		erase();

		//battle = newwin(30, 150, 0, 0);

		start_color();

		initapppairs();

		attron(COLOR_PAIR(fg));

		started = 1;
	}
}

void textcolor(int color)
{
	if(color > 7) init_pair(pair++, color, bg);

	checkstart();

	attroff(COLOR_PAIR(fg));

	fg = color;

	attron(COLOR_PAIR(fg));
}

void textbackground(int color)
{
	checkstart();

	attroff(COLOR_PAIR(fg));

	bg = color;

	initapppairs();

	attron(COLOR_PAIR(fg));
}

void color_reset()
{
	checkstart();
	attroff(COLOR_PAIR(fg));
	
	endwin();

	started = 0;
}
