#define LEFT 68
#define RIGHT 67
#define UP 65
#define DOWN 66
#define SPACE 32

namespace std
{
  class Hero{
    private:
      int coordX;
      int coordY;
      int healthPoints;
      bool alive;
    public:
      Hero(int y_val, int x_val){
        coordX = x_val;
        coordY = y_val;
        healthPoints = 3;
        alive = true;
      }

      void handleInput(int key)
      {
        switch (key)
        {
          case LEFT:
            coordX--;
            break;
          case RIGHT:
            coordX++;
            break;
          case UP:
            coordY--;
            break;
          case DOWN:
            coordY++;
            break;
          default:
            break;
        }

        // Prevent out-of-bounds
        if (coordX < 1) coordX = 1;
        if (coordX > 78) coordX = 78;
        if (coordY < 1) coordY = 1;
        if (coordY > 38) coordY = 38;

        return;
      }

      void moveTo(int y_val, int x_val)
      {
        coordX = x_val;
        coordY = y_val;

        return;
      }

      void hurt()
      {
        healthPoints--;

        return;
      }

      int x()
      {
        return coordX;
      }

      int y()
      {
        return coordY;
      }

      int life()
      {
        return healthPoints;
      }
  };
}
