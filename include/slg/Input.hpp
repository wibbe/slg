
#ifndef SLG_INPUT_HPP
#define SLG_INPUT_HPP

#include "glm/glm.hpp"

namespace slg {
  
  class Input
  {
    public:
      static const int MOUSE_BUTTON_COUNT = 3;
    public:
      Input();
      
      int mouseX() const { return m_mouseX; }
      int mouseY() const { return m_mouseY; }
      int mouseRelX();
      int mouseRelY();

      glm::ivec2 mousePosition() const { return glm::ivec2(m_mouseX, m_mouseY); }
      
      bool mouseButton(int button) const;
      bool isKeyDown(int key) const;
      
      void setMousePos(int x, int y);
      void setMouseButton(int button, bool down);
      
    private:
      int m_mouseX;
      int m_mouseY;
      int m_mouseRelX;
      int m_mouseRelY;
      bool m_mouseButtons[MOUSE_BUTTON_COUNT];
  };
  
}

#endif
