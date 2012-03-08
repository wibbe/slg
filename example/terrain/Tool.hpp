
#ifndef SLG_TOOL_HPP
#define SLG_TOOL_HPP

#include "slg/FrameBuffer.hpp"
#include "slg/Mesh.hpp"
#include "slg/Shader.hpp"

namespace slg {

  class Tool
  {
    public:
      enum Command
      {
        CLEAR,
        TURBULENCE
      };

    public:
      Tool();
      ~Tool();

      void apply(Command command, FrameBuffer & source, FrameBuffer & target, float dt);

    private:
      Mesh m_quad;

      Shader m_turbulence;
  };

}

#endif

