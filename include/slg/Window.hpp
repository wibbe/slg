
#ifndef SLG_WINDOW_HPP
#define SLG_WINDOW_HPP

namespace slg {
  
  class Window
  {
    public:
      Window(int width, int height);
      virtual ~Window();
      
      void run();
      bool step();
      
      virtual bool paint();
  };
  
}

#endif