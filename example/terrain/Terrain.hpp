
#ifndef SLG_TERRAIN_HPP
#define SLG_TERRAIN_HPP

#include "slg/Shader.hpp"
#include "slg/Mesh.hpp"
#include "slg/Texture.hpp"
#include "slg/FrameBuffer.hpp"
#include "slg/Camera.hpp"

#include "glm/glm.hpp"

#include "Tool.hpp"

namespace slg {

  class Terrain
  {
    public:
      Terrain(int width, int height, int patchSize);
      ~Terrain();

      void draw(Camera const& camera);

      bool worldToLocal(glm::vec3 const& world, glm::vec2 & local);

      void applyTool(Tool & tool, Tool::Command command, glm::vec2 const& pos, float dt);

    private:
      int m_width;
      int m_height;
      int m_patchSize;
      glm::ivec2 m_patchCount;

      Mesh m_patchMesh;
      FrameBuffer * m_heightMaps[2];

      int m_currentHeightMap;

      Shader m_shader;
  };

}

#endif

