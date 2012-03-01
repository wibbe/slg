
#include <vector>
#include <stdio.h>
#include <string>
#include <cstring>

#include "slg/Mesh.hpp"

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
        char stupidBuffer[1000];
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
  
}