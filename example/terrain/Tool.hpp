
#ifndef SLG_TOOL_HPP
#define SLG_TOOL_HPP

#include "slg/FrameBuffer.hpp"

namespace slg {

  class Tool
  {
    public:
      Tool() { }
      virtual ~Tool() { }

      virtual void apply(FrameBuffer & source, FrameBuffer & target, float dt) = 0;
  };


  class ClearTool : public Tool
  {
    public:
      ClearTool();

      void apply(FrameBuffer & source, FrameBuffer & target, float dt);
  };

}

#endif

