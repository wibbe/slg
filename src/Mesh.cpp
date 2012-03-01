
#include "slg/Mesh.hpp"
#include "slg/MeshHelpers.hpp"

namespace slg {
  
  Mesh::Mesh()
    : m_indexCount(0),
      m_loaded(false)
  {
    for (int i = 0; i < BUFFER_COUNT; ++i)
      m_buffers[i] = 0;
  }
  
  Mesh::~Mesh()
  {
    destroy();
  }
  
  void Mesh::destroy()
  {
    m_loaded = false;
    m_indexCount = 0;
    
    for (int i = 0; i < BUFFER_COUNT; ++i)
    {
      delete m_buffers[i];
      m_buffers[i] = 0;
    }
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
      
    m_buffers[VERTEX] = new Buffer(GL_ARRAY_BUFFER);
    m_buffers[NORMAL] = new Buffer(GL_ARRAY_BUFFER);
    m_buffers[UV] = new Buffer(GL_ARRAY_BUFFER);
    
    if (useIndicies)
      m_buffers[INDICIES] = new Buffer(GL_ELEMENT_ARRAY_BUFFER);
      
    if (computeTangents)
    {
      computeTangentBasis(vertices, uvs, normals, tangents, binormals);
      
      m_buffers[TANGENT] = new Buffer(GL_ARRAY_BUFFER);
      m_buffers[BINORMAL] = new Buffer(GL_ARRAY_BUFFER);
      
      if (useIndicies)
      {
        calculateIndex(vertices, uvs, normals, tangents, binormals,
                       finalIndicies, finalVertices, finalUvs, finalNormals, finalTangents, finalBinormals);
                     
        m_buffers[TANGENT]->upload(&tangents[0], tangents.size() * sizeof(float) * 3, GL_STATIC_DRAW);
        m_buffers[BINORMAL]->upload(&binormals[0], binormals.size() * sizeof(float) * 3, GL_STATIC_DRAW);
      }
      else
      {
        m_buffers[TANGENT]->upload(&finalTangents[0], finalTangents.size() * sizeof(float) * 3, GL_STATIC_DRAW);
        m_buffers[BINORMAL]->upload(&finalBinormals[0], finalBinormals.size() * sizeof(float) * 3, GL_STATIC_DRAW);        
      }
    }
    
    if (useIndicies)
    {
      if (!computeTangents)
        calculateIndex(vertices, uvs, normals, 
                       finalIndicies, finalVertices, finalUvs, finalNormals);
    
      m_buffers[VERTEX]->upload(&finalVertices[0], finalVertices.size() * sizeof(float) * 3, GL_STATIC_DRAW);
      m_buffers[NORMAL]->upload(&finalNormals[0], finalNormals.size() * sizeof(float) * 3, GL_STATIC_DRAW);
      m_buffers[UV]->upload(&finalUvs[0], finalUvs.size() * sizeof(float) * 2, GL_STATIC_DRAW);
      m_buffers[INDICIES]->upload(&finalIndicies[0], finalIndicies.size() * sizeof(unsigned short), GL_STATIC_DRAW);
      
      m_indexCount = finalIndicies.size();
    }
    else
    {
      m_buffers[VERTEX]->upload(&vertices[0], vertices.size() * sizeof(glm::vec3), GL_STATIC_DRAW);
      m_buffers[NORMAL]->upload(&normals[0], normals.size() * sizeof(glm::vec3), GL_STATIC_DRAW);
      m_buffers[UV]->upload(&uvs[0], uvs.size() * sizeof(glm::vec2), GL_STATIC_DRAW);
      
      m_indexCount = vertices.size();
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
    m_buffers[VERTEX]->bind();
    glVertexAttribPointer(VERTEX, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
    
    glEnableVertexAttribArray(NORMAL);
    m_buffers[NORMAL]->bind();
    glVertexAttribPointer(NORMAL, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
    
    glEnableVertexAttribArray(UV);  
    m_buffers[UV]->bind();
    glVertexAttribPointer(UV, 2, GL_FLOAT, GL_FALSE, 0, (void *)0);
  
    if (m_buffers[INDICIES])
      m_buffers[INDICIES]->bind();
    
    if (m_buffers[TANGENT])
    {
      shader.attribute(TANGENT, "tangent");
      shader.attribute(BINORMAL, "binormal");
      
      glEnableVertexAttribArray(TANGENT);
      m_buffers[TANGENT]->bind();
      glVertexAttribPointer(TANGENT, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
      
      glEnableVertexAttribArray(BINORMAL);
      m_buffers[BINORMAL]->bind();
      glVertexAttribPointer(BINORMAL, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
    }
    
    if (m_buffers[INDICIES])
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