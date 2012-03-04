
#include "Terrain.hpp"

namespace slg {

  Terrain::Terrain(int width, int height, int patchSize)
    : m_width(width),
      m_height(height),
      m_patchSize(patchSize),
      m_heightMap(width, height),
      m_shader()
  {
    m_heightMap.edit();
    m_heightMap.addColorTexture(GL_R32F);
    m_heightMap.done();
  }

  Terrain::~Terrain()
  {
  }

  void Terrain::draw()
  {
  }

}

