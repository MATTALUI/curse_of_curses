#include <ncurses.h>
#include<string>
#include <locale.h>
#include <cassert>

#include "Baddy.h"
#include "Hero.h"

using namespace std;

#define PLAYER_PAIR 1
#define COIN_PAIR 2
#define BADDY_PAIR 3

// Prototypes
void play();
void resetWindow(WINDOW * win);
Baddy * addBaddy(Baddy * baddies, int &baddyCount);

int main(int argc, char ** argv)
{
  // Initialize NCurses
  initscr();
  if (!has_colors()) {
    endwin();
    printf("Your terminal does not support color :(\n");
    exit(1);
  }

  start_color();
  init_pair(PLAYER_PAIR, COLOR_GREEN, COLOR_BLACK);
  init_pair(COIN_PAIR, COLOR_YELLOW, COLOR_BLACK);
  init_pair(BADDY_PAIR, COLOR_RED, COLOR_BLACK);
  cbreak();
  noecho();
  curs_set(0);

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
  int points = 0;
  int coin_x = rand() % (78-1 + 1) + 1;
  int coin_y =  rand() % (38-1 + 1) + 1;
  int baddyCount = 0;
  Hero hero(height / 2, width / 2);
  string playerCoords;
  string keyPressDirection;
  string pointStr = "POINTS: " + to_string(points) + "     ";
  string lifeStr = "LIFE: " + to_string(hero.life()) + "     ";
  string baddyStr;
  bool playing = true;
  WINDOW * info_win = newwin(height, width/2, win_y , win_x + width + 2);
  WINDOW * win = newwin(height, width, win_y, win_x);
  Baddy * baddies = new (nothrow) Baddy[baddyCount];
  Baddy * lastBaddy;
  assert(baddies);

  keypad(win, true);
  refresh();

  box(win, 0, 0);
  mvwprintw(win, 0, 5, "[THE CURSE OF CURSES]");
  resetWindow(win);
  mvwprintw(win, hero.y(), hero.x(), "O");
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
    // Control hero
    hero.handleInput(key);
    // Check if collected the coin
    if (hero.x() == coin_x &&
        hero.y() == coin_y)
    {
      points++;
      coin_x = rand() % (78-1 + 1) + 1;
      coin_y =  rand() % (38-1 + 1) + 1;
      if (points && !(points % 1))
        baddies = addBaddy(baddies, baddyCount);
    }
    // Handle Baddies
    lastBaddy = baddies + baddyCount;
    for (Baddy * baddy = baddies; baddy != lastBaddy; ++baddy)
    {
      if (!baddy->alive) continue;
      if (baddy->collision(hero.y(), hero.x()))
      {
        hero.hurt();
        baddy->die();
        continue;
      }
      if (baddyCount > 5) baddy->move();
      if (baddy->collision(hero.y(), hero.x()))
      {
        hero.hurt();
        baddy->die();
      }
    }
    // Populate Info Window
    lifeStr = "LIFE: " + to_string(hero.life()) + "     ";
    pointStr = "POINTS: " + to_string(points) + "     ";
    baddyStr = "DIFFICULTY: " + to_string(baddyCount) + "     ";
    keyPressDirection = "KEY: " + to_string(key) + "        ";
    playerCoords = "X: " + to_string(hero.x()) + " Y: " + to_string(hero.y()) + "       ";
    mvwprintw(info_win, 1, 1, lifeStr.c_str());
    mvwprintw(info_win, 2, 1, pointStr.c_str());
    mvwprintw(info_win, 3, 1, baddyStr.c_str());
    mvwprintw(info_win, 4, 1, keyPressDirection.c_str());
    mvwprintw(info_win, 5, 1, playerCoords.c_str());
    // Game stuff
    resetWindow(win);
    wattron(win, COLOR_PAIR(PLAYER_PAIR));
    mvwprintw(win, hero.y(), hero.x(), "O");
    wattroff(win, COLOR_PAIR(PLAYER_PAIR));
    wattron(win, COLOR_PAIR(COIN_PAIR));
    mvwprintw(win, coin_y, coin_x, "$");
    wattroff(win, COLOR_PAIR(COIN_PAIR));
    wattron(win, COLOR_PAIR(BADDY_PAIR));
    for (int i = 0; i < baddyCount; i++)
      if (baddies[i].alive)
        mvwprintw(win, baddies[i].y, baddies[i].x, "X");
    wattroff(win, COLOR_PAIR(BADDY_PAIR));


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

Baddy * addBaddy(Baddy * baddies, int &baddyCount)
{
  int lengthNeeded = 1;

  // No need to copy the "dead" bad guys
  for (int i = 0; i < baddyCount; i++)
    if (baddies[i].alive) lengthNeeded++;
  // Copy living baddies into new memory reserve
  Baddy * newBaddiesList = new (nothrow) Baddy[lengthNeeded];
  assert(newBaddiesList);
  for (int i = 0; i < baddyCount; i++)
    if (baddies[i].alive)
      newBaddiesList[i] = baddies[i];
  // Add the new baddy and increase total baddy count
  Baddy newBaddy;
  newBaddiesList[lengthNeeded - 1] = newBaddy;
  baddyCount = lengthNeeded;
  // Delete old list and make it official
  delete [] baddies;

  return newBaddiesList;
}
