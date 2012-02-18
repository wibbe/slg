
#include "slg/Window.hpp"

#include "GL/glew.h"


class GameWindow : public slg::Window
{
  public:
    GameWindow()
      : Window(800, 500)
    {
      glClearColor(0.7, 0.8, 0.9, 1.0);
    }
    
    bool paint()
    {
      return true;
    }
};


int main(int argc, char * argv[])
{
  GameWindow window;
  window.run();  
  
  return 0;
}