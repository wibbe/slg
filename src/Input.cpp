
#include "slg/Input.hpp"
#include "GL/glfw.h"

#include <cassert>

namespace slg {
  
  Input::Input()
    : m_mouseX(0),
      m_mouseY(0),
      m_mouseRelX(0),
      m_mouseRelY(0)
  {
    for (int i = 0; i < MOUSE_BUTTON_COUNT; ++i)
      m_mouseButtons[i] = false;
  }

  int Input::mouseRelX()
  {
    int val = m_mouseRelX;
    m_mouseRelX = 0;
    return val;
  }

  int Input::mouseRelY()
  {
    int val = m_mouseRelY;
    m_mouseRelY = 0;
    return val;
  }
  
  bool Input::mouseButton(int button) const
  {
    assert(button < MOUSE_BUTTON_COUNT);
    return m_mouseButtons[button];
  }

  bool Input::isKeyDown(int key) const
  {
    return glfwGetKey(key);
  }
  
  void Input::setMousePos(int x, int y)
  {
    m_mouseRelX = x - m_mouseX;
    m_mouseRelY = y - m_mouseY;
    m_mouseX = x;
    m_mouseY = y;
  }
  
  void Input::setMouseButton(int button, bool down)
  {
    m_mouseButtons[button] = down;
  }
  
}
