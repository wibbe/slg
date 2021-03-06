
#include "slg/Window.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <GL/glew.h>
#include <GL/glfw.h>
#include <cassert>

namespace slg {
  
  static Window * currentWindow = 0;
  
  // -- Callbacks --
  
  void mouseButton(int button, int state)
  {
    if (currentWindow)
      currentWindow->input().setMouseButton(button, state == GLFW_PRESS);
  }
  
  void mousePosition(int x, int y)
  {
    if (currentWindow)
      currentWindow->input().setMousePos(x, y);
  }

  void windowResized(int width, int height)
  {
    if (currentWindow)
      currentWindow->resize(width, height);
  }
  
  // -- Window --
  
  Window::Window(int width, int height)
  {
    assert(!currentWindow && "We may only have one window active at all times");
    currentWindow = this;
    
    glfwInit();
    
    glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 2);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 0);
    
    glfwOpenWindow(width, height, 8, 8, 8, 8, 24, 0, GLFW_WINDOW);
    
    glfwSetMouseButtonCallback(&mouseButton);
    glfwSetMousePosCallback(&mousePosition);
    glfwSetWindowSizeCallback(&windowResized);
    
    glewInit();
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);

    for (int texUnit = 0; texUnit < 4; ++texUnit)
    {
      glActiveTexture(GL_TEXTURE0 + texUnit);
      glEnable(GL_TEXTURE_2D);
    }

    glActiveTexture(GL_TEXTURE0);
    
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

    // Call resize before we start
    {
      int width, height;
      glfwGetWindowSize(&width, &height);
      resize(width, height);
    }
    
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
    
    paint();
		
		glfwSwapBuffers();
		return continueOn && glfwGetWindowParam(GLFW_OPENED);
  }
  
  void Window::setTitle(std::string const& title)
  {
    glfwSetWindowTitle(title.c_str());
  }
  
  glm::mat4 Window::ortho() const
  {
    int width;
    int height;
    glfwGetWindowSize(&width, &height);
    
    return glm::ortho(0.0f, (float)width, (float)height, (float)0.0f);
  }
  
}
