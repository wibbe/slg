
#ifndef SLG_INPUT_HPP
#define SLG_INPUT_HPP

namespace slg {
  
  class Input
  {
    public:
      Input();
      
      int mouseX() const { return m_mouseX; }
      int mouseY() const { return m_mouseY; }
      
    private:
      int m_mouseX;
      int m_mouseY;
  };
  
}

#endif