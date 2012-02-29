
#include "slg/Window.hpp"

#include <GL/glew.h>
#include <GL/glfw.h>
#include <cassert>

namespace slg {
  
  static Window * currentWindow = 0;
  
  Window::Window(int width, int height)
  {
    assert(!currentWindow && "We may only have one window active at all times");
    currentWindow = this;
    
    glfwInit();
    glfwOpenWindow(width, height, 8, 8, 8, 8, 24, 0, GLFW_WINDOW);
    glewInit();
  }
  
  Window::~Window()
  {
    currentWindow = 0;
    glfwTerminate();
  }
  
  void Window::run()
  {
    glfwSetTime(0.0);
    m_lastTimeStamp = 0.0;
    m_totalTime = 0.0;
    
    bool running = true;
    while (running)
    {
      running = step();
    }
  }
  
  bool Window::step()
  {
    double timeStamp = glfwGetTime();
    double dt = timeStamp - m_lastTimeStamp;
    m_lastTimeStamp = timeStamp;

    m_totalTime += dt;
    
    bool continueOn = update(dt);
    
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
    paint();
		
		glfwSwapBuffers();
		return continueOn && glfwGetWindowParam(GLFW_OPENED);
  }
  
  bool Window::isKeyDown(int key)
  {
    return glfwGetKey(key);
  }
  
  void Window::setTitle(std::string const& title)
  {
    glfwSetWindowTitle(title.c_str());
  }
  
}
