
#include "slg/Window.hpp"
#include "slg/Camera.hpp"
#include "slg/Buffer.hpp"
#include "slg/Shader.hpp"
#include "slg/Mesh.hpp"

#include "GL/glew.h"
#include "GL/glfw.h"

#include <cmath>

glm::vec3 cube[36] = {
glm::vec3(1.000000, -1.000000, -1.000000),
glm::vec3(1.000000, -1.000000, 1.000000),
glm::vec3(-1.000000, -1.000000, 1.000000),
glm::vec3(1.000000, -1.000000, -1.000000),
glm::vec3(-1.000000, -1.000000, 1.000000),
glm::vec3(-1.000000, -1.000000, -1.000000),
glm::vec3(1.000000, 1.000000, -0.999999),
glm::vec3(-1.000000, 1.000000, -1.000000),
glm::vec3(-1.000000, 1.000000, 1.000000),
glm::vec3(1.000000, 1.000000, -0.999999),
glm::vec3(-1.000000, 1.000000, 1.000000),
glm::vec3(0.999999, 1.000000, 1.000001),
glm::vec3(1.000000, -1.000000, -1.000000),
glm::vec3(1.000000, 1.000000, -0.999999),
glm::vec3(0.999999, 1.000000, 1.000001),
glm::vec3(1.000000, -1.000000, -1.000000),
glm::vec3(0.999999, 1.000000, 1.000001),
glm::vec3(1.000000, -1.000000, 1.000000),
glm::vec3(1.000000, -1.000000, 1.000000),
glm::vec3(0.999999, 1.000000, 1.000001),
glm::vec3(-1.000000, 1.000000, 1.000000),
glm::vec3(1.000000, -1.000000, 1.000000),
glm::vec3(-1.000000, 1.000000, 1.000000),
glm::vec3(-1.000000, -1.000000, 1.000000),
glm::vec3(-1.000000, -1.000000, 1.000000),
glm::vec3(-1.000000, 1.000000, 1.000000),
glm::vec3(-1.000000, 1.000000, -1.000000),
glm::vec3(-1.000000, -1.000000, 1.000000),
glm::vec3(-1.000000, 1.000000, -1.000000),
glm::vec3(-1.000000, -1.000000, -1.000000),
glm::vec3(1.000000, 1.000000, -0.999999),
glm::vec3(1.000000, -1.000000, -1.000000),
glm::vec3(-1.000000, -1.000000, -1.000000),
glm::vec3(1.000000, 1.000000, -0.999999),
glm::vec3(-1.000000, -1.000000, -1.000000),
glm::vec3(-1.000000, 1.000000, -1.000000)
};


class GameWindow : public slg::Window
{
  public:
    GameWindow()
      : Window(800, 500)
    {
      setTitle("SLG Example");
      
      m_camera.setPosition(0, 0, 5);
      m_camera.perspective(60.0f, 800.0 / 500.0f, 1.0, 500.0);
      
      m_mesh.load("../../example/suzanne.obj", true);

      m_shader.load("../../example/Test.vert", GL_VERTEX_SHADER);
      m_shader.load("../../example/Test.frag", GL_FRAGMENT_SHADER);
      m_shader.setupMeshAttributes();
      m_shader.link();
      
      glClearColor(0.7, 0.8, 0.9, 1.0);
    }
    
    bool update(double dt)
    {
      return !isKeyDown(GLFW_KEY_ESC);
    }
    
    void paint()
    {
      m_camera.apply();
      glViewport(0, 0, 800, 500);

      glRotatef(time() * 30.0, 0, 1, 0);
      
      m_shader.bind();
      m_shader.uniform("color", 0.5 + std::sin(time() * 1.5) * 0.5, 0.5 + std::sin(time() * 2.0) * 0.5, 0.5 + std::sin(time() * 4.0) * 0.5);
      
      m_mesh.draw();

      m_shader.unbind();
      
      
      //glDisableClientState(GL_VERTEX_ARRAY);
    }
    
  private:
    slg::Camera m_camera;
    slg::VertexBuffer m_quad;
    slg::Mesh m_mesh;
    slg::Shader m_shader;
};


int main(int argc, char * argv[])
{
  GameWindow window;
  window.run();  
  
  return 0;
}
