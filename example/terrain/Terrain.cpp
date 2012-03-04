
#include "Terrain.hpp"

#include "slg/MeshHelpers.hpp"
#include "glm/gtx/transform.hpp"

namespace slg {

  Terrain::Terrain(int width, int height, int patchSize)
    : m_width(width),
      m_height(height),
      m_patchSize(patchSize),
      m_patchCount(width / patchSize, height / patchSize),
      m_patchMesh(),
      m_heightMap(width, height),
      m_heightMapBuffer(width, height),
      m_shader()
  {
    m_heightMap.edit();
    m_heightMap.addColorTexture(GL_R32F);
    m_heightMap.done();

    m_heightMapBuffer.edit();
    m_heightMapBuffer.addColorTexture(GL_R32F);
    m_heightMapBuffer.done();

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

    // Setup heightmap
    FrameBufferTarget target(m_heightMap);
    glClearColor(0, 0, 0, 0);
		glClear(GL_COLOR_BUFFER_BIT);
  }

  Terrain::~Terrain()
  {
  }

  void Terrain::draw(Camera const& camera)
  {
    m_shader.bind();
    m_heightMap.bindTexture(0, 0);

    const glm::mat4 viewProj = camera.projection() * camera.view();

    float offsetX = m_patchCount.x * -0.5;
    float offsetZ = m_patchCount.y * -0.5;

    m_shader.uniform("heightMap", 0);

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

      texOffset.y += texDelta.y;
    }

    m_shader.unbind();
  }

}

