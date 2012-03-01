
#ifndef SLG_MESH_HPP
#define SLG_MESH_HPP

#include "glm/glm.hpp"

namespace slg {
  
  bool loadObj(const char * filename,
               std::vector<glm::vec3> & vertices, 
               std::vector<glm::vec2> & uvs,
               std::vector<glm::vec3> & normals);
  
}

#endif