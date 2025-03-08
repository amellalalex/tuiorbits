#include <ncurses.h>
#include <stdbool.h>
#include <math.h>

bool 
cercle(int x, int y, int m, int n, int r)
{
	y *= 2;
	/* (x-m)^2 + (y-n)^2 = r^2 */
	/* so x = sqrt(r^2 - (y-n)^2) + m */
	if(x <= (m+r) && x >= (m-r) && y <= (n+r) && y >= (n-r)) {
		return (
			x == (int)sqrt(r*r - (y-n)*(y-n)) + m
		||	x == (int)-sqrt(r*r - (y-n)*(y-n)) + m
		);
	} else {
		return false;
	}
}

main(void)
{
	int ch;
	int done;
	int x, y, m, n, r;

	m = 10;
	n = 10;
	r = 10;

	initscr();
	raw();
	keypad(stdscr, TRUE);
	noecho();

	for(x=0, y=0; y < getmaxy(stdscr); x++) {
		if(x > getmaxx(stdscr)) {
			x = 0;
			y++;
		}
		if(cercle(x, y, m, n, r)) {
			move(y, x);
			printw("*");
		}
	}

	ch = getch();
	refresh();

	endwin();
}
