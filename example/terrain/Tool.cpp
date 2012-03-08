
#include "Tool.hpp"

#include "GL/glew.h"

namespace slg {

  ClearTool::ClearTool()
    : Tool()
  { }

  void ClearTool::apply(FrameBuffer & source, FrameBuffer & target, float dt)
  {
    FrameBufferTarget fbtarget(target);
    glClearColor(0, 0, 0, 0);
		glClear(GL_COLOR_BUFFER_BIT);
  }

}

