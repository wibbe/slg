
SET(SOURCE
  Main.cpp
  Terrain.cpp
  Tool.cpp
)

SET(LIBRARIES
  ${OPENGL_LIBRARIES}
  ${EXTRA_LIBRARIES}
  ${GLFW_LIBRARIES}
  slg
)

ADD_EXECUTABLE(terrain-edit ${SOURCE})
TARGET_LINK_LIBRARIES(terrain-edit ${LIBRARIES})

# Installation
INSTALL(TARGETS terrain-edit CONFIGURATIONS Release DESTINATION bin)
