
SET(SOURCE
  Camera.cpp
  Shader.cpp
  Texture.cpp
  FrameBuffer.cpp
  Window.cpp
  Buffer.cpp
  BufferCollection.cpp
  Matrix4.cpp
  Quaternion.cpp
  Input.cpp
  File.cpp
  
  glew.c
  stb_image.c
)

SET(LIBRARIES
  ${OPENGL_LIBRARIES}
)

ADD_LIBRARY(slg ${SOURCE})
TARGET_LINK_LIBRARIES(slg ${LIBRARIES})

# Installation
INSTALL(TARGETS slg CONFIGURATIONS Release DESTINATION lib)

