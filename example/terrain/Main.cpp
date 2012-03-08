
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

#include "Terrain.hpp"
#include "Tool.hpp"

#include <cmath>

class GameWindow : public slg::Window
{
  public:
    GameWindow()
      : Window(800, 500),
        m_terrain(0),
        m_toolPos(0.0, 0.0),
        m_toolOnTerrain(false)
    {
      setTitle("Terrain Edit");

      m_terrain = new slg::Terrain(512, 512, 64);
      
      m_camera.setPosition(0, 1, 6);
      
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

      m_toolOnTerrain = m_terrain->worldToLocal(m_worldPos, m_toolPos);

      if (m_toolOnTerrain)
      {
        if (input().isKeyDown('T'))
          m_terrain->applyTool(m_tool, slg::Tool::TURBULENCE, m_toolPos, dt);

        if (input().isKeyDown('R'))
          m_terrain->applyTool(m_tool, slg::Tool::RIDGED, m_toolPos, dt);
      }

      if (input().isKeyDown('C'))
        m_terrain->applyTool(m_tool, slg::Tool::CLEAR, m_toolPos, 0.0);

      return !input().isKeyDown(GLFW_KEY_ESC);
    }

    void resize(int width, int height)
    {
      glViewport(0, 0, width, height);
      m_camera.perspective(60.0f, width / (float)height, 0.1, 500.0); 
    }
    
    void paint()
    {
      glClearColor(0.7, 0.8, 0.9, 1.0);
		  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      m_camera.update();

      m_terrain->draw(m_camera, m_toolPos, m_toolOnTerrain);

      m_worldPos = m_camera.pick(input().mousePosition());
    }
    
  private:
    slg::Camera m_camera;
    slg::VertexBuffer m_quad;
    slg::Mesh m_mesh;
    slg::Shader m_shader;
    
    slg::Terrain * m_terrain;
    slg::Tool m_tool;

    glm::vec3 m_worldPos;
    glm::vec2 m_toolPos;
    bool m_toolOnTerrain;
};


int main(int argc, char * argv[])
{
  GameWindow window;
  window.run();  
  
  return 0;
}
