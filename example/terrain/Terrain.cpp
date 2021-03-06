
#include "Terrain.hpp"
#include "Tool.hpp"

#include "slg/MeshHelpers.hpp"
#include "glm/gtx/transform.hpp"

namespace slg {

  Terrain::Terrain(int width, int height, int patchSize)
    : m_width(width),
      m_height(height),
      m_patchSize(patchSize),
      m_patchCount(width / patchSize, height / patchSize),
      m_patchMesh(),
      m_currentHeightMap(0),
      m_shader()
  {
    for (int i = 0; i < 2; ++i)
    {
      m_heightMaps[i] = new FrameBuffer(width, height);
      m_heightMaps[i]->edit();
      m_heightMaps[i]->addColorTexture(GL_R32F);
      m_heightMaps[i]->done();
    }

    std::vector<glm::vec3> vertices;
    std::vector<unsigned short> indicies;

    #define INDEX(x, z) ((z) * patchSize) + (x)

    for (int z = 0; z < patchSize; ++z)
      for (int x = 0; x < patchSize; ++x)
      {
        float ux = x / (patchSize - 1.0);
        float uz = z / (patchSize - 1.0);
        
        vertices.push_back(glm::vec3(ux, 0.0, uz));
        
        if (z < (patchSize - 1) && x < (patchSize - 1))
        {
          pushTriangle(indicies, INDEX(x, z), INDEX(x, z + 1), INDEX(x + 1, z));
          pushTriangle(indicies, INDEX(x, z + 1), INDEX(x + 1, z + 1), INDEX(x + 1, z));
        }
      }

    m_patchMesh.addBuffer(Mesh::VERTEX, vertices);
    m_patchMesh.addBuffer(Mesh::INDICIES, indicies);
    m_patchMesh.setIndexCount(indicies.size());

    m_shader.load("../../example/data/Terrain.vert", GL_VERTEX_SHADER);
    m_shader.load("../../example/data/Terrain.frag", GL_FRAGMENT_SHADER);
    m_shader.setupMeshAttributes();
    m_shader.link();
  }

  Terrain::~Terrain()
  {
    delete m_heightMaps[0];
    delete m_heightMaps[1];
  }

  void Terrain::draw(Camera const& camera, glm::vec2 const& toolPos, bool showTool)
  {
    m_shader.bind();
    m_heightMaps[m_currentHeightMap]->bindTexture(0, 0);

    const glm::mat4 viewProj = camera.projection() * camera.view();

    float offsetX = m_patchCount.x * -0.5;
    float offsetZ = m_patchCount.y * -0.5;

    m_shader.uniform("heightMap", 0);
    m_shader.uniform("texelSize", 1.0f / m_width, 1.0f / m_height);

    m_shader.uniform("toolPos", toolPos);
    m_shader.uniform("showTool", showTool ? 1.0f : 0.0f);

    glm::vec2 texOffset(0.0);
    const glm::vec2 texDelta(1.0 / m_patchCount.x, 1.0 / m_patchCount.y);

    for (int z = 0; z < m_patchCount.y; ++z)
    {
      for (int x = 0; x < m_patchCount.x; ++x)
      {
        const glm::mat4 model = glm::translate(glm::vec3(offsetX + x, 0.0, offsetZ + z));
        const glm::mat4 modelViewProj = viewProj * model;
        
        m_shader.uniform("modelViewProj", modelViewProj);
        m_shader.uniform("model", model);
        m_shader.uniform("color", x % 2, 0, z % 2);
        m_shader.uniform("texOffset", texOffset);
        m_shader.uniform("texScale", texDelta);

        m_patchMesh.draw();

        texOffset.x += texDelta.x;
      }

      texOffset.x = 0.0;
      texOffset.y += texDelta.y;
    }

    m_shader.unbind();
  }

  bool Terrain::worldToLocal(glm::vec3 const& world, glm::vec2 & local)
  {
    glm::vec2 start = glm::vec2(m_patchCount) * -0.5f;
    glm::vec2 size = glm::vec2(m_patchCount);
    glm::vec2 pos(world.x, world.z);

    if (pos.x < start.x ||
        pos.y < start.y ||
        pos.x > (start.x + size.x) ||
        pos.y > (start.y + size.y))
      return false;

    pos += start;
    pos /= size;
    //local = pos;
    local = glm::vec2(1.0f) + pos;

    return true;
  }

  void Terrain::applyTool(Tool & tool, Tool::Command command, glm::vec2 const& pos, float dt)
  {
    m_currentHeightMap = (m_currentHeightMap + 1) % 2;
    tool.apply(command, *m_heightMaps[(m_currentHeightMap + 1) % 2], *m_heightMaps[m_currentHeightMap], pos, dt);
  }

}

