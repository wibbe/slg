
#include "slg/Window.hpp"
#include "slg/Camera.hpp"
#include "slg/Buffer.hpp"
#include "slg/Shader.hpp"
#include "slg/Mesh.hpp"
#include "slg/CameraControllers.hpp"
#include "slg/Tile.hpp"
#include "slg/Texture.hpp"

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
        m_tile(),
        m_toolPos(0.0, 0.0),
        m_toolOnTerrain(false),
        m_currentTool(0)
    {
      setTitle("Terrain Edit");

      m_terrain = new slg::Terrain(512, 512, 64);
      
      m_camera.setPosition(0, 1, 6);
      
      m_mesh.load("../../example/data/suzanne.obj", true);

      m_shader.load("../../example/data/Test.vert", GL_VERTEX_SHADER);
      m_shader.load("../../example/data/Test.frag", GL_FRAGMENT_SHADER);
      m_shader.setupMeshAttributes();
      m_shader.link();
      
      m_ridgeIcon.load("../../example/data/ridge.png");
      
      glClearColor(0.7, 0.8, 0.9, 1.0);
    }
    
    bool update(double dt)
    {
      flyController(m_camera, input(), dt);

      m_toolOnTerrain = m_terrain->worldToLocal(m_worldPos, m_toolPos);

      if (m_toolOnTerrain)
      {
        if (input().mouseButton(0) && !m_tile.hit() && m_currentTool != 0)
          m_terrain->applyTool(m_tool, (slg::Tool::Command)m_currentTool, m_toolPos, dt);
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
      
      glDisable(GL_DEPTH_TEST);
      
      m_tile.begin(ortho(), input().mousePosition(), input().mouseButton(0));      
      m_tile.pushRow();
      
      if (m_tile.icon(m_ridgeIcon, 15))
        m_currentTool = slg::Tool::TURBULENCE;
      if (m_tile.icon(m_ridgeIcon, 15))
        m_currentTool = slg::Tool::RIDGED;
      
      m_tile.pop();
      
      glEnable(GL_DEPTH_TEST);
    }
    
  private:
    slg::Camera m_camera;
    slg::VertexBuffer m_quad;
    slg::Mesh m_mesh;
    slg::Shader m_shader;
    
    slg::Terrain * m_terrain;
    slg::Tool m_tool;
    
    slg::Texture m_ridgeIcon;
    
    slg::Tile m_tile;

    glm::vec3 m_worldPos;
    glm::vec2 m_toolPos;
    
    bool m_toolOnTerrain;
    
    int m_currentTool;
};


int main(int argc, char * argv[])
{
  GameWindow window;
  window.run();  
  
  return 0;
}
