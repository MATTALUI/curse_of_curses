#include <ncurses.h>
#include<string>
#include <locale.h>
using namespace std;

#define LEFT 68
#define RIGHT 67
#define UP 65
#define DOWN 66

// Prototypes
void play();
void showPlayer(WINDOW * win, int char_y, int char_x);

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
  WINDOW * win;
  WINDOW * info_win;
  int height, width, win_x, win_y, char_x, char_y;
  string playerCoords;
  string keyPressDirection;

  height = 40;
  width = 80;
  win_x = 5;
  win_y = 5;
  char_x = width / 2;
  char_y = height / 2;
  win = newwin(height, width, win_y, win_x);
  info_win = newwin(height, width/2, win_y , win_x + width + 2);
  keypad(win, true);
  refresh();
  box(win, 0, 0);
  box(info_win, 0, 0);
  mvwprintw(win, 0, 5, "[THE CURSE OF CURSES]");
  mvwprintw(info_win, 0, 5, "[INFO]");
  showPlayer(win, char_y, char_x);
  wrefresh(info_win);
  wrefresh(win);

  while (true)
  {
    int key;

    key = getch();
    if (key == LEFT)
    {
      keyPressDirection = "KEYPRESS: LEFT    ";
      char_x--;
    }
    if (key == RIGHT)
    {
      keyPressDirection = "KEYPRESS: RIGHT    ";
      char_x++;
    }
    if (key == UP)
    {
      keyPressDirection = "KEYPRESS: UP    ";
      char_y--;
    }
    if (key == DOWN)
    {
      keyPressDirection = "KEYPRESS: DOWN    ";
      char_y++;
    }

    // Prevent out-of-bounds
    if(char_x < 1) char_x = 1;
    if(char_x > 78) char_x = 78;
    if(char_y < 1) char_y = 1;
    if(char_y > 38) char_y = 38;
    // Populate Info Window
    playerCoords = "X: " + to_string(char_x) + " Y: " + to_string(char_y) + "       ";
    mvwprintw(info_win, 1, 1, keyPressDirection.c_str());
    mvwprintw(info_win, 2, 1, playerCoords.c_str());
    
    showPlayer(win, char_y, char_x);
    wrefresh(win);
    wrefresh(info_win);
  }

  return;
}

void showPlayer(WINDOW * win, int char_y, int char_x)
{

  for (int y = 1; y < 40 - 1; y++)
  {
    for (int x = 1; x < 80 - 1; x++)
    {
      string output;

      output = (y == char_y && x == char_x ? "X" : " ");
      mvwprintw(win, y, x, output.c_str());
    }
  }


  return;
}
