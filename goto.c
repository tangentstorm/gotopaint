//
//  gotopaint : an ncurses drawing tool with a pathological c coding standard.
//  homepage  : https://github.com/tangentstorm/gotopaint
//  license   : MIT/x11 style. see LICENSE.MIT for datails.
//
#include <ncurses.h>
int main() {
  MEVENT event; int ch; unsigned char buttons = 0;
INIT:
  initscr(); noecho(); cbreak(); keypad(stdscr, TRUE); start_color();
  mousemask( ALL_MOUSE_EVENTS /*BUTTON1_PRESSED | BUTTON1_RELEASED*/ | REPORT_MOUSE_POSITION, NULL );
  init_pair( 8, COLOR_BLACK,   COLOR_BLACK );
  init_pair( 1, COLOR_RED,     COLOR_BLACK );
  init_pair( 2, COLOR_GREEN,   COLOR_BLACK );
  init_pair( 3, COLOR_YELLOW,  COLOR_BLACK );
  init_pair( 4, COLOR_BLUE,    COLOR_BLACK );
  init_pair( 5, COLOR_MAGENTA, COLOR_BLACK );
  init_pair( 6, COLOR_CYAN,    COLOR_BLACK );
  init_pair( 7, COLOR_WHITE,   COLOR_BLACK );
  attron( COLOR_PAIR( 7 )); // light gray by default
TOP:
  ch = getch();
  if (ch == 27)        goto END; // escape key
  if (ch == KEY_MOUSE) goto MOUSE;
  0?: ch == 'k' ? attron( COLOR_PAIR( 8 ))
    : ch == 'r' ? attron( COLOR_PAIR( 1 ))
    : ch == 'g' ? attron( COLOR_PAIR( 2 ))
    : ch == 'y' ? attron( COLOR_PAIR( 3 ))
    : ch == 'b' ? attron( COLOR_PAIR( 4 ))
    : ch == 'm' ? attron( COLOR_PAIR( 5 ))
    : ch == 'c' ? attron( COLOR_PAIR( 6 ))
    : ch == 'w' ? attron( COLOR_PAIR( 7 ))
    : ch == 'K' ? attron( COLOR_PAIR( 8 )), attron( A_BOLD )
    : ch == 'R' ? attron( COLOR_PAIR( 1 )), attron( A_BOLD )
    : ch == 'G' ? attron( COLOR_PAIR( 2 )), attron( A_BOLD )
    : ch == 'Y' ? attron( COLOR_PAIR( 3 )), attron( A_BOLD )
    : ch == 'B' ? attron( COLOR_PAIR( 4 )), attron( A_BOLD )
    : ch == 'M' ? attron( COLOR_PAIR( 5 )), attron( A_BOLD )
    : ch == 'C' ? attron( COLOR_PAIR( 6 )), attron( A_BOLD )
    : ch == 'W' ? attron( COLOR_PAIR( 7 )), attron( A_BOLD )
    : 0; goto TOP;
MOUSE:
  if (getmouse(&event) != OK)         goto TOP;
  attron( A_REVERSE );
  mvprintw(0, 0, "(%2i,%2i) %x", event.x, event.y, event.bstate);
  attroff( A_REVERSE );
  if (event.bstate & BUTTON1_PRESSED)  buttons |= 1;
  if (event.bstate & BUTTON1_RELEASED) buttons ^= 1;
  if (event.bstate & BUTTON2_PRESSED)  buttons |= 2;
  if (event.bstate & BUTTON2_RELEASED) buttons ^= 2;
  if (event.bstate & REPORT_MOUSE_POSITION) goto MOVED;
  mvprintw(0, 50, "         [%i]    ", buttons);
  goto REFRESH;
MOVED:
  mvprintw(0, 50, "MOVED.   [%i]    ", buttons);
  if (buttons & 1) goto DRAW;
  if (buttons & 2) goto ERASE;
  goto REFRESH;
DRAW:
  mvprintw(0, 50, "DRAW    [%i]     ", buttons);
  mvprintw(event.y, event.x, "%s", "#");
  goto REFRESH;
ERASE:
  mvprintw(0, 50, "ERASE   [%i]     ", buttons);
  mvprintw(event.y, event.x, "%s", " ");
  goto REFRESH;
REFRESH:
  refresh();
  goto TOP;
END:
  endwin();
  return 0; }
