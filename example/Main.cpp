
#include "slg/Window.hpp"
#include "slg/Camera.hpp"
#include "slg/Buffer.hpp"

#include "GL/glew.h"
#include "GL/glfw.h"


class GameWindow : public slg::Window
{
  public:
    GameWindow()
      : Window(800, 500)
    {
      setTitle("SLG Example");
      
      m_camera.setPosition(0, 0, 5);
      m_camera.perspective(60.0f, 800.0 / 500.0f, 1.0, 500.0);
      
      slg::BufferBuilder<float> builder(m_quad);
      builder.vec3(-1, 1, 0);
      builder.vec3(-1, -1, 0);
      builder.vec3(1, -1, 0);
      builder.vec3(1, 1, 0);
      builder.done();
      
      glClearColor(0.7, 0.8, 0.9, 1.0);
    }
    
    bool update(double dt)
    {
      m_camera.yaw(dt * 36.0f);
      
      return !isKeyDown(GLFW_KEY_ESC);
    }
    
    void paint()
    {
      m_camera.apply();
      glViewport(0, 0, 800, 500);
      
      glEnableClientState(GL_VERTEX_ARRAY);
      m_quad.bind();
      glVertexPointer(3, GL_FLOAT, 0, 0);
      
      glDrawArrays(GL_QUADS, 0, 4);
      
      
      glDisableClientState(GL_VERTEX_ARRAY);
    }
    
  private:
    slg::Camera m_camera;
    slg::VertexBuffer m_quad;
};


int main(int argc, char * argv[])
{
  GameWindow window;
  window.run();  
  
  return 0;
}