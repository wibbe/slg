
#include "slg/Window.hpp"

#include <GL/glew.h>
#include <GL/glfw.h>

namespace slg {
  
  Window::Window(int width, int height)
  {
    glfwInit();
    glfwOpenWindow(width, height, 8, 8, 8, 8, 24, 0, GLFW_WINDOW);
    glewInit();
  }
  
  Window::~Window()
  {
    glfwTerminate();
  }
  
  void Window::run()
  {
    bool running = true;
    while (running)
    {
      running = step();
    }
  }
  
  bool Window::step()
  {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
    bool continueOn = paint();
		
		glfwSwapBuffers();
		return continueOn && glfwGetWindowParam(GLFW_OPENED);
  }
  
  bool Window::paint()
  {
    return true;
  }
  
}