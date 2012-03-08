
#include "Tool.hpp"
#include "slg/MeshHelpers.hpp"

#include "GL/glew.h"
#include "glm/glm.hpp"

namespace slg {

  Tool::Tool()
    : m_quad(),
      m_turbulence()
  {
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> coords;
    std::vector<unsigned short> indicies;

    vertices.push_back(glm::vec3(-1, 1, 0));
    vertices.push_back(glm::vec3(-1, -1, 0));
    vertices.push_back(glm::vec3(1, -1, 0));
    vertices.push_back(glm::vec3(1, 1, 0));

    coords.push_back(glm::vec2(0, 1));
    coords.push_back(glm::vec2(0, 0));
    coords.push_back(glm::vec2(1, 0));
    coords.push_back(glm::vec2(1, 1));

    pushTriangle(indicies, 0, 1, 2);
    pushTriangle(indicies, 0, 2, 3);

    m_quad.addBuffer(Mesh::VERTEX, vertices);
    m_quad.addBuffer(Mesh::UV, coords);
    m_quad.addBuffer(Mesh::INDICIES, indicies);
    m_quad.setIndexCount(indicies.size());

    m_turbulence.load("../../example/data/tool.vert", GL_VERTEX_SHADER);
    m_turbulence.load2("../../example/data/noise2D.glsl", "../../example/data/turbulence.frag", GL_FRAGMENT_SHADER);
    m_turbulence.setupMeshAttributes();
    m_turbulence.link();

    m_ridged.load("../../example/data/tool.vert", GL_VERTEX_SHADER);
    m_ridged.load2("../../example/data/noise2D.glsl", "../../example/data/ridged.frag", GL_FRAGMENT_SHADER);
    m_ridged.setupMeshAttributes();
    m_ridged.link();
  }

  Tool::~Tool()
  {
  }

  void Tool::apply(Command command, FrameBuffer & source, FrameBuffer & target, float dt)
  {
    switch (command)
    {
      case CLEAR:
        {
          FrameBufferTarget fbtarget(target);
          glClearColor(0, 0, 0, 0);
		      glClear(GL_COLOR_BUFFER_BIT);
		    }
		    break;

		  case TURBULENCE:
        {
          FrameBufferTarget fbtarget(target);

          source.bindTexture(0, 0);

          m_turbulence.bind();
          m_turbulence.uniform("dt", dt);
          m_turbulence.uniform("previous", 0);
          m_quad.draw();
          m_turbulence.unbind();
        }
        break;

		  case RIDGED:
        {
          FrameBufferTarget fbtarget(target);

          source.bindTexture(0, 0);

          m_ridged.bind();
          m_ridged.uniform("dt", dt);
          m_ridged.uniform("previous", 0);
          m_quad.draw();
          m_ridged.unbind();
        }
        break;
		}
  }

}

