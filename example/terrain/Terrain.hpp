
#ifndef SLG_TERRAIN_HPP
#define SLG_TERRAIN_HPP

#include "slg/Shader.hpp"
#include "slg/Mesh.hpp"
#include "slg/Texture.hpp"
#include "slg/FrameBuffer.hpp"

namespace slg {

  class Terrain
  {
    public:
      Terrain(int width, int height, int patchSize);
      ~Terrain();

      void draw();

    private:
      int m_width;
      int m_height;
      int m_patchSize;

      Mesh m_patchMesh;
      FrameBuffer m_heightMap;

      Shader m_shader;
  };

}

#endif

