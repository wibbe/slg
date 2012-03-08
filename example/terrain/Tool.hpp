
#ifndef SLG_TOOL_HPP
#define SLG_TOOL_HPP

#include "slg/FrameBuffer.hpp"
#include "slg/Mesh.hpp"
#include "slg/Shader.hpp"

#include "glm/glm.hpp"

namespace slg {

  class Tool
  {
    public:
      enum Command
      {
        CLEAR,
        TURBULENCE,
        RIDGED
      };

    public:
      Tool();
      ~Tool();

      void apply(Command command, FrameBuffer & source, FrameBuffer & target, glm::vec2 const& pos, float dt);

    private:
      Mesh m_quad;

      Shader m_turbulence;
      Shader m_ridged;
  };

}

#endif

