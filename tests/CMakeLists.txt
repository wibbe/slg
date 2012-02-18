
SET(SOURCE
   Main.cpp
   TestNode.cpp
)

SET(LIBRARIES
  slg
)

INCLUDE_DIRECTORIES(
  "${CMAKE_CURRENT_SOURCE_DIR}/catch/single_include"
)

ADD_EXECUTABLE(unit_test ${SOURCE})
TARGET_LINK_LIBRARIES(unit_test ${LIBRARIES})
