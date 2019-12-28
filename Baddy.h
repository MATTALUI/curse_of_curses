namespace std
{
  class Baddy
  {
    public:
    int x;
    int y;
    // char character;
    bool alive;

    Baddy()
    {
      x = rand() % (78-1 + 1) + 1;
      y =  rand() % (38-1 + 1) + 1;
      // character = 'X';
      alive = true;
    }

    void die()
    {
      x = 0;
      y = 0;
      alive = false;
    }

    void move()
    {
      int direction = rand() % (4 - 1 + 1) + 1;
      // TODO: We can implement better random movement somehow. Currently
      // switch (direction)
      // {
      //   case 1:
      //     x++;
      //   case 2:
      //     x--;
      //   case 3:
      //     y++;
      //   case 4:
      //     y--;
      // }

      // maintain Baddy inbounds
      if (x < 1) x = 1;
      if (x > 78) x = 78;
      if (y < 1) y = 1;
      if (y > 38) y = 38;

      return;
    }

    bool collision(int objY, int objX)
    {
      return objY == y && objX == x;
    }
  };
}
