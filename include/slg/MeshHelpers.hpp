
#ifndef SLG_MESH_HELPERS_HPP
#define SLG_MESH_HELPERS_HPP

#include "glm/glm.hpp"
#include "slg/Mesh.hpp"

#include <vector>

namespace slg {
  
  bool loadObj(const char * filename,
               std::vector<glm::vec3> & vertices, 
               std::vector<glm::vec2> & uvs,
               std::vector<glm::vec3> & normals);
               
  void computeTangentBasis(std::vector<glm::vec3> const& vertices,
                           std::vector<glm::vec2> const& uvs,
                           std::vector<glm::vec3> const& normals,
                           std::vector<glm::vec3> & tangents,
                           std::vector<glm::vec3> & bitangents);
                           
   void calculateIndex(std::vector<glm::vec3> const& inVertices,
                       std::vector<glm::vec2> const& inUvs,
                       std::vector<glm::vec3> const& inNormals,
                       std::vector<unsigned short> & outIndices,
                       std::vector<glm::vec3> & outVertices,
                       std::vector<glm::vec2> & outUvs,
                       std::vector<glm::vec3> & outNormals);


  void calculateIndex(std::vector<glm::vec3> const& inVertices,
                      std::vector<glm::vec2> const& inUvs,
                      std::vector<glm::vec3> const& inNormals,
                      std::vector<glm::vec3> const& inTangents,
                      std::vector<glm::vec3> const& inBitangents,
                      std::vector<unsigned short> & outIndices,
                      std::vector<glm::vec3> & outVertices,
                      std::vector<glm::vec2> & outUvs,
                      std::vector<glm::vec3> & outNormals,
                      std::vector<glm::vec3> & outTangents,
                      std::vector<glm::vec3> & outBitangents);
                      
  void createQuad(Mesh & mesh, bool inClipSpace);

  inline void pushTriangle(std::vector<unsigned short> & data, unsigned short a, unsigned short b, unsigned short c)
  {
    data.push_back(a);
    data.push_back(b);
    data.push_back(c);
  }
  
}

#endif
