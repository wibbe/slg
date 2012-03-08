
#include <vector>
#include <stdio.h>
#include <string>
#include <cstring>
#include <map>

#include "slg/MeshHelpers.hpp"
#include "glm/core/func_vector_relational.hpp"

namespace slg {
  
  bool loadObj(const char * filename,
               std::vector<glm::vec3> & vertices, 
               std::vector<glm::vec2> & uvs,
               std::vector<glm::vec3> & normals)
  {
    std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
    std::vector<glm::vec3> tempVertices; 
    std::vector<glm::vec2> tempUvs;
    std::vector<glm::vec3> tempNormals;

    FILE * file = fopen(filename, "r");
    if (!file)
    {
      fprintf(stderr, "Could not load mesh %s\n", filename);
      return false;
    }

    while (true)
    {
      char lineHeader[128];
      // read the first word of the line
      int res = fscanf(file, "%s", lineHeader);
      
      if (res == EOF)
        break;

      if (strcmp(lineHeader, "v") == 0)
      {
        glm::vec3 vertex;
        fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
        tempVertices.push_back(vertex);
      }
      else if (strcmp(lineHeader, "vt") == 0)
      {
        glm::vec2 uv;
        fscanf(file, "%f %f\n", &uv.x, &uv.y);
        uv.y = -uv.y;
        tempUvs.push_back(uv);
      }
      else if (strcmp(lineHeader, "vn") == 0)
      {
        glm::vec3 normal;
        fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
        tempNormals.push_back(normal);
      }
      else if (strcmp(lineHeader, "f") == 0)
      {
        unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
        int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
        if (matches != 9)
        {
          fprintf(stderr, "Could not read mesh %s\n", filename);
          fclose(file);
          return false;
        }
        
        vertexIndices.push_back(vertexIndex[0]);
        vertexIndices.push_back(vertexIndex[1]);
        vertexIndices.push_back(vertexIndex[2]);
        uvIndices.push_back(uvIndex[0]);
        uvIndices.push_back(uvIndex[1]);
        uvIndices.push_back(uvIndex[2]);
        normalIndices.push_back(normalIndex[0]);
        normalIndices.push_back(normalIndex[1]);
        normalIndices.push_back(normalIndex[2]);
      }
      else
      {
        // Probably a comment, eat up the rest of the line
        char stupidBuffer[1024];
        fgets(stupidBuffer, 1000, file);
      }
    }
    
    fclose(file);

    // For each vertex of each triangle
    for (unsigned int i = 0; i < vertexIndices.size(); ++i)
    {
      // Get the indices of its attributes
      unsigned int vertexIndex = vertexIndices[i];
      unsigned int uvIndex = uvIndices[i];
      unsigned int normalIndex = normalIndices[i];
    
      // Get the attributes thanks to the index
      glm::vec3 vertex = tempVertices[vertexIndex - 1];
      glm::vec2 uv = tempUvs[uvIndex - 1];
      glm::vec3 normal = tempNormals[normalIndex - 1];
    
      // Put the attributes in buffers
      vertices.push_back(vertex);
      uvs.push_back(uv);
      normals.push_back(normal);
    }

    return true;    
  }
  
  void computeTangentBasis(std::vector<glm::vec3> const& vertices,
                           std::vector<glm::vec2> const& uvs,
                           std::vector<glm::vec3> const& normals,
                           std::vector<glm::vec3> & tangents,
                           std::vector<glm::vec3> & bitangents)
  {
    for (size_t i = 0; i < vertices.size(); i += 3)
    {
      // Shortcuts for vertices
      glm::vec3 const& v0 = vertices[i + 0];
      glm::vec3 const& v1 = vertices[i + 1];
      glm::vec3 const& v2 = vertices[i + 2];

      // Shortcuts for UVs
      glm::vec2 const& uv0 = uvs[i + 0];
      glm::vec2 const& uv1 = uvs[i + 1];
      glm::vec2 const& uv2 = uvs[i + 2];

      // Edges of the triangle : postion delta
      glm::vec3 deltaPos1 = v1 - v0;
      glm::vec3 deltaPos2 = v2 - v0;

      // UV delta
      glm::vec2 deltaUV1 = uv1 - uv0;
      glm::vec2 deltaUV2 = uv2 - uv0;

      float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
      glm::vec3 tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y) * r;
      glm::vec3 bitangent = (deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.x) * r;

      // Set the same tangent for all three vertices of the triangle.
      // They will be merged later, in vboindexer.cpp
      tangents.push_back(tangent);
      tangents.push_back(tangent);
      tangents.push_back(tangent);

      // Same thing for binormals
      bitangents.push_back(bitangent);
      bitangents.push_back(bitangent);
      bitangents.push_back(bitangent);
    }

    // See "Going Further"
    for (size_t i = 0; i < vertices.size(); i += 1)
    {
      glm::vec3 const& n = normals[i];
      glm::vec3 & t = tangents[i];
      glm::vec3 & b = bitangents[i];

      // Gram-Schmidt orthogonalize
      t = glm::normalize(t - n * glm::dot(n, t));

      // Calculate handedness
      if (glm::dot(glm::cross(n, t), b) < 0.0f)
        t = t * -1.0f;
    }
  }

  struct PackedVertex
  {
    glm::vec3 position;
    glm::vec2 uv;
    glm::vec3 normal;
    
    bool operator < (PackedVertex const& that) const
    {
      return memcmp((void*)this, (void*)&that, sizeof(PackedVertex)) > 0;
    };
  };

  bool getSimilarVertexIndex(PackedVertex const& packed, 
                             std::map<PackedVertex,unsigned short> const& vertexToOutIndex,
                             unsigned short & result)
  {
    std::map<PackedVertex, unsigned short>::const_iterator it = vertexToOutIndex.find(packed);
    
    if (it == vertexToOutIndex.end())
    {
      return false;
    }
    else
    {
      result = it->second;
      return true;
    }
  }

  void calculateIndex(std::vector<glm::vec3> const& inVertices,
                      std::vector<glm::vec2> const& inUvs,
                      std::vector<glm::vec3> const& inNormals,
                      std::vector<unsigned short> & outIndices,
                      std::vector<glm::vec3> & outVertices,
                      std::vector<glm::vec2> & outUvs,
                      std::vector<glm::vec3> & outNormals)
  {
    std::map<PackedVertex, unsigned short> vertexToOutIndex;

    // For each input vertex
    for (size_t i = 0; i < inVertices.size(); ++i)
    {
      PackedVertex packed = { inVertices[i], inUvs[i], inNormals[i] };

      unsigned short index;
      if (getSimilarVertexIndex(packed, vertexToOutIndex, index))
      {
        // A similar vertex is already in the VBO, use it instead !
        outIndices.push_back(index);
      }
      else
      {
        // If not, it needs to be added in the output data.
        outVertices.push_back(inVertices[i]);
        outUvs.push_back(inUvs[i]);
        outNormals.push_back(inNormals[i]);
        
        unsigned short newindex = outVertices.size() - 1;
        outIndices.push_back(newindex);
        
        vertexToOutIndex.insert(std::make_pair(packed, newindex));
      }
    }
  }
  
  bool getSimilarVertexIndex(glm::vec3 const& vertex, 
                             glm::vec2 const& uv, 
                             glm::vec3 const& normal, 
                             std::vector<glm::vec3> const& outVertices,
                             std::vector<glm::vec2> const& outUvs,
                             std::vector<glm::vec3> const& outNormals,
                             unsigned short & result)
  {
    for (size_t i = 0; i < outVertices.size(); ++i)
    {
      if (glm::all(glm::equal(vertex, outVertices[i])) &&
          glm::all(glm::equal(normal, outNormals[i])) &&
          glm::all(glm::equal(uv, outUvs[i])))
      {
        result = i;
        return true;
      }
    }
    
    return false;
  }

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
                      std::vector<glm::vec3> & outBitangents)
  {
    // For each input vertex
    for (size_t i = 0; i < inVertices.size(); ++i)
    {
      unsigned short index;
      if (getSimilarVertexIndex(inVertices[i], inUvs[i], inNormals[i], outVertices, outUvs, outNormals, index))
      {
        outIndices.push_back(index);
      }
      else
      {
        outVertices.push_back(inVertices[i]);
        outUvs.push_back(inUvs[i]);
        outNormals.push_back(inNormals[i]);
        outTangents.push_back(inTangents[i]);
        outBitangents.push_back(inBitangents[i]);
        outIndices.push_back((unsigned short)outVertices.size() - 1);
      }
    }
  } 
  
  void createQuad(Mesh & mesh, bool inClipSpace)
  {
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> coords;
    std::vector<unsigned short> indicies;
    
    if (inClipSpace)
    {
      vertices.push_back(glm::vec3(-1, 1, 0));
      vertices.push_back(glm::vec3(-1, -1, 0));
      vertices.push_back(glm::vec3(1, -1, 0));
      vertices.push_back(glm::vec3(1, 1, 0));
    }
    else
    {
      vertices.push_back(glm::vec3(0, 0, 0));
      vertices.push_back(glm::vec3(0, 1, 0));
      vertices.push_back(glm::vec3(1, 1, 0));
      vertices.push_back(glm::vec3(1, 0, 0));
    }

    coords.push_back(glm::vec2(0, 1));
    coords.push_back(glm::vec2(0, 0));
    coords.push_back(glm::vec2(1, 0));
    coords.push_back(glm::vec2(1, 1));

    pushTriangle(indicies, 0, 1, 2);
    pushTriangle(indicies, 0, 2, 3);
    
    mesh.addBuffer(Mesh::VERTEX, vertices);
    mesh.addBuffer(Mesh::UV, coords);
    mesh.addBuffer(Mesh::INDICIES, indicies);
    mesh.setIndexCount(indicies.size());
  }

}