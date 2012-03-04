
#include "Terrain.hpp"

#include "slg/MeshHelpers.hpp"

namespace slg {

  Terrain::Terrain(int width, int height, int patchSize)
    : m_width(width),
      m_height(height),
      m_patchSize(patchSize),
      m_patchMesh(),
      m_heightMap(width, height),
      m_shader()
  {
    m_heightMap.edit();
    m_heightMap.addColorTexture(GL_R32F);
    m_heightMap.done();

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
  }

  Terrain::~Terrain()
  {
  }

  void Terrain::draw()
  {
    m_heightMap.bindTexture(0, 0);
  }

}

