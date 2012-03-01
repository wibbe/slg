
#include "slg/Mesh.hpp"
#include "slg/MeshHelpers.hpp"

namespace slg {
  
  Mesh::Mesh()
    : m_indexCount(0),
      m_hasTangents(false),
      m_useIndicies(false),
      m_loaded(false)
  {
  }
  
  Mesh::Mesh(Mesh const& copy)
  {
    m_vertex = copy.m_vertex;
    m_uv = copy.m_uv;
    m_normal = copy.m_normal;
    m_tangent = copy.m_tangent;
    m_binormal = copy.m_binormal;
    m_indicies = copy.m_indicies;
    m_hasTangents = copy.m_hasTangents;
    m_useIndicies = copy.m_useIndicies;
    m_loaded = copy.m_loaded;
    m_indexCount = copy.m_indexCount;
  }
  
  Mesh::~Mesh()
  {
    destroy();
  }
  
  Mesh const& Mesh::operator = (Mesh const& copy)
  {
    m_vertex = copy.m_vertex;
    m_uv = copy.m_uv;
    m_normal = copy.m_normal;
    m_tangent = copy.m_tangent;
    m_binormal = copy.m_binormal;
    m_indicies = copy.m_indicies;
    m_hasTangents = copy.m_hasTangents;
    m_useIndicies = copy.m_useIndicies;
    m_loaded = copy.m_loaded;
    m_indexCount = copy.m_indexCount;
    
    return *this;
  }
  
  void Mesh::destroy()
  {
    m_loaded = false;
    m_hasTangents = false;
    m_useIndicies = false;
    m_indexCount = 0;
    m_vertex = Buffer();
    m_uv = Buffer();
    m_normal = Buffer();
    m_tangent = Buffer();
    m_binormal = Buffer();
    m_indicies = Buffer();
  }
  
  bool Mesh::load(const char * filename, bool useIndicies, bool computeTangents)
  {
    destroy();
    
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec3> tangents;
    std::vector<glm::vec3> binormals;
    
    std::vector<glm::vec3> finalVertices;
    std::vector<glm::vec2> finalUvs;
    std::vector<glm::vec3> finalNormals;
    std::vector<glm::vec3> finalTangents;
    std::vector<glm::vec3> finalBinormals;
    std::vector<unsigned short> finalIndicies;
    
    if (!loadObj(filename, vertices, uvs, normals))
      return false;
      
    m_useIndicies = useIndicies;
      
    m_vertex = Buffer(GL_ARRAY_BUFFER);
    m_normal = Buffer(GL_ARRAY_BUFFER);
    m_uv = Buffer(GL_ARRAY_BUFFER);
    
    if (useIndicies)
      m_indicies = Buffer(GL_ELEMENT_ARRAY_BUFFER);
      
    if (computeTangents)
    {
      computeTangentBasis(vertices, uvs, normals, tangents, binormals);
      m_hasTangents = true;
      
      m_tangent = Buffer(GL_ARRAY_BUFFER);
      m_binormal = Buffer(GL_ARRAY_BUFFER);
      
      if (useIndicies)
      {
        calculateIndex(vertices, uvs, normals, tangents, binormals,
                       finalIndicies, finalVertices, finalUvs, finalNormals, finalTangents, finalBinormals);
                     
        m_tangent.upload(&tangents[0], tangents.size() * sizeof(float) * 3, GL_STATIC_DRAW);
        m_binormal.upload(&binormals[0], binormals.size() * sizeof(float) * 3, GL_STATIC_DRAW);
      }
      else
      {
        m_tangent.upload(&finalTangents[0], finalTangents.size() * sizeof(float) * 3, GL_STATIC_DRAW);
        m_binormal.upload(&finalBinormals[0], finalBinormals.size() * sizeof(float) * 3, GL_STATIC_DRAW);        
      }
    }
    
    if (useIndicies)
    {
      if (!computeTangents)
        calculateIndex(vertices, uvs, normals, 
                       finalIndicies, finalVertices, finalUvs, finalNormals);
    
      m_vertex.upload(&finalVertices[0], finalVertices.size() * sizeof(float) * 3, GL_STATIC_DRAW);
      m_normal.upload(&finalNormals[0], finalNormals.size() * sizeof(float) * 3, GL_STATIC_DRAW);
      m_uv.upload(&finalUvs[0], finalUvs.size() * sizeof(float) * 2, GL_STATIC_DRAW);
      m_indicies.upload(&finalIndicies[0], finalIndicies.size() * sizeof(unsigned short), GL_STATIC_DRAW);
      
      m_indexCount = finalIndicies.size();
    }
    else
    {
      m_vertex.upload(&vertices[0], vertices.size() * sizeof(float) * 3, GL_STATIC_DRAW);
      m_normal.upload(&normals[0], normals.size() * sizeof(float) * 3, GL_STATIC_DRAW);
      m_uv.upload(&uvs[0], uvs.size() * sizeof(float) * 2, GL_STATIC_DRAW);
      
      m_indexCount = vertices.size();
    }
    
    for (size_t i = 0; i < vertices.size(); ++i)
    {
      glm::vec3 vec = vertices[i];
      printf("vertex[%d] = %f, %f, %f\n", i, vec.x, vec.y, vec.z);
    }
    
    m_loaded = true;
    
    return true;
  }
  
  void Mesh::draw(Shader const& shader) const
  {
    assert(m_loaded);
    
    shader.attribute(VERTEX, "vertex");
    shader.attribute(NORMAL, "normal");
    shader.attribute(UV, "uv");
    
    glEnableVertexAttribArray(VERTEX);
    m_vertex.bind();
    glVertexAttribPointer(VERTEX, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
    
    glEnableVertexAttribArray(NORMAL);
    m_normal.bind();
    glVertexAttribPointer(NORMAL, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
    
    glEnableVertexAttribArray(UV);  
    m_uv.bind();
    glVertexAttribPointer(UV, 2, GL_FLOAT, GL_FALSE, 0, (void *)0);
  
    if (m_useIndicies)
      m_indicies.bind();
    
    if (m_hasTangents)
    {
      shader.attribute(TANGENT, "tangent");
      shader.attribute(BINORMAL, "binormal");
      
      glEnableVertexAttribArray(TANGENT);
      m_tangent.bind();
      glVertexAttribPointer(TANGENT, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
      
      glEnableVertexAttribArray(BINORMAL);
      m_binormal.bind();
      glVertexAttribPointer(BINORMAL, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
    }
    
    if (m_useIndicies)
      glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_SHORT, (void *)0);
    else
      glDrawArrays(GL_TRIANGLES, 0, m_indexCount);
    
    glDisableVertexAttribArray(VERTEX);
    glDisableVertexAttribArray(NORMAL);
    glDisableVertexAttribArray(UV);
    glDisableVertexAttribArray(TANGENT);
    glDisableVertexAttribArray(BINORMAL);
  }
  
}