
#include "slg/Input.hpp"

#include <cassert>

namespace slg {
  
  Input::Input()
    : m_mouseX(0),
      m_mouseY(0)
  {
    for (int i = 0; i < MOUSE_BUTTON_COUNT; ++i)
      m_mouseButtons[i] = false;
  }
  
  bool Input::mouseButton(int button) const
  {
    assert(button < MOUSE_BUTTON_COUNT);
    return m_mouseButtons[button];
  }
  
  void Input::setMousePos(int x, int y)
  {
    m_mouseX = x;
    m_mouseY = y;
  }
  
  void Input::setMouseButton(int button, bool down)
  {
    m_mouseButtons[button] = down;
  }
  
}
