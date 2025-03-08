#include <ncurses.h>
#include <stdbool.h>
#include <math.h>
#include "log.h"

struct Vec2D {
	int x;
	int y;
};

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

struct Vec2D
centerscr(int width, int height)
{
	return (struct Vec2D) {
		.x = (getmaxx(stdscr) / 2) - (width / 2),
		.y = (getmaxy(stdscr) / 2) - (height / 2),
	};
}

int main(void)
{
	int ch;
	int done;
	int x, y, m, n, r;
	struct Vec2D c;

	initscr();
	raw();
	keypad(stdscr, TRUE);
	noecho();

	r = 10;
	c = centerscr(2*r, 2*r);
	m = c.x;
	n = c.y;

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

	log_info("r = %d", r);
	log_info("m = %d", m);
	log_info("n = %d", n);

}
