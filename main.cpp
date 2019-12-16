#include <ncurses.h>
#include<string>
#include <locale.h>
using namespace std;

#define LEFT 68
#define RIGHT 67
#define UP 65
#define DOWN 66
#define SPACE 32

// Prototypes
void play();
void resetWindow(WINDOW * win);

int main(int argc, char ** argv)
{
  // Initialize NCurses
  initscr();
  cbreak();
  noecho();
  curs_set(0);
  setlocale(LC_ALL, "");

  // Run game loop
  play();

  // Clear up NCurses memory
  endwin();

  return 0;
}

void play(){
  int key;
  int height = 40;
  int width = 80;
  int win_x = 5;
  int win_y = 5;
  int char_x = width / 2;
  int char_y = height / 2;
  int points = 0;
  int coin_x = rand() % (78-1 + 1) + 1;
  int coin_y =  rand() % (38-1 + 1) + 1;
  int life = 3;
  string playerCoords;
  string keyPressDirection;
  string pointStr = "POINTS: " + to_string(points) + "     ";
  string lifeStr = "LIFE: " + to_string(life) + "     ";
  bool playing = true;
  WINDOW * info_win = newwin(height, width/2, win_y , win_x + width + 2);
  WINDOW * win = newwin(height, width, win_y, win_x);

  keypad(win, true);
  refresh();

  box(win, 0, 0);
  mvwprintw(win, 0, 5, "[THE CURSE OF CURSES]");
  resetWindow(win);
  mvwprintw(win, char_y, char_x, "X");
  mvwprintw(win, coin_y, coin_x, "$");

  box(info_win, 0, 0);
  mvwprintw(info_win, 0, 5, "[INFO]");
  mvwprintw(info_win, 1, 1, lifeStr.c_str());
  mvwprintw(info_win, 2, 1, pointStr.c_str());

  wrefresh(info_win);
  wrefresh(win);

  while (playing)
  {
    // Interpret input
    key = getch();
    switch (key)
    {
      case LEFT:
        keyPressDirection = "KEYPRESS: LEFT    ";
        char_x--;
        break;
      case RIGHT:
        keyPressDirection = "KEYPRESS: RIGHT    ";
        char_x++;
        break;
      case UP:
        keyPressDirection = "KEYPRESS: UP    ";
        char_y--;
        break;
      case DOWN:
        keyPressDirection = "KEYPRESS: DOWN    ";
        char_y++;
        break;
      default:
        break;
    }
    // Prevent out-of-bounds
    if (char_x < 1) char_x = 1;
    if (char_x > 78) char_x = 78;
    if (char_y < 1) char_y = 1;
    if (char_y > 38) char_y = 38;
    // Check if collected the coin
    if (char_x == coin_x &&
        char_y == coin_y)
    {
      points++;
      coin_x = rand() % (78-1 + 1) + 1;
      coin_y =  rand() % (38-1 + 1) + 1;
    }
    // Populate Info Window
    lifeStr = "LIFE: " + to_string(life) + "     ";
    pointStr = "POINTS: " + to_string(points) + "     ";
    playerCoords = "X: " + to_string(char_x) + " Y: " + to_string(char_y) + "       ";
    mvwprintw(info_win, 1, 1, lifeStr.c_str());
    mvwprintw(info_win, 2, 1, pointStr.c_str());
    mvwprintw(info_win, 3, 1, keyPressDirection.c_str());
    mvwprintw(info_win, 4, 1, playerCoords.c_str());

    resetWindow(win);
    mvwprintw(win, char_y, char_x, "X");
    mvwprintw(win, coin_y, coin_x, "$");

    wrefresh(win);
    wrefresh(info_win);
  }

  return;
}

void resetWindow(WINDOW * win)
{
  for (int y = 1; y < 40 - 1; y++)
    for (int x = 1; x < 80 - 1; x++)
      mvwprintw(win, y, x, " ");

  return;
}
