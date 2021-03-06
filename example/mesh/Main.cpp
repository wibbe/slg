
#include "slg/Window.hpp"
#include "slg/Camera.hpp"
#include "slg/Buffer.hpp"
#include "slg/Shader.hpp"
#include "slg/Mesh.hpp"
#include "slg/CameraControllers.hpp"

#include "GL/glew.h"
#include "GL/glfw.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <cmath>

class GameWindow : public slg::Window
{
  public:
    GameWindow()
      : Window(800, 500)
    {
      setTitle("SLG Example");
      
      m_camera.setPosition(0, 0, 5);
      
      m_mesh.load("../../example/data/suzanne.obj", true);

      m_shader.load("../../example/data/Test.vert", GL_VERTEX_SHADER);
      m_shader.load("../../example/data/Test.frag", GL_FRAGMENT_SHADER);
      m_shader.setupMeshAttributes();
      m_shader.link();
      
      glClearColor(0.7, 0.8, 0.9, 1.0);
    }
    
    bool update(double dt)
    {
      flyController(m_camera, input(), dt);

      return !input().isKeyDown(GLFW_KEY_ESC);
    }

    void resize(int width, int height)
    {
      glViewport(0, 0, width, height);
      m_camera.perspective(60.0f, width / (float)height, 1.0, 500.0);
    }
    
    void paint()
    {
      m_camera.update();

      glm::mat4 model = glm::rotate(glm::mat4(1.0), (float)(time() * 30.0), glm::vec3(0, 1, 0));
      glm::mat4 modelViewProj = m_camera.projection() * m_camera.view() * model;

      //glRotatef(time() * 30.0, 0, 1, 0);
      
      m_shader.bind();
      m_shader.uniform("color", 0.5 + std::sin(time() * 1.5) * 0.5, 0.5 + std::sin(time() * 2.0) * 0.5, 0.5 + std::sin(time() * 4.0) * 0.5);
      m_shader.uniform("modelViewProj", modelViewProj);
      m_shader.uniform("model", model);
      
      m_mesh.draw();

      m_shader.unbind();
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
