
SET(SOURCE
  Camera.cpp
  Shader.cpp
  Texture.cpp
  FrameBuffer.cpp
  Window.cpp
  Buffer.cpp
  Input.cpp
  File.cpp
  Mesh.cpp
  MeshHelpers.cpp
  CameraControllers.cpp
  Tile.cpp
  
  glew.c
  soil/SOIL.c
  soil/image_DXT.c
  soil/stb_image_aug.c
  soil/image_helper.c
  soil/stbi_DDS_aug_c.h
)

SET(LIBRARIES
    ${OPENGL_LIBRARIES}
    ${GLFW_LIBRARIES}
    ${EXTRA_LIBRARIES}
)

ADD_LIBRARY(slg ${SOURCE})
TARGET_LINK_LIBRARIES(slg ${LIBRARIES})

# Installation
INSTALL(TARGETS slg CONFIGURATIONS Release DESTINATION lib)

